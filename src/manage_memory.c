/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:10:05 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/31 09:13:46 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_memalloc(size_t size)
{
	char	*ret;
	size_t	i;

	ret = (char *)malloc(size);
	if (!ret)
	{
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		ret[i++] = 0;
	}
	return ((void *)ret);
}

char	*ft_stralloc(char c, size_t size)
{
	char	*ret;
	size_t	i;

	ret = NULL;
	ret = (char *)malloc(size + 1);
	if (!ret)
	{
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		ret[i++] = c;
	}
	ret[size] = 0;
	return ((void *)ret);
}

t_return	join_results(char **return_string, int total_bytes, \
							t_node *chunks_list)
{
	size_t	ret_i;
	size_t	cur_i;

	if (chunks_list == NULL)
		return (FAIL);
	*return_string = (char *)ft_stralloc('\0', total_bytes);
	if (*return_string == NULL)
		return (FAIL);
	ret_i = 0;
	while (chunks_list)
	{
		if (chunks_list->res.s == NULL)
			return (FAIL);
		cur_i = 0;
		while (cur_i < chunks_list->res.len)
		{
			return_string[0][ret_i] = chunks_list->res.s[cur_i];
			++ret_i;
			++cur_i;
		}
		chunks_list = chunks_list->next;
	}
	return (SUCCESS);
}

t_return	release_conversions(t_node *chunks_list)
{
	t_node	*next;

	if (chunks_list == NULL)
		return (FAIL);
	while (chunks_list != NULL)
	{
		next = chunks_list->next;
		if (chunks_list->res.s != NULL)
		{
			free(chunks_list->res.s);
			ft_memset(chunks_list, 0, sizeof(t_node));
		}
		free(chunks_list);
		chunks_list = next;
	}
	return (SUCCESS);
}
