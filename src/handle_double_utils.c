/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:58:51 by pcovalio          #+#    #+#             */
/*   Updated: 2023/02/05 09:34:56 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/**
 * @brief Get exponent of current number under provided base
 * 
 * @param tmp *t_node, current conversion node
 * @param exp *int, addres to store exponent value
 * @param n *long double, address of the number that is normalized
 * @param base int
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
t_return	get_exponent(t_node *tmp, int *exp, long double *n, int base)
{
	exp[0] = 0;
	if (tmp->ln_md == ll || tmp->ln_md == L)
		n[0] = (long double)tmp->v.f128;
	else
		n[0] = (long double)tmp->v.f64;
	while (n[0] >= base || n[0] <= -base)
	{
		n[0] /= base;
		++exp[0];
	}
	while (n[0] < 1 && n[0] > -1)
	{
		n[0] *= base;
		--exp[0];
	}
	return (SUCCESS);
}

/**
 * @brief Ugly untested hack: move 0x prefix into padding part of conversion
 * 			if it is set to zeroes and is to the left from the number
 * 			(checks done by caller)
 * @param tmp *t_node, current conversion node
 * @param pad *char, padding string
*/
static void	handle_xprefix(t_node *tmp, char *pad)
{
	char		*pos;
	uint64_t	index;

	if (tmp == NULL || pad == NULL)
		return ;
	pos = ft_strchr(tmp->res.s, 'x');
	if (pos == NULL)
		pos = ft_strchr(tmp->res.s, 'X');
	if (pos == NULL)
		return ;
	index = pos - tmp->res.s;
	if (index < ft_strlen(pad))
		pad[index] = *pos;
	else
		tmp->res.s[index - ft_strlen(pad)] = *pos;
	*pos = '0';
}

/**
 * @brief Handle width of field for floating point number conversions
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
t_return	handle_double_width(t_node *tmp)
{
	char	*pad;

	pad = NULL;
	if (tmp->width > tmp->res.len && tmp->flags[1] != ZERO)
		pad = ft_stralloc(' ', tmp->width - tmp->res.len);
	else if (tmp->width > tmp->res.len && tmp->flags[1] == ZERO)
		pad = ft_stralloc('0', tmp->width - tmp->res.len);
	if (tmp->width > tmp->res.len && pad == NULL)
		return (FAIL);
	if (pad != NULL && pad[0] == '0' && ft_strchr("-+", tmp->res.s[0]) != NULL)
	{
		pad[0] = tmp->res.s[0];
		tmp->res.s[0] = '0';
	}
	if (pad != NULL && tmp->flags[1] == ZERO)
		handle_xprefix(tmp, pad);
	if (pad != NULL && tmp->flags[1] == MINUS)
		tmp->res.s = string_joiner(2, tmp->res.s, pad);
	else if (pad != NULL)
		tmp->res.s = string_joiner(2, pad, tmp->res.s);
	tmp->res.len = ft_strlen(tmp->res.s);
	return (SUCCESS);
}
