/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillett <dwillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:08:06 by dwillett          #+#    #+#             */
/*   Updated: 2021/01/24 14:20:07 by dwillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro.h"

int	ft_close(FILE *fd, char **res, int i, int flag)
{
	fclose(fd);
	while (i-- > 0)
		free(res[i]);
	if (res)
		free(res);
	if (flag == 1)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	return (0);
}

void	ft_fill(t_micro *data, char **res)
{
	float	i;
	float	j;
	float	i_end;
	float	j_end;
	int		flag;
	int		flag_border;

	i = 0;
	j_end = data->x + data->f_width;
	i_end = data->y + data->f_height;
	while ((int)i < data->height)
	{
		j = 0;
		flag = 0;
		flag_border = 0;
		if (i >= data->y && i <= i_end)
			flag = 1;
		if (powf((data->y - i), 2) < 1.0 || powf((i_end - i), 2) < 1.0)
			flag_border = 1;
		while ((int)j < data->width)
		{
			if (j >= data->x && j <= j_end && flag == 1)
			{
				if (data->c_flag == 'R')
					res[(int)i][(int)j] = data->f_char;
				else
				{
					if (powf((data->x - j), 2) < 1.0 || powf((j_end - j), 2) < 1.0 || flag_border == 1)
						res[(int)i][(int)j] = data->f_char;
				}
			}
			j++;
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	FILE	*input;
	t_micro	data;
	char	**res;
	int		i;
	int		tmp;

	res = NULL;
	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!(input = fopen(argv[1], "r")))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	tmp = fscanf(input, "%d %d %c\n", &data.width, &data.height, &data.bg);
	if (tmp != 3)
		return (ft_close(input, res, -1, 1));
	if (data.width < 1 || data.width > 300 || data.height < 1 || data.height > 300)
		return (ft_close(input, res, -1, 1));
	if (!(res = malloc(sizeof(char*) * data.height)))
		return(ft_close(input, res, -1, 1));
	i = 0;
	while (i < data.height)
	{
		if (!(res[i] = calloc((data.width + 1), sizeof(char))))
			return (ft_close(input, res, i, 1));
		memset(res[i], data.bg, data.width);
		i++;
	}
	while ((tmp = fscanf(input, "%c %f %f %f %f %c\n", \
	&data.c_flag, &data.x, &data.y, &data.f_width, &data.f_height, &data.f_char)) == 6)
	{
		if (data.f_width <= 0 || data.f_height <= 0 || (data.c_flag != 'r' && data.c_flag != 'R'))
			return (ft_close(input, res, i, 1));
		ft_fill(&data, res);
	}
	if (tmp != -1)
		return (ft_close(input, res, i, 1));
	i = 0;
	while (i < data.height)
	{
		write(1, res[i], data.width);
		write(1, "\n", 1);
		i++;
	}
	return (ft_close(input, res, i, 0));
}