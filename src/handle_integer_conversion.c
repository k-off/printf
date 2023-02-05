/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_integer_conversion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:50:56 by pcovalio          #+#    #+#             */
/*   Updated: 2023/02/05 09:49:31 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

int			numeric_base(uint8_t conversion);
void		swap_minus(t_node *tmp, char *padding);
t_return	xxo_hash_padding(t_node *tmp, char **pad);

/**
 * @brief Convert signed integers depending on length modifiers hh, h, l, ll
 * 
 * @param tmp *t_node, current conversion node
 * @param bs int, base of number (ie dec, hex)
 * @param up bool, upper case flag for hex
 * @param sep int8_t, character value of thousand separator (zero to skip)
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
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

/**
 * @brief Convert unsigned integers depending on length modifiers hh, h, l, ll
 * 
 * @param tmp *t_node, current conversion node
 * @param bs int, base of number (ie dec, hex)
 * @param up bool, upper case flag for hex
 * @param sep int8_t, character value of thousand separator (zero to skip)
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
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

/**
 * @brief Handle width of field for integer number conversions
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
static t_return	handle_integer_width(t_node *tmp)
{
	char	*padding;

	padding = NULL;
	if (tmp->width > tmp->res.len && numeric_base(tmp->conv) != 10 && \
			tmp->v.u64 != 0 && tmp->flags[0] == HASH)
		tmp->width -= (numeric_base(tmp->conv) / 8);
	if (tmp->width > tmp->res.len)
	{
		if (tmp->flags[1] == ZERO && tmp->is_prcsn_def == false)
			padding = ft_stralloc('0', tmp->width - tmp->res.len);
		else
			padding = ft_stralloc(' ', tmp->width - tmp->res.len);
		if (padding == NULL)
			return (FAIL);
		tmp->res.len = tmp->width;
	}
	if (xxo_hash_padding(tmp, &padding) == SUCCESS && tmp->flags[1] == MINUS)
		tmp->res.s = string_joiner(2, tmp->res.s, padding);
	else
		tmp->res.s = string_joiner(2, padding, tmp->res.s);
	if (tmp->res.s == NULL)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Convert an integer number into a string with params
 * 
 * @param tmp *t_node, current conversion node
 * @param bs int, base of number (ie dec, hex)
 * @param up bool, upper case flag for hex
 * @param sep int8_t, character value of thousand separator (zero to skip)
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
static t_return	get_integer_string(t_node *tmp, int bs, t_bool up, int8_t sep)
{
	char	*precision;

	if (tmp->conv == 0 || ft_strchr("diouxXp", tmp->conv) == NULL)
		return (FAIL);
	if ((tmp->conv == 'd' || tmp->conv == 'i') && \
										get_signed(tmp, bs, up, sep) == FAIL)
		return (FAIL);
	if ((tmp->conv != 'd' && tmp->conv != 'i') && \
										get_unsigned(tmp, bs, up, sep) == FAIL)
		return (FAIL);
	tmp->res.len = ft_strlen(tmp->res.s);
	if (tmp->is_prcsn_def == true && tmp->prcsn > (tmp->res.len - \
													(tmp->res.s[0] == '-')))
	{
		tmp->res.len -= (tmp->res.s[0] == '-');
		precision = ft_stralloc('0', tmp->prcsn - tmp->res.len);
		swap_minus(tmp, precision);
		tmp->res.s = string_joiner(2, precision, tmp->res.s);
		tmp->res.len = tmp->prcsn;
	}
	return (SUCCESS);
}

/**
 * @brief Convert integer node value into a string
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
t_return	handle_integer_conversion(t_node *tmp)
{
	if (get_integer_string(tmp, numeric_base(tmp->conv), tmp->conv == 'X', \
					(numeric_base(tmp->conv) == 10) * tmp->flags[3]) == FAIL)
		return (FAIL);
	if (tmp->flags[0] == HASH && tmp->conv == 'x' && tmp->res.s[0] != '0')
		tmp->res.s = string_joiner(2, ft_strdup("0x"), tmp->res.s);
	if (tmp->flags[0] == HASH && tmp->conv == 'X' && tmp->res.s[0] != '0')
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
	if (ft_strchr("xXo", tmp->conv) == NULL)
		tmp->res.len = ft_strlen(tmp->res.s);
	if (handle_integer_width(tmp) == FAIL)
		return (FAIL);
	tmp->res.len = ft_strlen(tmp->res.s);
	return (SUCCESS);
}
