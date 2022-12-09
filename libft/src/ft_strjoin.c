/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:06:27 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/03 14:47:08 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	buf_len;

	ret = 0;
	if (s1 && s2)
	{
		buf_len = ft_strlen(s1) + ft_strlen(s2) + 1;
		ret = malloc(buf_len);
		if (!ret)
			return (ret);
		ret[0] = 0;
		ft_strlcpy(ret, s1, buf_len);
		ft_strlcat(ret, s2, buf_len);
	}
	return (ret);
}
