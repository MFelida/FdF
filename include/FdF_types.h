/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:26:11 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/04 13:53:48 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_TYPES_H
# define FDF_TYPES_H

# include "ft_dynarr.h"
# include "vector.h"
# include "matrix.h"
# include "check_endian.h"

# include <stdint.h>

typedef t_dynarr	t_verteces;

# if IS_LITTLE_ENDIAN

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
# else

typedef struct u_vertex
{
	t_vec4	v;
	union
	{
		int32_t	c;
		struct
		{
			uint8_t	r;
			uint8_t	g;
			uint8_t	b;
			uint8_t	a;
		};
	};
}	t_vertex;
# endif

typedef t_dynarr	t_edges;

typedef struct s_edge
{
	size_t	start;
	size_t	end;
}	t_edge;

typedef struct u_model
{
	t_verteces	*verts;
	t_edges		*edges;
	size_t		width;
	size_t		height;
	struct s_mat
	{
		t_mat4		rotate;
		t_mat4		scale;
		t_mat4		translate;
		t_mat4		transform;
		int			update_matrix;
	}	t;
}	t_model;
#endif // !FDF_TYPES_H
