/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillett <dwillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:20:18 by dwillett          #+#    #+#             */
/*   Updated: 2021/01/24 15:07:04 by dwillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		ft_close(FILE *fd, char **res, int i, int flag)
{
	fclose(fd);
	while (i-- > 0)
		free(res[i]);
	if (res)
		free(res);
	if (flag == 1)
		write(1, "Error: Operation file corrupted\n", 32);
	return (flag);
}

void	ft_fill(char **res, t_mini *data)
{
	float	i;
	float	j;
	float	tmp;
	int		flag;
	
	i = 0;
	flag = 0;
	if (data->c_flag == 'C')
		flag = 1;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			tmp = sqrtf(powf(j - data->x, 2) + powf(i - data->y, 2));
			if (tmp <= data->radius)
			{
				if (tmp > data->radius - 1)
					res[(int)i][(int)j] = data->f_char;
				if (flag == 1)
					res[(int)i][(int)j] = data->f_char;
			}
			j++;
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	FILE	*input;
	t_mini	data;
	char	**res;
	int		tmp;
	
	res = NULL;
	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!(input = fopen(argv[1], "r")))
		return (ft_close(input, res, -1, 1));
	if ((tmp = fscanf(input, "%d %d %c\n", &data.width, &data.height, &data.bg)) != 3)
		return (ft_close(input, res, -1, 1));
	if (data.width <= 0 || data.width > 300 || data.height <= 0 || data.height > 300)
		return (ft_close(input, res, -1, 1));
	if (!(res = malloc(sizeof(char*) * data.height)))
		return (ft_close(input, res, -1, 1));
	tmp = 0;
	while (tmp < data.height)
	{
		if (!(res[tmp] = calloc(data.width + 1, sizeof(char))))
			return (ft_close(input, res, tmp, 1));
		memset(res[tmp], data.bg, data.width);
		tmp++;
	}
	while ((tmp = fscanf(input, "%c %f %f %f %c\n", \
	&data.c_flag, &data.x, &data.y, &data.radius, &data.f_char)) == 5)
	{
		if (data.radius <= 0 || (data.c_flag != 'c' && data.c_flag != 'C'))
			return (ft_close(input, res, data.height, 1));
		ft_fill(res, &data);
	}
	if (tmp != -1)
		return (ft_close(input, res, data.height, 1));
	tmp = 0;
	while (tmp < data.height)
	{
		write(1, res[tmp], data.width);
		write(1, "\n", 1);
		tmp++;
	}
	return (ft_close(input, res, tmp, 0));
}