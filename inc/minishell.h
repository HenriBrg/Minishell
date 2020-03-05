/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:07:34 by hberger           #+#    #+#             */
/*   Updated: 2020/03/05 18:11:38 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <signal.h>
# include <dirent.h>
/*
** MVCURSOR_BEGL : Move cursor to beginning of line.
** MVCURSOR_LEFT : Move cursor left by # characters.
** MVCURSOR_POS : Move cursor to specific position. First # is row number,
** second # is column
** CLR_LINE : Clear current line (but don"t move cursor).
** CLR_LINE_LEFT : Clear line to the left of current position.
** CLR_LINE_RIGHT : Clear line to the right of current position.
*/

# define MVCURSOR_BEGL		"\033[1G"
# define MVCURSOR_LEFT		"\033[1D"
# define MVCURSOR_POS		"\033[#;#f"
# define CLR_LINE			"\033[2K"
# define CLR_LINE_LEFT		"\033[1K"
# define CLR_LINE_RIGHT		"\033[0K"

# define PATH_MAX 4096

int							g_exitvalue;
int							g_shellisrunning;
char						**g_environ_strstab;

typedef struct				s_envar
{
	char					*name;
	char					*value;
	struct s_envar			*next;
}							t_envar;

typedef struct				s_strlist
{
	char					*str;
	int						out_type;
	struct s_strlist		*next;
}							t_strlist;

typedef struct				s_command
{
	char					**args;
	t_strlist				*out;
	t_strlist				*in;
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

typedef struct				s_envsubvar
{
	int						len_var_name;
	char					*var_name;
	char					*var_subst;
	char					*a;
	char					*c;
	char					*new_string;
	char					*tmp;
}							t_envsubvar;

/*
** main.c
*/

void						prompt(t_envar *envar);

/*
** utils/
*/

char						*getvar(t_envar *envar, char *name);
t_envar						*lstenv(char **env);
void						lstclear(t_envar *lst);
int							inputcontrol(char *input);
int							strcmpcasei(char *s1, char *s2);
void						handle_error(char *message);
void						siglisten(void);
void						commands_lstclear(t_commands_list *list);

/*
** parse/
*/

t_commands_list				*parse(char *input, t_envar *envar);
void						parse_redirections(t_strlist *command,
	t_command *supertab, int n);
t_command					*parse_commands(t_strlist **pipe_list);
void						parse_args(t_strlist *command, t_command *supertab,
	int n);
t_strlist					*ft_supersplit(char *string, char **separators,
	int inclusion, int trim);
void						addback(t_strlist **list, char *str, int n,
	int trim);
char						*trim_quotes(char *s, t_envar *envar);
void						substitute_variable(char **s, int *i, int *len,
	t_envar *envar);
void						purify(t_commands_list *list, t_envar *envar);

/*
** bultins/
*/

void						pushbackenvar(char *name, char *value,
	t_envar *envar);
void						namevaluefilter(char *cmd, char **name,
	char **value);
void						pushbackenvar(char *name, char *value,
	t_envar *envar);
void						namevaluefilter(char *cmd, char **name,
	char **value);
void						builtinpwd(t_envar *envar);
void						cd(char **cmds, t_envar *envar);
void						builtinecho(char **cmds, t_envar *envar);
void						builtinpwd(t_envar *envar);
void						builtinexit(char **cmds, int piped);
void						builtinsenv(char **cmds, t_envar *envar);
void						builtinpwd(t_envar *envar);
void						builtincd(char **cmds, t_envar *envar);
void						sortenvar(t_envar *envar);
void						exportenvar(char **cmds, t_envar *envar);

/*
** executables/
*/

void						executables(char **cmds, t_envar *envar);

/*
** direction/
*/

int							isbuiltin(char **cmds);
void						executebuiltins(char **cmds, t_envar *envar,
	int piped);
void						pipeline(t_command *tab, t_envar *envar,
	int nbpipes);
void						pipexec(t_command *tab, t_envar *envar, int piped);
int							nopiped_chevrons(t_command *tab, t_envar *envar);
void						executablesnofork(char **cmds, t_envar *envar);
char						*finishpath(char **pathtab, char *tmp2);
char						*checkpath(char **cmds, struct stat *s,
	char *envpath);
int							monoprocess(t_command *tab, t_envar *envar);

#endif
