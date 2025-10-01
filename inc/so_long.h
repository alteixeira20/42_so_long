/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:00:30 by paalexan          #+#    #+#             */
/*   Updated: 2025/10/01 16:22:11 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf_bonus.h"
# include "../libft/gnl/get_next_line_bonus.h"

// Game Struct
typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*exit;
	void	*collectible;
	void	*player[4];
}	t_textures;

typedef struct s_graphics
{
	void		*mlx;
	void		*window;
	int			tile_size;
	int			screen_w;
	int			screen_h;
	t_textures	tx;
}	t_graphics;

typedef struct s_game
{
	char		**map;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	int			player_dir;
	int			moves;
	int			collectibles;
	t_graphics	gfx;
}	t_game;

typedef struct s_player
{
	int	x;
	int	y;
	int	dir;
}	t_player;

// Game Keys
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100

// Game Assets
# define FLOOR      "assets/static/floor.xpm"
# define WALL       "assets/static/wall.xpm"
# define COLLECT    "assets/static/collectible.xpm"
# define EXIT       "assets/static/exit.xpm"
# define P_UP       "assets/player/player_up0.xpm"
# define P_DOWN     "assets/player/player_down0.xpm"
# define P_LEFT     "assets/player/player_left0.xpm"
# define P_RIGHT    "assets/player/player_right0.xpm"

// Game Window
# define MAX_WINDOW_WIDTH	1280
# define MAX_WINDOW_HEIGHT	720
# define TILE_SIZE			64

// Game Functions
void	render_map(t_game *game, t_graphics *gfx);
int		handle_input(int key, t_game *game, t_graphics *gfx);
void	start_game(t_game *game);
void	close_game(t_game *game, t_graphics *gfx);
int		load_textures(t_graphics *gfx);
void	free_textures(t_graphics *gfx);
int		count_collectibles(char **map);
int		check_invalid_chars(char **map);

// Map Functions
int		get_map_height(char *mapname);
int		get_last_row(char **map);
int		check_components_errors(int start_pos, int exit_pos, int reward);
char	**read_map(char *mapname);
char	**duplicate_map(char **map);
int		is_map_valid(char **map);
int		is_map_solvable(char **map);
void	free_map(char **map);
void	free_dup(char **dup);

#endif
