/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:28:49 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/24 16:30:04 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

// floor/ceiling: precomputed color of the row, then vignette
static void	fill_column(t_data *data, int x, int start, int end)
{
	t_img			*img;
	unsigned int	c;
	int				k;

	img = data->mlx->img[BACKGROUND];
	while (start < end)
	{
		c = data->amb.bg[start];
		k = data->amb.vig_x[x] * data->amb.vig_y[start] >> 8;
		*(unsigned int *)(img->addr + start * img->line_len
				+ x * (img->bpp / 8)) = (((c >> 16 & 0xFF) * k >> 8) << 16)
			| (((c >> 8 & 0xFF) * k >> 8) << 8) | ((c & 0xFF) * k >> 8);
		start++;
	}
}

void	draw_background_column(t_data *data, int x)
{
	fill_column(data, x, 0, data->raycast->draw_start);
	fill_column(data, x, data->raycast->draw_end, HEIGHT);
}

// darkens the screen edges, x256 factors (separable: vig_x * vig_y)
void	init_vignette(t_data *data)
{
	double	n;
	int		i;

	i = -1;
	while (++i < WIDTH)
	{
		n = (i - WIDTH / 2.0) / (WIDTH / 2.0);
		data->amb.vig_x[i] = (int)(256 * (1.0 - VIGNETTE * n * n));
	}
	i = -1;
	while (++i < HEIGHT)
	{
		n = (i - HEIGHT / 2.0) / (HEIGHT / 2.0);
		data->amb.vig_y[i] = (int)(256 * (1.0 - VIGNETTE * n * n));
	}
}
