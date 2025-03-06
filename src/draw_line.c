/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:07:43 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/05 18:40:01 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF_types.h"
#include "MLX42/MLX42.h"
#include "vector.h"

#include <math.h>

static void	_draw_line_flat(mlx_image_t *image, t_vertex a, t_vertex b)
{
	t_vec2	d;
	float	yi;
	float	big_d;

	d = vec2_add(b.v.xy, vec2_scale(a.v.xy, -1));
	yi = 1;
	if (d.y < 0)
	{
		yi = -1;
		d.y *= -1;
	}
	big_d = 2 * d.y - d.x;
	while (a.v.x <= b.v.x)
	{
		mlx_put_pixel(image, a.v.x, a.v.y, a.c);
		if (big_d > 0)
		{
			a.v.y += yi;
			big_d += 2 * (d.y - d.x);
		}
		else
			big_d += 2 * d.y;
		a.v.x += 1;
	}
}

static void	_draw_line_steep(mlx_image_t *image, t_vertex a, t_vertex b)
{
	t_vec2	d;
	float	xi;
	float	big_d;

	d = vec2_add(b.v.xy, vec2_scale(a.v.xy, -1));
	xi = 1;
	if (d.x < 0)
	{
		xi = -1;
		d.x *= -1;
	}
	big_d = 2 * d.x - d.y;
	while (a.v.y <= b.v.y)
	{
		mlx_put_pixel(image, a.v.x, a.v.y, a.c);
		if (big_d > 0)
		{
			a.v.x += xi;
			big_d += 2 * (d.x - d.y);
		}
		else
			big_d += 2 * d.x;
		a.v.y += 1;
	}
}

static void	_draw_line_horizontal(mlx_image_t *image, t_vertex a, t_vertex b)
{
	int	dx;

	dx = 1;
	if (a.v.x > b.v.x)
		dx = -1;
	while ((dx == 1 && a.v.x <= b.v.x) || (dx == -1 && a.v.x >= b.v.x))
	{
		mlx_put_pixel(image, a.v.x, a.v.y, a.c);
		a.v.x += dx;
	}
}

static void	_draw_line_vertical(mlx_image_t *image, t_vertex a, t_vertex b)
{
	int	dy;

	dy = 1;
	if (a.v.y > b.v.y)
		dy = -1;
	while ((dy == 1 && a.v.y <= b.v.y) || (dy == -1 && a.v.y >= b.v.y))
	{
		mlx_put_pixel(image, a.v.x, a.v.y, a.c);
		a.v.y += dy;
	}
}

void	draw_line(mlx_image_t *image, t_vertex a, t_vertex b)
{
	t_vec2	d;

	d = vec2_add(b.v.xy, vec2_scale(a.v.xy, -1));
	if (d.x == 0)
		_draw_line_vertical(image, a, b);
	else if (d.y == 0)
		_draw_line_horizontal(image, a, b);
	else if (fabsf(d.y) < fabsf(d.x))
	{
		if (a.v.x > b.v.x)
			_draw_line_flat(image, b, a);
		else
			_draw_line_flat(image, a, b);
	}
	else
	{
		if (a.v.y > b.v.y)
			_draw_line_steep(image, b, a);
		else
			_draw_line_steep(image, a, b);
	}
}
