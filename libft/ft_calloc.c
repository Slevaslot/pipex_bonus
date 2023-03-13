/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:54:39 by slevaslo          #+#    #+#             */
/*   Updated: 2022/11/20 11:50:06 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*ptr;
	size_t	h;

	if (elementCount >= SIZE_MAXOU || elementSize >= SIZE_MAXOU)
		return (NULL);
	h = elementCount * elementSize;
	ptr = malloc(h);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, h);
	return (ptr);
}
// int main()
// {
// 	char*	str;

// 	str = ft_calloc(3,6);
// 	ft_strlcpy(str, "32", 6);
// 	printf("%s", str);
// }
