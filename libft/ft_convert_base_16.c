/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base_16.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:47:24 by ede-cola          #+#    #+#             */
/*   Updated: 2025/02/17 00:39:13 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_convert_base_16(unsigned int nb)
{
	unsigned int	quotient;
	unsigned int	remainder;
	unsigned int	i;
	unsigned int	j;
	char			hex[100];

	i = 0;
	quotient = nb;
	while (quotient != 0)
	{
		remainder = quotient % 16;
		if (remainder <= 10)
			hex[i++] = 48 + remainder;
		else
			hex[i++] = 55 + remainder;
		quotient /= 16;
	}
	j = 0;
	while (i > 0)
		j = j * 10 + hex[--i] - '0';
	return (j);
}
