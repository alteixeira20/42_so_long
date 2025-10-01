/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:59:35 by paalexan          #+#    #+#             */
/*   Updated: 2025/10/01 16:21:50 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

void	draw_tile(t_game *game, t_graphics *gfx, int x, int y)
{
	char		tile;

	tile = game->map[y][x];
	mlx_put_image_to_window(gfx->mlx, gfx->window, gfx->tx.floor,
		x * gfx->tile_size, y * gfx->tile_size);
	if (tile == '1')
		mlx_put_image_to_window(gfx->mlx, gfx->window, gfx->tx.wall,
			x * gfx->tile_size, y * gfx->tile_size);
	else if (tile == 'C')
		mlx_put_image_to_window(gfx->mlx, gfx->window,
			gfx->tx.collectible, x * gfx->tile_size, y * gfx->tile_size);
	else if (tile == 'E')
		mlx_put_image_to_window(gfx->mlx, gfx->window,
			gfx->tx.exit, x * gfx->tile_size, y * gfx->tile_size);
	else if (tile == 'P')
		mlx_put_image_to_window(gfx->mlx, gfx->window,
			gfx->tx.move_anim[game->p_dir].frames[game->p_frame],
			x * gfx->tile_size, y * gfx->tile_size);
	else if (tile == 'X')
		mlx_put_image_to_window(gfx->mlx, gfx->window, gfx->tx.enemy,
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
			draw_tile(game, gfx, x, y);
			x++;
		}
		y++;
	}
	draw_move_counter(game);
}
