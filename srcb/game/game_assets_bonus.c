/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_assets_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:35:38 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/28 16:07:41 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static int	load_image(void **img, void *mlx, char *path)
{
	int	w;
	int	h;

	*img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!*img)
	{
		ft_printf("Error\n	Failed to load %s\n", path);
		return (0);
	}
	return (1);
}

int	load_textures(t_graphics *gfx)
{
	if (!load_image(&gfx->tx.floor, gfx->mlx, FLOOR)
		|| !load_image(&gfx->tx.wall, gfx->mlx, WALL)
		|| !load_image(&gfx->tx.collectible, gfx->mlx, COLLECT)
		|| !load_image(&gfx->tx.exit, gfx->mlx, EXIT)
		|| !load_anim(gfx, &gfx->tx.move_anim[0], MOVE_UP, MOVE_FRAMES)
		|| !load_anim(gfx, &gfx->tx.move_anim[1], MOVE_DOWN, MOVE_FRAMES)
		|| !load_anim(gfx, &gfx->tx.move_anim[2], MOVE_LEFT, MOVE_FRAMES)
		|| !load_anim(gfx, &gfx->tx.move_anim[3], MOVE_RIGHT, MOVE_FRAMES)
		|| !load_anim(gfx, &gfx->tx.mining_anim[0], MINE_UP, MINE_FRAMES)
		|| !load_anim(gfx, &gfx->tx.mining_anim[1], MINE_DOWN, MINE_FRAMES)
		|| !load_anim(gfx, &gfx->tx.mining_anim[2], MINE_LEFT, MINE_FRAMES)
		|| !load_anim(gfx, &gfx->tx.mining_anim[3], MINE_RIGHT, MINE_FRAMES))
		return (0);
	return (1);
}

void	free_mining_textures(t_graphics *gfx)
{
	int	dir;
	int	i;

	dir = 0;
	while (dir < 4)
	{
		if (gfx->tx.mining_anim[dir].frames)
		{
			i = 0;
			while (i < gfx->tx.mining_anim[dir].frame_count)
			{
				if (gfx->tx.mining_anim[dir].frames[i])
					mlx_destroy_image(gfx->mlx,
						gfx->tx.mining_anim[dir].frames[i]);
				i++;
			}
			free(gfx->tx.mining_anim[dir].frames);
		}
		dir++;
	}
}

void	free_move_textures(t_graphics *gfx)
{
	int	dir;
	int	i;

	dir = 0;
	while (dir < 4)
	{
		if (gfx->tx.move_anim[dir].frames)
		{
			i = 0;
			while (i < gfx->tx.move_anim[dir].frame_count)
			{
				if (gfx->tx.move_anim[dir].frames[i])
					mlx_destroy_image(gfx->mlx,
						gfx->tx.move_anim[dir].frames[i]);
				i++;
			}
			free(gfx->tx.move_anim[dir].frames);
		}
		dir++;
	}
}

void	free_static_textures(t_graphics *gfx)
{
	if (gfx && gfx->mlx && gfx->tx.floor)
		mlx_destroy_image(gfx->mlx, gfx->tx.floor);
	if (gfx && gfx->mlx && gfx->tx.wall)
		mlx_destroy_image(gfx->mlx, gfx->tx.wall);
	if (gfx && gfx->mlx && gfx->tx.collectible)
		mlx_destroy_image(gfx->mlx, gfx->tx.collectible);
	if (gfx && gfx->mlx && gfx->tx.exit)
		mlx_destroy_image(gfx->mlx, gfx->tx.exit);
}
