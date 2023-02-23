/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/02/23 17:36:39 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	ft_putstr("you gave up\n");
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
		if (data->collected == data->map->collectables)
			ft_win();
		else
			return (0);
	}
	return (0);
}
