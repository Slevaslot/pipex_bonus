/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:32:43 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/25 17:45:31 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	b(char c, va_list args, int d)
{
	void	*p;

	if (c == 'c')
		return (pc(va_arg(args, int)));
	else if (c == 's')
		return (ps(va_arg(args, char *)));
	else if (c == 'p')
	{
		p = va_arg(args, void *);
		if (p != NULL)
			return (ps("0x") + pu((unsigned long int)p, LX, &d));
		else
			return (ps("(nil)"));
	}
	else if (c == 'd' || c == 'i')
		return (pn(va_arg(args, int), &d));
	else if (c == 'u')
		return (pu(va_arg(args, unsigned int), D, &d));
	else if (c == 'x')
		return (pu(va_arg(args, unsigned int), LX, &d));
	else if (c == 'X')
		return (pu(va_arg(args, unsigned int), BX, &d));
	return (pc('%'));
}

int	ft_printf(const char *formats, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	if (!formats)
		return (0);
	va_start(args, formats);
	while (formats[i])
	{
		if (formats[i] == '%')
		{
			count += b(formats[i + 1], args, 0);
			i++;
		}
		else
		{
			pc(formats[i]);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
// #include <stdio.h>

// int	main()
// {
// 	// int a = 4;
// 	// int n = 2;
// 	// void *p = &a;
// 	// void *x = &n;

// 	ft_printf(NULL);
// 	// printf("%d\n", ft_printf("%s", NULL));
// // 	char *str = NULL;
// // 	printf("%d\n", printf("%p", str));
// }
