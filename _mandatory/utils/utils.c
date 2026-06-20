/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:05:54 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/18 16:12:05 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

size_t	ft_longest_line(char **map)
{
	int		i;
	size_t	width;

	i = 0;
	width = 0;
	while (map[i])
	{
		if (width < ft_strlen(map[i]))
			width = ft_strlen(map[i]);
		i++;
	}
	return (width);
}

char	*ft_strdup_wtn(const char *s)
{
	int		i;
	char	*ret;

	if (!s)
		return (NULL);
	ret = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i] && !ft_is_whitespaces(s[i]))
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_get_textures_path(char *path, char *entry)
{
	int		i;
	char	*ret;

	i = 0;
	while (ft_is_whitespaces(path[i]))
		i++;
	if (!ft_strncmp(path + i, entry, ft_strlen(entry)))
		i += ft_strlen(entry);
	if (!ft_is_whitespaces(path[i]))
		return (NULL);
	while (ft_is_whitespaces(path[i]))
		i++;
	ret = ft_strdup_wtn(path + i);
	return (ret);
}

char	*ft_join_to_comb_empty(char *line, size_t longest_line)
{
	size_t	i;
	char	*ret;

	ret = ft_calloc(longest_line + 1, sizeof(char));
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		ret[i] = line[i];
		i++;
	}
	while (i < longest_line - 1)
	{
		ret[i] = '2';
		i++;
	}
	ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}
