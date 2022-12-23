/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:44:52 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/23 14:00:34 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static t_return	handle_integers(t_node *tmp)
{
	(void)tmp;
	return (SUCCESS);
}

static t_return	handle_strings(t_node *tmp)
{
	(void)tmp;
	return (SUCCESS);
}

static t_return	handle_chars(t_node *tmp)
{
	(void)tmp;
	return (SUCCESS);
}

static t_return	handle_pointers(t_node *tmp)
{
	(void)tmp;
	return (SUCCESS);
}

t_return	handle_conversions(int *total_bytes, t_node *chunks_list)
{
	if (total_bytes == NULL || chunks_list == NULL)
		return (FAIL);
	while (chunks_list)
	{
		if (chunks_list->conv == 0 && chunks_list->res.s == NULL)
			chunks_list->res.s = ft_memalloc(1);
		else if (ft_strchr("diouxX", chunks_list->conv))
			handle_integers(chunks_list);
		else if (chunks_list->conv == 's')
			handle_strings(chunks_list);
		else if (chunks_list->conv == 'c')
			handle_chars(chunks_list);
		else if (chunks_list->conv == 'p')
			handle_pointers(chunks_list);
		else if (ft_strchr("aA", chunks_list->conv))
			handle_doubles_aa(chunks_list);
		else if (ft_strchr("eEfFgG", chunks_list->conv))
			handle_doubles_other(chunks_list);
		else
			return (FAIL);
		*total_bytes += chunks_list->res.len;
		chunks_list = chunks_list->next;
	}
	return (SUCCESS);
}
