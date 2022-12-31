/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:44:52 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/31 09:07:39 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_return	handle_string_conversion(t_node *tmp);
t_return	handle_doubles_other(t_node *tmp);
t_return	handle_doubles_aa(t_node *tmp);

static t_return	handle_integers(t_node *tmp)
{
	(void)tmp;
	return (SUCCESS);
}

static t_return	handle_chars(t_node *tmp)
{
	char	str[2];
	char	*width;

	if (tmp == NULL)
		return (FAIL);
	str[0] = (int8_t)tmp->v.u32;
	str[1] = '\0';
	width = NULL;
	tmp->res.len = 1;
	if (tmp->width > 1)
	{
		width = ft_stralloc(' ', tmp->width - 1);
		tmp->res.len = tmp->width;
	}
	if (tmp->flags[1] == '-')
		tmp->res.s = string_joiner(2, ft_strdup(str), width);
	else
		tmp->res.s = string_joiner(2, width, ft_strdup(str));
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
			handle_string_conversion(chunks_list);
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
