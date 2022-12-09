#include "libftprintf.h"

// int get_values() {
//     return (0);
// }

// size_t  generate_nodes(t_node **n, const char *s, size_t *len)
// {

// }

// int ft_printf(const char *s, ...)
// {
//     va_list v;
//     size_t  v_len;
//     t_node  *p_list;

//     v_len = generate_nodes(&p_list, s, &v_len);
//     va_start(v, 1);
//     va_end(v);
//     return 0;
// }
#include <stdio.h>
int main() {
    float f = 4.0;
    double d = 8.0;
    long double l = 16.0;
    l *=l;
    printf("%f, %f, %#Lf\n", f, d, l);
    int i = 5;
    printf("%hhd, %hd, %d, %ld, %lld\n", i, i, i, (long)i, (long long)i);
    return 0;
}