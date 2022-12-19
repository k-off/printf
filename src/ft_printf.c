/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:44:52 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/18 13:51:56 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <unistd.h>

int	ft_vsprintf(char **str, const char *s, va_list ap)
{
	(void)str;
	(void)s;
	(void)ap;

	return (0);
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
	if (res > 0 && str)
		write(fd, str, res);
	if (str)
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
