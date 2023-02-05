/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_integer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:25:44 by pcovalio          #+#    #+#             */
/*   Updated: 2023/02/05 09:59:18 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/**
 * @brief Get numberic value of base from conversion character
 * 
 * @param conversion uint8_t, character value of conversion
 * @return numeric value of base or FAIL (-1)
*/
int	numeric_base(uint8_t conversion)
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

/**
 * @brief Ugly but tested hack: move `+ -x` characters from number 
 * 			string into padding string if it is set to zeroes and 
 * 			is to the left from number string
 * @param tmp *t_node, current conversion node
 * @param padding *char, padding string
*/
void	swap_minus(t_node *tmp, char *padding)
{
	char	*pos;

	if (padding && padding[0] == '0')
	{
		pos = ft_strchr("+- ", tmp->res.s[0]);
		if (pos != NULL)
		{
			padding[0] = tmp->res.s[0];
			tmp->res.s[0] = '0';
		}
		pos = ft_strchr(tmp->res.s, 'x');
		if (pos == NULL)
			pos = ft_strchr(tmp->res.s, 'X');
		if (pos != NULL)
		{
			if (ft_strlen(padding) > 1)
				padding[1 + (ft_strchr("+- ", tmp->res.s[0]) != NULL)] = pos[0];
			else
				tmp->res.s[0] = pos[0];
			pos[0] = '0';
		}
	}
}

/**
 * @brief Ugly but tested hack for handling xXo conversions with padding
 * 
 * @param tmp *t_node, current conversion node
 * @param pad **char, address of padding string to be allocated and set
 * @return t_return SUCCESS(0) or FAIL(-1)
*/
t_return	xxo_hash_padding(t_node *tmp, char **pad)
{
	char	*suf;

	if (tmp->v.u64 != 0 && tmp->flags[0] == HASH && ft_strchr("xXo", tmp->conv))
	{
		suf = ft_stralloc('0', 2 - (tmp->conv == 'o'));
		if (tmp->conv == 'x')
			suf[1] = 'x';
		else if (tmp->conv == 'X')
			suf[1] = 'X';
		if (ft_strnstr(tmp->res.s, "0X", 5) == NULL && \
			ft_strnstr(tmp->res.s, "0x", 5) == NULL)
		{
			if (tmp->flags[1] == MINUS || pad[0] == NULL || pad[0][0] == ' ')
				tmp->res.s = string_joiner(2, suf, tmp->res.s);
			else if (pad[0] == NULL)
				pad[0] = suf;
			else if (pad[0][0] == '0')
				pad[0] = string_joiner(2, suf, pad[0]);
		}
		else
			free(suf);
	}
	swap_minus(tmp, *pad);
	return (SUCCESS);
}
