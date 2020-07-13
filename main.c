#include "includes/ft_printf.h"

int main()
{
	ft_printf("%.4+.5*d\n", 45, 56);
	printf("%.4+.5*d\n", 45, 56);
    return 0;
}