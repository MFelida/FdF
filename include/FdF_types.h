/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:11 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/26 15:38:55 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_TYPES_H
# define FDF_TYPES_H

# include "ft_dynarr.h"
# include "vector.h"
# include "matrix.h"

# include <stdint.h>

typedef struct u_vertex
{
	t_vec4	v;
	union
	{
		int32_t	c;
		struct
		{
			uint8_t	a;
			uint8_t	b;
			uint8_t	g;
			uint8_t	r;
		};
	};
}	t_vertex;

typedef union u_verteces
{
	const t_vertex	*data;
	t_dynarr		attr;
}	t_verteces;

typedef struct s_edge
{
	size_t	start;
	size_t	end;
}	t_edge;

typedef union u_edges
{
	const t_edge	*data;
	t_dynarr		attr;
}	t_edges;

typedef struct s_view
{
	t_mat4		base;
	t_mat4		rotate;
	t_mat4		scale;
	t_mat4		translate;
	t_mat4		transform;
	int			update;
	t_verteces	*verts;
}	t_view;

typedef struct s_model
{
	t_verteces	*verts;
	t_edges		*edges;
	size_t		width;
	size_t		height;
	t_view		view;
}	t_model;

typedef union u_hsv
{
	struct
	{
		float	hue;
		float	sat;
		float	val;
	};
	t_vec3	v;
}	t_hsv;

#endif // !FDF_TYPES_H
