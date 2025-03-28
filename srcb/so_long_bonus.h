/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:00:30 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/28 16:37:01 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf_bonus.h"
# include "../libft/gnl/get_next_line_bonus.h"

// Game Structs
typedef struct s_anim
{
	void	**frames;
	int		frame_count;
	int		delay;
}	t_anim;

typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*exit;
	void	*collectible;
	t_anim	move_anim[4];
	t_anim	mining_anim[4];
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
	int			p_dir;
	int			p_frame;
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
# define FLOOR			"assets/floor.xpm"
# define WALL			"assets/wall.xpm"
# define COLLECT		"assets/collectible.xpm"
# define EXIT			"assets/exit.xpm"
# define MOVE_UP "assets/player/player_up"
# define MOVE_DOWN "assets/player/player_down"
# define MOVE_LEFT "assets/player/player_left"
# define MOVE_RIGHT "assets/player/player_right"
# define MOVE_FRAMES 7
# define MINE_UP "assets/mining/mining_up"
# define MINE_DOWN "assets/mining/mining_down"
# define MINE_LEFT "assets/mining/mining_left"
# define MINE_RIGHT "assets/mining/mining_right"
# define MINE_FRAMES	5

// Game Window
# define MAX_WINDOW_WIDTH	1280
# define MAX_WINDOW_HEIGHT	720
# define TILE_SIZE			64

// Game Functions
void	render_map(t_game *game, t_graphics *gfx);
void	start_game(t_game *game);
void	close_game(t_game *game, t_graphics *gfx);
void	move_player(t_game *game, t_graphics *gfx, t_player *pos);
void	set_player_pos(t_game *game, int x, int y);
int		handle_input(int key, t_game *game, t_graphics *gfx);
void	handle_collectible(t_game *game, t_player *pos);
int		handle_exit(t_game *game, t_player *pos);

// Sprites Functions
int		load_textures(t_graphics *gfx);
int		load_anim(t_graphics *gfx, t_anim *anim, char *prefix, int count);
void	play_mining_anim(t_graphics *gfx, t_anim *animation, int x, int y);
void	play_move_anim(t_game *game, t_anim *anim, int dir);

// Free Memory Functions
void	free_static_textures(t_graphics *gfx);
void	free_mining_textures(t_graphics *gfx);
void	free_move_textures(t_graphics *gfx);
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
