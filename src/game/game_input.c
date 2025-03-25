/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:06:44 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/25 00:00:06 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	set_player_pos(t_game *game, int x, int y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[y][x] = 'P';
	game->player_x = x;
	game->player_y = y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

static void	update_player_pos(t_game *game, t_player *pos)
{
	char	tile;

	tile = game->map[pos->y][pos->x];
	if (tile == '1')
		return ;
	if (tile == 'C')
		game->collectibles--;
	if (tile == 'E')
	{
		if (game->collectibles == 0)
			close_game(game, &game->gfx);
		else
			return ;
	}
	set_player_pos(game, pos->x, pos->y);
}

static void	set_direction(int key, t_player *pos)
{
	if (key == KEY_W)
	{
		pos->y -= 1;
		pos->dir = 0;
	}
	else if (key == KEY_S)
	{
		pos->y += 1;
		pos->dir = 1;
	}
	else if (key == KEY_A)
	{
		pos->x -= 1;
		pos->dir = 2;
	}
	else if (key == KEY_D)
	{
		pos->x += 1;
		pos->dir = 3;
	}
}

void	move_player(t_game *game, t_graphics *gfx, t_player *pos)
{
	game->player_dir = pos->dir;
	update_player_pos(game, pos);
	render_map(game, gfx);
}

int	handle_input(int key, t_game *game, t_graphics *gfx)
{
	t_player	pos;

	pos.x = game->player_x;
	pos.y = game->player_y;
	pos.dir = game->player_dir;
	if (key == KEY_ESC)
		close_game(game, gfx);
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		set_direction(key, &pos);
		move_player(game, gfx, &pos);
	}
	return (0);
}
