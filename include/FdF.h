/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:14:16 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/10 21:15:51 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "FdF_types.h"
# include "MLX42/MLX42.h"

# include <stddef.h>
# include <stdint.h>

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_model		*m;
	mlx_image_t	*image;
}	t_fdf;

t_model		*model_new( void );
void		model_free(t_model **m);

uint32_t	get_color(char *s);
int			load_map(t_model **m, char *file);

void		center_map(t_model *m);
void		draw_map(mlx_image_t *image, t_model *m);

void		draw_line(mlx_image_t *image, t_vertex a, t_vertex b);
void		fdf_put_pixel(mlx_image_t *image, const t_vec3 *v,
				uint32_t c);
t_hsv		rgb_to_hsv(float r, float g, float b);
uint32_t	hsv_to_rgb(t_hsv hsv);
float		clamp_hue(float hue);
uint32_t	interpolate_color(const t_vertex *a, const t_vertex *b,
				const t_vec2 *t_d);

t_verteces	*verts_new(size_t size);
int			verts_push(t_verteces *e, t_vertex new);
t_vertex	verts_get(t_verteces *e, size_t idx);
void		verts_set(t_verteces *v, size_t idx, t_vertex new);

t_edges		*edges_new(size_t size);
int			edges_push(t_edges *e, t_edge new);
t_edge		edges_get(t_edges *e, size_t idx);
void		edges_set(t_edges *e, size_t idx, t_edge new);

#endif	// FDF_H
