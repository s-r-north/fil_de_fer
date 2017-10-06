/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:47:49 by snorth            #+#    #+#             */
/*   Updated: 2017/08/11 19:58:06 by snorth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	numswap(t_xy *xy)
{
	float	tmp;

	tmp = xy->x1;
	xy->x1 = xy->x2;
	xy->x2 = tmp;
	tmp = xy->y1;
	xy->y1 = xy->y2;
	xy->y2 = tmp;
}

void	slope_calc(t_xy *xy, t_env *env, int xy1, int xy2)
{
	xy->x1 = env->point[xy1]->image->x;
	xy->x2 = env->point[xy2]->image->x;
	xy->y1 = env->point[xy1]->image->y;
	xy->y2 = env->point[xy2]->image->y;
	xy->dx = xy->x2 - xy->x1;
	xy->dy = xy->y2 - xy->y1;
	xy->slope = fabsf(xy->dy) > fabsf(xy->dx) ? xy->dx / xy->dy :
			xy->dy / xy->dx;
	if (xy->dx < 0 && xy->dy < 0 && xy->slope >= 0)
		numswap(xy);
	if (xy->slope < 0)
	{
		if (fabsf(xy->dy) <= fabsf(xy->dx) && xy->dx < 0)
			numswap(xy);
		if (fabsf(xy->dy) > fabsf(xy->dx) && xy->dy < 0)
			numswap(xy);
	}
}

void	negative_slope(t_xy *xy, t_env *env, int steep)
{
	if (steep)
	{
		while (xy->x1 >= xy->x2 && xy->y1 <= xy->y2)
		{
			if (xy->x1 >= 0 && xy->y1 >= 0 && xy->x1 < WIN_X && xy->y1 < WIN_Y
					&& (int)(xy->x1) + ((int)(xy->y1) * WIN_X) <
					WIN_X * WIN_Y - 1)
				env->data[(int)xy->x1 + ((int)xy->y1 * WIN_X)] = env->color;
			xy->x1 += fabsf(xy->dy) > fabsf(xy->dx) ? xy->slope : 1;
			xy->y1 += fabsf(xy->dy) > fabsf(xy->dx) ? 1 : xy->slope;
		}
	}
	else
	{
		while (xy->x1 <= xy->x2 && xy->y1 >= xy->y2)
		{
			if (xy->x1 >= 0 && xy->y1 >= 0 && xy->x1 < WIN_X && xy->y1 < WIN_Y
					&& (int)(xy->x1) + ((int)(xy->y1) * WIN_X) <
					WIN_X * WIN_Y - 1)
				env->data[(int)xy->x1 + ((int)xy->y1 * WIN_X)] = env->color;
			xy->x1 += fabsf(xy->dy) > fabsf(xy->dx) ? xy->slope : 1;
			xy->y1 += fabsf(xy->dy) > fabsf(xy->dx) ? 1 : xy->slope;
		}
	}
}

void	positive_slope(t_xy *xy, t_env *env)
{
	while (xy->x1 <= xy->x2 && xy->y1 <= xy->y2)
	{
		if (xy->x1 >= 0 && xy->y1 >= 0 && xy->x1 < WIN_X && xy->y1 < WIN_Y &&
				(int)(xy->x1) + ((int)(xy->y1) * WIN_X) < WIN_X * WIN_Y - 1)
			env->data[(int)xy->x1 + ((int)xy->y1 * WIN_X)] = env->color;
		xy->x1 += fabsf(xy->dy) > fabsf(xy->dx) ? xy->slope : 1;
		xy->y1 += fabsf(xy->dy) > fabsf(xy->dx) ? 1 : xy->slope;
	}
}

void	line_draw(t_env *env, int x, int y)
{
	t_xy	xy;

	if (x < (env->map_x) - 1)
	{
		slope_calc(&xy, env, x + (env->map_x * y), x + 1 + (env->map_x * y));
		if (xy.slope < 0)
			negative_slope(&xy, env, (fabsf(xy.dy) > fabsf(xy.dx)));
		else if (xy.slope >= 0)
			positive_slope(&xy, env);
	}
	if (y < (env->map_y) - 1)
	{
		slope_calc(&xy, env, x + (env->map_x * y), x + (env->map_x * (y + 1)));
		if (xy.slope < 0)
			negative_slope(&xy, env, (fabsf(xy.dy) > fabsf(xy.dx)));
		else if (xy.slope >= 0)
			positive_slope(&xy, env);
	}
}
