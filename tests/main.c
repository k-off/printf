/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:12:06 by pcovalio          #+#    #+#             */
/*   Updated: 2023/01/06 13:18:23 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libftprintf.h"
#include "../ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>
#include <math.h>

int test_string_joiner()
{
	printf("Testing strjoiner\n");
	char *s[] = {"-", "1", NULL, "", NULL, "hello", NULL, "", NULL, " ", NULL, "world!",  NULL};
	for (int i = 0; i < 11; ++i)
	{
		char *res = string_joiner(i,
			i > 0 ? ft_strdup(s[0]) : NULL,
			i > 1 ? ft_strdup(s[1]) : NULL,
			i > 2 ? ft_strdup(s[2]) : NULL,
			i > 3 ? ft_strdup(s[3]) : NULL,
			i > 4 ? ft_strdup(s[4]) : NULL,
			i > 5 ? ft_strdup(s[5]) : NULL,
			i > 6 ? ft_strdup(s[6]) : NULL,
			i > 7 ? ft_strdup(s[7]) : NULL,
			i > 8 ? ft_strdup(s[8]) : NULL,
			i > 9 ? ft_strdup(s[9]) : NULL,
			i > 10 ? ft_strdup(s[10]) : NULL);
		printf("res: \"%s\"\n", res);
		if (res)
			free(res);
	}
	return (0);
}

int test_ulltoa_base()
{
	printf("Testing ulltoa_base\n");
	unsigned long long ull[] = {ULLONG_MAX, 0, 1, UINT16_MAX, UINT32_MAX, UINT64_MAX};
	int base[] = {2, 8, 10, 16, 36};
	for (int i = 0; i < 6; ++i) {
		for (int is_upper = 0; is_upper < 2; ++is_upper) {
			printf("%30llu: ", ull[i]);
			for (int j = 0; j < 5; ++j) {
				char *res = ulltoa_base(ull[i], base[j], is_upper, ' ');
				if (res)
				{
					j ? printf("%27s|", res) : printf("%65s|", res);
					free(res);
				}
			}
				printf("\n");
		}
	}
	return (0);
}

int test_lltoa_base()
{
	printf("Testing lltoa_base\n");
	long long ll[] = {LLONG_MIN, LLONG_MAX, -1, 0, 1, INT64_MIN, INT64_MAX};
	int base[] = {2, 8, 10, 16, 36};
	for (int i = 0; i < 7; ++i) {
		for (int is_upper = 0; is_upper < 2; ++is_upper) {
			printf("%30lld: ", ll[i]);
			for (int j = 0; j < 5; ++j) {
				char *res = lltoa_base(ll[i], base[j], is_upper, ' ');
				if (res)
				{
					j ? printf("%27s|", res) : printf("%65s|", res);
					free(res);
				}
			}
				printf("\n");
		}
	}
	return (0);
}

int test_stralloc()
{
	char *s = ft_stralloc('0', 0);
	printf("ft_stralloc: %s", !ft_memcmp(s, "\0", 1) ? "OK" : "KO");
	free(s);
	s = ft_stralloc('0', 1);
	printf(" %s", !ft_memcmp(s, "0\0", 2) ? "OK" : "KO");
	free(s);
	s = ft_stralloc('0', 10);
	printf(" %s\n", !ft_memcmp(s, "0000000000\0", 11) ? "OK" : "KO");
	free(s);
	return (0);
}

void printBin(long double n) {
	printf("%10Lf: ", n);
	for (int i = 16; i >0;)
	{
		--i;
		int8_t c = ((char *)(&n))[i];
		//printf("%i: ", i);
		for (int j = 8; j > 0;) {
			--j;
			printf("%d", (int)((c >> j) & 1));
		}
		printf(" ");
	}
	printf(", %X\n", *((uint32_t *)(&((char *)(&n))[6])));
	if ((*((uint8_t *)(&((char *)(&n))[9])) >> 7) == 1)
	{
		*((uint8_t *)(&((char *)(&n))[9])) ^= (uint8_t)(1 << 7);
		printf(", %X\n", *((uint32_t *)(&((char *)(&n))[6])));
	}
}

static void	ft_round(long double *n, uint64_t prec)
{
	long double	tmp;
	long double cor;

	tmp = 5.0L;
	cor = 1.0L / (1ULL << 63);
	tmp /= 10.0L;
	while (prec--)
	{
		tmp /= 10.0L;
		if (cor < 0.1L)
			cor *= 10.0L;
	}
	tmp *= (1.0L + cor);
	*n += tmp;
}

int test_round() {
	printf("%.0Lf\n", 1.5L);
	long double	half = 1;
	int max_prc = 60;
	for (int i = 0; i < max_prc; ++i) {
		long double	cur = 1.0L;
		half /= 2;
		cur += half;
		printf("%.65Lf : ", cur);
		ft_round(&cur, i);
		printf("%.65Lf\n", cur);
	}
	return (0);
}

void floatPlayground()
{
		// int n = printf("%s%c%s", "hello ", 0, "world");
	// unsigned long long int d = 149;
	// printf("\n%-+10.4lld|\n", d);
	//printf("LDBL_MIN         = %.16950Lf\n", LDBL_MIN);
	// long double n = INFINITY;
	// printf("%Lf|\n", n);
	// n = n;
	// printBin(n);
	// printBin(-n);
	// printBin(NAN);
	// printBin(-NAN);
	// printBin(0.0);
	// printBin(-0.0);
	// long double f = NAN;
	// char *s = dbltostr_base(INFINITY, 10, true, 5);
	// printf("%s\n", s);
	// free(s);
	// s = dbltostr_base(-INFINITY, 10, false, 5);
	// printf("%s\n", s);
	// free(s);
	// s = dbltostr_base(NAN, 10, false, 5);
	// printf("%s\n", s);
	// free(s);
	// s = dbltostr_base(-f, 10, true, 5);
	// printf("%s\n", s);
	// free(s);
	// f = 150321.64656;
	// s = dbltostr_base(f, 10, true, 5);
	// printf("%15.5Lf: %s\n", f, s);
	// free(s);
	// f = -150321.64656;
	// s = dbltostr_base(f, 16, true, 5);
	// printf("%15.5Lf: %s\n", f, s);
	// free(s);
	// f = -0.00000356L;
	// s = dbltostr_base(f, 10, true, 6);
	// printf("%15.6Lf: %s\n", f, s);
	// free(s);
	// s = dbltostr_base(f, 10, true, 7);
	// printf("%15.7Lf: %s\n", f, s);
	// free(s);
	// s = dbltostr_base(f, 10, true, 8);
	// printf("%15.8Lf: %s\n", f, s);
	// free(s);
	// s = dbltostr_base(f, 10, true, 9);
	// printf("%15.9Lf: %s\n", f, s);
	// free(s);
	// s = dbltostr_base(f, 10, true, 10);
	// printf("%15.10Lf: %s\n", f, s);
	// free(s);
	// test_round();

		// if (((((char *)(&n))[i] >> 7) & 1) == 1) //((((char *)(&n))[i] >> 7) & 1) == 1
		// 	printf("%i: %ld|\n", i, (long)n);
	// if (((((char *)(&n))[9] >> 7) & 1) == 1)
	// 	printf("0x%ld|\n", (long)n);
	// n = NAN;
	// if (((((char *)(&n))[9] >> 7) & 1) == 1)
	// 	printf("0x%ld|\n", (long)n);
	// n = -0.0L;
	// printf("0x%ld|\n", (long)n);
	// if (n < 0)
	// 	printf("%-10.5f|\n", -n);
	// if (-0.0L == 0.0L)
	// 	printf("%-10.5f|\n", -0.0);
	// while (n > 1 && (unsigned long long)(n) == 0)
	// 	n/=10;
	// printf("%lu\n", (uint64_t)(n));
	// printf("%lu\n", UINT64_MAX);
}

void va_playground(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	123.456L   != va_arg(ap, long double) ? printf(" KO") : printf(" OK");
	123.456    != va_arg(ap,      double) ? printf(" KO") : printf(" OK");
	123.456F   != va_arg(ap,      double) ? printf(" KO") : printf(" OK");
	NULL       != va_arg(ap,       void*) ? printf(" KO") : printf(" OK");
	UINT64_MAX != va_arg(ap,    uint64_t) ? printf(" KO") : printf(" OK");
	INT64_MAX  != va_arg(ap,    uint64_t) ? printf(" KO") : printf(" OK");
	UINT32_MAX != va_arg(ap,    uint32_t) ? printf(" KO") : printf(" OK");
	INT32_MAX  != va_arg(ap,    uint32_t) ? printf(" KO") : printf(" OK");
	UINT16_MAX != va_arg(ap,    uint32_t) ? printf(" KO") : printf(" OK");
	INT16_MAX  != va_arg(ap,    uint32_t) ? printf(" KO") : printf(" OK");
	UINT8_MAX  != va_arg(ap,    uint32_t) ? printf(" KO") : printf(" OK");
	INT8_MAX   != va_arg(ap,    uint32_t) ? printf(" KO") : printf(" OK");
	INT8_MIN   != (char)va_arg(ap,    uint32_t) ? printf(" KO") : printf(" OK");
	va_end(ap);
}

int test_join_results(t_node *chunks_list) {
	int total_bytes = 0;
	char *return_string;
	if (chunks_list == NULL)
		return (SUCCESS);
	if (handle_conversions(&total_bytes, chunks_list) == FAIL)
		printf("handle_conversions() failed\n");
	else if (join_results(&return_string, total_bytes, chunks_list) == FAIL)
		printf("join_results() failed\n");
	else if (release_conversions(chunks_list) == FAIL)
		printf("release_conversions() failed\n");
	else if (return_string == NULL)
		printf("something is completely off, string is not allocated");
	else
	{
		printf("bytes: (%d vs %ld), str: '%s'\n", total_bytes, ft_strlen(return_string), return_string);
		free(return_string);
	}
	return (SUCCESS);
}

int test_format_parser(char *fmt, ...) {
	t_node *head = NULL;
	t_node *tmp = NULL;
	va_list ap;
	va_start(ap, fmt);
	if (parse_format(&head, fmt, ap) == SUCCESS) {
		tmp = head;
	}
	va_end(ap);
	while (head)
	{
		if (head->conv == 0)
			printf("'%s'\n", head->res.s);
		else {
			head->res.s = ft_strdup(" test ");
			head->res.len = ft_strlen(head->res.s);
			printf("%u %u %d : ", head->width, head->prcsn,head->ln_md);
		}
		if (ft_strchr("diouxX", head->conv) != NULL && head->conv != 0)
			printf("%hd\n", head->v.u32);
		else if (ft_strchr("s", head->conv) != NULL && head->conv != 0)
			printf("'%s'\n", (char *)head->v.ptr);
		else if (ft_strchr("FaAeEgG", head->conv) != NULL && head->conv != 0)
			printf("'%Lf'\n", head->v.f128);
		head = head->next;
	}
	test_join_results(tmp);
	return 0;
}

// int test_char()
// {
// 	printf("|%c| ", 'a');		write(1, "", 1);	ft_printf("|%c| ", 'Z');
// 	printf("|%5c| ", 'a');		write(1, "", 1);	ft_printf("|%5c| ", 'Z');
// 	printf("|%-5c| ", 'a');		write(1, "", 1);	ft_printf("|%-5c| ", 'Z');
// 	printf("|%05c| ", 'a');		write(1, "", 1);	ft_printf("|%05c| ", 'Z');
// 	printf("|%-05c| ", 'a');	write(1, "", 1);	ft_printf("|%-05c| ", 'Z');
// 	printf("|%5.3c| ", 'a');	write(1, "", 1);	ft_printf("|%5.3c| ", 'Z');
// 	printf("|%-05.3c| ", 'a');	write(1, "", 1);	ft_printf("|%-05.3c|\n", 'Z');
// 	printf("|%+c| ", 'a');		write(1, "", 1);	ft_printf("|%+c| ", 'Z');
// 	printf("|%+5c| ", 'a');		write(1, "", 1);	ft_printf("|%+5c| ", 'Z');
// 	printf("|%+-5c| ", 'a');		write(1, "", 1);	ft_printf("|%+-5c| ", 'Z');
// 	printf("|%+05c| ", 'a');		write(1, "", 1);	ft_printf("|%+05c| ", 'Z');
// 	printf("|%+-05c| ", 'a');	write(1, "", 1);	ft_printf("|%+-05c| ", 'Z');
// 	printf("|%+5.3c| ", 'a');	write(1, "", 1);	ft_printf("|%+5.3c| ", 'Z');
// 	printf("|%+-05.3c| ", 'a');	write(1, "", 1);	ft_printf("|%+-05.3c|\n", 'Z');
// 	return SUCCESS;
// }

int test_string()
{
	char	*s;
	char	*values[] = {NULL, "", "hello"};

	for (int i = 0; i < 3; ++i)
	{
		s = values[i];
		printf("\n===================== |%s| =====================\n", s);
		printf(" = %d bytes :: ", printf("|%s|", s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%s|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|% s|", s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|% s|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%.s|", s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%.s|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|% .s|", s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|% .s|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%10.3s|", s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%10.3s|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%-10.3s|", s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%-10.3s|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%10s|", s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%10s|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%-10s|", s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%-10s|", s)); fflush(stdout);
	}
	return SUCCESS;
}

int test_integer()
{
	int	s;
	int	values[] = {INT_MIN, -1, 0, 1, INT_MAX};

	for (int i = 0; i < 5; ++i)
	{
		s = values[i];
		printf("\n===================== |%d: no_flag| =====================\n", s);
		printf(" = %d bytes :: ", printf("|%d|", s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%d|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%hhd|", (char)s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%hhd|", (char)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%hd|", (short)s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%hd|", (short)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%ld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%ld|", (int64_t)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%lld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", ft_printf("|%lld|", (int64_t)s)); fflush(stdout);
		exit(0);printf("\n===================== |%d: zero_flag| =====================\n", s);
		printf(" = %d bytes :: ", printf("|%0d|", s)); fflush(stdout); printf(" = %d bytes\n", printf("|%0d|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%0hhd|", (char)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%0hhd|", (char)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%0hd|", (short)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%0hd|", (short)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%0ld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%0ld|", (int64_t)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%0lld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%0lld|", (int64_t)s)); fflush(stdout);
		printf("\n===================== |%d: space_flag| =====================\n", s);
		printf(" = %d bytes :: ", printf("|% d|", s)); fflush(stdout); printf(" = %d bytes\n", printf("|% d|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|% hhd|", (char)s)); fflush(stdout); printf(" = %d bytes\n", printf("|% hhd|", (char)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|% hd|", (short)s)); fflush(stdout); printf(" = %d bytes\n", printf("|% hd|", (short)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|% ld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|% ld|", (int64_t)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|% lld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|% lld|", (int64_t)s)); fflush(stdout);
		printf("\n===================== |%d: hash_flag| =====================\n", s);
		printf(" = %d bytes :: ", printf("|%#d|", s)); fflush(stdout); printf(" = %d bytes\n", printf("|%#d|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%#hhd|", (char)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%#hhd|", (char)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%#hd|", (short)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%#hd|", (short)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%#ld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%#ld|", (int64_t)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%#lld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%#lld|", (int64_t)s)); fflush(stdout);
		printf("\n===================== |%d: plus_flag| =====================\n", s);
		printf(" = %d bytes :: ", printf("|%+d|", s)); fflush(stdout); printf(" = %d bytes\n", printf("|%+d|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%+hhd|", (char)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%+hhd|", (char)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%+hd|", (short)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%+hd|", (short)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%+ld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%+ld|", (int64_t)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%+lld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%+lld|", (int64_t)s)); fflush(stdout);
		printf("\n===================== |%d: separator_flag| =====================\n", s);
		printf(" = %d bytes :: ", printf("|%'d|", s)); fflush(stdout); printf(" = %d bytes\n", printf("|%'d|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%'hhd|", (char)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%'hhd|", (char)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%'hd|", (short)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%'hd|", (short)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%'ld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%'ld|", (int64_t)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%'lld|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%'lld|", (int64_t)s)); fflush(stdout);
		printf("\n===================== |%d: width_precision| =====================\n", s);
		printf(" = %d bytes :: ", printf("|%0d|", s)); fflush(stdout); printf(" = %d bytes\n", printf("|%0d|", s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%1d|", (char)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%1d|", (char)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%2.0d|", (short)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%2.0d|", (short)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|%2.1d|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|%2.1d|", (int64_t)s)); fflush(stdout);
		printf(" = %d bytes :: ", printf("|% -13.11d|", (int64_t)s)); fflush(stdout); printf(" = %d bytes\n", printf("|% -13.11d|", (int64_t)s)); fflush(stdout);
	}
	return SUCCESS;
}

int main() {
	// test_string_joiner();
	// test_ulltoa_base();
	// test_lltoa_base();
	// test_stralloc();

	// va_playground(12, 123.456L, 123.456, 123.456F, NULL, UINT64_MAX, INT64_MAX, \
	// 	UINT32_MAX, INT32_MAX, UINT16_MAX, INT16_MAX, UINT8_MAX, INT8_MAX, INT8_MIN);

	// test_format_parser(NULL);
	// test_format_parser("");
	// test_format_parser("blah");
	// test_format_parser("Print %-+30.30hhd words \'%-+30.30lls\' and floats %+-30.30LF", INT16_MAX, "hello", 0.019364L);
	// test_format_parser("Print %-+30.30hhd words \'%-+30.30lls\' and floats %+-30.30LF", INT16_MAX, "hello");

	// test_char();

	// test_string();
	//test_integer();
	// printf(" %p \n", 1);
	// printf(" %p \n", 15);
	// printf(" %p \n", 16);
	// printf(" %p \n", 17);
	// printf(" %p %p \n", LONG_MIN, LONG_MAX);
	// printf(" %p %p \n", INT_MIN, INT_MAX);
	// printf(" %p %p \n", ULONG_MAX, -ULONG_MAX);
	// printf(" %p %p \n", 0, 0);
	// printf("=======================");
	// ft_printf(" %p \n", 1);
	// ft_printf(" %p \n", 15);
	// ft_printf(" %p \n", 16);
	// ft_printf(" %p \n", 17);
	// ft_printf(" %p %p \n", LONG_MIN, LONG_MAX);
	// ft_printf(" %p %p \n", INT_MIN, INT_MAX);
	// ft_printf(" %p %p \n", ULONG_MAX, -ULONG_MAX);
	// ft_printf(" %p %p \n", 0, 0);
	// ft_printf(" = %d\n",ft_printf("%%"));
	ft_printf("%%");
	return (0);
}

