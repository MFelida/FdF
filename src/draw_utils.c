/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:55:08 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/07 19:18:55 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_settings.h"
#include "MLX42/MLX42.h"
#include "libft.h"
#include "vector.h"

#include <math.h>
#include <stddef.h>
#include <stdint.h>

void	fdf_put_pixel(mlx_image_t *image, const t_vec3 *v, uint32_t c)
{
	static float	z[WINDOW_WIDTH][WINDOW_HEIGHT] = {{-INFINITY}};
	t_vec2			u;
	size_t			i;
	size_t			j;

	if (!image)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			i = 0;
			while (i < WINDOW_WIDTH)
				z[i++][j] = -INFINITY;
			j++;
		}
	}
	u.x = roundf(v->x) + WINDOW_WIDTH / 2;
	u.y = roundf(v->y) + WINDOW_HEIGHT / 2;
	if (u.x < 0 || u.x >= WINDOW_WIDTH || u.y < 0 || u.y >= WINDOW_HEIGHT
		|| z[(size_t) u.x][(size_t) u.y] > v->z)
		return ;
	mlx_put_pixel(image, u.x, u.y, c);
	z[(size_t) u.x][(size_t) u.y] = v->z;
}
