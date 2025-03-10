/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:21:10 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/09 23:15:22 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_settings.h"
#include "FdF_types.h"
#include "MLX42/MLX42.h"
#include "libft.h"
#include "matrix.h"
#include "vector_utils.h"

#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void	loop_callback(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	ft_bzero(fdf->image->pixels,
		fdf->image->width * fdf->image->height * sizeof(uint32_t));
	draw_map(fdf->image, fdf->m);
}

int	main(int argc, char *argv[])
{
	t_fdf	fdf;

	if (argc != 2 || load_map(&fdf.m, argv[1]))
		return (EXIT_FAILURE);
	fdf.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	if (!fdf.mlx)
		return (model_free(&fdf.m), EXIT_FAILURE);
	fdf.image = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!fdf.image)
		return (model_free(&fdf.m), mlx_terminate(fdf.mlx), EXIT_FAILURE);
	mlx_image_to_window(fdf.mlx, fdf.image, 0, 0);
	draw_map(fdf.image, fdf.m);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	model_free(&fdf.m);
	return (EXIT_SUCCESS);
}
