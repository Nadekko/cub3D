/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:32:00 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/27 17:04:41 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static void	ft_set_doors(t_data *data, t_doors *door, int k, int j)
{
	door->x = k;
	door->y = j;
	door->is_open = 0;
	door->has_been_open = 0;
	door->nb = ft_counter(data->map->map_tab, 'D');
	door->anim_frame = 0;
	door->dist_to_player = 0;
}

int	ft_get_doors(t_data *data, int nb)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = -1;
	if (nb == 0)
		return (0);
	data->doors = ft_calloc(nb, sizeof(t_doors));
	if (!data->doors)
		return (1);
	while (data->map->map_tab[++j])
	{
		k = -1;
		while (data->map->map_tab[j][++k])
		{
			if (data->map->map_tab[j][k] == 'D')
			{
				ft_set_doors(data, &data->doors[i], k, j);
				i++;
			}
		}
	}
	return (0);
}

int	ft_clean_init_elements(t_data *data)
{
	int	nb_doors;

	nb_doors = ft_counter(data->map->map_tab, 'D');
	if (nb_doors == 0)
		return (0);
	if (ft_get_doors(data, nb_doors))
		return (1);
	return (0);
}
