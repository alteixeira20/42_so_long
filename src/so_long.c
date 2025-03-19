/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:44:41 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/19 21:06:31 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	main(int argc, char **argv)
{
	char	**map;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long <mapname.ber>\n");
		return (1);
	}
	map = read_map(argv[1]);
	if (!is_ready(map))
		return (1);
	ft_printf("Map was validated successfully.\n");
	//start_game(map);
	free_map(map);
	return (0);
}
