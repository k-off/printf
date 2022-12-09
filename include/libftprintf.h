#ifndef LIBFTPRINTF_H
# define LIBFPRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>

typedef enum e_len_mod {
    NONE, L, ll, l, h, hh
}   t_len_mod;

typedef enum e_flags {
    HASH='#', ZERO='0', MINUS='-', SPACE=' ', PLUS='+', SEP='\''
}           t_flags;

typedef enum e_conv {
    NONE, c = 'c', s = 's', p = 'p', d = 'd', i = 'i', o = 'o', u = 'u', \
    x = 'x', X = 'X', f = 'f', F = 'F', prc='%'
}   t_conv;

typedef union u_val {
    long double f128;
    double      f64;
    void        *ptr;
    u_int64_t   u64;
    u_int32_t   u32;
} t_val;

typedef struct s_res {
    char    *s;
    size_t  len;
}   t_res;

typedef struct s_node {
    int32_t         width;
    int32_t         prcsn;
    t_flags         flags;
    t_len_mod       ln_md;
    t_val           v;
    t_conv          conv;
    t_res           res;
    struct s_node   *next;
} t_node;

int ft_printf(const char *s, ...);

#endif
