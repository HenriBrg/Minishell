# Détails à connaitre pour coder en SHELL

# -  Les guillemets importe : "$" est différent de $ car "$" prendra en compte
#    tout le string et ne s'arrête pas, par exemple, sur les espaces


RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # NO COLOR

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
)
function outputTest() {

	.././minishell "$1" > minioutput 2>&1
	bash -c	"$1" > bashoutput 2>&1

	cmp -s minioutput bashoutput
	if [ $? != 0 ]; then
		echo "OUTPUT TEST : $1" " : ${RED}KO${NC}"
		# diff minioutput bashoutput > diffoutput
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
	"exit -1A" # Celui là KO
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
		# echo "DIFFERENCE : mini=$exitMini et bash=$exitBash"
	fi
}
echo


# CD ><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><><><><><><

# Impossible de tester en récupérant PWD car on exit aussitôt
# Donc on teste via un ls pour check si on est au bon endroit
# "cd - ; ls" # Impossible à tester ... étrange
declare -a testCD=(
"cd ; ls"
"cd . ; ls")
function cdTest() {

	.././minishell "$1" > minioutput 2>&1
	bash -c	"$1" > bashoutput 2>&1
	cmp -s minioutput bashoutput

	if [ $? != 0 ]; then
		echo "CD TEST : $1" " : ${RED}KO${NC}"
	else
		echo "CD TEST : $1" " : ${GREEN}OK${NC}"
	fi
}

# PARSING EXIT VALUE ><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
# TRICKY TESTS ><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><

# HERE ARE THE TESTING LOOPS ><><><><><><><><><><><><><><><><><><><><><><><><><>

for t in "${testOuput[@]}"; do
	outputTest "$t"
done

for t in "${testBuitinExit[@]}"; do
	exitTest "$t"
done

for t in "${testCD[@]}"; do
	cdTest "$t"
done
