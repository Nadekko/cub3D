/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:05:02 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/27 16:57:35 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static int	ft_get_max_width(char **map)
{
	int	max_width;
	int	i;
	int	len;

	max_width = 0;
	i = 0;
	while (map[i])
	{
		len = 0;
		while (map[i][len] && map[i][len] != '\n')
			len++;
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

static int	ft_convert_line(char *line, int **tab, int i, int width)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '\n')
	{
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E'
			|| line[j] == 'W')
			tab[i][j] = 3;
		else if (line[j] == 'D')
			tab[i][j] = 4;
		else if (ft_is_whitespaces(line[j]) != 1)
			tab[i][j] = ft_atoi_char(line[j]);
		else
			tab[i][j] = 2;
		j++;
	}
	while (j < width)
	{
		tab[i][j] = 2;
		j++;
	}
	return (1);
}

int	**ft_convert_map(char **map)
{
	int	**tab;
	int	i;
	int	width;

	width = ft_get_max_width(map);
	tab = ft_calloc(ft_tab_len(map), sizeof(int *));
	if (!tab)
		return (NULL);
	i = 0;
	while (map[i])
	{
		tab[i] = ft_calloc(width, sizeof(int));
		if (!tab[i])
		{
			while (i--)
				free(tab[i]);
			return (NULL);
		}
		ft_convert_line(map[i], tab, i, width);
		i++;
	}
	return (tab);
}
