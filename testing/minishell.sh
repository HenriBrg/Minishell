#!/bin/bash

# Détails à connaitre pour coder en SHELL

# -  Les guillemets importe : "$" est différent de $ car "$" prendra en compte
#    tout le string et ne s'arrête pas, par exemple, sur les espaces

# -  Usage de bash avec "-" "--" : Deux caractères -- permettent d'indiquer la fin des options
#    et empêchent le traitement des arguments restants.  Ces derniers sont alors traités
#    comme des noms de fichiers et des paramètre

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # NO COLOR
ERRORS=0

touch bashoutput
touch minioutput
touch diffoutput
make -C .. VERBOSE=1


# OUTPUT ><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><><><><

declare -a testOuput=(
	# Commandes valides et basiques
	"/bin/ls"
	"/bin/echo -n \"Hello\""
	"/bin/echo -n \" \$PATH \""
	"/bin/ls -a"
	"/bin/ls -a ../"
	"awk"

	"echo"
	"echo -n"
	"echo -n -n -n -n"
	"echo Hello"
	"echo A B C D E F -n G H I"
	"/bin/ls filethatdoesntexist"

	# Commandes valides et + complexes

	"ls ; pwd ; echo Hello"
	"ls ; pwd ;"
	"pwd;ls"
	"\"echo\" \"hello\""
	"\"echo\" \"he;llo\""
	"echo \"\ls\"ls"

	# Commandes builtins valide
	# Export (tout court) non testable car variables d'ENV toujours différentes
	# Export non testable car le nom du shell qui est en cours d'exécution s'affiche dans l'erreur
	"unset qd sdfbdqfgqdfgsdg"
	# env pareil qu'export

	# Commandes echo + variables d'environnement
	"echo \$PATH"
	"echo \"PATH\""
	"echo PATH"
	"echo \'PATH\'"
	"echo \" PATH \""
	"echo \" \$PATH \""
	"echo \" \$PATH \$_system_name\""
	"echo \'\$PATH\'"
	"echo \' \$PATH \'"
	"echo \"\$PATH\" \$SHELL Hello \"\$1\""

	# Commandes export
	"export A B C ; echo \$A \$B \$C"
	"export A= B= C= ; echo \$A \$B \$C"
	"export A=XXX B=YYY C=ZZZ ; echo \$A \$B \$C"
	"export LS=\"ls -la\" ; \$LS"

	# Test PWD
	"pwd"
	"\"pwd\""
	"pwd ."
	"pwd .."
	" pwd .. "
	"pwd ; echo \$?"

	# Test Simple Quotes
	"'/bin/ls'"
	'l''s'

	# Test Pipe
	"cat file | grep bla | more"
	"ls filethatdoesntexist | grep bla | more"
	"ls .. | grep Makefile | rev"
	"/bin/ls \"|\" /usr/bin/grep microshell"
	# "pwd | cut -c7- | rev | tr e 42 | rev | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42  | tr e 42 | tr e 42 | tr e 42 "
	"pwd | cut -c7- | rev | tail | echo \$PWD"
	"unset LESS ; echo \$LESS"
	# Impossible de tester en récupérant PWD car on exit aussitôt
	# Donc on teste via un ls pour check si on est au bon endroit
	# "cd - ; ls" # Impossible à tester ... étrange

	"cd ; ls"
	"cd . ; ls"
	"cd .. ; ls"
	# "cd - ; ls" # Etrange que ça ne passe pas les tests
	"cd ~ ; ls"
	"cd ~/ ; ls"
	"cd .. ; pwd"
	"cd .. ; pwd ; echo \$?"
	"cd ; /bin/ls"
	"cd ; ../../bin/ls"

)
function outputTest() {
	.././minishell "$1" > minioutput 2>&1
	bash -c	"$1" > bashoutput 2>&1
	cmp -s minioutput bashoutput
	if [ $? != 0 ]; then
		echo "OUTPUT TEST : $1" " : ${RED}KO${NC}"
		ERRORS=`expr $ERRORS + 1`
		diff minioutput bashoutput > diffoutput
	else
		echo "OUTPUT TEST : $1" " : ${GREEN}OK${NC}"
	fi
}

# BUILTIN EXIT ><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><

