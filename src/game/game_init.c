/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:18:41 by paalexan          #+#    #+#             */
/*   Updated: 2025/10/01 16:18:07 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static int	handle_exit(void *param)
{
	t_game				*game;

	game = (t_game *)param;
	close_game(game, &game->gfx);
	return (0);
}

static int	handle_input_wrapper(int key, void *param)
{
	t_game				*game;

	game = (t_game *)param;
	handle_input(key, game, &game->gfx);
	return (0);
}

void	close_game(t_game *game, t_graphics *gfx)
{
	if (gfx->mlx)
	{
		if (gfx->window)
			mlx_destroy_window(gfx->mlx, gfx->window);
		free_textures(gfx);
		mlx_destroy_display(gfx->mlx);
		free(gfx->mlx);
	}
	free_map(game->map);
	exit(0);
}

void	start_game(t_game *game)
{
	game->gfx.mlx = mlx_init();
	if (!game->gfx.mlx)
	{
		ft_printf("Error\n	MLX failed to initialize.\n");
		close_game(game, &game->gfx);
	}
	game->gfx.tile_size = TILE_SIZE;
	ft_bzero(&game->gfx.tx, sizeof(t_textures));
	if (!load_textures(&game->gfx))
		close_game(game, &game->gfx);
	game->gfx.window = mlx_new_window(game->gfx.mlx,
			game->width * game->gfx.tile_size,
			game->height * game->gfx.tile_size,
			"so_long");
	if (!game->gfx.window)
	{
		ft_printf("Error\n	Failed to create a Window.\n");
		close_game(game, &game->gfx);
	}
	render_map(game, &game->gfx);
	mlx_key_hook(game->gfx.window, handle_input_wrapper, game);
	mlx_hook(game->gfx.window, 17, 0, handle_exit, game);
	mlx_loop(game->gfx.mlx);
}
