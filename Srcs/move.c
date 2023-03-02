/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/03/02 12:10:36 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_player_move(t_data *data, char position, int direction)
{
	if (position == 'y' && direction == UP)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_up,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
	if (position == 'y' && direction == DOWN)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_down,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
	if (position == 'x' && direction == LEFT)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_left,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
	if (position == 'x' && direction == RIGHT)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_right,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
}

static void	ft_collect(t_data *data, char pos, int dir)
{
	data->collected++;
	data->map->map[data->p_y][data->p_x] = '0';
	mlx_put_image_to_window(data->mlx, data->win, data->img->background,
		(data->p_x * IMG_W), (data->p_y * IMG_H));
	ft_player_move(data, pos, dir);
}

static void	ft_do_move(t_data *data, char pos, int dir)
{
	if (pos == 'y' && data->map->map[data->p_y + 1 * dir][data->p_x] != '1'
		&& (data->map->map[data->p_y + 1 * dir][data->p_x] != 'E'
		|| data->collected == data->map->collectables))
	{
		if (data->map->map[data->p_y][data->p_x] == 'E')
			mlx_put_image_to_window(data->mlx, data->win, data->img->exit,
				(data->p_x * IMG_W), (data->p_y * IMG_H));
		data->p_y = data->p_y + 1 * dir;
	}
	else if (pos == 'x' && data->map->map[data->p_y][data->p_x + 1 * dir] != '1'
		&& (data->map->map[data->p_y][data->p_x + 1 * dir] != 'E'
		|| data->collected == data->map->collectables))
	{
		if (data->map->map[data->p_y][data->p_x] == 'E')
			mlx_put_image_to_window(data->mlx, data->win, data->img->exit,
				(data->p_x * IMG_W), (data->p_y * IMG_H));
		data->p_x = data->p_x + 1 * dir;
	}
}

static void	ft_do_exit_move(t_data *data, char pos, int dir)
{
	if (pos == 'y' && data->map->map[data->p_y + 1 * dir][data->p_x] == 'E'
		&& data->collected != data->map->collectables)
	{
		data->p_y = data->p_y + 1 * dir;
		ft_putstr("collecte all devils fruits before leaving\n");
	}
	else if (pos == 'x' && data->map->map[data->p_y][data->p_x + 1 * dir] == 'E'
		&& data->collected != data->map->collectables)
	{
		data->p_x = data->p_x + 1 * dir;
		ft_putstr("collecte all devils fruits before leaving\n");
	}
}

void	ft_move(t_data *data, char pos, int dir)
{

	mlx_put_image_to_window(data->mlx, data->win, data->img->background,
		(data->p_x * IMG_W), (data->p_y * IMG_H));
	ft_do_move(data, pos, dir);
	ft_do_exit_move(data, pos, dir);
	ft_player_move(data, pos, dir);
	if (data->map->map[data->p_y][data->p_x] == 'C')
		ft_collect(data, pos, dir);
	mlx_do_sync(data->mlx);
	ft_putstr("You did ");
	ft_printnbr(++data->counter);
	ft_putstr(" moves.\r");
}
