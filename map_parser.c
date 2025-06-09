/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:16:44 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/06/09 11:46:05 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	name_check(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (ERROR);
	if (ft_strncmp(&filename[len - 4], ".ber", 4) == 0)
		return (SUCCESS);
	return (ERROR);
}

static	size_t get_line_length(const char *line)
{
	size_t	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		return (len - 1);
	return (len);
}

static int	get_map_dimensions(int fd, t_game *game)
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

static int allocate_map_data(t_game *game)
{
    game->data = malloc(sizeof(char *) * (game->height + 1));
    if (!game->data)
        return (ft_printf("Error\nMalloc failed\n"), ERROR);
    game->data[game->height] = NULL;
    return (SUCCESS);
}

static int store_map_data(const char *filename, t_game *game)
{
    int     fd;
    char    *line;
    size_t     i;

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

static int check_walls(t_game *game)
{
    size_t i;

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

static void update_counts(char tile, t_game *game, int *p, int *e, size_t x, size_t y)
{
    if (tile == 'P')
    {
        (*p)++;
        game->player_x = x;
        game->player_y = y;
    }
    else if (tile == 'C')
        game->collectibles_left++;
    else if (tile == 'E')
        (*e)++;
}
static int validate_counts(t_game *game, int p_count, int e_count)
{
    if (p_count != 1 || e_count != 1 || game->collectibles_left < 1)
        return (ft_printf("Error\nInvalid number of P, C, or E\n"), ERROR);
    return (SUCCESS);
}

static int check_content_and_count(t_game *game)
{
    size_t  y;
    size_t  x;
    int     p_count;
    int     e_count;

    y = -1;
    p_count = 0;
    e_count = 0;
    game->collectibles_left = 0;
    while (++y < game->height)
    {
        x = -1;
        while (++x < game->width)
        {
            char tile = game->data[y][x];
            if (!ft_strchr("01CEP", tile))
                return (ft_printf("Error\nInvalid char '%c' in map\n", tile), ERROR);
            update_counts(tile, game, &p_count, &e_count, x, y);
        }
    }
    return (validate_counts(game, p_count, e_count));
}

static int check_map_content(t_game *game)
{
    if (check_walls(game) == ERROR)
        return (ERROR);
    if (check_content_and_count(game) == ERROR)
        return (ERROR);
    return (SUCCESS);
}

int parse_and_validate_map(const char *filename, t_game *game)
{
    int     fd;

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
