/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verteces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:27:15 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/06 12:07:02 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "ft_dynarr.h"

#include <math.h>
#include <stddef.h>

t_verteces	*verts_new(size_t	size)
{
	return ((t_verteces *)dynarr_new(size, sizeof(t_vertex)));
}

static int	_vertex_invalid(t_vertex v)
{
	size_t	i;

	i = 0;
	while (i < 4)
		if (isnanf(v.v.elements[i]) || isinff(v.v.elements[i++]))
			return (1);
	return (0);
}

// Returns 0 on success
int	verts_push(t_verteces *v, t_vertex	new)
{
	if (_vertex_invalid(new))
		return (1);
	return (v->attr.size == dynarr_pushback(&v->attr, &new));
}

// Coordinates of vertex set to NaN if failed
t_vertex	verts_get(t_verteces *v, size_t idx)
{
	t_vertex	*p_res;
	t_vertex	res;
	size_t		i;
	float		nan;

	p_res = dynarr_at(&v->attr, idx);
	if (p_res)
		return (*p_res);
	i = 0;
	nan = nanf("");
	while (i < 4)
		res.v.elements[i++] = nan;
	return (res);
}

void	verts_set(t_verteces *v, size_t idx, t_vertex new)
{
	t_vertex	*dest;

	dest = (t_vertex *) dynarr_at(&v->attr, idx);
	if (!dest)
		return ;
	*dest = new;
}
