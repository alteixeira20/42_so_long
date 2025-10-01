/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:59:13 by paalexan          #+#    #+#             */
/*   Updated: 2025/10/01 16:18:42 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

static int	is_rectangular(char **map)
{
	int	i;

	i = 0;
	while (map[i] && map[i + 1])
	{
		if (ft_strlen(map[i]) != ft_strlen(map[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

static int	are_walls_valid(char **map)
{
	int	i;
	int	last_row;
	int	len;

	i = 0;
	last_row = get_last_row(map);
	len = ft_strlen(map[0]) - 2;
	while (i <= len)
	{
		if (map[0][i] != '1' || map[last_row][i] != '1')
			return (0);
		i++;
	}
	i = 1;
	while (i < last_row)
	{
		if (map[i][0] != '1' || map[i][len] != '1')
			return (0);
		i++;
	}
	return (1);
}

static void	count_components(char **map, int *start, int *exit, int *rewards)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				(*start)++;
			else if (map[i][j] == 'E')
				(*exit)++;
			else if (map[i][j] == 'C')
				(*rewards)++;
			j++;
		}
		i++;
	}
}

static int	check_components(char **map)
{
	int	start_pos;
	int	exit_pos;
	int	rewards;

	start_pos = 0;
	exit_pos = 0;
	rewards = 0;
	count_components(map, &start_pos, &exit_pos, &rewards);
	if (!check_components_errors(start_pos, exit_pos, rewards))
		return (0);
	return (1);
}

int	is_map_valid(char **map)
{
	if (!is_rectangular(map))
	{
		ft_printf("Error\n	Map is not retangular.\n");
		return (0);
	}
	if (!are_walls_valid(map))
	{
		ft_printf("Error\n	Map has invalid wall configuration.\n");
		return (0);
	}
	if (!check_components(map))
		return (0);
	if (!is_map_solvable(map))
	{
		ft_printf("Error\n	Map is not solvable.\n");
		return (0);
	}
	if (!check_invalid_chars(map))
	{
		ft_printf("Error\n	Invalid chars found.\n");
		return (0);
	}
	return (1);
}
