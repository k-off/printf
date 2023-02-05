/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string_conversion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 08:29:17 by pcovalio          #+#    #+#             */
/*   Updated: 2023/02/05 10:03:03 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/**
 * @brief Handle string conversion precision
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
static t_return	handle_string_precision(t_node *tmp)
{
	if (tmp->v.ptr == NULL)
	{
		if (tmp->is_prcsn_def == true && tmp->prcsn < 6)
			tmp->res.s = ft_strdup("");
		else
			tmp->res.s = ft_strdup("(null)");
		tmp->res.len = ft_strlen(tmp->res.s);
	}
	else
	{
		if (tmp->is_prcsn_def == true)
			tmp->res.s = ft_substr((char *)tmp->v.ptr, 0, tmp->prcsn);
		else
			tmp->res.s = ft_strdup((char *)tmp->v.ptr);
		tmp->res.len = ft_strlen(tmp->res.s);
	}
	return (SUCCESS);
}

/**
 * @brief Handle string conversion width
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
static t_return	handle_string_width(t_node *tmp)
{
	char	*padding;

	padding = NULL;
	if (tmp->width > tmp->res.len)
	{
		padding = ft_stralloc(' ', tmp->width - tmp->res.len);
		if (padding == NULL)
			return (FAIL);
		tmp->res.len = tmp->width;
	}
	if (tmp->flags[1] == MINUS)
		tmp->res.s = string_joiner(2, tmp->res.s, padding);
	else
		tmp->res.s = string_joiner(2, padding, tmp->res.s);
	if (tmp->res.s == NULL)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Convert string node value into a string
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
t_return	handle_string_conversion(t_node *tmp)
{
	if (tmp == NULL)
		return (FAIL);
	if (handle_string_precision(tmp) == FAIL)
		return (FAIL);
	if (handle_string_width(tmp) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
