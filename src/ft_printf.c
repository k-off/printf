/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:44:52 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/31 09:12:40 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <unistd.h>

int	ft_vsprintf(char **return_string, const char *format, va_list ap)
{
	t_node		*chunks_list;
	int			total_bytes;
	t_return	status;

	return_string[0] = NULL;
	total_bytes = 0;
	status = FAIL;
	if (parse_format(&chunks_list, format, ap) == SUCCESS)
		if (handle_conversions(&total_bytes, chunks_list) == SUCCESS)
			status = join_results(return_string, total_bytes, chunks_list);
	if (release_conversions(chunks_list) == FAIL || status == FAIL)
		return ((int)FAIL);
	return (total_bytes);
}

int	ft_sprintf(char **str, const char *s, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, s);
	res = ft_vsprintf(str, s, ap);
	va_end(ap);
	return (res);
}

int	ft_vdprintf(int fd, const char *s, va_list ap)
{
	int		res;
	char	*str;

	str = NULL;
	res = ft_vsprintf(&str, s, ap);
	if (res > 0 && str != NULL)
		write(fd, str, res);
	if (str != NULL)
		free (str);
	return (res);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, s);
	res = ft_vdprintf(fd, s, ap);
	va_end(ap);
	return (res);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, s);
	res = ft_vdprintf(1, s, ap);
	va_end(ap);
	return (res);
}
