/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillett <dwillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:26:07 by dwillett          #+#    #+#             */
/*   Updated: 2020/11/28 17:35:47 by dwillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	check;
	
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	j = 0;
	check = 0;
	while (argv[1][i] != '\0')
	{
		while (j < i)
		{
			if (argv[1][j++] == argv[1][i])
				check = 1;
		}
		j = 0;
		if (!check)
			write(1, &argv[1][i], 1);
		i++;
		check = 0;
	}
	i = 0;
	while (argv[2][i] != '\0')
	{
		while (j < i)
		{
			if (argv[2][j++] == argv[2][i])
				check = 1;
		}
		j = 0;
		while (argv[1][j] != '\0')
		{
			if (argv[1][j++] == argv[2][i])
				check = 1;
		}
		j = 0;
		if (!check)
			write(1, &argv[2][i], 1);
		i++;
		check = 0;
	}
	write(1, "\n", 1);
	return (0);
}