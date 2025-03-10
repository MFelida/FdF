/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:53:24 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/10 21:15:08 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_types.h"
#include "libft.h"

#include <math.h>

#define WHITE	0XFFFFFFFF

static char	*_to_lower(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		s[i] = ft_tolower(s[i]);
		i++;
	}
	return (s);
}

uint32_t	get_color(char *s)
{
	if (ft_strnstr(s, "0x", ft_strlen(s)))
		return (ft_atoi_base(ft_strchr(_to_lower(s), 'x') + 1,
				"0123456789abcdef") << 8 | 0xFF);
	return (WHITE);
}

static t_vec3	_hsv_to_vec3(float r, float g, float b)
{
	t_vec3	res;

	res.elements[0] = r;
	res.elements[1] = g;
	res.elements[2] = b;
	return (res);
}

static	uint32_t	_vec3_to_rgb(t_vec3	v, float m)
{
	uint32_t	res;

	v.elements[0] += m;
	v.elements[1] += m;
	v.elements[2] += m;
	res = 0xFF;
	res |= ((uint8_t)(roundf(v.elements[0] * 255))) << 24;
	res |= ((uint8_t)(roundf(v.elements[1] * 255))) << 16;
	res |= ((uint8_t)(roundf(v.elements[2] * 255))) << 8;
	return (res);
}

uint32_t	hsv_to_rgb(t_hsv hsv)
{
	float		c;
	float		x;
	float		m;
	t_vec3		res;

	c = hsv.sat * hsv.val;
	hsv.hue = clamp_hue(hsv.hue);
	hsv.hue /= 60;
	x = c * (1 - fabsf(fmodf(hsv.hue, 2) - 1));
	m = hsv.val - c;
	if (hsv.hue < 1)
		res = _hsv_to_vec3(c, x, 0);
	else if (hsv.hue < 2)
		res = _hsv_to_vec3(x, c, 0);
	else if (hsv.hue < 3)
		res = _hsv_to_vec3(0, c, x);
	else if (hsv.hue < 4)
		res = _hsv_to_vec3(0, x, c);
	else if (hsv.hue < 5)
		res = _hsv_to_vec3(x, 0, c);
	else if (hsv.hue < 6)
		res = _hsv_to_vec3(c, 0, x);
	else
		res = (_hsv_to_vec3(0, 0, 0));
	return (_vec3_to_rgb(res, m));
}
