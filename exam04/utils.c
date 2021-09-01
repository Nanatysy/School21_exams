#include "microshell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		error(SYSCALL_ERROR, NULL);
	i = 0;
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_list	*ft_lstnew(void)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		error(SYSCALL_ERROR, NULL);
	new->flag = 0;
	new->prev_flag = 0;
	new->arg = malloc(sizeof(char *));
	if (!new->arg)
		error(SYSCALL_ERROR, NULL);
	new->arg[0] = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstadd(t_list **head, t_list *new)
{
	t_list	*tmp;

	if (!head)
		return ;
	tmp = *head;
	if (!tmp)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	**add_arg(char **ref, char *new)
{
	int		i;
	char	**res;

	i = 0;
	while (ref[i])
		i++;
	if (!(res = malloc(sizeof(char *) * (i + 2))))
		error(SYSCALL_ERROR, NULL);
	i = 0;
	while (ref[i])
	{
		res[i] = ft_strdup(ref[i]);
		free(ref[i]);
		i++;
	}
	res[i++] = ft_strdup(new);
	res[i] = NULL;
	free(ref);
	return (res);
}