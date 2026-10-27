/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:38:31 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:26:32 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	hud_cat_int(char *buf, long n)
{
	char	tmp[24];
	int		i;
	int		neg;

	neg = (n < 0);
	if (neg)
		n = -n;
	i = 23;
	tmp[i] = '\0';
	if (n == 0)
		tmp[--i] = '0';
	while (n > 0)
	{
		tmp[--i] = '0' + n % 10;
		n /= 10;
	}
	if (neg)
		tmp[--i] = '-';
	ft_strlcat(buf, tmp + i, HUD_BUF);
}

// same as printf("%.2f")
void	hud_cat_double(char *buf, double v)
{
	long	cents;

	cents = (long)round(v * 100.0);
	if (cents < 0)
	{
		ft_strlcat(buf, "-", HUD_BUF);
		cents = -cents;
	}
	hud_cat_int(buf, cents / 100);
	ft_strlcat(buf, ".", HUD_BUF);
	if (cents % 100 < 10)
		ft_strlcat(buf, "0", HUD_BUF);
	hud_cat_int(buf, cents % 100);
}

// darkens a rectangle of the image so the text stays readable
void	hud_darken(t_img *img, int x0, int y0)
{
	unsigned int	*px;
	int				x;
	int				y;

	y = y0;
	while (y < y0 + HUD_LINES * HUD_LINE_H + 10 && y < img->height)
	{
		x = x0;
		while (x < x0 + HUD_W && x < img->width)
		{
			px = (unsigned int *)(img->addr + y * img->line_len
					+ x * (img->bpp / 8));
			*px = (*px >> 1) & 0x7F7F7F;
			x++;
		}
		y++;
	}
}
