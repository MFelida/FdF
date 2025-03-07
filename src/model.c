/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:08:55 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/07 12:12:52 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "ft_dynarr.h"
#include "libft.h"
#include "matrix.h"

#include <stdlib.h>

#define DEFAULT_SIZE 1024

t_model	*model_new( void )
{
	t_model	*m;

	m = ft_calloc(1, sizeof(t_model));
	if (!m)
		return (NULL);
	m->edges = edges_new(DEFAULT_SIZE);
	m->verts = verts_new(DEFAULT_SIZE);
	if (!m->verts || !m->edges)
		return (model_free(&m), NULL);
	m->view.verts = NULL;
	m->width = 0;
	m->height = 0;
	m->view.update = 1;
	m->view.rotate = mat4_identity();
	m->view.scale = mat4_identity();
	m->view.translate = mat4_identity();
	return (m);
}

void	model_free(t_model **m)
{
	if (!*m)
		return ;
	if ((*m)->verts && (*m)->verts->attr.me)
		(*m)->verts = dynarr_free((*m)->verts->attr.me);
	if ((*m)->edges && (*m)->edges->attr.me)
		(*m)->edges = dynarr_free((*m)->edges->attr.me);
	if ((*m)->view.verts)
		dynarr_free(&(*m)->view.verts->attr);
	free(*m);
	*m = NULL;
}
