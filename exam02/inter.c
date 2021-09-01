/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillett <dwillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:08:38 by dwillett          #+#    #+#             */
/*   Updated: 2020/11/28 17:24:41 by dwillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	int		k;
	int		check;
	
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	check = 0;
	i = 0;
	j = 0;
	k = 0;
	while (argv[1][i] != '\0')
	{
		while (argv[2][j] != '\0' && check != 1)
		{
			if (argv[1][i] == argv[2][j++])
				check = 1;
		}
		j = 0;
		while (k < i)
		{
			if (argv[1][k++] == argv[1][i])
				check = -1;
		}
		if (check == 1)
			write(1, &argv[1][i], 1);
		check = 0;
		k = 0;
		i++;
	}
	write(1, "\n", 1);
	return (0);
}