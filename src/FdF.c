/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:21:10 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/13 14:34:00 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include "FdF_settings.h"
#include "MLX42/MLX42.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void	esc_close(mlx_key_data_t key_data, void *fdf_data)
{
	t_fdf	*fdf;

	if (key_data.action == MLX_RELEASE && key_data.key == MLX_KEY_ESCAPE)
	{
		fdf = fdf_data;
		mlx_close_window(fdf->mlx);
	}
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
	mlx_key_hook(fdf.mlx, esc_close, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	model_free(&fdf.m);
	return (EXIT_SUCCESS);
}
