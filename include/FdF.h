/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:14:16 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/03 21:27:05 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "ft_dynarr.h"
# include "vector.h"
# include "check_endian.h"

# include <stddef.h>
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
}	t_model;

t_model	*model_new( void );
void	model_free(t_model *m);
	
t_verteces	*verts_new(size_t size);
int			verts_push(t_verteces *e, t_vertex new);
t_vertex	verts_get(t_verteces *e, size_t idx);

t_edges		*edges_new(size_t size);
int			edges_push(t_edges *e, t_edge new);
t_edge		edges_get(t_edges *e, size_t idx);

#endif	// FDF_H
