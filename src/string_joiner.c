/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_joiner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:38:52 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/31 09:17:21 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	join_and_free(char *ret, char **arr, size_t ret_len, size_t arr_len)
{
	size_t	i;

	i = 0;
	while (i < arr_len)
	{
		if (arr[i] != NULL)
		{
			ft_strlcat(ret, arr[i], ret_len);
			free(arr[i]);
			arr[i] = 0;
		}
		++i;
	}
	if ((ft_strlcat(ret, "", ret_len) == ret_len - 1))
		return (SUCCESS);
	return (FAIL);
}

static void	*ft_alloc_if_n(size_t n)
{
	if (n)
		return (ft_memalloc(sizeof(char *) * n));
	return (NULL);
}

char	*string_joiner(size_t n, ...)
{
	char	*ret;
	char	**arr;
	size_t	i;
	size_t	total_len;
	va_list	v;

	arr = (char **)ft_alloc_if_n(n);
	if (arr == NULL)
		return (NULL);
	i = 0;
	va_start(v, n);
	while (i < n)
		arr[i++] = va_arg(v, char *);
	total_len = 0;
	while (i)
		if (arr[--i])
			total_len += ft_strlen(arr[i]);
	ret = ft_memalloc(total_len + 1);
	if (join_and_free(ret, arr, total_len + 1, n) == FAIL)
	{
		free(ret);
		ret = 0;
	}
	free (arr);
	return (ret);
}
