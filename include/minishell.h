/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:41:49 by jugingas          #+#    #+#             */
/*   Updated: 2023/10/31 11:18:18 by jugingas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define RESET "\033[0m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[1;34m"
# define PURPLE "\e[0;35m"
# define CYAN "\e[1;36m"
# define WHITE "\e[0;37m"

# define MAX_PATH_SIZE 1024

extern int	g_signal;

typedef struct s_pp
{
	int		pid;
	int		*pidtab;
	int		cmd_nb;
	int		pipe_nb;
	int		*pipe;
	int		idx;
	char	**no_redirec;
	char	*cmd_name;
	char	*name;
	char	**tab;
}		t_pp;

typedef struct s_shell
{
	char	**builtins;
	char	*line;
	char	**tokens;
	char	**env;
	char	**tab;
	int		*meta;
	char	ex_path[MAX_PATH_SIZE];
	int		pid;
	int		errno;
	int		badline_errno;
	int		(*f_ptr[7])(struct s_shell *, char *);
}		t_shell;

//---- Main Functions ---

int		badline(char *str, t_shell *shell);
void	init_shell(t_shell *shell, char **env);
char	*get_cwd(void);
char	*init_builtins(char *cmd);
void	patch(t_shell *shell, char *arg);
void	prompt(t_shell *shell);
void	main_core(t_shell *shell);
char	*anti_douillax(char *str);
char	*douillax(char *str);
int		check_endz(char *str, char c);
void	free_it(t_pp *pp, char *str, t_shell *shell);

//-------- Utils --------

char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	print_tab(char **tab);
char	**ft_split(char const *s, char c);
char	**token_it(t_shell *shell, char *str);
char	*ft_strdup(const char *s);
char	*ft_epurstr(char *str);
char	*str_add(char *str, char *add, int fr_str, int fr_add);
char	*ft_strcpy(char *src, char *dest);
char	**epur_tab(char **tab);
int		ft_strncmp(char *s1, char *s2, int n);
void	power_free(char **tab);
int		mnsh_strcmp(char *s1, char *s2);
int		ft_envstrcmp(char *s1, char *s2);
char	*get_args(char *line);
void	print_write_error(t_shell *shell, int i);
int		is_neg(int i);
int		is_alphanum(char c);
char	*get_cmd(char *line, char **env);
char	*get_cmd_name(char *line);
int		ft_strlen(const char *str);
char	**ft_split_quote(t_shell *shell, char *arg);
void	init_signals(void);
int		tab_len(char **tab);
int		count_word(char *arg);
char	**init_sep(void);
char	*get_home_path(char **env);
int		ft_envstrcmp(char *s1, char *s2);
int		ft_find_start(char *str, int x);
int		count_word(char *arg);
int		ft_strcmp(char *s1, char *s2);
int		ft_checkcmd(char *s1, char *s2);
char	*ft_extension_of_the_territory(t_shell *shell, char *str, int exp);
char	*ft_str_eg_cpy(char *env, char *str);
char	*remove_quote(char *str);
char	*cut_str_env(char *env);
int		ft_strenvcmp(char *tmp, char *env);
char	*itoa(int nb);
int		ft_atoi(const char *nptr);
char	*get_next_line(int fd, char *del);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_str_without_exp(char *str, int exp);
char	**get_path_tab(char **env);
char	*get_full_cmd(struct dirent *dir, char *tabi, char **tab);
char	*get_cmd(char *line, char **env);
char	*ft_tab_to_str(char **tab);

//------ Redirects -----

int		check_redirect(char *cmd);
char	**ignore_redirections(char **tab, int fr);
char	*get_heredoc(char *delimiter);
int		simple_right(char *filename);
int		double_right(char *filename);
int		simple_left(char *filename);
int		double_left(char *delimiter);

//-------- Pipes -------

int		ft_pipe(t_shell *shell);
void	end_pipe(t_pp *pp, char **no_redirec, char **tab, char *cmd_name);
int		cmd_count(char **token);
void	create_pipes(t_pp *pp);
void	close_pipes(t_pp *pp);
void	do_the_redirections(t_pp *pp);
void	init_pipe(t_pp *pp, char *cmd, t_shell *shell);
void	dup2_spe(int z, int f);
int		redirect(char **cmdtab, int i);
int		tab_len(char **tab);

//------- Builtins ------

int		call_builtins(t_shell *shell, int idx);
int		ft_echo(t_shell *shell, char *arg);
int		ft_cd(t_shell *shell, char *cmd_line);
int		ft_pwd(t_shell *shell, char *arg);
int		ft_export(t_shell *shell, char *arg);
int		ft_unset(t_shell *shell, char *arg);
int		ft_env(t_shell *shell, char *arg);
int		ft_exit(t_shell *shell, char *arg);

//-------- env ----------

void	init_env(t_shell *shell, char **env);
int		update_pwd(t_shell *shell);
void	create_env(t_shell *shell);
char	*get_home_path(char **env);
void	update_env(char *arg, t_shell *shell, int fr_arg);
void	ft_init_struct(t_shell *sh);
void	ft_simple_export(t_shell *shell);
char	*get_value(char *str);

//------- quotes --------

bool	ft_next_quote(char *arg, int type, int x);
char	*remove_quote_3(char *str, int nb, int type);
char	**ft_split_str(t_shell *shell, char *str, char **tab);
char	**resplit_tab(char **tab);
int		ft_need_expand(char *str);
char	*ft_add_str(t_shell *shell, char *str, int start, int end);
int		calc_size(char **tab, int idx, int size);
char	*copy_line(char **tab, int idx, int size);
int		expand_not_quoted(char *str, int dollar);

#endif
