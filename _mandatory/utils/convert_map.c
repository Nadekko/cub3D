/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:05:02 by ede-cola          #+#    #+#             */
/*   Updated: 2025/02/22 18:15:54 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static int	ft_convert_line(char *line, int **tab, int i)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '\n')
	{
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E'
			|| line[j] == 'W')
			tab[i][j] = 3;
		else if (ft_is_whitespaces(line[j]) != 1)
			tab[i][j] = ft_atoi_char(line[j]);
		else
			tab[i][j] = 2;
		j++;
	}
	return (1);
}

int	**ft_convert_map(char **map)
{
	int	**tab;
	int	i;

	tab = ft_calloc(ft_tab_len(map), sizeof(int *));
	if (!tab)
		return (NULL);
	i = 0;
	while (map[i])
	{
		tab[i] = ft_calloc(ft_strlen(map[i]), sizeof(int));
		if (!tab[i])
		{
			while (i--)
				free(tab[i]);
			return (NULL);
		}
		ft_convert_line(map[i], tab, i);
		i++;
	}
	return (tab);
}
