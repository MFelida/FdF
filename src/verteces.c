/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verteces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:27:15 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/03 22:37:34 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "ft_dynarr.h"

#include <stddef.h>
#include <math.h>

t_verteces	*verts_new(size_t	size)
{
	return (dynarr_new(size, sizeof(t_vertex)));
}

static int	_vertex_invalid(t_vertex v)
{
	size_t	i;

	i = 0;
	while (i < (sizeof(v.v) / sizeof(v.v.x)))
		if (isnanf(v.v.elements[i++]))
			return (1);
	return (0);
}

// Returns 0 on success
int	verts_push(t_verteces *v, t_vertex	new)
{
	if (_vertex_invalid(new))
		return (1);
	return (v->size == dynarr_pushback(v, &new));
}

// Coordinates of vertex set to NaN if failed
t_vertex	verts_get(t_verteces *v, size_t idx)
{
	t_vertex	*p_res;
	t_vertex	res;
	size_t		i;
	float		nan;

	p_res = dynarr_at(v, idx);
	if (p_res)
		return (*p_res);
	i = 0;
	nan = nanf("");
	while (i < (sizeof(res.v) / sizeof(res.v.x)))
		res.v.elements[i++] = nan;
	return (res);
}

void	verts_set(t_verteces *v, size_t idx, t_vertex new)
{
	t_vertex	*dest;

	dest = (t_vertex *) dynarr_at(v, idx);
	if (!dest)
		return ;
	*dest = new;
}
