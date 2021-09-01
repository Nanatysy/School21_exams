#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <stdio.h>

typedef	struct	s_mini
{
	int			width;
	int			height;
	char		bg;
	char		c_flag;
	float		x;
	float		y;
	float		radius;
	char		f_char;
}				t_mini;

void	ft_fill(char **res, t_mini *data);
int		ft_close(FILE *fd, char **res, int i, int flag);

#endif