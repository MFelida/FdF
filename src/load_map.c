/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:57:53 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/04 13:50:04 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "libft.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

size_t	_add_row(t_model *m, char *line)
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
	while (line_split[i])
	{
		new.v.x = i;
		new.v.z = ft_atoi(line_split[i]);
		if (ft_strnstr(line_split[i], "0x", ft_strlen(line_split[i])))
			new.c = ft_atoi_base(ft_strchr(line_split[i], 'x') + 1,
					"0123456789abcdef");
		else
			new.c = 0xFFFFFFFF;
		verts_push(m->verts, new);
		i++;
	}
	m->height++;
	return (i);
}

int	load_map(t_model *m, int fd)
{
	char	*line;

	line = ft_gnl(fd);
	while (line)
	{
		if (m->width == 0)
			m->width = _add_row(m, line);
		else if (m->width != _add_row(m, line))
			return (free(line), 1);
		free(line);
		line = ft_gnl(fd);
	}
	return (0);
}
