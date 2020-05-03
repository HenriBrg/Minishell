/* THREAD TESTER
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

void *threadMinishell() {
	system("./minishell");
	return ((void*)0);
}
int main() {
	pthread_t m;
	if (pthread_create(&m, NULL, &threadMinishell, NULL))
		return (1);
	pthread_detach(m);
	sleep(1);
	write(0, "ls\n", 3);
	sleep(1);
	return (0);
}
 */

/* Simple Command
- Execute a simple command with an absolute path like /bin/ls or any
  other command without options

	1) /bin/ls
	2) /bin/echo -n "Hello"
	3) /bin/echo -n " $PATH "
	4) /usr/bin/cd ..
	5) /usr/sbin/lsof .. */

/* Arguments
- Execute a simple command with an absolute path like /bin/ls or any other command with arguments but without quotes and double quotes
- Repeat multiple times with different commands and arguments

	1) /bin/ls -a
	2) /bin/ls -a ../
	3) /usr/sbin/lsof Hello
	4) /usr/bin/nm minishell */

/* echo
- Execute the echo command with or without arguments or options
- Repeat multiple times with different arguments

	1) echo
	2) echo -n
	3) echo -n -n -n -n
	4) echo Hello
	5) echo A B C D E F -n G H I */

/* exit
- Execute exit command with or without arguments
- Repeat multiple times with different arguments
- Don’t forget to relaunch the minishell

	1) exit
	2) exit 1
	3) exit A
	4) exit 1 2
	5) exit A B C
	6) exit A1 B2
	7) exit 1A 2B
	8) exit -1
	9) exit -A
	11) exit 100000000000000000
	11) exit -100000000000000000 */

/*
Return value of a process
- Execute a simple command with absolute path like /bin/ls or any other command with arguments but without quotes and double quotes then execute echo $?
- Check the printed value. You can repeat the same in bash and compare it.
- Repeat multiple times with different commands and arguments, use some failing commands like ‘/bin/ls filethatdoesntexist’

	1) /bin/ls
	2) cat qsdf
	3) exit A
	4) exit 1
	5) exit A
	6) exit 100
	7) exit 1000000
	8) exit -100
	9) exit -100000
	10) exit A B C
	11) exit exit
	12) /bin/ls filethatdoesntexist */

/* Semicolons
- Execute multiple simple commands with absolute path with arguments but separate them with semicolons
- Repeat multiple times with different commands and don’t forget to try with or without whitespaces around the semicolons

	1) ;
	2) ; ; ;
	3) ;;;;;
	4) ls ; pwd ; echo Hello
	5) ls ; pwd ;
	6) ; pwd ; echo Hello
	7) grep a ; pwd puis CTRL C (vérifier que pwd s'execute quand même)
	8) pwd;ls
	9) pwd;;;ls
	10) ;;ls;;
	11) ;ls;pwd; */

/* Signals
- Try ctrl-C in an empty prompt
- Try ctrl-\ in an empty prompt
- Try ctrl-D in an empty prompt
- Try ctrl-C in a prompt after you wrote some stuff
- Try ctrl-D in a prompt after you wrote some stuff
- Try ctrl-\ in a prompt after you wrote some stuff
- Try ctrl-C after running a blocking command like cat or grep without arguments
- Try ctrl-\ after running a blocking command like cat or grep without arguments
- Try ctrl-D after running a blocking command like cat or grep without arguments
- Repeat multiple times with different commands

	Via pkill -SIGINT minishell ou pkill -SIGQUIT minishell

	1) CTRL C : OK
	2) CTRL \ : OK
	3) CTRL D : OK MAIS VALEUR RETOUR MAC PROBLEME (à check sur Ubuntu)
	4) CTRL C avec écriture : OK
	5) CTRL D avec écriture : OK
	6) CTRL \ avec écriture : OK

	7) ... le reste OK mais à recheck sur Ubuntu */

/* Double Quotes
- Execute a simple command with absolute path with arguments but this time double quotes (you should include whitespaces and semicolons in the quotes)
- Think about empty arguments or a weird use of ‘\’
- Do not try multiline strings

	1) '
	2) "
	3) ""
	4) ''
	5) '''''
	6) """"""
	7) ';'
	8) ";"
	9) "echo" "hello"
	10) "echo" "he;llo"
	11) echo "\"" --> Erreur ou c'est pas a gérer ?
	12) echo """"\'
	13) ech;o
	14) ech\o
	14) echo "\ls"ls */

