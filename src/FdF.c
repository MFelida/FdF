/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:21:10 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/06 12:19:40 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_settings.h"
#include "FdF_types.h"
#include "MLX42/MLX42.h"
#include "libft.h"
#include "matrix.h"
#include "vector.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	t_model		*m;
	size_t		i;
	// mlx_t		*mlx;
	// mlx_image_t	*im;

	if (argc != 2 || load_map(&m, argv[1]))
		return (EXIT_FAILURE);
	// mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	// if (!mlx)
		// return (model_free(&m), mlx_terminate(mlx), EXIT_FAILURE);
	// im = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// if (!im)
		// return (model_free(&m), EXIT_FAILURE);
	m->view.scale = mat4_scale(50, 50, 50, 50);
	// mlx_image_to_window(mlx, im, 0, 0);
	// draw_map(im, m);
	i = 0;
	while (i < m->verts->attr.size)
	{
		ft_printf("%d", (int) m->verts->data[i++].v.z);
		if (i % m->width == 0)
			ft_putchar_fd('\n', STDOUT_FILENO);
		else
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	// free(im);
	model_free(&m);
	return (EXIT_SUCCESS);
}
