/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:00:25 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/27 18:39:11 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

// void	ft_free_mlx(t_mlx *mlx)
// {
// 	free(mlx->img[5]);
// 	ft_free_img(mlx, IMG_COUNT - 1);
// 	if (mlx->win)
// 		mlx_destroy_window(mlx->mlx, mlx->win);
// 	mlx_destroy_display(mlx->mlx);
// 	free(mlx->mlx);
// }

void	ft_free_elements(t_data *data)
{
	if (data->doors)
		free(data->doors);
}
