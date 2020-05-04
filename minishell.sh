make  VERBOSE=1
touch bashoutput
touch minioutput

function outputTest() {
	echo -n > minioutput # Vide forcé par précaution
	echo -n > bashoutput # Vide forcé par précaution
	# ./minishell $1 > minioutput
	bash -c	"$1" > bashoutput # NB : "$" est différent de $ car "$" prendra en compte tout le string et ne s'arrête pas, par exemple, sur les espaces
}

declare -a testOuput=("/bin/ls" "/bin/echo -n Hello" "/bin/echo -n \$PATH")
declare -a testExit=("exit" "exit 1" "exit A" "exit 1 2" "exit A B C" "exit A1 B2" "exit 1A 2B" "exit -1" "exit -A" "exit 100000000000000000" "exit -100000000000000000")

for t in "${testOuput[@]}"
do
	outputTest "$t" # NB BIS : "$t" est différent de $t car "$t" prendra en compte tout le string et ne s'arrête pas sur les espaces
	cat bashoutput
done

# for t in "${testExit[@]}"
# do
#
# done

rm bashoutput minioutput
