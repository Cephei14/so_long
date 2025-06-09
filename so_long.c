/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:16:41 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/06/09 11:46:08 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void init_game_struct(t_game *game)
{
    game->mlx_ptr = NULL;
    game->win_ptr = NULL;
    game->data = NULL;
    game->width = 0;
    game->height = 0;
    game->player_img = NULL;
    game->wall_img = NULL;
    game->floor_img = NULL;
    game->collectible_img = NULL;
    game->exit_img = NULL;
    game->player_x = 0;
    game->player_y = 0;
    game->moves = 0;
    game->collectibles_left = 0;
}

static void move_player(t_game *game, int new_x, int new_y)
{
    char next_tile;

    next_tile = game->data[new_y][new_x];
    if (next_tile == '1')
        return;
    if (next_tile == 'E')
    {
        if (game->collectibles_left == 0)
        {
            ft_printf("You win! Total moves: %d\n", game->moves + 1);
            cleanup_and_exit(game, 0);
        }
        return;
    }
    game->player_x = new_x;
    game->player_y = new_y;
    game->moves++;
    ft_printf("Moves: %d\n", game->moves);
    if (next_tile == 'C')
    {
        game->collectibles_left--;
        game->data[new_y][new_x] = '0';
    }
    render_map(game);
}

int handle_keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        cleanup_and_exit(game, 0);
    else if (keycode == KEY_W)
        move_player(game, game->player_x, game->player_y - 1);
    else if (keycode == KEY_A)
        move_player(game, game->player_x - 1, game->player_y);
    else if (keycode == KEY_S)
        move_player(game, game->player_x, game->player_y + 1);
    else if (keycode == KEY_D)
        move_player(game, game->player_x + 1, game->player_y);
    return (0);
}

int handle_window_close(t_game *game)
{
    cleanup_and_exit(game, 0);
    return (0);
}

// In so_long.c
void    render_map(t_game *game)
{
    size_t  y;
    size_t  x;

    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            char tile_type = game->data[y][x];
            void *image_to_draw;

            // Step 1: Draw the background tile (floor or wall)
            if (tile_type == '1')
                image_to_draw = game->wall_img;
            else
                image_to_draw = game->floor_img;
            mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                image_to_draw, x * TILE_SIZE, y * TILE_SIZE);

            // Step 2: If the tile is a C or E, draw it on top of the floor
            if (tile_type == 'C')
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                    game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
            else if (tile_type == 'E')
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                    game->exit_img, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
        game->player_img, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}

int main(int ac, char **av)
{
    t_game game;

    if (ac != 2)
    {
        ft_printf("Error: Please provide a map file.\n");
        return (1);
    }
    init_game_struct(&game);
    if (parse_and_validate_map(av[1], &game) == ERROR)
        cleanup_and_exit(&game, 1);
    game.mlx_ptr = mlx_init();
    if (!game.mlx_ptr)
        cleanup_and_exit(&game, 1);
    game.win_ptr = mlx_new_window(game.mlx_ptr, game.width * TILE_SIZE,
                                 game.height * TILE_SIZE, "So Long!");
    if (!game.win_ptr)
        cleanup_and_exit(&game, 1);
    load_images(&game);
    render_map(&game);
	mlx_key_hook(game.win_ptr, handle_keypress, &game);
    mlx_hook(game.win_ptr, 17, 0, handle_window_close, &game);
    mlx_loop(game.mlx_ptr);
    cleanup_and_exit(&game, 0);
    return (0);
}
