/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:01:52 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/31 09:14:06 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static t_return	parse_flags(t_node *tmp, const char **fmt)
{
	if (fmt[0] == NULL || fmt[0][0] == '\0')
		return (FAIL);
	while (fmt[0][0] != '\0' && ft_strchr("#0- +\'", fmt[0][0]) != NULL)
	{
		if (fmt[0][0] == HASH)
			tmp->flags[0] = HASH;
		if (fmt[0][0] == ZERO && tmp->flags[1] != MINUS)
			tmp->flags[1] = ZERO;
		if (fmt[0][0] == MINUS)
			tmp->flags[1] = MINUS;
		if (fmt[0][0] == SPACE && tmp->flags[2] != PLUS)
			tmp->flags[1] = SPACE;
		if (fmt[0][0] == PLUS)
			tmp->flags[2] = PLUS;
		if (fmt[0][0] == SEP)
			tmp->flags[2] = SEP;
		++fmt[0];
	}
	return (SUCCESS);
}

static t_return	parse_width(t_node *tmp, const char **fmt)
{
	int	width;

	if (fmt[0] == NULL || fmt[0][0] == '\0')
		return (FAIL);
	width = ft_atoi(fmt[0]);
	if (width < 0)
		return (FAIL);
	tmp->width = (uint32_t)width;
	while (ft_isdigit(fmt[0][0]))
		++fmt[0];
	return (SUCCESS);
}

static t_return	parse_precision(t_node *tmp, const char **fmt)
{
	int	precision;

	if (fmt[0] == NULL || fmt[0][0] == '\0' || fmt[0][1] == '\0')
		return (FAIL);
	if (fmt[0][0] == '.')
		++fmt[0];
	else
		return (SUCCESS);
	precision = ft_atoi(fmt[0]);
	if (precision < 0)
		return (FAIL);
	tmp->prcsn = (uint32_t)precision;
	tmp->is_prcsn_def = true;
	while (ft_isdigit(fmt[0][0]))
		++fmt[0];
	return (SUCCESS);
}

static t_return	parse_modifier(t_node *tmp, const char **fmt)
{
	if (fmt[0] == NULL || fmt[0][0] == '\0')
		return (FAIL);
	if (fmt[0][0] == 'L')
		tmp->ln_md = L;
	if (fmt[0][0] == 'l')
		tmp->ln_md = l;
	if (fmt[0][0] == 'h')
		tmp->ln_md = h;
	if (ft_strchr("lhL", fmt[0][0]) != NULL)
		++fmt[0];
	if (fmt[0][0] == 'l' && tmp->ln_md == l)
		tmp->ln_md = ll;
	else if (fmt[0][0] == 'l' && tmp->ln_md != l)
		return (FAIL);
	if (fmt[0][0] == 'h' && tmp->ln_md == h)
		tmp->ln_md = hh;
	else if (fmt[0][0] == 'h' && tmp->ln_md != h)
		return (FAIL);
	if (fmt[0][0] == 'l' || fmt[0][0] == 'h')
		++fmt[0];
	return (SUCCESS);
}

t_return	parse_conversion(t_node *tmp, const char **fmt)
{
	if (tmp == NULL || fmt == NULL || fmt[0] == NULL)
		return (FAIL);
	++fmt[0];
	if (parse_flags(tmp, fmt) == FAIL || parse_width(tmp, fmt) == FAIL || \
		parse_precision(tmp, fmt) == FAIL || parse_modifier(tmp, fmt) == FAIL)
		return (FAIL);
	if (fmt[0] == NULL || fmt[0][0] == '\0')
		return (FAIL);
	if (ft_strchr("cspdiouxXfFaAeEgG%", fmt[0][0]))
	{
		if (ft_strchr("diouxX", tmp->conv) && tmp->is_prcsn_def == false)
			tmp->prcsn = 1;
		else if (ft_strchr("fFeEgG", tmp->conv) && tmp->is_prcsn_def == false)
			tmp->prcsn = 6;
		else if (ft_strchr("aA", tmp->conv) && tmp->is_prcsn_def == false)
			tmp->prcsn = 4;
		tmp->conv = fmt[0][0];
		++fmt[0];
	}
	else
		return (FAIL);
	return (SUCCESS);
}
