/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:55:08 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/13 14:33:47 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_settings.h"
#include "FdF_types.h"
#include "MLX42/MLX42.h"
#include "vector.h"

#include <math.h>
#include <stddef.h>
#include <stdint.h>

static void	_clear_z(float z[WINDOW_WIDTH][WINDOW_HEIGHT])
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		i = 0;
		while (i < WINDOW_WIDTH)
			z[i++][j] = -INFINITY;
		j++;
	}
}

float	clamp_hue(float hue)
{
	if (isnanf(hue) || isinff(hue))
		return (hue);
	while (hue < 0)
		hue += 360;
	while (hue > 360)
		hue -= 260;
	return (hue);
}

uint32_t	interpolate_color(const t_vertex *a, const t_vertex *b,
						const t_vec2 *t_d)
{
	float	total_length;
	float	curr_length;
	t_hsv	hsv_a;
	t_hsv	hsv_b;
	t_hsv	diff;

	total_length = vec2_length(*t_d);
	curr_length = vec2_length(vec2_add(b->v.xy, vec2_scale(a->v.xy, -1)));
	hsv_a = rgb_to_hsv(a->r, a->g, a->b);
	hsv_b = rgb_to_hsv(b->r, b->g, b->b);
	if (hsv_a.val == 0 || hsv_a.sat == 0)
		hsv_a.hue = hsv_b.hue;
	if (hsv_b.val == 0 || hsv_b.sat == 0)
		hsv_b.hue = hsv_a.hue;
	diff.v = vec3_add(hsv_b.v, vec3_scale(hsv_a.v, -1));
	if (diff.hue > 180)
		diff.hue -= 360;
	else if (diff.hue < -180)
		diff.hue += 360;
	hsv_a.v = vec3_add(hsv_a.v,
			vec3_scale(diff.v, 1 - (curr_length / total_length)));
	return (hsv_to_rgb(hsv_a));
}

void	fdf_put_pixel(mlx_image_t *image, const t_vec3 *v, uint32_t c)
{
	static float	z[WINDOW_WIDTH][WINDOW_HEIGHT];
	t_vec2			u;

	if (!image)
	{
		_clear_z(z);
		return ;
	}
	u.x = roundf(v->x) + WINDOW_WIDTH / 2.0f;
	u.y = roundf(v->y) + WINDOW_HEIGHT / 2.0f;
	if (u.x < 0 || u.x >= WINDOW_WIDTH || u.y < 0 || u.y >= WINDOW_HEIGHT
		|| z[(size_t) u.x][(size_t) u.y] > v->z)
		return ;
	mlx_put_pixel(image, u.x, u.y, c);
	z[(size_t) u.x][(size_t) u.y] = v->z;
}
