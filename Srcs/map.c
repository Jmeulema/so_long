/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/02/23 17:31:25 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_window_size(t_data *data, char **av)
{
	int	fd;
	int	len;

	len = ft_strlen(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nInvalid map_path/map\n");
		exit(EXIT_FAILURE);
	}
	if (av[1][len - 4] != '.' && av[1][len - 3] != 'b')
	{
		ft_putstr("Error\nmap has to be .ber\n");
		exit(EXIT_FAILURE);
	}
	if (av[1][len - 2] != 'e' && av[1][len - 1] != 'r')
	{
		ft_putstr("Error\nmap has to be .ber\n");
		exit(EXIT_FAILURE);
	}
	data->size_x = (ft_line_length(fd) * IMG_W);
	data->size_y = (ft_count_lines(fd, data->size_x, IMG_W) * IMG_H);
}

void	ft_create_map(t_data *data)
{
	data->map->x = 0;
	data->map->y = 0;
	while (data->map->y < (data->size_y / IMG_H))
	{
		if (data->map->map[data->map->y][data->map->x] == 'P')
			ft_put_player(data);
		else if (data->map->map[data->map->y][data->map->x] == '1')
			ft_put_objects(data, "./img/wall.xpm");
		else if (data->map->map[data->map->y][data->map->x] == 'C')
			ft_put_objects(data, "./img/collectable.xpm");
		else if (data->map->map[data->map->y][data->map->x] == 'E')
			ft_put_objects(data, "./img/exit.xpm");
		if (data->map->x < (data->size_x / IMG_W))
			data->map->x++;
		else
		{
			data->map->y++;
			data->map->x = 0;
		}
	}
}