/* env
- Check if env shows you the current environment variables

	1) env
	2) "env"
	3) env


/* export
- Export environment variables, create new ones and replace old ones
- Check them with env
	1) export
	2) export A
	3) export A B C
	4) export A= B= C= --> OK c'est corrigé (ancienne ERREUR (si on run export A B C avant) car non mise à jour dans ENV !)
	5) export A=AAA B=BBB C=CCC
	6) export =
	7) export ;
	8) export _ --> OK c'est corrigé
	9) export 1
	10) export -1 */

/* unset
- Export environment variables, create new ones and replace old ones
- Use unset to remove some of them
- Check the result with env

	Après avoir run tous les export
	1) unset A
	2) unset B C
	3) unset qd sdfbdqfgqdfgsdg
	4) unset =
*/

/* Environment Variables
- Execute echo with some $ variables as arguments
- Check if double quotes around $ variables is working correctly (like in bash)

	1) echo $PATH
	2) echo "PATH"
	3) echo PATH
	4) echo 'PATH'
	5) echo " PATH "
	6) echo " $PATH "
	7) echo " $PATH $_system_name"
	8) echo '$PATH' --> Surprenant
	9) echo ' $PATH '
	10) echo "$PATH" $SHELL Hello "$1"

*/

/* cd
- Use the command cd to move the working directory and check if you are in the right directory with /bin/ls
- Repeat multiple times with working and not working cd
- try ‘.’ ‘..’ as arguments too

	1) cd
	2) cd -
	3) cd .
	4) unset $HOME ; cd --> tricky celle là
	5) cd ...

*/

/* pwd
- Use the command pwd
- Repeat multiple times in multiple directories
- try ‘.’ ‘..’ as arguments too

	1) pwd
	2) pwd pwd
	3) "pwd"
	4) pwd .
	5) pwd ..
	6) cd .. ; pwd ; echo $?
	7) cd sdf ; pwd ; echo $?

*/

/* Relative Path
- Execute commands but this time use a relative path
- Repeat multiple times in multiple directories with complex relative path (lots of ..)

	1) ls
	2) cat
	3) cat Makefile
	4) ../../bin/ls (en bougeant au bon endroit)
	5) ../../bin/cat

*/

/* Environment Path
- Execute commands but this time without any path. (ls, wc, awk etc...)
- Unset the $PATH and check if it is not working anymore
- Set the $PATH to a multiple directory value (directory1:directory2) and check that directories are checked in order from left to right

	0) unset PATH
	1) awk
	2) ls
	3) ../../bin/ls

*/

/* Simple Quotes
- Execute commands with simple quotes as argument
- Try empty arguments
- Try environment variables, whitespaces and semicolons in the simple quotes

	1) '
	1) ''
	1) '''
	1) ' ' ' ' ''

	2) "
	2) ""
	2) """
	2) " " ""

	3) 'ls'
	3) '/bin/ls'
	3) 'l''s'

	4) "ls"
	4) "/bin/ls"
	4) "l""s"

	5) "echo" "$PATH"
	6) ls ; "pwd" ; 'ech''o' "Hello" World
	7) ls ; "pwd" ; 'ech''o' "$LESS" World $PAGER "$USER"

*/

/* Redirection
- Execute commands with redirections < and/or >
- Repeat multiple times with different commands and arguments and sometimes change > with >>
- Check if multiple of the same redirections fail

	1) < --> Erreur car on affiche aucun message, par contre $? est bien différent de 0
	2) >
	3) ls <
	4) < ls
	5) ls > tmp
	6) ls < tmp
	7) echo "Makefile" > tmp
	8) ls < tmp
	9) cat tmp ; echo $PATH > tmp
	10) cat tmp ; echo $PATH >> tmp
	11) <<<
	12) >>>
	13) < " " < ' '<
	14) " " ' ' > < > ''
*/

/* Pipes
- Execute commands with pipes like ‘cat file | grep bla | more’
- Repeat multiple times with different commands and arguments
- Try some failing commands like ‘ls filethatdoesntexist | grep bla | more’
- Try to mix pipes and redirections.

	1) cat file | grep bla | more
	2) ls filethatdoesntexist | grep bla | more
	3) ls | grep Makefile | rev
	4) ls | grep Makefile | rev > output
	5) ls | grep Makefile | tail
	6) echo -al > tmp ; ls < tmp | grep Makefile | rev
	7) export aa=-al ; echo $aa > tmp ; ls < tmp | grep Makefile | rev
	8) ls | grep Makefile | rev > output ; cat output --> ERREUR le cat se fait pas dans bash ???
	9) Pourquoi bash print rien ??? ls < tmp | grep Makefile avec -al dans tmp
*/

/* Go Crazy
- Execute commands that should not work like ‘dsbksdgbksdghsd’ and check if the shell doesn’t crash and prints an error
- Try to execute a really really really long command with a ton of arguments
- Have fun with that beautiful minishell and enjoy it
*/
