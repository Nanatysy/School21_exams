#ifndef MICRO_H
# define MICRO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

typedef	struct	s_micro
{
	int			width;
	int			height;
	char		bg;
	float		x;
	float		y;
	float		f_width;
	float		f_height;
	char		f_char;
	char		c_flag;
}				t_micro;

void	ft_fill(t_micro *data, char **res);
int		ft_close(FILE *fd, char **res, int i, int flag);

#endif 
