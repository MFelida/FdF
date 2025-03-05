/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:57:53 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/05 13:41:38 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_types.h"
#include "libft.h"

#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#define WHITE	0XFFFFFFFF

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
	new.v.y = m->height;
	new.v.w = 1;
	while (line_split[i])
	{
		new.c = WHITE;
		new.v.x = i;
		new.v.z = ft_atoi(line_split[i]);
		if (ft_strnstr(line_split[i], "0x", ft_strlen(line_split[i])))
			new.c = ft_atoi_base(ft_strchr(line_split[i], 'x') + 1,
					"0123456789abcdef");
		verts_push(m->verts, new);
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
		trimmed = ft_strtrim(line, "\n ");
		if (!trimmed)
			return (free(line), 1);
		free(line);
		if (m->width == 0)
			m->width = _add_row(m, trimmed);
		else if (m->width != _add_row(m, trimmed))
			return (free(trimmed), 1);
		free(trimmed);
		line = ft_gnl(fd);
	}
	return (0);
}

static int	_get_edges(t_model *m)
{
	size_t	i;
	t_edge	e;

	i = 0;
	while (i < m->verts->size)
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
			e.start = 1;
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
	return (0);
}
