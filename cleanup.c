/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:52:15 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/06/09 13:37:53 by rdhaibi          ###   ########.fr       */
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

static void	free_map_data(t_game *game)
{
	size_t	i;

	if (!game->data)
		return ;
	i = 0;
	while (i < game->height)
	{
		if (game->data[i])
			free(game->data[i]);
		i++;
	}
	free(game->data);
	game->data = NULL;
}

void	load_images(t_game *game)
	{
	int	w;
	int	h;

	game->player_img = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/player.xpm", &w, &h);
	game->wall_img = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/wall.xpm", &w, &h);
	game->floor_img = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/floor.xpm", &w, &h);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/collectible.xpm", &w, &h);
	game->exit_img = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/exit.xpm", &w, &h);
	if (!game->player_img || !game->wall_img || !game->floor_img
		|| !game->collectible_img || !game->exit_img)
	{
		ft_printf("Error\nCould not load one or more XPM images.\n");
		cleanup_and_exit(game, 1);
	}
}

int	handle_window_close(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}

void	cleanup_and_exit(t_game *game, int exit_status)
{
	free_map_data(game);
	if (game->player_img)
		mlx_destroy_image(game->mlx_ptr, game->player_img);
	if (game->wall_img)
		mlx_destroy_image(game->mlx_ptr, game->wall_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx_ptr, game->floor_img);
	if (game->collectible_img)
		mlx_destroy_image(game->mlx_ptr, game->collectible_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx_ptr, game->exit_img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(exit_status);
}
