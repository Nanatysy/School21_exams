/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillett <dwillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:20:55 by dwillett          #+#    #+#             */
/*   Updated: 2020/12/03 11:45:26 by dwillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

// typedef struct	s_info
// {
// 	int			width;
// 	int			pre;
// 	char		type;
// }				t_info;

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int		ft_atoi(const char *s)
{
	int	i;
	int	res;
	int	flag;

	i = 0;
	res = 0;
	flag = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i++] == '-')
			flag = 1;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	if (flag)
		res = res * -1;
	return (res);
}

// t_info	*init(void)
// {
// 	t_info	*new;

// 	if (!(new = malloc(sizeof(t_info))))
// 		return (NULL);
// 	new->width = -1;
// 	new->pre = -1;
// 	new->type = '0';
// 	return (new);
// }

int		ft_pow(int base, int n)
{
	int	res;

	res = 1;
	while (n > 0)
	{
		res *= base;
		n--;
	}
	return (res);
}

int		ft_rank(int base, long long n)
{
	int	res;

	res = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		res++;
		n /= base;
	}
	return (res);
}

void	ft_hex(unsigned int n)
{
	int		rank;
	char	c;
	int		tmp;
	
	rank = ft_rank(16, n) - 1;
	while (rank >= 0)
	{
		tmp = n / ft_pow(16, rank);
		if (tmp > 9)
			c = tmp - 10 + 'a';
		else
			c = tmp + '0';
		write(1, &c, 1);
		n = n % ft_pow(16, rank);
		rank--;
	}
}

void	ft_putlnbr(long int n)
{
	int		rank;
	int		tmp;
	char	c;

	rank = ft_rank(10, n) - 1;
	while (rank >= 0)
	{
		tmp = n / ft_pow(10, rank);
		c = tmp + '0';
		write(1, &c, 1);
		n = n % ft_pow(10, rank);
		rank--;
	}
}

int		ft_print_s(va_list *tmp, int width, int pre)
{
	int		res;
	int		count;
	int		count_p;
	char	*s;

	s = va_arg(*tmp, char*);
	if (!s)
		s = "(null)";
	count = ft_strlen(s);
	count_p = (count > pre) ? pre : count;
	res = (count_p > width) ? count_p : width;
	while (width-- > count_p)
		write(1, " ", 1);
	write(1, s, count_p);
	return (res);
}

int		ft_print_d(va_list *tmp, int width, int pre)
{
	int	res;
	int	n;
	int	count_p;
	int	flag;
	
	n = va_arg(*tmp, int);
	count_p = (ft_rank(10, n) > pre) ? ft_rank(10, n) : pre;
	flag = (n < 0) ? 1 : 0;
	res = (count_p > width) ? count_p : width;
	while (width-- > (count_p + flag))
		write(1, " ", 1);
	if (flag)
		write(1, "-", 1);
	while (pre-- > (ft_rank(10, n) + flag))
		write(1, "0", 1);
	if (flag)
		ft_putlnbr(-n);
	else
		ft_putlnbr(n);
	return (res);
}

int		ft_print_x(va_list *tmp, int width, int pre)
{
	int				res;
	int				count_p;
	unsigned int	n;

	n = va_arg(*tmp, unsigned int);
	count_p = (ft_rank(16, n) > pre) ? ft_rank(16, n) : pre;
	res = (count_p > width) ? count_p : width;
	while (width-- > count_p)
		write(1, " ", 1);
	while (pre-- > ft_rank(16, n))
		write(1, "0", 1);
	ft_hex(n);
	return (res);
}

int		ft_printf(const char *str, ...)
{
	int		res;
	va_list	tmp;
	// t_info	*cur;
	int		i;
	int		pre;
	int 	width;

	i = 0;
	res = 0;
	va_start(tmp, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			pre = -1;
			width = -1;
			if ((str[i] >= '0' && str[i] <= '9') || str[i] == '*')
			{
				if (str[i] == '*')
					width = va_arg(tmp, int);
				else
					width = ft_atoi(str + i);
				while ((str[i] >= '0' && str[i] <= '9') || str[i] == '*')
					i++;
			}
			if (str[i] == '.')
			{
				i++;
				if ((str[i] >= '0' && str[i] <= '9') || str[i] == '*')
				{
				if (str[i] == '*')
					pre = va_arg(tmp, int);
				else
					pre = ft_atoi(str + i);
				while ((str[i] >= '0' && str[i] <= '9') || str[i] == '*')
					i++;
				}
			}
			if (str[i] == 'd')
				res += ft_print_d(&tmp, width, pre);
			else if (str[i] == 's')
				res += ft_print_s(&tmp, width, pre);
			else if (str[i] == 'x')
				res += ft_print_x(&tmp, width, pre);
			i++;
		}
		else
		{
			write(1, &str[i++], 1);
			res++;
		}
	}
	va_end(tmp);
	return (res);
}