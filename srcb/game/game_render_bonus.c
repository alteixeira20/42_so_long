/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:59:35 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/28 18:12:15 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static void	render_tile(t_game *game, t_graphics *gfx, int x, int y)
{
	void	*img;
	char	tile;

	tile = game->map[y][x];
	img = gfx->tx.floor;
	if (tile == '1')
		img = gfx->tx.wall;
	else if (tile == 'C')
		img = gfx->tx.collectible;
	else if (tile == 'E')
		img = gfx->tx.exit;
	else if (tile == 'P')
		img = game->gfx.tx.move_anim[game->p_dir].frames[game->p_frame];
	else if (tile == 'X')
		img = gfx->tx.enemy;
	mlx_put_image_to_window(gfx->mlx, gfx->window, img,
		x * gfx->tile_size, y * gfx->tile_size);
}

static void	draw_move_counter(t_game *game)
{
	char	*text;
	char	*count;

	count = ft_itoa(game->moves);
	if (!count)
		return ;
	text = ft_strjoin("Moves: ", count);
	free(count);
	if (!text)
		return ;
	mlx_string_put(game->gfx.mlx, game->gfx.window,
		10, 20, 0xFFFFFF, text);
	free(text);
}

void	render_map(t_game *game, t_graphics *gfx)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			render_tile(game, gfx, x, y);
			x++;
		}
		y++;
	}
	draw_move_counter(game);
}
