/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pftools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:36:01 by pdosso-d          #+#    #+#             */
/*   Updated: 2023/01/25 16:57:41 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strle(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	pn(int n, int *count)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		n *= -1;
		write(1, "-", 1);
		*count += 1;
		pn(n, count);
	}
	else if (n <= 9)
	{
		pc(n + 48);
		*count += 1;
		return (*count);
	}
	else
	{
		pn(n / 10, count);
		pn(n % 10, count);
	}
	return (*count);
}

int	ps(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	pc(char c)
{
	write(1, &c, 1);
	return (1);
}

int	pu(unsigned long int n, char *base, int *count)
{
	if (n > ft_strle(base) - 1)
		pu(n / ft_strle(base), base, count);
	return (*count += pc(base[n % ft_strle(base)]));
}
