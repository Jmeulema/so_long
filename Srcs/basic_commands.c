/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/02/23 15:35:08 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	printf("you gave up");
	exit(EXIT_SUCCESS);
}

int	ft_basic_commands(int command, t_data *data)
{
	if (command == ESC)
		ft_exit(data);
	else if (command == W)
		ft_move(data, 'y', UP);
	else if (command == S)
		ft_move(data, 'y', DOWN);
	else if (command == A)
		ft_move(data, 'x', LEFT);
	else if (command == D)
		ft_move(data, 'x', RIGHT);
	if (data->map->map[data->p_y][data->p_x] == 'E')
	{
		if (data->collected != data->map->collectables)
		{
			printf("ok");
			return (0);
		}
		else
		{
			printf("ko\n");
			ft_win(data);
		}
	}
	return (0);
}
