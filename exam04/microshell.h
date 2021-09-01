#ifndef MICROSHELL_H
# define MICROSHELL_H

# define CD_ARG_ERROR 1
# define CD_ERROR 2
# define SYSCALL_ERROR 3
# define EXECVE_ERROR 4

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct		s_list
{
	char			**arg;
	int				flag;
	int				prev_flag;
	struct	s_list	*next;
}					t_list;

t_list	*ft_lstnew(void);
void	ft_lstadd(t_list **head, t_list *new);
void	error(int flag, char *arg);
void	cd(char **args);
char	**add_arg(char **ref, char *new);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);

#endif
