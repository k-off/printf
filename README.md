# printf (42 school project)
Recode printf function

## Learn `va_args` and recode `printf (3)` function family:

```
int ft_printf(const char *format, ...);
int ft_dprintf(int fd, const char *format, ...);
int ft_sprintf(char **str, const char *format, ...); // in contrast to original one, allocates enough memory for the resulting string
int ft_vprintf(const char *format, va_list ap);
int ft_vdprintf(int fd, const char *format, va_list ap);
int ft_vsprintf(char **str, const char *format, va_list ap); // in contrast to original one, allocates enough memory for the resulting string
```

### What's in:

 - Full support of `cspdiuxX%` conversions with `#-+ 0` flags, width and precision.
 - `'` flag for `diu` conversions will always add thousand delimiter `'` in format 1'000'000 (no locale support).
 - Limited support of `ofFeEgGaA` conversions - not fully tested, some flag combinations are not supported.

Switch to `dev` branch to see the subject pdf file and other extra files.
