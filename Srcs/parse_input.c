/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/02/27 15:10:32 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_map_error(char *error_msg)
{
	ft_putstr(error_msg);
	exit(EXIT_FAILURE);
}

static void	ft_check_walls(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < (data->size_y / IMG_H))
	{
		if ((int)ft_strlen(data->map->map[y]) != data->size_x / IMG_W)
			ft_map_error("Error\nmap has to be rectangular\n");
		x = 0;
		while (x < (data->size_x / IMG_W))
		{
			if (data->map->map[y][x] != '0' && data->map->map[y][x] != '1' &&
				data->map->map[y][x] != 'C' && data->map->map[y][x] != 'P' &&
				data->map->map[y][x] != 'E')
				ft_map_error("Error\nshould contained '0','1','C','P','E'\n");
			else if ((y == 0 || x == 0) && data->map->map[y][x] != '1')
				ft_map_error("Error\nmap has to be surrounded by walls\n");
			else if ((y == (data->size_y / IMG_H - 1)
					|| x == (data->size_x / IMG_W - 1))
				&& data->map->map[y][x] != '1')
				ft_map_error("Error\nmap has to be surrounded by walls\n");
			x++;
		}
		y++;
	}
}

static void	ft_check_content(t_data *data)
{
	int	y;
	int	exit;
	int	player;

	exit = 0;
	player = 0;
	data->map->collectables = 0;
	y = 0;
	while (data->map->map && data->map->map[y])
	{
		exit += ft_count_c(data->map->map[y], 'E');
		player += ft_count_c(data->map->map[y], 'P');
		data->map->collectables += ft_count_c(data->map->map[y], 'C');
		y++;
	}
	if (player != 1)
		ft_map_error("Error\nonly valid map if one player is contained\n");
	if (exit != 1)
		ft_map_error("Error\nonly valid map if one exit is contained\n");
	if (data->map->collectables == 0)
		ft_map_error("Error\nonly valid map if at least 1 fruit is contained\n");
}

static void	ft_input_error(int ac)
{
	if (ac != 2)
	{
		ft_map_error("Error\nUsage './so_long mappath/mapname.ber\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_parse_input(t_data *data, char **av, int ac)
{
	int		fd;
	int		i;
	int		bytes;
	char	buffer[2];

	ft_input_error(ac);
	i = 0;
	bytes = 1;
	buffer[1] = '\0';
	fd = open(av[1], O_RDONLY);
	while (bytes == 1)
	{
		bytes = read(fd, buffer, 1);
		if (bytes != 1)
			break ;
		if (buffer[0] != '\n' && buffer[0] != '\0')
		{
			data->map->map[i] = ft_strjoin(data->map->map[i], buffer);
		}
		else
			i++;
	}
	ft_check_content(data);
	ft_check_walls(data);
}
