/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:08:55 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/04 15:02:36 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "ft_dynarr.h"
#include "libft.h"

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
	m->width = 0;
	m->height = 0;
	return (m);
}

void	model_free(t_model **m)
{
	if (!*m)
		return ;
	if ((*m)->verts)
		dynarr_free(&(*m)->verts);
	if ((*m)->edges)
		dynarr_free(&(*m)->edges);
	free(*m);
	*m = NULL;
}
