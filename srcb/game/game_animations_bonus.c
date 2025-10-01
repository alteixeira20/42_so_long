/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_animations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:17:37 by paalexan          #+#    #+#             */
/*   Updated: 2025/10/01 16:21:39 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

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

static void	init_anim_ctx(t_anim_ctx *ctx, t_game *game, t_anim *anim, int dir)
{
	ctx->delta_x = 0;
	ctx->delta_y = 0;
	if (dir == 0)
		ctx->delta_y = -1;
	else if (dir == 1)
		ctx->delta_y = 1;
	else if (dir == 2)
		ctx->delta_x = -1;
	else if (dir == 3)
		ctx->delta_x = 1;
	ctx->start_x = game->player_x;
	ctx->start_y = game->player_y;
	ctx->dest_x = ctx->start_x + ctx->delta_x;
	ctx->dest_y = ctx->start_y + ctx->delta_y;
	ctx->origin_x = ctx->start_x * game->gfx.tile_size;
	ctx->origin_y = ctx->start_y * game->gfx.tile_size;
	ctx->index = 0;
	ctx->denom = anim->frame_count - 1;
	if (ctx->denom <= 0)
		ctx->denom = 1;
}

void	play_move_anim(t_game *game, t_anim *anim, int dir)
{
	int			step;
	t_anim_ctx	ctx;

	init_anim_ctx(&ctx, game, anim, dir);
	while (ctx.index < anim->frame_count)
	{
		draw_tile(game, &game->gfx, ctx.start_x, ctx.start_y);
		if (ctx.dest_x >= 0 && ctx.dest_x < game->width
			&& ctx.dest_y >= 0 && ctx.dest_y < game->height)
			draw_tile(game, &game->gfx, ctx.dest_x, ctx.dest_y);
		step = (game->gfx.tile_size * ctx.index) / ctx.denom;
		mlx_put_image_to_window(game->gfx.mlx, game->gfx.window,
			anim->frames[ctx.index],
			ctx.origin_x + (ctx.delta_x * step),
			ctx.origin_y + (ctx.delta_y * step));
		usleep(anim->delay * 242);
		mlx_do_sync(game->gfx.mlx);
		ctx.index++;
	}
	game->p_frame = 0;
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
