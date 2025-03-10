/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_hsv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:09:18 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/10 21:22:21 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

#include <math.h>

t_hsv	rgb_to_hsv(float r, float g, float b)
{
	t_hsv	res;
	float	c_max;
	float	c_min;
	float	delta;

	r = r / 255;
	g = g / 255;
	b = b / 255;
	c_max = fmaxf(r, fmaxf(g, b));
	c_min = fminf(r, fminf(g, b));
	delta = c_max - c_min;
	if (c_max == r)
		res.hue = 60 * fmodf(((g - b) / delta), 6);
	else if (c_max == g)
		res.hue = 60 * (((b - r) / delta) + 2);
	else if (c_max == b)
		res.hue = 60 * (((r - g) / delta) + 4);
	res.sat = 0;
	if (c_max != 0)
		res.sat = delta / c_max;
	res.val = c_max;
	return (res);
}
