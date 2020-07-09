#include "../includes/ft_printf.h"

void    ft_out(char *fp, char *sp, t_struct *st)
{
    int i;
    int j;

    rounding(sp, st);
    i = 0;
    if (st->sign_bit == 1)
        st->schet = st->schet + re_putchar('-');
    if (st->f_zero == 0)
    {
        while (st->fp[i] == '0')
            i++;
        while (st->fp[i] != '\0')
        {
            ft_putchar(st->fp[i]);
            i++;
        }
    }
    else
        st->schet = st->schet + re_putchar('0');
    if (st->round != 0 || st->f_resh != 0)
        st->schet = st->schet + re_putchar('.');
    i = ft_strlen(st->sp);
    j = 0;
    while (j < st->round && j < i)
    {
        st->schet = st->schet + re_putchar(st->sp[j]);
        j++;
    }
    while (j < st->round)
    {
        st->schet = st->schet + re_putchar('0');
        j++;
    }
}

void    rounding(char *sp, t_struct *st) //округление
{
    int i;
    int j;
//    int round;
    char *arr;

    j = 0;
    i = ft_strlen(sp);
//    if (st->f_pres == 1)
//        round = st->wdth_pres;
//    else
//        round = 6;
    if (st->round == 0 && sp[st->round] == '5' && st->sign_bit == 1)
        st->neg_round = 1;
    if (st->round == 0 && sp[st->round] >= '5' && st->neg_round == 0)
        rounding_fp(st);
    if (st->round < i && sp[st->round] >= '5')
    {
        arr = ft_memalloc(st->round + 1);
        arr[j] = '1';
        while (j < st->round - 1)
        {
            j++;
            arr[j] = '0';
        }
        sum_reverse(sp, arr, st);
    }
//    j = 0;
//    while (j < st->round && j < i)
//    {
//        ft_putchar(sp[j]);
//        j++;
//    }
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