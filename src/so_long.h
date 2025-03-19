/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:00:30 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/19 19:39:10 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf_bonus.h"
# include "../libft/gnl/get_next_line_bonus.h"

// Map Functions
int		get_map_height(char *mapname);
int		get_last_row(char **map);
int		check_components_errors(int start_pos, int exit_pos, int reward);
char	**read_map(char *mapname);
char	**duplicate_map(char **map);
int		is_map_valid(char **map);
int		is_map_solvable(char **map);
void	free_map(char **map);
void	free_dup(char **dup);

#endif
