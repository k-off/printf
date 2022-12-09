/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:12:21 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/03 18:11:17 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	actual;

	ret = 0;
	if (s)
	{
		actual = ft_strlen(s);
		if (start >= actual)
			return (ft_strdup(""));
		actual -= start;
		if (len < actual)
			actual = len;
		ret = malloc(actual + 1);
		if (!ret)
			return (ret);
		ret[0] = 0;
		ft_strlcpy(ret, &s[start], actual + 1);
	}
	return (ret);
}
