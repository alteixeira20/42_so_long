/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:57:21 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/19 18:57:24 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
		ft_printf("Error\n	More than ONE or NO starting position detected.\n");
	if (exit_pos != 1)
		ft_printf("Error\n	More than ONE or NO exit detected.\n");
	if (reward < 1)
		ft_printf("Error\n	No rewards detected.\n");
	if (start_pos != 1 || exit_pos != 1 || reward < 1)
		return (0);
	return (1);
}
