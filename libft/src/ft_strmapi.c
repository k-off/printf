/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:09:43 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/02 19:34:11 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	int		i;

	ret = 0;
	if (s)
	{
		i = 0;
		ret = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
		if (!ret)
			return (ret);
		while (s[i])
		{
			ret[i] = f(i, s[i]);
			++i;
		}
		ret[i] = 0;
	}
	return (ret);
}
