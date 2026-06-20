/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:24:27 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/27 18:17:39 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

int	ft_get_textures_part2(char **file, t_data *data, int i, int j)
{
	if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'F')
	{
		if (data->texture_f || ft_set_textures_struct(data, file[i], 'F'))
			return (1);
	}
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'C')
	{
		if (data->texture_c || ft_set_textures_struct(data, file[i], 'C'))
			return (1);
	}
	return (0);
}
