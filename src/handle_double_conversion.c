/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_conversion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:44:52 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/31 09:07:28 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/**
 * @brief Convert data from the chunks list into string chunks and store total
 * 		bytes amount for doble numbers under conversions e, E, f, F, g and G
 * 
 * @param tmp t_node*, current conversion node
 * @return t_return SUCCESS or FAIL
 */
t_return	handle_doubles_other(t_node *tmp)
{
	(void)tmp;
	return (SUCCESS);
}

/**
 * @brief Convert data from the chunks list into string chunks and store total
 * 		bytes amount for doble numbers under conversions a and A
 * 
 * @param tmp t_node*, current conversion node
 * @return t_return SUCCESS or FAIL
 */
t_return	handle_doubles_aa(t_node *tmp)
{
	(void)tmp;
	return (SUCCESS);
}
