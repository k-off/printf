/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:05:16 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/04 08:20:14 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	buf_len;

	ret = 0;
	if (s)
	{
		buf_len = ft_strlen(s) + 1;
		ret = (char *)malloc((buf_len) * sizeof(char));
		if (!ret)
			return (0);
		ret[0] = 0;
		ft_strlcpy(ret, s, buf_len);
	}
	return (ret);
}
