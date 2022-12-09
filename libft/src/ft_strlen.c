/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:07:45 by pcovalio          #+#    #+#             */
/*   Updated: 2022/11/29 17:49:06 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	if (s)
	{
		while (s[len])
		{
			++len;
		}
	}
	return (len);
}
