#include "../include/libftprintf.h"
#include <stdio.h>
#include <limits.h>
#include <float.h>

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
}

int main() {
	test_string_joiner();
	test_ulltoa_base();
	test_lltoa_base();

	//printf("LDBL_MIN         = %.16950Lf\n", LDBL_MIN);
	long double n = LDBL_MAX;
	for (int i = 0; i < 10; ++i)
	{
		printf("LDBL_MAX         = %Lf\n", n);
		n /= 10;
	}
    

	return (0);
}