/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:38:31 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:26:32 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

// channel i (0 = red) of an 0xRRGGBB color
static int	chan(unsigned int color, int i)
{
	return ((color >> (16 - 8 * i)) & 0xFF);
}

// fog factor f: 0 next to the player, tends to 1 far away
// per column: lit = light tinted by LIGHT_COLOR (x256), fog = FOG_COLOR part
// future light sources only have to add up into `light`
void	column_light(t_data *data)
{
	t_raycast	*r;
	double		light;
	double		f;
	int			i;

	r = data->raycast;
	light = 1.0;
	if (r->side == 1)
		light = SIDE_LIGHT;
	f = 1.0 - exp(-r->wall_dist * FOG_DENSITY);
	i = -1;
	while (++i < 3)
	{
		r->lit[i] = (int)(light * (1.0 - f) * chan(LIGHT_COLOR, i));
		r->fog[i] = (int)(f * chan(FOG_COLOR, i));
	}
}

// texel -> final color: light, fog, then vignette
unsigned int	shade_pixel(t_data *data, unsigned int c, int x, int y)
{
	t_raycast	*r;
	int			ch[3];
	int			k;
	int			i;

	r = data->raycast;
	k = data->amb.vig_x[x] * data->amb.vig_y[y] >> 8;
	i = -1;
	while (++i < 3)
	{
		ch[i] = ((chan(c, i) * r->lit[i] >> 8) + r->fog[i]) * k >> 8;
		if (ch[i] > 255)
			ch[i] = 255;
	}
	return (ch[0] << 16 | ch[1] << 8 | ch[2]);
}

// color lit by `light` (tinted by LIGHT_COLOR) and faded into FOG_COLOR
static unsigned int	fade(unsigned int c, double light, double f)
{
	int	ch[3];
	int	i;

	i = -1;
	while (++i < 3)
	{
		ch[i] = (int)(chan(c, i) * light * (1.0 - f) * chan(LIGHT_COLOR, i)
				/ 255.0 + f * chan(FOG_COLOR, i));
		if (ch[i] > 255)
			ch[i] = 255;
	}
	return (ch[0] << 16 | ch[1] << 8 | ch[2]);
}

// floor/ceiling color per row: a row of the screen is a fixed distance
// on the floor, HEIGHT / (2 * (y - HEIGHT / 2)), like the walls
void	init_ambiance(t_data *data)
{
	double	f;
	int		y;

	init_vignette(data);
	y = -1;
	while (++y < HEIGHT)
	{
		f = 1.0 - exp(-FOG_DENSITY * HEIGHT
				/ (2.0 * fmax(1.0, fabs(y - HEIGHT / 2.0))));
		if (y < HEIGHT / 2)
			data->amb.bg[y] = fade(data->color_c, CEIL_LIGHT, f);
		else
			data->amb.bg[y] = fade(data->color_f, FLOOR_LIGHT, f);
	}
}