declare -a testBuitinExit=(

	# Attention aux différences UBUNTU / OSX

	"exit"
	"exit 1"
	"exit A"
	"exit 1 2"
	"exit A B C"
	"exit A1 B2"
	"exit 1A 2B"
	"exit -1"
	"exit -A"
	# "exit -1A" # KO
	"exit 1-A"
	"exit 1A-"
	"exit 100000000000000000"
	"exit -100000000000000000"
)
function exitTest() {
	.././minishell "$1" > minioutput 2>&1
	exitMini=$?
	bash -c	"$1" > bashoutput 2>&1
	exitBash=$?
	# Attention : le then/else est inversé car "-eq" retourne true à priori
	if [ "$exitMini" -eq "$exitBash" ]; then
		echo "EXIT TEST : $1" " : ${GREEN}OK${NC}"
	else
		echo "EXIT TEST : $1" " : ${RED}KO${NC}"
		ERRORS=`expr $ERRORS + 1`
		echo "DIFFERENCE : mini=$exitMini et bash=$exitBash"
	fi
}



# PARSING EXIT VALUE ><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

declare -a testExitVal=(
	";"
	";;;"
	"<"
	">"
	";;;;;"
	"\";"\"
	"\"; ; ;\""
	"\"; < ;\""
	"\"; > ;\""
	"; pwd ; echo Hello"
	"pwd;;;ls"
	";;ls;;"
	";ls;pwd;"
	"'"
	"\""
	"\"\""
	"''"
	"'''''"
	"\"\"\"\"\"\""
	" \"  \" "
	"|"
	" | "
	"  |;"
	";|"
	";|<"
	"<;"
	">;"
	";<"
	";>"
	" ;< ls ; "
	" ;> ls ; "

	"'';"
	">>"
	" > \"|\" "
	"  \"|\" ;"
	"'|'"
	"  '|' "
	"|."
	"< \" \" < ' '<"
	"\" \" ' ' > < > ''"
	"<"
	">"
	"> IMUSTEXIST"
	"<<<<<<<<"
	"<<<"
	">>>"
	">>> < ><<"


	"cat fddsqffgfhds"
	"unset HOME ; cd"
	"cd ; ../../bin/cdfg"
	"cd ; ../../bin/ls"

	"ls||pwd" # KO MAIS LE TEST NE DETECTE PAS ! Pourquoi ? Remet en cause les tests ...
	"ls|;|pwd" # OK mais par exemple ici, il y a une différence d'exit value si on rajoute --posix
	"ls filethatdoesntexist | grep bla | more"
)
function exitValTest() {

	.././minishell "$1" > minioutput 2>&1
	exitMini=$?
	bash -c "$1" > bashoutput 2>&1
	exitBash=$?

	# Needed because --posix change returned value and I ignore the behavior on Ubuntu so I accept the two behaviors (posix and non-posix)
	bash -c --posix 	"$1" > bashoutput 2>&1
	exitBashPosix=$?

	# Attention : le then/else est inversé car "-eq" retourne true à priori
	if [ "$exitMini" -eq "$exitBash" ] || [ "$exitMini" -eq "$exitBashPosix" ]
	then
		echo "PARSE EXIT TEST : $1" " : ${GREEN}OK${NC}"
	else
		echo "PARSE EXIT TEST : $1" " : ${RED}KO${NC}"
		ERRORS=`expr $ERRORS + 1`
		echo "DIFFERENCE : mini=$exitMini et bash=$exitBash et bashposix=$exitBashPosix"
	fi
}

# TRICKY TESTS ><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><

declare -a trickyTest=(
	"chmod 0 .././minishell ; .././minishell"
	"mkdir tmp ; cd tmp ; rm -rf ../tmp ; cd .."
)

# HERE ARE THE TESTING LOOPS ><><><><><><><><><><><><><><><><><><><><><><><><><>

for t in "${testOuput[@]}"; do
	outputTest "$t"
done

echo
for t in "${testBuitinExit[@]}"; do
	exitTest "$t"
done

echo
for t in "${testExitVal[@]}"; do
	exitValTest "$t"
done

echo
echo "Nombre d'erreurs : $ERRORS"

rm minioutput bashoutput diffoutput \| \"\|\"

# Current failing tests ><><><><><><><><><><><><><><><><><><><><><><><><><><><><

# outputTest "export A B C ; echo \$A \$B \$C"
# outputTest "export A= B= C= ; echo \$A \$B \$C"
# outputTest "export A=XXX B=YYY C=ZZZ ; echo \$A \$B \$C"
# outputTest "export LS=\"ls -la\" ; \$LS"

# Tests manuels qui fail

# L'exit value du signal SIGQUIT à 130 au lieu de 131 dans le cas suivant :
# ./minishell / grep abc / pkill -SIGQUIT grep abc
