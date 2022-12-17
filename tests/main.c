#include "../include/libftprintf.h"
#include <stdio.h>
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

int main() {
	// test_string_joiner();
	// test_ulltoa_base();
	// test_lltoa_base();
	// test_stralloc();

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
	float f = NAN;
	char *s = dbltostr_base(INFINITY, 10, true, 5);
	printf("%s\n", s);
	free(s);
	s = dbltostr_base(-INFINITY, 10, false, 5);
	printf("%s\n", s);
	free(s);
	s = dbltostr_base(NAN, 10, false, 5);
	printf("%s\n", s);
	free(s);
	s = dbltostr_base(-f, 10, true, 5);
	printf("%s\n", s);
	free(s);
	f = 150321.64656;
	s = dbltostr_base(f, 10, true, 5);
	printf("%Lf: %s\n", (long double)-f, s);
	free(s);
	f = -150321.64656;
	s = dbltostr_base(f, 16, true, 5);
	printf("%Lf: %s\n", (long double)-f, s);
	free(s);
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
	return (0);
}
