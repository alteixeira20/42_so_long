/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:57:21 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/27 17:06:10 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

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
