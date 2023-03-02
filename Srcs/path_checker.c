/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/03/02 13:41:26 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**duplicate_map(t_data *data)
{
	int		i;
	int		j;
	char	**my_map;

	i = 0;
	while (data->map->map[i])
		i++;
	my_map = malloc(sizeof(char *) * (i + 1));
	if (!my_map)
		return (NULL);
	i = -1;
	while (data->map->map[++i])
	{
		j = -1;
		my_map[i] = malloc(sizeof(char) * (ft_strlen(data->map->map[i]) + 1));
		if (!(my_map[i]))
			return (NULL);
		while (data->map->map[i][++j])
			my_map[i][j] = data->map->map[i][j];
		my_map[i][j] = 0;
	}
	my_map[i] = 0;
	return (my_map);
}

void	ft_path_help(t_path *path, char **map, int y, int x)
{
	if (map[y][x + 1] != '1')
	{
		if (map[y][x + 1] == 'C')
			path->coins++;
		if (map[y][x + 1] == 'E')
			path->exit++;
		map[y][x + 1] = '1';
		ft_path(path, map, y, x + 1);
	}
	if (map[y][x - 1] != '1')
	{
		if (map[y][x - 1] == 'C')
			path->coins++;
		if (map[y][x - 1] == 'E')
			path->exit++;
		map[y][x - 1] = '1';
		ft_path(path, map, y, x - 1);
	}
}

void	ft_path(t_path *path, char **map, int y, int x)
{
	if (map[y + 1][x] != '1')
	{
		if (map[y + 1][x] == 'C')
			path->coins++;
		if (map[y + 1][x] == 'E')
			path->exit++;
		map[y + 1][x] = '1';
		ft_path(path, map, y + 1, x);
	}
	if (map[y - 1][x] != '1')
	{
		if (map[y - 1][x] == 'C')
			path->coins++;
		if (map[y - 1][x] == 'E')
			path->exit++;
		map[y - 1][x] = '1';
		ft_path(path, map, y - 1, x);
	}
	ft_path_help(path, map, y, x);
}

int	check_paths(t_data *data, int pos_y, int pos_x, int collectables)
{
	char	**dup;
	t_path	path;

	dup = duplicate_map(data);
	path.coins = 0;
	path.exit = 0;
	ft_path(&path, dup, pos_y, pos_x);
	pos_y = 0;
	while (dup[pos_y])
		free(dup[pos_y++]);
	free(dup);
	return (path.coins == collectables && path.exit == 1);
}
