#include "../include/FdF.h"

void    update(t_fdf *f)
{
    if (f->key[LTURN])
        f->c->rot[0] -= 0.0174533;
    if (f->key[RTURN])
        f->c->rot[0] += 0.0174533;
}