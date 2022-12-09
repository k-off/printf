/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:58:51 by pcovalio          #+#    #+#             */
/*   Updated: 2023/02/05 08:01:51 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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

static void	handle_xprefix(t_node *tmp, char *pad)
{
	char	*pos;

	pos = ft_strchr(tmp->res.s, 'x');
	if (pos == NULL)
		pos = ft_strchr(tmp->res.s, 'X');
	if (pos == NULL)
		return ;
	pad[pos - tmp->res.s] = *pos;
	*pos = '0';
}

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
