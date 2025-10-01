/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:57:21 by paalexan          #+#    #+#             */
/*   Updated: 2025/10/01 16:18:43 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

int	get_last_row(char **map)
{
	int	i;

	i = 0;
	while (map[i] && map[i + 1])
		i++;
	return (i);
}

int	check_components_errors(int start_pos, int exit_pos, int reward)
{
	if (start_pos != 1)
	{
		ft_printf("Error\n	More than ONE or NO starting position detected.\n");
		return (0);
	}
	if (exit_pos != 1)
	{
		ft_printf("Error\n	More than ONE or NO exit detected.\n");
		return (0);
	}
	if (reward < 1)
	{
		ft_printf("Error\n	No rewards detected.\n");
		return (0);
	}
	return (1);
}

int	count_collectibles(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static int	is_char_valid(char c)
{
	if (c == '1' || c == '0' || c == 'P' || c == 'E' || c == 'C' || c == 'X')
		return (1);
	return (0);
}

int	check_invalid_chars(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (!is_char_valid(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
