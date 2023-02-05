/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:44:52 by pcovalio          #+#    #+#             */
/*   Updated: 2023/02/05 08:54:43 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_return	handle_string_conversion(t_node *tmp);
t_return	handle_double_conversion(t_node *tmp);
t_return	handle_integer_conversion(t_node *tmp);

/**
 * @brief Convert pointer node value into a string
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
static t_return	handle_pointer_conversion(t_node *tmp)
{
	if (tmp->v.u64 == 0)
	{
		if (tmp->is_prcsn_def == false || tmp->prcsn > 4)
			tmp->res.s = ft_strdup("(nil)");
		else
			tmp->res.s = ft_strdup("");
		tmp->res.len = ft_strlen(tmp->res.s);
		if (tmp->width > tmp->res.len && tmp->flags[1] == MINUS)
			tmp->res.s = string_joiner(2, tmp->res.s, \
				ft_stralloc(' ', tmp->width - tmp->res.len));
		if (tmp->width > tmp->res.len && tmp->flags[1] != MINUS)
			tmp->res.s = string_joiner(2, ft_stralloc(' ', \
				tmp->width - tmp->res.len), tmp->res.s);
		tmp->res.len = ft_strlen(tmp->res.s);
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

/**
 * @brief Convert character node value into a string
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
static t_return	handle_character_conversion(t_node *tmp)
{
	tmp->res.len = 1;
	if (tmp->width > 1)
	{
		tmp->res.s = ft_stralloc(' ', tmp->width);
		tmp->res.len = tmp->width;
		if (tmp->flags[1] == MINUS)
			tmp->res.s[0] = (int8_t)tmp->v.u32;
		else
			tmp->res.s[tmp->res.len - 1] = (int8_t)tmp->v.u32;
	}
	else
		tmp->res.s = ft_stralloc((int8_t)tmp->v.u32, tmp->res.len);
	return (SUCCESS);
}

/**
 * @brief Convert percent node value into a string
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
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
		else if (ft_strchr("eEfFgGaA", chunks_list->conv))
			handle_double_conversion(chunks_list);
		else if (chunks_list->conv == '%')
			handle_percent_conversion(chunks_list);
		else
			return (FAIL);
		*total_bytes += chunks_list->res.len;
		chunks_list = chunks_list->next;
	}
	return ((total_bytes == NULL || chunks_list != NULL) * FAIL);
}
