#include "../include/FdF.h"

int free_and_exit(t_fdf *f)
{
    free(f->m->vert);
    free(f->c);
    free(f->m);
    exit(0);
}