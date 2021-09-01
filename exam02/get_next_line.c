/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillett <dwillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:08:15 by dwillett          #+#    #+#             */
/*   Updated: 2020/12/02 21:24:45 by dwillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*res;
	
	i = ft_strlen(s);
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;
	
	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(res = malloc(sizeof(char) * i)))
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		res[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		res[j++] = s2[i++];
	res[j] = '\0';
	free(s1);
	return (res);
}

int		get_next_line(char **line)
{
	char		buf[2];
	int			i;
	
	if (!(*line = ft_strdup("\0")))
		return (-1);
	i = read(0, buf, 1);
	if (!i)
		return (0);
	buf[1] = '\0';
	while (buf[0] != '\n' && i != 0)
	{
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
		i = read(0, buf, 1);
		buf[1] = '\0';
	}
	if (!i)
		return (0);
	return (1);
}