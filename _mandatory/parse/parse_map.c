/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:13:37 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/18 11:10:44 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int	ft_condition_map(char **map, int i, int j)
{
	if (map[i][j] && (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
			&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'))
		return (1);
	return (0);
}

int	ft_check_char(char **map, int i, int j)
{
	if ((i - 1 >= 0 && ft_condition_map(map, i - 1, j)) || i - 1 < 0)
		return (1);
	else if ((j - 1 >= 0 && ft_condition_map(map, i, j - 1)) || j - 1 < 0)
		return (1);
	else if (map[i + 1] && (ft_condition_map(map, i + 1, j) || !map[i + 1][j]))
		return (1);
	else if (ft_condition_map(map, i, j + 1) || !map[i][j + 1])
		return (1);
	return (0);
}

int	ft_check_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\t')
				return (1);
			else if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (ft_check_char(map, i, j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_player(char **map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		return (1);
	return (0);
}
