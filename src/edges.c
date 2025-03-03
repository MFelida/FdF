/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:44:52 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/03 22:18:19 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "ft_dynarr.h"
#include <stddef.h>

t_edges	*edges_new(size_t size)
{
	return (dynarr_new(size, sizeof(t_edge)));
}

// Return 0 on success
int	edges_push(t_edges *e, t_edge new)
{
	if (new.start == new.end)
		return (1);
	return (e->size == dynarr_pushback(e, &new));
}

// Start and end equal if failed
t_edge	edges_get(t_edges *e, size_t idx)
{
	t_edge	*p_res;
	t_edge	res;

	p_res = dynarr_at(e, idx);
	if (p_res)
		return (*p_res);
	res.end = res.start;
	return (res);
}
