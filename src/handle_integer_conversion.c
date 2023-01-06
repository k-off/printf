/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_integer_conversion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:50:56 by pcovalio          #+#    #+#             */
/*   Updated: 2023/01/06 12:18:36 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	numeric_base(uint8_t conversion)
{
	if (conversion == 0)
		return (FAIL);
	else if (ft_strchr("diufFgGeE", conversion) != NULL)
		return (10);
	else if (ft_strchr("paAxX", conversion) != NULL)
		return (16);
	else if (conversion == 'o')
		return (8);
	return (FAIL);
}

static t_return	get_signed(t_node *tmp, int bs, t_bool up, int8_t sep)
{
	if (tmp->is_prcsn_def == true && tmp->prcsn == 0 && tmp->v.u64 == 0)
		tmp->res.s = ft_strdup("");
	else if (tmp->ln_md == hh)
		tmp->res.s = lltoa_base((int8_t)tmp->v.u32, bs, up, sep);
	else if (tmp->ln_md == h)
		tmp->res.s = lltoa_base((int16_t)tmp->v.u32, bs, up, sep);
	else if (tmp->ln_md == l || tmp->ln_md == ll)
		tmp->res.s = lltoa_base((int64_t)tmp->v.u64, bs, up, sep);
	else
		tmp->res.s = lltoa_base((int32_t)tmp->v.u32, bs, up, sep);
	if (tmp->res.s == NULL)
		return (FAIL);
	return (SUCCESS);
}

static t_return	get_unsigned(t_node *tmp, int bs, t_bool up, int8_t sep)
{
	if (tmp->is_prcsn_def == true && tmp->prcsn == 0 && tmp->v.u64 == 0)
		tmp->res.s = ft_strdup("");
	else if (tmp->ln_md == hh)
		tmp->res.s = ulltoa_base((uint8_t)tmp->v.u32, bs, up, sep);
	else if (tmp->ln_md == h)
		tmp->res.s = ulltoa_base((uint16_t)tmp->v.u32, bs, up, sep);
	else if (tmp->ln_md == l || tmp->ln_md == ll)
		tmp->res.s = ulltoa_base((uint64_t)tmp->v.u64, bs, up, sep);
	else
		tmp->res.s = ulltoa_base((uint32_t)tmp->v.u32, bs, up, sep);
	if (tmp->res.s == NULL)
		return (FAIL);
	return (SUCCESS);
}

static t_return	handle_integer_width(t_node *tmp)
{
	char	*padding;

	padding = NULL;
	if (tmp->width > tmp->res.len)
	{
		if (tmp->flags[1] != ZERO)
			padding = ft_stralloc(' ', tmp->width - tmp->res.len);
		else
			padding = ft_stralloc('0', tmp->width - tmp->res.len);
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

static t_return	get_integer_string(t_node *tmp, int bs, t_bool up, int8_t sep)
{
	if (tmp->conv == 0 || ft_strchr("diouxXp", tmp->conv) == NULL)
		return (FAIL);
	if ((tmp->conv == 'd' || tmp->conv == 'i') && \
										get_signed(tmp, bs, up, sep) == FAIL)
		return (FAIL);
	if ((tmp->conv != 'd' && tmp->conv != 'i') && \
										get_unsigned(tmp, bs, up, sep) == FAIL)
		return (FAIL);
	tmp->res.len = ft_strlen(tmp->res.s);
	if (tmp->is_prcsn_def == true && tmp->prcsn > tmp->res.len)
	{
		tmp->res.s = string_joiner(2, \
			ft_stralloc('0', tmp->prcsn - tmp->res.len), tmp->res.s);
		tmp->res.len = tmp->prcsn;
	}
	if (handle_integer_width(tmp) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

t_return	handle_integer_conversion(t_node *tmp)
{
	if (get_integer_string(tmp, numeric_base(tmp->conv), tmp->conv == 'X', \
					(numeric_base(tmp->conv) == 10) * tmp->flags[3]) == FAIL)
		return (FAIL);
	if (tmp->flags[0] == HASH && tmp->conv == 'x')
		tmp->res.s = string_joiner(2, ft_strdup("0x"), tmp->res.s);
	if (tmp->flags[0] == HASH && tmp->conv == 'X')
		tmp->res.s = string_joiner(2, ft_strdup("0X"), tmp->res.s);
	if (tmp->flags[0] == HASH && tmp->conv == 'o' && tmp->res.s[0] != '0')
		tmp->res.s = string_joiner(2, ft_strdup("0"), tmp->res.s);
	if (tmp->flags[2] == SPACE && ft_strchr("di", tmp->conv) != NULL && \
			ft_isdigit(tmp->res.s[0]))
		tmp->res.s = string_joiner(2, ft_strdup(" "), tmp->res.s);
	if (tmp->flags[2] == PLUS && ft_strchr("di", tmp->conv) != NULL && \
			ft_isdigit(tmp->res.s[0]))
		tmp->res.s = string_joiner(2, ft_strdup("+"), tmp->res.s);
	if (tmp->res.s == NULL)
		return (FAIL);
	tmp->res.len = ft_strlen(tmp->res.s);
	return (SUCCESS);
}
