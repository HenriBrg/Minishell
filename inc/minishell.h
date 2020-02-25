#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <signal.h>

/*
** Signal stuff
**
** Move cursor to beginning of line.
** Move cursor left by # characters.
** Move cursor to specific position. First # is row number, second # is column
** Clear current line (but don"t move cursor).
** Clear line to the left of current position.
** Clear line to the right of current position.
*/

# define MVCURSOR_BEGL	"\033[1G"
# define MVCURSOR_LEFT	"\033[1D"
# define MVCURSOR_POS	"\033[#;#f"
# define CLR_LINE		"\033[2K"
# define CLR_LINE_LEFT	"\033[1K"
# define CLR_LINE_RIGHT	"\033[0K"

# define PATH_MAX 4096

enum PIPES {READ, WRITE};

int						g_exitvalue;
int						g_shellisrunning;

typedef struct			s_envar
{
	char				*name;
	char				*value;
	struct s_envar		*next;
}						t_envar;

typedef struct				s_strlist
{
	char					*str;
	struct s_strlist		*next;
}							t_strlist;

typedef struct				s_command
{
	char					**args;
	char					*out;
	char					*in;
	int						out_type;
}							t_command;

typedef struct				s_commands_list
{
	t_command				*command;
	struct s_commands_list	*next;
}							t_commands_list;

typedef struct				s_envsplit
{
	char					*string;
	char					**separators;
	int						inclusion;
	char					*trim;
	int						index;
	char					quotes[3];
	t_strlist				*list;
}							t_envsplit;

/*
** main.c
*/

void					prompt(t_envar *envar);


/*
** utils/
*/

char					*getvar(t_envar *envar, char *name);
t_envar					*lstenv(char **env);
void					lstclear(t_envar *lst);
int						inputcontrol(char *input);
int						strcmpcasei(char *s1, char *s2);
void					handle_error(char *message);
void					siglisten(void);


/*
** parse/
*/

t_commands_list				*parse(char *input);
void						parse_redirections(t_strlist *command,
											t_command *supertab, int n);
t_command					*parse_commands(t_strlist **pipe_list);
void						parse_args(t_strlist *command, t_command *supertab,
										int n);
t_strlist					*ft_supersplit(char *string, char **separators,
											int inclusion);
void						addback(t_strlist **list, char *str, int n);

/*
** bultins/
*/

void						pushbackenvar(char *name, char *value,
											t_envar *envar);
void						namevaluefilter(char *cmd, char **name,
											char **value);
void					pushbackenvar(char *name, char *value, t_envar *envar);
void					namevaluefilter(char *cmd, char **name, char **value);
void					builtinpwd(t_envar *envar);
void					cd(char **cmds, t_envar *envar);
void					builtinecho(char **cmds, t_envar *envar);
void					builtinpwd(t_envar *envar);
void					builtinexit(char **cmds);
void					builtinsenv(char **cmds, t_envar *envar);
void					builtinpwd(t_envar *envar);
void					builtincd(char **cmds, t_envar *envar);
void					sortenvar(t_envar *envar);
void					exportenvar(char **cmds, t_envar *envar);

/*
** executables/
*/

void					executables(char **cmds, t_envar *envar);

/*
** direction/
*/

int						isbuiltin(char **cmds);
void					executebuiltins(char **cmds, t_envar *envar);
void		pipeline(t_command *tab, t_envar *envar);

#endif
