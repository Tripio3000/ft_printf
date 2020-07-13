#include "../includes/ft_printf.h"

void    ft_out(char *fp, char *sp, t_struct *st)
{
    int i;

    i = 0;
    while (fp[i] == '0')
        i++;
    while (fp[i] != '\0')
    {
        st->schet = st->schet + re_putchar(fp[i]);
        i++;
    }
    st->schet = st->schet + re_putchar('.');
    rounding(sp, st);
}

void    rounding(char *sp, t_struct *st) //округление
{
    int i;
    int j;
    int round;
    char *arr;

    j = 0;
    i = ft_strlen(sp);
    if (st->f_pres == 1)
        round = st->wdth_pres;
    else
        round = 6;
    if (round < i && sp[round] >= '5')
    {
        arr = ft_memalloc(round);
        arr[j] = '1';
        while (j < round - 1)
        {
            j++;
            arr[j] = '0';
        }
        sp = sum_reverse(sp, arr);
    }
    j = 0;
    while (j < round && j < i)
    {
        st->schet = st->schet + re_putchar(sp[j]);
        j++;
    }
}

void print_float(char *fp, char *sp, t_struct *st, t_sun eeei)
{
    if (st->f_minus == 1)
    {
        if (st->f_plus == 1)
        {
            if (eeei.v.sign == 1)
                st->schet = st->schet + re_putchar('-');
            else
                st->schet = st->schet + re_putchar('+');
        }


    }
//    else if (st->f_minus == 0)
//        print_else(format, st);
    ft_out(st->fp, st->sp, st);
}