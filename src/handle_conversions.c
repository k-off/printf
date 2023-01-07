/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:44:52 by pcovalio          #+#    #+#             */
/*   Updated: 2023/01/07 10:31:28 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_return	handle_string_conversion(t_node *tmp);
t_return	handle_doubles_other(t_node *tmp);
t_return	handle_doubles_aa(t_node *tmp);
t_return	handle_integer_conversion(t_node *tmp);

static t_return	handle_pointer_conversion(t_node *tmp)
{
	if (tmp->v.u64 == 0)
	{
		tmp->res.s = ft_strdup("(nil)");
		tmp->res.len = 5;
	}
	else
	{
		tmp->conv = 'x';
		tmp->ln_md = ll;
		tmp->flags[0] = HASH;
		if (handle_integer_conversion(tmp) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

static t_return	handle_character_conversion(t_node *tmp)
{
	char	str[2];
	char	*width;

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

static t_return	handle_percent_conversion(t_node *tmp)
{
	tmp->res.s = ft_strdup("%");
	tmp->res.len = 1;
	if (tmp->res.s == NULL)
		return (FAIL);
	return (SUCCESS);
}

t_return	handle_conversions(int *total_bytes, t_node *chunks_list)
{
	while (total_bytes != NULL && chunks_list != NULL)
	{
		if (chunks_list->conv == 0 && chunks_list->res.s == NULL)
			chunks_list->res.s = ft_memalloc(1);
		else if (ft_strchr("diouxX", chunks_list->conv))
			handle_integer_conversion(chunks_list);
		else if (chunks_list->conv == 's')
			handle_string_conversion(chunks_list);
		else if (chunks_list->conv == 'c')
			handle_character_conversion(chunks_list);
		else if (chunks_list->conv == 'p')
			handle_pointer_conversion(chunks_list);
		else if (ft_strchr("aA", chunks_list->conv))
			handle_doubles_aa(chunks_list);
		else if (ft_strchr("eEfFgG", chunks_list->conv))
			handle_doubles_other(chunks_list);
		else if (chunks_list->conv == '%')
			handle_percent_conversion(chunks_list);
		else
			return (FAIL);
		*total_bytes += chunks_list->res.len;
		chunks_list = chunks_list->next;
	}
	return ((total_bytes == NULL || chunks_list != NULL) * FAIL);
}
