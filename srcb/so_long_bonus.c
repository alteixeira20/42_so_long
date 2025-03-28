/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:44:41 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/28 16:13:07 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	is_ready(char **map)
{
	if (!map)
	{
		ft_printf("Error\n	Map not found!\n");
		free_map(map);
		return (0);
	}
	if (!is_map_valid(map))
	{
		free(map);
		return (0);
	}
	if (!is_map_solvable(map))
	{
		free(map);
		return (0);
	}
	return (1);
}

static void	set_start_pos(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	**map;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long <mapname.ber>\n");
		return (1);
	}
	map = read_map(argv[1]);
	if (!is_ready(map))
		return (1);
	game.map = map;
	set_start_pos(&game);
	game.width = ft_strlen(map[0]) - 1;
	game.height = get_last_row(map) + 1;
	game.moves = 0;
	game.collectibles = count_collectibles(map);
	game.p_dir = 1;
	game.p_frame = 0;
	start_game(&game);
	return (0);
}
