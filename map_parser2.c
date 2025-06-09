/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:12:50 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/06/09 13:25:00 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	get_line_length(const char *line)
{
	size_t	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		return (len - 1);
	return (len);
}

int	get_map_dimensions(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (ft_printf("Error\nMap is empty\n"), ERROR);
	game->width = get_line_length(line);
	game->height = 0;
	while (line)
	{
		game->height++;
		if (get_line_length(line) != game->width)
		{
			free(line);
			return (ft_printf("Error\nMap is not rectangular\n"), ERROR);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (game->width == 0)
		return (ft_printf("Error\nMap contains empty lines\n"), ERROR);
	return (SUCCESS);
}

void	update_counts(char tile, t_game *game, size_t x, size_t y)
{
	if (tile == 'P')
	{
		game->p_count++;
		game->player_x = x;
		game->player_y = y;
	}
	else if (tile == 'C')
		game->collectibles_left++;
	else if (tile == 'E')
		game->e_count++;
}

int	validate_counts(t_game *game, int p_count, int e_count)
{
	if (p_count != 1 || e_count != 1 || game->collectibles_left < 1)
		return (ft_printf("Error\nInvalid number of P, C, or E\n"), ERROR);
	return (SUCCESS);
}

int	check_content_and_count(t_game *game)
{
	size_t	y;
	size_t	x;
	char	tile;

	y = -1;
	game->p_count = 0;
	game->e_count = 0;
	game->collectibles_left = 0;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			tile = game->data[y][x];
			if (!ft_strchr("01CEP", tile))
			{
				ft_printf("Error\nInvalid char '%c' in map\n", tile);
				return (ERROR);
			}
			update_counts(tile, game, x, y);
		}
	}
	if (game->p_count != 1 || game->e_count != 1 || game->collectibles_left < 1)
		return (ft_printf("Error\nInvalid number of P, C, or E\n"), ERROR);
	return (SUCCESS);
}
