#include "microshell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		flag;
	int		prev;
	int		mypipe[2];
	int		fd[2];
	int		status;
	pid_t	pid;
	t_list	*commands;
	t_list	*tmp;

	if (argc == 1)
		return (0);

	// parse
	i = 1;
	commands = NULL;
	tmp = NULL;
	flag = 1;
	prev = 0;
	while (argv[i])
	{
		if (flag)
		{
			tmp = ft_lstnew();
			ft_lstadd(&commands, tmp);
			tmp->prev_flag = prev;
		}
		if (strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
		{
			flag = 0;
			tmp->arg = add_arg(tmp->arg, argv[i]);
		}
		else
		{
			if (strcmp(argv[i], "|") == 0)
			{
				tmp->flag = 1;
				prev = 1;
			}
			else
				prev = 0;
			flag = 1;
		}
		i++;
	}

	fd[0] = dup(0);
	// execute
	tmp = commands;
	while (tmp)
	{
		if (tmp->prev_flag)
		{
			fd[0] = dup(0);
			dup2(mypipe[0], 0);
			close(mypipe[0]);
		}
		if (tmp->flag)
		{
			pipe(mypipe);
			pid = fork();
			if (pid == 0)
			{
				dup2(mypipe[1], 1);
				close(mypipe[0]);
				close(mypipe[1]);
				flag = execve(tmp->arg[0], tmp->arg, envp);
				if (flag == -1)
					error(EXECVE_ERROR, tmp->arg[0]);
			}
			else if (pid < 0)
				error(SYSCALL_ERROR, NULL);
			else
			{
				close(mypipe[1]);
				waitpid(pid, &status, 0);
			}
		}
		else
		{
			if (tmp->arg)
			{
				pid = fork();
				if (pid == 0)
				{
					if (strcmp(tmp->arg[0], "cd") != 0)
					{
						flag = execve(tmp->arg[0], tmp->arg, envp);
						if (flag == -1)
							error(EXECVE_ERROR, tmp->arg[0]);
					}
					exit(0);
				} else if (pid < 0)
					error(SYSCALL_ERROR, NULL);
				else
				{
					if (strcmp(tmp->arg[0], "cd") == 0)
						cd(tmp->arg);
					waitpid(pid, &status, 0);
					dup2(fd[0], 0);
					close(fd[0]);
				}
			}
		}
		tmp = tmp->next;
	}

	tmp = commands;
	while (tmp)
	{
		i = 0;
		while (tmp->arg[i])
			free(tmp->arg[i++]);
		free(tmp->arg);
		commands = tmp;
		tmp = tmp->next;
		free(commands);
	}

	return (0);
}
