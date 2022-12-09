/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:40:15 by pcovalio          #+#    #+#             */
/*   Updated: 2022/11/29 17:54:43 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
