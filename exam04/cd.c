#include "microshell.h"

void	cd(char **args)
{
	int	i;

	i = 1;
	while(args[i])
		i++;
	if (i != 2)
		error(CD_ARG_ERROR, NULL);
	else
	{
		i = chdir(args[1]);
		if (i != 0)
			error(CD_ERROR, args[1]);
	}
}