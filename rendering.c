/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:44:05 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/06/09 13:54:33 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_game *game, size_t y, size_t x)
{
	char	tile_type;
	void	*img;

	tile_type = game->data[y][x];
	if (tile_type == '1')
		img = game->wall_img;
	else
		img = game->floor_img;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		img, x * TILE_SIZE, y * TILE_SIZE);
	if (tile_type == 'C')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile_type == 'E')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->exit_img, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_tile(game, y, x);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player_img,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}
