/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#             */
/*   Updated: 2023/02/23 16:20:20 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define IMG_W 50
# define IMG_H 50
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP -1
# define DOWN 1
# define LEFT -1
# define RIGHT 1

typedef struct s_img
{
	void	*player_up;
	void	*player_left;
	void	*player_right;
	void	*player_down;
	void	*background;
	void	*exit;
}							t_img;

typedef struct s_map
{
	char	**map;
	void	*object;
	int		x;
	int		y;
	int		collectables;
}							t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		size_x;
	int		size_y;
	int		p_x;
	int		p_y;
	int		counter;
	int		collected;
	t_map	*map;
	t_img	*img;
}							t_data;

/* get_next_line */

size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *str);
char		*get_next_line(int fd);

/* so_long_utils */

char		*ft_strnstr(const char *str, const char *to_find, size_t len);
void		exit_error(void);
int			ft_count_lines(int fd, int x, int img_w);
int			ft_line_length(int fd);
int			ft_count_c(char *s, char c);

/* so_long_utils2 */

void		*ft_calloc(size_t nelem, size_t elsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char *s1, const char *s2);

/* map */

void		ft_window_size(t_data *data, char **av);
void		ft_create_map(t_data *data);

/* init */

void		ft_init(t_data *data, t_map *map);

/* put_elements */

void		ft_put_background(t_data *data);
void		ft_put_objects(t_data *data, char *relative_path);
void		ft_put_player(t_data *data);

/* basic_command */

int			ft_exit(t_data *data);
int			ft_basic_commands(int command, t_data *data);

/* move */

void		ft_move(t_data *data, char pos, int dir);

/* win */

void		ft_win(t_data *data);

/* parse_input */

void		ft_parse_input(t_data *data, char **av, int ac);

/* so_long */


#endif