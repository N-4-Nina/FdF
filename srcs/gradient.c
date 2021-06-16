#include "../include/FdF.h"

double  percent(int start, int end, int current)
{
    double  placement;
    double  distance;


    placement = current - start;
    distance = end - start;

    if (distance == 0)
        return(1.0);
    else
        return (placement/distance);
}

int get_light(int start, int end, double percentage)
{
    return ((int)(1- percentage) * start + percentage * end);
}

int set_point_color(int bottom, int top, int point)
{
    double  percentage;

    percentage = percent(bottom, top, point);

    if (percentage < 0.1)
        return (COL_ONE);
    else if (percentage < 0.2)
        return (COL_TWO);
    else if (percentage < 0.3)
        return (COL_THR);
    else if (percentage < 0.4)
        return (COL_FOU);
    else if (percentage < 0.5)
        return (COL_FIV);
    else if (percentage < 0.6)
        return (COL_SIX);
    else if (percentage < 0.7)
        return (COL_SEV);
    else if (percentage < 0.8)
        return (COL_EIG);
    else if (percentage < 0.9)
        return (COL_NIN);
    else
        return (COL_TEN);
}

int get_color(t_vert start, t_vert end, t_vert current, t_point delta)
{
    int     rgb[3];
    double  percentage;

    if (current.color == end.color)
        return(start.color);
    if (delta.x > delta.y)
        percentage = percent(start.p.x, end.p.x, current.p.x);
    else
        percentage = percent(start.p.y, end.p.y, current.p.y);

    rgb[0] = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
    rgb[1] = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
    rgb[2] = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
    return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
    
}