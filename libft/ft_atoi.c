/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:13:27 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/14 13:20:04 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		j;
	int		nb;
	char	*str_cmp;

	i = 0;
	j = 0;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			j++;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
		nb = nb * 10 + (nptr[i++] - '0');
	if (j != 0)
		nb = -nb;
	str_cmp = ft_itoa(nb);
	if (ft_strncmp(nptr, str_cmp, ft_strlen(nptr)))
		return (free(str_cmp), -1);
	return (free(str_cmp), nb);
}

int	ft_atoi_char(const char nptr)
{
	int		nb;

	nb = 0;
	if (nptr >= 48 && nptr <= 57)
		nb = nb * 10 + (nptr - '0');
	return (nb);
}
