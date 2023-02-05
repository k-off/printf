/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_conversion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:44:52 by pcovalio          #+#    #+#             */
/*   Updated: 2023/02/05 09:09:21 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_return	get_exponent(t_node *tmp, int *exp, long double *n, int base);
t_return	handle_double_width(t_node *tmp);

/**
 * @brief Handle fF conversion - convert float value of current node
 * 			into a string result formatted as [+]ff.fffff
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS (0) or FAIL (-1)
*/
static t_return	handle_f(t_node *tmp)
{
	if (!tmp->is_prcsn_def)
		tmp->prcsn = 6;
	if (!tmp->is_prcsn_def)
		tmp->is_prcsn_def = true;
	if (tmp->ln_md == ll || tmp->ln_md == L)
		tmp->res.s = dbltostr_base((long double)tmp->v.f128, \
						10, tmp->conv < 91u, tmp->prcsn);
	else
		tmp->res.s = dbltostr_base((long double)tmp->v.f64, \
						10, tmp->conv < 91u, tmp->prcsn);
	if (tmp->res.s == NULL)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Handle eE conversion - convert float value of current node
 * 			into a string result in exponential format [+]e.eee+dd
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS (0) or FAIL (-1)
*/
static t_return	handle_e(t_node *tmp)
{
	int			exp;
	long double	n;

	if (get_exponent(tmp, &exp, &n, 10) == FAIL)
		return (FAIL);
	tmp->res.s = dbltostr_base(n, 10, false, tmp->prcsn);
	if (tmp->conv < 91u)
		tmp->res.s = string_joiner(2, tmp->res.s, ft_strdup("E"));
	else
		tmp->res.s = string_joiner(2, tmp->res.s, ft_strdup("e"));
	if (exp < 0)
		tmp->res.s = string_joiner(2, tmp->res.s, ft_strdup("-"));
	else
		tmp->res.s = string_joiner(2, tmp->res.s, ft_strdup("+"));
	if (exp < 0)
		exp = -exp;
	if (exp < 10)
		tmp->res.s = string_joiner(2, tmp->res.s, ft_strdup("0"));
	tmp->res.s = string_joiner(2, tmp->res.s, ulltoa_base(exp, 10, 0, 0));
	if (tmp->res.s == NULL)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Handle gG conversion - convert float value of current node
 * 			into a string result in exponential format [+]e.eee+dd 
 * 			or float format [+]ff.ffffff depending on exponent and precision
 * 			values. Doesnt entirely correspond to printf gG conversion - 
 * 			no zero trimming
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS (0) or FAIL (-1)
*/
static t_return	handle_g(t_node *tmp)
{
	int			exp;
	long double	n;

	if (get_exponent(tmp, &exp, &n, 10) == FAIL)
		return (FAIL);
	if ((exp < -4 || exp >= (int)tmp->prcsn) && handle_e(tmp) == FAIL)
		return (FAIL);
	else if (handle_f(tmp) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Handle aA conversion - convert float value of current node
 * 			into a string result in exponential format as hexadecimal 
 * 			[+]0xh.hhhhp+dd.
 * 			L and ll length modifiers are not supported.
 * 			Limited precision.
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS (0) or FAIL (-1)
*/
static t_return	handle_a(t_node *tmp)
{
	int			exp;
	long double	n;

	if (get_exponent(tmp, &exp, &n, 2) == FAIL)
		return (FAIL);
	if (n < 0)
		tmp->res.s = ft_strdup("-");
	if (n < 0)
		n = -n;
	if (tmp->conv == 'A')
		tmp->res.s = string_joiner(4, tmp->res.s, ft_strdup("0X"), \
					dbltostr_base(n, 16, false, tmp->prcsn), ft_strdup("P"));
	else
		tmp->res.s = string_joiner(4, tmp->res.s, ft_strdup("0x"), \
					dbltostr_base(n, 16, false, tmp->prcsn), ft_strdup("p"));
	if (exp < 0)
		tmp->res.s = string_joiner(2, tmp->res.s, ft_strdup("-"));
	else
		tmp->res.s = string_joiner(2, tmp->res.s, ft_strdup("+"));
	if (exp < 0)
		exp = -exp;
	tmp->res.s = string_joiner(2, tmp->res.s, ulltoa_base(exp, 10, 0, 0));
	if (tmp->res.s == NULL)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Convert float/double node value into a string
 * 
 * @param tmp *t_node, current conversion node
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
t_return	handle_double_conversion(t_node *tmp)
{
	if (ft_strchr("fF", tmp->conv))
		if (handle_f(tmp) != SUCCESS)
			return (FAIL);
	if (tmp->conv == 'e' || tmp->conv == 'E')
		if (handle_e(tmp) != SUCCESS)
			return (FAIL);
	if (tmp->conv == 'g' || tmp->conv == 'G')
		if (handle_g(tmp) != SUCCESS)
			return (FAIL);
	if (ft_strchr("aA", tmp->conv))
		if (handle_a(tmp) != SUCCESS)
			return (FAIL);
	if (tmp->flags[2] == PLUS && tmp->res.s[0] != '-')
		tmp->res.s = string_joiner(2, ft_strdup("+"), tmp->res.s);
	tmp->res.len = ft_strlen(tmp->res.s);
	if (handle_double_width(tmp) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
