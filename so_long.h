/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:16:38 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/06/06 21:45:49 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
#include <fcntl.h>

# define ERROR 1
# define SUCCESS 0
# define TILE_SIZE 64
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_game {
    char    **data;
    size_t  width;
    size_t  height;
    void    *mlx_ptr;
    void    *win_ptr;
    void    *player_img;
    void    *wall_img;
    void    *floor_img;
    void    *collectible_img;
    void    *exit_img;
    int     player_x;
    int     player_y;
    int     moves;
    int     collectibles_left;
} t_game;

int		name_check(const char *filename);
int		parse_and_validate_map(const char *file_name, t_game *game);
void    cleanup_and_exit(t_game *game, int exit_status);
void    load_images(t_game *game);
void    render_map(t_game *game);
int     handle_keypress(int keycode, t_game *game);
int     handle_window_close(t_game *game);

#endif