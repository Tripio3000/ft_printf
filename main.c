#include "ft_printf.h"
#include <float.h>
#include <stdio.h>

int     main() {
    ft_printf("%f\n", DBL_MAX);
    printf("%f\n", DBL_MAX);
    return 0;
}