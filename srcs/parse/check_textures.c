/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:32 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/27 16:56:53 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static void	ft_grow_box(t_img *img, int x, int y)
{
	if (x < img->box[0])
		img->box[0] = x;
	if (y < img->box[1])
		img->box[1] = y;
	if (x > img->box[2])
		img->box[2] = x;
	if (y > img->box[3])
		img->box[3] = y;
}

static void	ft_set_box(t_img *img)
{
	int				x;
	int				y;
	unsigned int	color;

	img->box[0] = img->width;
	img->box[1] = img->height;
	img->box[2] = -1;
	img->box[3] = -1;
	y = 0;
	while (y < img->height && y < HEIGHT)
	{
		x = 0;
		while (x < img->width && x < WIDTH)
		{
			color = *(unsigned int *)(img->addr + y * img->line_len
					+ x * (img->bpp / 8));
			if (color != 0xFF000000)
				ft_grow_box(img, x, y);
			x++;
		}
		y++;
	}
}

t_img	*ft_init_img(t_mlx *mlx, char *path)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx->mlx, path, &img->width, &img->height);
	if (!img->img)
		return (free(img), NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return (mlx_destroy_image(mlx->mlx, img->img), free(img), NULL);
	ft_set_box(img);
	return (img);
}

t_img	*ft_init_new_img(t_mlx *mlx, int width, int height)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx->mlx, width, height);
	if (!img->img)
		return (free(img), NULL);
	img->width = width;
	img->height = height;
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return (mlx_destroy_image(mlx->mlx, img->img), free(img), NULL);
	return (img);
}

int	ft_check_rgb(t_data *data)
{
	if (data->texture_c->red < 0 || data->texture_f->red < 0)
		return (1);
	else if (data->texture_c->red > 255 || data->texture_f->red > 255)
		return (1);
	else if (data->texture_c->green < 0 || data->texture_f->green < 0)
		return (1);
	else if (data->texture_c->green > 255 || data->texture_f->green > 255)
		return (1);
	else if (data->texture_c->blue < 0 || data->texture_f->blue < 0)
		return (1);
	else if (data->texture_c->blue > 255 || data->texture_f->blue > 255)
		return (1);
	return (0);
}
