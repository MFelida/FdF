/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:14:16 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/04 13:53:56 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "FdF_types.h"

# include <stddef.h>
# include <stdint.h>

t_model		*model_new( void );
void		model_free(t_model *m);

int			load_map(t_model *m, int fd);

t_verteces	*verts_new(size_t size);
int			verts_push(t_verteces *e, t_vertex new);
t_vertex	verts_get(t_verteces *e, size_t idx);
void		verts_set(t_verteces *v, size_t idx, t_vertex new);

t_edges		*edges_new(size_t size);
int			edges_push(t_edges *e, t_edge new);
t_edge		edges_get(t_edges *e, size_t idx);
void		edges_set(t_edges *e, size_t idx, t_edge new);

#endif	// FDF_H
