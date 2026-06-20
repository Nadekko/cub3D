/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:08:58 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/22 18:15:16 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

unsigned int	get_pixel(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_len)
			+ (x * img.bpp / 8))));
}

//copy the pixel on an img
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img->addr)
		return ;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
	else
		printf("Erreur : put_pixel hors limites (%d, %d)\n", x, y);
}

//copy an img on another, ignore transparency
void	put_img_to_img(t_data *data, t_img src, int x, int y)
{
	int	j;
	int	i;

	(void)y;
	i = 0;
	while (i < src.width)
	{
		j = 0;
		while (j < src.height)
		{
			if (get_pixel(src, i, j) != 0xFF000000)
				put_pixel(data->mlx->img[5], (x + i), (y + j),
					get_pixel(src, i, j));
			j++;
		}
		i++;
	}
}

/*
0x000000 = 24_BITS
0xRRGGBB = 24_BITS


R = 0xFF0000 = 8_BITS
G = 0x00FF00 = 8_BITS
B = 0x0000FF = 8_BITS

R = 2 ^ 16 = 65536	(256 * 256)
G = 2 ^ 8 = 256
B = 2 ^ 0 = 1

red = 240
green = 0
blue = 113
color = (240 * 65536) + (0 * 256) + 113 = 15790361 // hex = 0xF00071;
*/

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
