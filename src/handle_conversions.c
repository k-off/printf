/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:44:52 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/19 22:00:59 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_return handle_conversions(int *total_bytes, t_node *chunks_list)
{
    if (total_bytes == NULL || chunks_list == NULL)
        return (FAIL);
    while(chunks_list)
    {
        if (chunks_list->conv == 0 && chunks_list->res.s == NULL)
            chunks_list->res.s = ft_memalloc(1);
        *total_bytes += chunks_list->res.len;
        chunks_list = chunks_list->next;
    }
    return (SUCCESS);
}
