/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:00:30 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/18 18:09:00 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// Map Functions
int		get_map_height(char *mapname);
int		get_last_row(char **map);
int		check_components_errors(int start_pos, int exit_pos, int reward);
char	**read_map(char *mapname);
void	free_map(char **map, int height);

#endif
