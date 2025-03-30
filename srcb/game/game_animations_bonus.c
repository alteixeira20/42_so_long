/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_animations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:17:37 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/30 15:16:37 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static char	*generate_frame_path(const char *prefix, int index)
{
	char	*num;
	char	*ext;
	char	*full;

	num = ft_itoa(index);
	if (!num)
		return (NULL);
	ext = ft_strjoin(num, ".xpm");
	free(num);
	if (!ext)
		return (NULL);
	full = ft_strjoin(prefix, ext);
	free(ext);
	return (full);
}

static void	set_offset(t_player *offset, int dir)
{
	offset->x = 0;
	offset->y = 0;
	if (dir == 0)
		offset->y = -1;
	else if (dir == 1)
		offset->y = 1;
	else if (dir == 2)
		offset->x = -1;
	else if (dir == 3)
		offset->x = 1;
}

void	play_move_anim(t_game *game, t_anim *anim, int dir)
{
	int			i;
	int			step;
	t_player	offset;
	int			px;
	int			py;

	set_offset(&offset, dir);
	i = 0;
	while (i < anim->frame_count)
	{
		step = (game->gfx.tile_size * i) / anim->frame_count;
		px = (game->player_x * game->gfx.tile_size) + (offset.x * step);
		py = (game->player_y * game->gfx.tile_size) + (offset.y * step);
		if (dir == 0 && game->map[game->player_y + 1][game->player_x] == '0')
			mlx_put_image_to_window(game->gfx.mlx, game->gfx.window,
				game->gfx.tx.floor, px, py + game->gfx.tile_size);
		if (dir == 1 && game->map[game->player_y - 1][game->player_x] == '0')
			mlx_put_image_to_window(game->gfx.mlx, game->gfx.window,
				game->gfx.tx.floor, px, py - game->gfx.tile_size);
		mlx_put_image_to_window(game->gfx.mlx, game->gfx.window,
			anim->frames[i], px, py);
		usleep(anim->delay * 242);
		mlx_do_sync(game->gfx.mlx);
		i++;
	}
}

void	play_mining_anim(t_graphics *gfx, t_anim *animation, int x, int y)
{
	int	i;

	i = 0;
	while (i < animation->frame_count)
	{
		mlx_put_image_to_window(gfx->mlx, gfx->window,
			animation->frames[i], x * gfx->tile_size, y * gfx->tile_size);
		mlx_do_sync(gfx->mlx);
		usleep(animation->delay * 1000);
		i++;
	}
}

int	load_anim(t_graphics *gfx, t_anim *anim, char *prefix, int count)
{
	char	*path;
	int		i;
	int		w;
	int		h;

	anim->frames = malloc(sizeof(void *) * count);
	if (!anim->frames)
		return (0);
	i = 0;
	while (i < count)
	{
		path = generate_frame_path(prefix, i);
		anim->frames[i] = mlx_xpm_file_to_image(gfx->mlx, path, &w, &h);
		if (!anim->frames[i])
		{
			ft_printf("Error\n	Failed to load %s\n", path);
			free(path);
			return (0);
		}
		free(path);
		i++;
	}
	anim->frame_count = count;
	anim->delay = 100;
	return (1);
}
