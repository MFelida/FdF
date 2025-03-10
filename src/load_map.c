/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:57:53 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/10 21:37:13 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_types.h"
#include "ft_dynarr.h"
#include "libft.h"
#include "matrix.h"

#include <ctype.h>
#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

static size_t	_add_row(t_model *m, char *line)
{
	char		**line_split;
	size_t		i;
	t_vertex	new;

	if (!line)
		return (0);
	line_split = ft_split(line, ' ');
	if (!line_split)
		return (0);
	i = 0;
	new.v.y = m->height * 10;
	new.v.w = 1;
	while (line_split[i])
	{
		new.v.x = i * 10;
		new.v.z = ft_atoi(line_split[i]);
		new.c = get_color(line_split[i]);
		if (verts_push(m->verts, new))
			return (ft_split_free(line_split), 0);
		i++;
	}
	m->height++;
	return (ft_split_free(line_split), i);
}

static int	_load_verteces(t_model *m, int fd)
{
	char	*line;
	char	*trimmed;

	line = ft_gnl(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, "\n");
		if (!trimmed)
			return (free(line), 1);
		free(line);
		if (m->height == 0)
			m->width = _add_row(m, trimmed);
		else if (m->width == 0 || m->width != _add_row(m, trimmed))
			return (free(trimmed), 1);
		free(trimmed);
		if (m->width == 0)
			return (1);
		line = ft_gnl(fd);
	}
	return (0);
}

static int	_get_edges(t_model *m)
{
	size_t	i;
	t_edge	e;

	i = 0;
	while (i < m->verts->attr.size)
	{
		if (i % m->width < m->width - 1)
		{
			e.start = i;
			e.end = i + 1;
			if (edges_push(m->edges, e))
				return (1);
		}
		if (i / m->width < m->height - 1)
		{
			e.start = i;
			e.end = i + m->width;
			if (edges_push(m->edges, e))
				return (1);
		}
		i++;
	}
	return (0);
}

int	load_map(t_model **m, char *file)
{
	int	fd;

	*m = model_new();
	if (!*m)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (model_free(m), 1);
	if (_load_verteces(*m, fd))
		return (close(fd), model_free(m), 1);
	close(fd);
	if (_get_edges(*m))
		return (model_free(m), 1);
	(*m)->view.verts = (t_verteces *) dynarr_copy(&(*m)->verts->attr);
	if (!(*m)->view.verts)
		return (model_free(m), 1);
	center_map(*m);
	return (0);
}
