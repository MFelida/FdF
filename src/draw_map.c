/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:43:30 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/05 20:07:07 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_types.h"
#include "MLX42/MLX42.h"
#include "matrix.h"
#include "vector.h"
#include <stddef.h>

static void	_transform_map(t_model *m)
{
	size_t		i;
	t_vertex	v;

	m->view.transform = m->view.rotate;
	m->view.transform = mat4_multiply(m->view.transform, m->view.scale);
	m->view.transform = mat4_multiply(m->view.transform, m->view.translate);
	i = 0;
	while (i < m->verts->size)
	{
		v = verts_get(m->verts, i);
		v.v = vec4_transform(m->view.transform, v.v);
		v.v = vec4_scale(v.v, 1.0f / v.v.w);
		verts_set(m->view.verts, i, v);
		i++;
	}
	m->view.update = 0;
}

void	draw_map(mlx_image_t *image, t_model *m)
{
	size_t	i;
	t_edge	e;

	i = 0;
	if (m->view.update)
		_transform_map(m);
	while (i < m->edges->size)
	{
		e = edges_get(m->edges, i);
		draw_line(image,
			verts_get(m->view.verts, e.start),
			verts_get(m->view.verts, e.end));
		i++;
	}
}
