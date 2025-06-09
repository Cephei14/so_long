/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:16:44 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/06/09 12:14:42 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	allocate_map_data(t_game *game)
{
	game->data = malloc(sizeof(char *) * (game->height + 1));
	if (!game->data)
		return (ft_printf("Error\nMalloc failed\n"), ERROR);
	game->data[game->height] = NULL;
	return (SUCCESS);
}

static int	store_map_data(const char *filename, t_game *game)
{
	int		fd;
	char	*line;
	size_t	i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	i = 0;
	while (i < game->height)
	{
		line = get_next_line(fd);
		game->data[i] = ft_substr(line, 0, get_line_length(line));
		free(line);
		if (!game->data[i])
		{
			close(fd);
			ft_printf("Error\nMalloc failed for map line\n");
			return (ERROR);
		}
		i++;
	}
	close(fd);
	return (SUCCESS);
}

static int	check_walls(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->width)
	{
		if (game->data[0][i] != '1' || game->data[game->height - 1][i] != '1')
			return (ft_printf("Error\nMap is not enclosed by walls\n"), ERROR);
		i++;
	}
	i = 0;
	while (i < game->height)
	{
		if (game->data[i][0] != '1' || game->data[i][game->width - 1] != '1')
			return (ft_printf("Error\nMap is not enclosed by walls\n"), ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	check_map_content(t_game *game)
{
	if (check_walls(game) == ERROR)
		return (ERROR);
	if (check_content_and_count(game) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	parse_and_validate_map(const char *filename, t_game *game)
{
	int	fd;

	if (name_check(filename) == ERROR)
		return (ft_printf("Error\nInvalid file extension\n"), ERROR);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nCould not open file\n"), ERROR);
	if (get_map_dimensions(fd, game) == ERROR)
	{
		close(fd);
		return (ERROR);
	}
	close(fd);
	if (game->width < 3 || game->height < 3)
	{
		ft_printf("Error\nMap is too small\n");
		return (ERROR);
	}
	if (allocate_map_data(game) == ERROR)
		return (ERROR);
	if (store_map_data(filename, game) == ERROR)
		return (ERROR);
	if (check_map_content(game) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
