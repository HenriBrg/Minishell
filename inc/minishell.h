#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdio.h>

# define PATH_MAX 4096

int						g_exitvalue;

typedef struct			s_envar
{
	char				*name;
	char				*value;
	struct s_envar		*next;
}						t_envar;

typedef struct			s_strlist
{
	char				*str;
	struct s_strlist	*next;
}						t_strlist;

typedef struct			s_command
{
	char				**args;
	int					out_type;
	char				*out;
	char				*in;
}						t_command;

typedef struct			s_envsplit
{
	char				*string;
	char				**separators;
	int					inclusion;
	char				*trim;
	int					index;
	char				quotes[3];
	t_strlist			*list;
}						t_envsplit;

/*
** utils/
*/

char					*getvar(t_envar *envar, char *name);
t_envar					*lstenv(char **env);
void					lstclear(t_envar *lst);
int						inputcontrol(char *input);
int						strcmpcasei(char *s1, char *s2);
void					handle_error(char *message);

/*
** parse/
*/

int						parse(char *input);
t_strlist				*ft_supersplit(char *string, char **separators,
										int inclusion, char *trim);

/*
** bultins/
*/

void		pushbackenvar(char *name, char *value, t_envar *envar);
void		namevaluefilter(char *cmd, char **name, char **value);
void		builtinpwd(t_envar *envar);
void		cd(char **cmds, t_envar *envar);
void		builtinecho(char **cmds, t_envar *envar);
void		builtinpwd(t_envar *envar);
void		builtinexit(char **cmds);
void		builtinsenv(char **cmds, t_envar *envar);
void		builtinpwd(t_envar *envar);
void		builtincd(char **cmds, t_envar *envar);
void		sortenvar(t_envar *envar);
void		exportenvar(char **cmds, t_envar *envar);

#endif
