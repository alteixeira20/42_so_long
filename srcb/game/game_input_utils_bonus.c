/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:17:21 by paalexan          #+#    #+#             */
/*   Updated: 2025/10/01 16:21:48 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

void	set_direction(int key, t_player *pos)
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

int	handle_input(int key, t_game *game, t_graphics *gfx)
{
	t_player	pos;

	pos.x = game->player_x;
	pos.y = game->player_y;
	pos.dir = game->p_dir;
	if (key == KEY_ESC)
		close_game(game, gfx);
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		set_direction(key, &pos);
		move_player(game, gfx, &pos);
	}
	return (0);
}

void	handle_collectible(t_game *game, t_player *pos)
{
	play_mining_anim(&game->gfx, &game->gfx.tx.mining_anim[game->p_dir],
		game->player_x, game->player_y);
	game->collectibles--;
	set_player_pos(game, pos->x, pos->y);
}

void	handle_exit(t_game *game, t_player *pos)
{
	if (game->collectibles == 0)
	{
		set_player_pos(game, pos->x, pos->y);
		ft_printf("Congratulations you finished the game with %d moves.\n",
			game->moves);
		close_game(game, &game->gfx);
	}
	else
		return ;
}
