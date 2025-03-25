/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:00:30 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/24 22:00:50 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
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
# define FLOOR      "assets/floor.xpm"
# define WALL       "assets/wall.xpm"
# define COLLECT    "assets/collectible.xpm"
# define EXIT       "assets/exit.xpm"
# define P_UP       "assets/player_up.xpm"
# define P_DOWN     "assets/player_down.xpm"
# define P_LEFT     "assets/player_left.xpm"
# define P_RIGHT    "assets/player_right.xpm"

// Game Window
# define MAX_WINDOW_WIDTH	1280
# define MAX_WINDOW_HEIGHT	720

// Game Functions
void	render_map(t_game *game, t_graphics *gfx);
int		handle_input(int key, t_game *game, t_graphics *gfx);
void	start_game(t_game *game);
void	close_game(t_game *game, t_graphics *gfx);
int		load_textures(t_graphics *gfx);
void	free_textures(t_graphics *gfx);
int		count_collectibles(char **map);

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
