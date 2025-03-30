/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:06:44 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/30 15:31:43 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static void	update_player_pos(t_game *game, t_player *pos)
{
	char	tile;

	tile = game->map[pos->y][pos->x];
	if (tile == '1')
		return ;
	if (tile == 'C')
	{
		handle_collectible(game, pos);
		return ;
	}
	if (tile == 'E')
	{
		handle_exit(game, pos);
		return ;
	}
	if (tile == 'X')
	{
		ft_printf("You touched an enemy. Game over!\n");
		close_game(game, &game->gfx);
	}
	game->map[game->player_y][game->player_x] = '0';
	render_map(game, &game->gfx);
	play_move_anim(game, &game->gfx.tx.move_anim[game->p_dir], game->p_dir);
	set_player_pos(game, pos->x, pos->y);
}

void	set_player_pos(t_game *game, int x, int y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[y][x] = 'P';
	game->player_x = x;
	game->player_y = y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	move_player(t_game *game, t_graphics *gfx, t_player *pos)
{
	game->p_dir = pos->dir;
	update_player_pos(game, pos);
	render_map(game, gfx);
}
