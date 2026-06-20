/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:32 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/27 18:48:47 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

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
		return (free(img->img), free(img), NULL);
	return (img);
}

int	ft_check_textures(t_data *data)
{
	data->mlx->img[NO_TEXTURE] = ft_init_img(data->mlx, data->texture_n);
	if (!data->mlx->img[NO_TEXTURE])
		return (1);
	data->mlx->img[SO_TEXTURE] = ft_init_img(data->mlx, data->texture_s);
	if (!data->mlx->img[SO_TEXTURE])
		return (1);
	data->mlx->img[WE_TEXTURE] = ft_init_img(data->mlx, data->texture_w);
	if (!data->mlx->img[WE_TEXTURE])
		return (1);
	data->mlx->img[EA_TEXTURE] = ft_init_img(data->mlx, data->texture_e);
	if (!data->mlx->img[EA_TEXTURE])
		return (1);
	data->mlx->img[4] = ft_init_img(data->mlx, "./texture/paw/1.xpm");
	if (!data->mlx->img[4])
		return (1);
	data->mlx->img[5] = ft_calloc(1, sizeof(t_img));
	if (!data->mlx->img[5])
		return (1);
	return (0);
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

// int	ft_check_rgb_values(char *texture)
// {
// 	char	**tab;
// 	int		i;

// 	tab = ft_split(texture, ',');
// 	if (ft_tab_len(tab) > 3 || ft_tab_len(tab) < 3)
// 		return (ft_free_tab(tab), 1);
// 	i = 0;
// 	while (tab[i])
// 	{
// 		if (ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255)
// 			return (ft_free_tab(tab), 1);
// 		i++;
// 	}
// 	ft_free_tab(tab);
// 	return (0);
// }

// int	ft_check_rgb(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->texture_c[i])
// 	{
// 		if ((data->texture_c[i] != ','
// 				&& !ft_isdigit(data->texture_c[i]))
// 			|| (data->texture_f[i] != ','
// 				&& !ft_isdigit(data->texture_f[i])))
// 			return (1);
// 		i++;
// 	}
// 	if (ft_check_rgb_values(data->texture_c)
// 		|| ft_check_rgb_values(data->texture_f))
// 		return (1);
// 	return (0);
// }
