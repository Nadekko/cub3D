/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:12:30 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/27 16:39:44 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static int	ft_check_sprites_doors(t_data *data)
{
	data->mlx->img[DOOR] = ft_init_img(data->mlx, "./texture/doorclosed.xpm");
	if (!data->mlx->img[DOOR])
		return (1);
	data->mlx->img[DOOR + 1] = ft_init_img(data->mlx, "./texture/door1.xpm");
	if (!data->mlx->img[DOOR + 1])
		return (1);
	data->mlx->img[DOOR + 2] = ft_init_img(data->mlx, "./texture/door2.xpm");
	if (!data->mlx->img[DOOR + 2])
		return (1);
	data->mlx->img[DOOR + 3] = ft_init_img(data->mlx, "./texture/door3.xpm");
	if (!data->mlx->img[DOOR + 3])
		return (1);
	data->mlx->img[DOOR + 4] = ft_init_img(data->mlx, "./texture/door4.xpm");
	if (!data->mlx->img[DOOR + 4])
		return (1);
	return (0);
}

static int	ft_check_more_sprites_player(t_data *data)
{
	data->mlx->img[PLAYER + 5] = ft_init_img(data->mlx, "./texture/paw/6.xpm");
	if (!data->mlx->img[PLAYER + 5])
		return (1);
	data->mlx->img[PLAYER + 6] = ft_init_img(data->mlx, "./texture/paw/7.xpm");
	if (!data->mlx->img[PLAYER + 6])
		return (1);
	data->mlx->img[PLAYER + 7] = ft_init_img(data->mlx, "./texture/paw/8.xpm");
	if (!data->mlx->img[PLAYER + 7])
		return (1);
	data->mlx->img[PLAYER + 8] = ft_init_img(data->mlx, "./texture/paw/9.xpm");
	if (!data->mlx->img[PLAYER + 8])
		return (1);
	data->mlx->img[PLAYER + 9] = ft_init_img(data->mlx, "./texture/paw/10.xpm");
	if (!data->mlx->img[PLAYER + 9])
		return (1);
	return (ft_check_sprites_doors(data));
}

static int	ft_check_sprites_player(t_data *data)
{
	data->mlx->img[PLAYER] = ft_init_img(data->mlx, "./texture/paw/1.xpm");
	if (!data->mlx->img[PLAYER])
		return (1);
	data->mlx->img[PLAYER + 1] = ft_init_img(data->mlx, "./texture/paw/2.xpm");
	if (!data->mlx->img[PLAYER + 1])
		return (1);
	data->mlx->img[PLAYER + 2] = ft_init_img(data->mlx, "./texture/paw/3.xpm");
	if (!data->mlx->img[PLAYER + 2])
		return (1);
	data->mlx->img[PLAYER + 3] = ft_init_img(data->mlx, "./texture/paw/4.xpm");
	if (!data->mlx->img[PLAYER + 3])
		return (1);
	data->mlx->img[PLAYER + 4] = ft_init_img(data->mlx, "./texture/paw/5.xpm");
	if (!data->mlx->img[PLAYER + 4])
		return (1);
	return (ft_check_more_sprites_player(data));
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
	data->mlx->img[BACKGROUND] = ft_init_new_img(data->mlx, WIDTH, HEIGHT);
	if (!data->mlx->img[BACKGROUND])
		return (1);
	data->mlx->img[MINI_MAP] = ft_init_new_img(data->mlx, MINISIZE, MINISIZE);
	if (!data->mlx->img[MINI_MAP])
		return (1);
	return (ft_check_sprites_player(data));
}
