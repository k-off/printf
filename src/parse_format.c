/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:32:21 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/19 22:01:24 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static t_return	store_plain_part(t_node *tmp, const char **fmt)
{
	if (fmt[0] == NULL)
		return (FAIL);
	while (fmt[0][tmp->res.len] != '%' && fmt[0][tmp->res.len] != '\0')
		++tmp->res.len;
	tmp->res.s = ft_substr(fmt[0], 0, tmp->res.len);
	fmt[0] = &((fmt[0])[tmp->res.len]);
	if (tmp->res.s == NULL)
		return (FAIL);
	return (SUCCESS);
}

static t_return	get_float(t_node *tmp, va_list ap)
{
	if (tmp->ln_md == L || tmp->ln_md == ll)
		tmp->v.f128 = va_arg(ap, long double);
	else
		tmp->v.f64 = va_arg(ap, double);
	return (SUCCESS);
}

static t_return	get_int(t_node *tmp, va_list ap)
{
	if (tmp->ln_md == l || tmp->ln_md == ll)
		tmp->v.u64 = va_arg(ap, uint64_t);
	else
		tmp->v.u32 = va_arg(ap, uint32_t);
	return (SUCCESS);
}

static t_return	get_from_va_list(t_node *tmp, va_list ap)
{
	if (tmp->conv != 0 && ft_strchr("fFaAeEgG", tmp->conv) != NULL)
		get_float(tmp, ap);
	else if (tmp->conv == 's' || tmp->conv == 'p')
		tmp->v.ptr = va_arg(ap, void *);
	else if (tmp->conv == '%')
	{
		if (tmp->flags != NO_FLAG || tmp->width != 0 || \
			tmp->prcsn != 0 || tmp->ln_md != NO_MOD)
			return (FAIL);
	}
	else if (tmp->conv != 0 && ft_strchr("cdiouxX", tmp->conv) != NULL)
		get_int(tmp, ap);
	else if (tmp->conv != 0)
		return (FAIL);
	return (SUCCESS);
}

t_return	parse_format(t_node **head, const char *fmt, va_list ap)
{
	t_node		*tmp;
	t_return	res;

	if (head == NULL || fmt == NULL)
		return (FAIL);
	*head = ft_memalloc(sizeof(t_node));
	tmp = *head;
	while (*fmt != '\0')
	{
		if (tmp == NULL)
			return (FAIL);
		if (fmt[0] == '%')
			res = parse_conversion(tmp, &fmt);
		else
			res = store_plain_part(tmp, &fmt);
		if (res != FAIL && tmp->conv != '%')
			res = get_from_va_list(tmp, ap);
		if (res == FAIL)
			return (FAIL);
		tmp->next = ft_memalloc(sizeof(t_node));
		tmp = tmp->next;
	}
	return (SUCCESS);
}
