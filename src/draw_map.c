/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:43:30 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/05 17:56:31 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_types.h"
#include "MLX42/MLX42.h"
#include <stddef.h>

void	draw_map(mlx_image_t *image, t_model *m)
{
	size_t	i;
	t_edge	e;

	i = 0;
	while (i < m->edges->size)
	{
		e = edges_get(m->edges, i);
		draw_line(image,
			verts_get(m->verts, e.start),
			verts_get(m->verts, e.end));
		i++;
	}
}
