/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:59:35 by paalexan          #+#    #+#             */
/*   Updated: 2025/10/01 16:18:12 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

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
		img = gfx->tx.player[game->player_dir];
	mlx_put_image_to_window(gfx->mlx, gfx->window, img,
		x * gfx->tile_size, y * gfx->tile_size);
}

void	render_map(t_game *game, t_graphics *gfx)
{
	int	x;
	int	y;

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
}
