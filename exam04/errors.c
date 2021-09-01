#include "microshell.h"

void	error(int flag, char *arg)
{
	if (flag == CD_ARG_ERROR)
	{
		write(2, "error: cd: bad arguments\n", ft_strlen("error: cd: bad "
														 "arguments\n"));
		return ;
	}
	else if (flag == CD_ERROR)
	{
		write(2, "error: cd: cannot change directory to ", ft_strlen("error: "
																	 "cd: cannot change directory to "));
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
		return ;
	}
	else if (flag == EXECVE_ERROR)
	{
		write(2, "error: cannot execute ", ft_strlen("error: cannot execute "));
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
	}
	else if (flag == SYSCALL_ERROR)
		write(2, "error: fatal\n", ft_strlen("error: fatal"));
	exit(0);
}