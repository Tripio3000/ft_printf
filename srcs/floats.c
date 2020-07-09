#include "../includes/ft_printf.h"
# define SIZE_E 1023
# define SIZE_M 52

//void    bit_parcer(long double f)
//{
//    t_sun eeei;
//    //unsigned displayMask = 1 << 22;
//    int c;
//
//    eeei.f = f;
//    printf("\n");
////    printf("%d_ %d_ %d  %f\n", eeei.v.sign, eeei.v.exp, eeei.v.mant, eeei.f);
//    for (c=0; c<=23; c++)
//    {
//        ft_putchar(eeei.v.mant & (1 << c) ? '1' : '0');
//        //eeei.v.mant <<= 1;
//
////        if (c % 8 == 0)
////            putchar(' ');
//    }
//}

void    *ft_cpy(char *newptr, char *ptr, int size)
{
    int i;
    int j;

//    write(1, "ok", 2);
    i = 0;
    j = 0;
    while (ptr[i] != '\0')
    {
        newptr[i] = ptr[i];
        i++;
    }
    while (i < size)
    {
        newptr[i] = '0';
        i++;
    }
    newptr[i] = '\0';
    return (newptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
    char	*newptr;

//    if (size == 64)
//        printf("1\n");
//    printf("realloc\n");
//    write(1, "ok", 2);
    if (!size && ptr)
    {
        if (!(newptr = (char *)malloc(1)))
            return (NULL);
        ft_memdel(&ptr);
        return (newptr);
    }
    if (!(newptr = (char *)malloc(size + 1)))
        return (NULL);
    if (ptr)
    {
        ft_cpy(newptr, ptr, size);
        //free(ptr);
        ft_memdel(&ptr);
    }
//    printf("newptr:%s\n", newptr);
    return (newptr);
}

void    *get_char(char *arr)
{
    char *mas;
    int i;
    int j;
    char tmp;

    j = ft_strlen(arr);
    i = 0;
    mas = ft_memalloc(ft_strlen(arr) + 1);
    while (arr[i] != '\0')
    {
        mas[i] = arr[j - 1];
        i++;
        j--;
    }
    mas[i] = '\0';
//    ft_memdel(&arr);
    return (mas);
}

void    *sum_char(char *ans, char *tmp)
{
    int i;
    int j;
    char symb;
//    char *str;
    char *newptr;
//    write(1, "ok", 2);

//    str = ft_memalloc(ft_strlen(tmp));
//    ft_strcpy(str, tmp);
    i = ft_strlen(ans);
    j = ft_strlen(tmp);
    while ((i - 1) == j || j > i)
    {
        ans = ft_realloc(ans, (i*2));
        i = ft_strlen(ans);
        j = ft_strlen(tmp);
    }

    i = 0;
    while (tmp[i] != '\0' && ans[i] != '\0')
    {
        symb = tmp[i];
        ans[i] += symb - '0';
        if (ans[i] > '9')
        {
            if (ans[i + 1] == '\0')
            {
                newptr = ft_strnew(j + 1);
                ft_strcpy(newptr, ans);
                newptr[i] -= 10;
                newptr[i + 1] = 49;
                newptr[i + 2] = '\0';
//                ft_memdel(&str);
                ft_memdel(&ans);
//                write(1, "end", 3);
                return (newptr);
            }
            else
            {
                ans[i + 1]++;
                ans[i] -= 10;
            }
        }
        i++;
    }
//    ft_memdel(&str);
//    write(1, "en", 3);
    return (ans);
}

void    *two_degree(char *arr)
{
    char *tm;
    char *newptr;
    int i;

    tm = ft_memalloc(ft_strlen(arr));
    ft_strcpy(tm, arr);
    i = 0;
    while (arr[i] != '\0')
    {
        arr[i] += tm[i] - '0';
        i++;
    }
    i = 0;
    while (arr[i] != '\0')
    {
        if (arr[i + 1] == '\0' && arr[i] > '9')
        {
            newptr = ft_memalloc(i + 3);
            ft_strcpy(newptr, arr);
            newptr[i] -= 10;
            newptr[i + 1] = 49;
            newptr[i + 2] = '\0';
//            ft_memdel(&arr);
            ft_memdel(&tm);
            return (newptr);
        }
        if (arr[i] > '9')
        {
            arr[i] -= 10;
            arr[i + 1]++;
        }
        i++;
    }
    ft_memdel(&tm);
    return (arr);
}

void    rounding_fp(t_struct *st)
{
    char *arr;

    arr = ft_memalloc(2);
    arr[0] = '1';
    arr[1] = '\0';
    st->fp = get_char(st->fp);
    sum_char(st->fp, arr);
    st->fp = get_char(st->fp);
    st->f_zero = 0;
    st->sp[0] -= 10;
}

void    sum_reverse(char *ans, char *tmp, t_struct *st)
{
    int i;
    int j;
    int k;
    char symb;
    char *arr;

    i = ft_strlen(st->sp);
    j = ft_strlen(tmp);
    arr = ft_memalloc(j);
    arr = get_char(tmp);
    while ((i - 1) == j || j > i)
    {
        st->sp = ft_realloc(st->sp, (i*2));
        i = ft_strlen(st->sp);
    }
//    while (i > j && ans[i - 1] == '0')
//        i--;
    i = 0;
    j = 0;
    while (arr[j] != '\0')
    {
        symb = arr[j];
        st->sp[i] += symb - '0';
        k = i;
        while (k > 0)
        {
            if (st->sp[k] > '9')
            {
                st->sp[k - 1]++;
                st->sp[k] -= 10;
            }
            k--;
        }
        i++;
        j++;
    }
    if (k == 0 && st->sp[k] > '9')
        rounding_fp(st);
//    return (st->sp);
}

void    *get_zero(char *arr)
{
    char *newptr;
    int i;

    newptr = ft_memalloc(ft_strlen(arr) + 3);
    i = 0;
    while (arr[i] != '\0')
    {
        newptr[i] = arr[i];
        i++;
    }
    newptr[i] = '0';
    newptr[i + 1] = '\0';
//    void *arra = (void*)arr;
//    ft_memdel(&arra);
    return (newptr);
}

void    *multiplication(char *arr, int num, int deg)
{
    int i;
    int j;
    char symb;
    char *newptr;

    i = ft_strlen(arr);
    newptr = ft_memalloc(ft_strlen(arr) + 2);
    ft_strcpy(newptr, arr);

    i = 0;
    while (i < num - 1)
    {
        j = 0;
        while (arr[j] != '\0')
        {
            symb = arr[j];
            newptr[j] += symb - '0';
            if (newptr[j] > '9')
            {
                if (newptr[j + 1] == '\0')
                    newptr[j + 1] = '0';
                newptr[j + 1]++;
                newptr[j] -= 10;
            }
            j++;
        }
        i++;
    }
    i = ft_strlen(newptr);
    if (ft_strlen(newptr) < deg)
        newptr = get_zero(newptr);
//    printf("newptr:%s\n", newptr);
    return (newptr);
}

//void    rounding(char *sp, t_struct *st) //округление
//{
//    int i;
//    int j;
//    int round;
//    char *arr;
//
//    j = 0;
//    i = ft_strlen(sp);
//    if (st->f_pres == 1)
//        round = st->wdth_pres;
//    else
//        round = 6;
//    if (round < i && sp[round] >= '5')
//    {
//        arr = ft_memalloc(round);
//        arr[j] = '1';
//        while (j < round - 1)
//        {
//            j++;
//            arr[j] = '0';
//        }
//        sp = sum_reverse(sp, arr);
//    }
//    j = 0;
//    while (j < round && j < i)
//    {
//        ft_putchar(sp[j]);
//        j++;
//    }
//}

//void    ft_out(char *fp, char *sp, t_struct *st)
//{
//    int i;
//
//    i = 0;
//    while (fp[i] == '0')
//        i++;
//    while (fp[i] != '\0')
//    {
//        ft_putchar(fp[i]);
//        i++;
//    }
//    ft_putchar('.');
//    rounding(sp, st);
//}

int exp_shift(t_sun eeei)
{
    int a;

    a = eeei.v.exp - SIZE_E;
    return (a);
}

int     check_zero_inf(t_sun eeei, t_struct *st)
{
    int i;

    i = 0;
    if (eeei.v.exp == 0 && eeei.v.mant == 0)
    {
        if (st->sign_bit == 1)
            st->schet = st->schet + re_putchar('-');
        st->schet = st->schet + re_putchar('0');
        if (st->round != 0 || st->f_resh != 0)
            st->schet = st->schet + re_putchar('.');
        while (i < st->round)
        {
            st->schet = st->schet + re_putchar('0');
            i++;
        }
        return (1);
    }
    if (eeei.v.exp == 2047)
    {
        if (st->sign_bit == 1)
            st->schet = st->schet + re_putchar('-');
        st->schet = st->schet + re_putstr("inf");
        return (1);
    }
    return (0);
}

int temp = 40;
void    after_point(t_sun eeei, t_struct *st)
{
//    char *sp;
//    int size;
    char *arr;
    int count;
    int c;
    int b;

//    size = 8;
    arr = ft_memalloc(2);
//    sp = ft_memalloc(size);
//    sp = ft_realloc(sp, size);
    arr[0] = '1';
//    printf("sp:%s\n", sp);
    count = 0;
    for (c = (SIZE_M - st->shift - 1); c >= 0; c--)
    {
        count++;
        eeei.v.mant & (1L << c) ? (b = 1) : (b = 0);
        if (c > SIZE_M)
        {
            arr = multiplication(arr, 5, count);
            continue;
        }
        arr = multiplication(arr, 5, count);
        if (c == SIZE_M)
            sum_reverse(st->sp, arr, st);
        if (b == 1)
        {
            sum_reverse(st->sp, arr, st);
//            printf("sp:%s arr:%s c:%d %d %d\n", st->sp, arr, c, ft_strlen(st->sp), ft_strlen(arr));
        }
    }
    ft_memdel(&arr);
}

void    init_chars(t_struct *st)
{
    st->sp = ft_memalloc(st->size);
    st->sp = ft_realloc(st->sp, st->size);
    st->fp = ft_memalloc(st->size);
    st->fp = ft_realloc(st->fp, st->size);
    st->f_zero = 0;
    st->neg_round = 0;
    st->sign_bit = 0;
    if (st->f_pres == 1)        //надо записать round в структуру
        st->round = st->wdth_pres;  //и удалить такую же операцию  в roundation
    else
        st->round = 6;
}

void    bit_parcer(double f, t_struct *st)
{
    t_sun eeei;
    int c;
    int b;
    char *arr;

    st->size = 8;
    eeei.f = f;
    init_chars(st);
    if (eeei.v.sign == 1)
        st->sign_bit = 1;
    c = check_zero_inf(eeei, st);
    if (c == 1)
        return;
    arr = ft_memalloc(1);
    arr[0] = '1';
    arr[1] = '\0';
    st->shift = exp_shift(eeei);
    if (st->shift >= 0)
    {
        for (c = (SIZE_M - st->shift); c < SIZE_M; c++)
        {
            if (c == (SIZE_M - st->shift))
            {
                eeei.v.mant & (1L << c) ? (b = 1) : (b = 0);
                if (b == 1 && c > 0)
                    st->fp = sum_char(st->fp, arr);
                continue ;
            }
            if (c < 0)
            {
                arr = two_degree(arr);
                continue ;
            }
            eeei.v.mant & (1L << c) ? (b = 1) : (b = 0);
            arr = two_degree(arr);
            if (b == 1)
                st->fp = sum_char(st->fp, arr);
        }
        if (st->shift != 0)
            arr = two_degree(arr);
        st->fp = sum_char(st->fp, arr);

        st->fp = get_char(st->fp);
        ft_memdel(&arr);
    }
    else
        st->f_zero = 1;

//    printf("%d_ %d_ %d  %.32f\n", eeei.v.sign, eeei.v.exp, eeei.v.mant, eeei.f);
//    printf("shift:%d\n", st->shift);
//    for (c = (SIZE_M - st->shift); c < SIZE_M; c++)
//        ft_putchar(eeei.v.mant & (1L << c) ? '1' : '0');
//    printf("\n");


    after_point(eeei, st);

    ft_out(st->fp, st->sp, st);

}



//int two_degree(char *arr, int deg)
//{
//    int i;
//    int len;
//    char *newptr;
//
//    i = 0;
//    if (arr[i] == '\0')
//        arr[i] = '1';
//    i = ft_strlen(arr);
//    len = i;
//    while (deg > 0)
//    {
//        i--;
//        tmp = arr[i];
//        arr[i] += tmp - '0';
//        if (arr[i] > '9' && i == 0)
//        {
//            newptr = ft_strnew(len + 1);
//            fp[i]-= 10;
//            fp[i - 1]++;
//        }
//    }
//}


//for (c = (SIZE_M - st->shift); c < SIZE_M; c++)
//{
//if (c == (SIZE_M - st->shift))
//{
//eeei.v.mant & (1L << c) ? (b = 1) : (b = 0);
//if (b == 1)
//st->fp = sum_char(st->fp, arr);
//continue ;
//}
//if (c < 0)
//{
//arr = sum_char(arr, arr);
//continue ;
//}
//eeei.v.mant & (1L << c) ? (b = 1) : (b = 0);
//arr = sum_char(arr, arr);
//if (b == 1)
//st->fp = sum_char(st->fp, arr);
//}
//if (st->shift != 0)
//arr = sum_char(arr, arr);
//st->fp = sum_char(st->fp, arr);