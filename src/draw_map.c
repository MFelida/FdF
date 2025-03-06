/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:43:30 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/06 16:36:33 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_types.h"
#include "FdF_settings.h"
#include "MLX42/MLX42.h"
#include "matrix.h"
#include "vector.h"
#include <math.h>
#include <stddef.h>

static void	_transform_map(t_model *m)
{
	size_t		i;
	t_vertex	v;

	m->view.transform = m->view.rotate;
	m->view.transform = mat4_multiply(m->view.scale, m->view.transform);
	m->view.transform = mat4_multiply(m->view.translate, m->view.transform);
	i = 0;
	while (i < m->verts->attr.size)
	{
		v = verts_get(m->verts, i);
		v.v = vec4_transform(m->view.transform, v.v);
		v.v = vec4_scale(v.v, 1.0f / v.v.w);
		verts_set(m->view.verts, i, v);
		i++;
	}
	m->view.update = 0;
}

static t_vec4	_find_map_minmax(t_model *m)
{
	t_vec4		minmax;
	size_t		i;
	t_vec2	v;

	minmax.x = INFINITY;
	minmax.y = INFINITY;
	minmax.z = -INFINITY;
	minmax.w = -INFINITY;
	i = 0;
	while (i < m->verts->attr.size)
	{
		v = m->view.verts->data[i].v.xy;
		if (v.x < minmax.elements[0])
			minmax.elements[0] = v.x;
		if (v.x > minmax.elements[2])
			minmax.elements[2] = v.x;
		if (v.y < minmax.elements[1])
			minmax.elements[1]= v.y;
		if (v.y > minmax.elements[3])
			minmax.elements[3] = v.y;
		i++;
	}
	return (minmax);
}

void	center_map(t_model *m)
{
	t_vec2	minmax[2];
	t_vec4	*mm4;
	float	scale;

	mm4 = (t_vec4 *) minmax;
	_transform_map(m);
	*mm4 = _find_map_minmax(m);
	scale = fminf(((float) WINDOW_WIDTH - 20) / (minmax[1].x - minmax[0].x),
			((float) WINDOW_HEIGHT - 20) / (minmax[1].y - minmax[0].y));
	m->view.scale = mat4_scale(scale, scale, scale, 1);
	m->view.translate = mat4_translate(minmax[0].x * -scale + 10,
									minmax[0].y * -scale + 10, 0);
	m->view.update = 1;
}

void	draw_map(mlx_image_t *image, t_model *m)
{
	size_t	i;
	t_edge	e;

	i = 0;
	if (m->view.update)
		_transform_map(m);
	while (i < m->edges->attr.size)
	{
		e = edges_get(m->edges, i);
		draw_line(image,
			m->view.verts->data[e.start],
			m->view.verts->data[e.end]);
		i++;
	}
}
