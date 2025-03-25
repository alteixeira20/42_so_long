/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:35:38 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/24 22:02:04 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
		|| !load_image(&gfx->tx.player[0], gfx->mlx, P_UP)
		|| !load_image(&gfx->tx.player[1], gfx->mlx, P_DOWN)
		|| !load_image(&gfx->tx.player[2], gfx->mlx, P_LEFT)
		|| !load_image(&gfx->tx.player[3], gfx->mlx, P_RIGHT))
		return (0);
	return (1);
}

void	free_textures(t_graphics *gfx)
{
	int	i;

	if (gfx && gfx->mlx && gfx->tx.floor)
		mlx_destroy_image(gfx->mlx, gfx->tx.floor);
	if (gfx && gfx->mlx && gfx->tx.wall)
		mlx_destroy_image(gfx->mlx, gfx->tx.wall);
	if (gfx && gfx->mlx && gfx->tx.collectible)
		mlx_destroy_image(gfx->mlx, gfx->tx.collectible);
	if (gfx && gfx->mlx && gfx->tx.exit)
		mlx_destroy_image(gfx->mlx, gfx->tx.exit);
	i = 0;
	while (i < 4)
	{
		if (gfx && gfx->mlx && gfx->tx.player[i])
			mlx_destroy_image(gfx->mlx, gfx->tx.player[i]);
		i++;
	}
}
