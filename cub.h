/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:59:17 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/28 15:13:44 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <math.h>

# define HEIGHT 668 // 768
# define WIDTH 1024
# define IMG_COUNT 6
# define PIXEL 48
# define FOV 0.66
// MOVE
# define ROT_SPEED 0.02
# define MOVE_SPEED 0.04
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Z 122
# define KEY_Q 113
# define KEY_ESC 65307
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
// IMG
# define NO_TEXTURE 0
# define SO_TEXTURE 1
# define WE_TEXTURE 2
# define EA_TEXTURE 3
# define PLAYER 4
# define BACKGROUND 5
# define MINI_MAP 6

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct s_size
{
	int			screen_width;
	int			screen_height;
}				t_size;

typedef struct s_map
{
	int			height;
	int			width;
	char		**map_tab;
	int			**map_int;
}				t_map;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			endian;
	int			bpp;
	int			line_len;
	int			width;
	int			height;
}				t_img;

typedef struct s_player
{
	double		pos_y;
	double		pos_x;
	double		next_y;
	double		next_x;
}				t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		*img[IMG_COUNT];
}				t_mlx;

typedef struct s_raycast
{
	double		camera_x;
	double		ray_x;
	double		ray_y;
	double		dir_x;
	double		dir_y;
	double		delta_x;
	double		delta_y;
	double		plane_x;
	double		plane_y;
	double		side_x;
	double		side_y;
	double		step_x;
	double		step_y;
	double		line_height;
	double		wall_dist;
	int			map_x;
	int			map_y;
	int			side;
	int			texture;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			tex_y;
	double		tex_p;
	double		wall_x;

}				t_raycast;

typedef struct s_move
{
	int			z;
	int			s;
	int			q;
	int			d;
	int			l;
	int			r;
}				t_move;

typedef struct s_data
{
	t_map		*map;
	t_mlx		*mlx;
	t_player	*player;
	t_raycast	*raycast;
	t_move		move;
	t_color		*texture_f;
	t_color		*texture_c;
	char		*texture_n;
	char		*texture_s;
	char		*texture_e;
	char		*texture_w;

}				t_data;

/*		PARSE				*/
char			**ft_read_map(char *map);
int				ft_check_existance(char *texture);
int				ft_check_map(char **map);
int				ft_get_data(t_data *data, char **file);
int				ft_check_map_extension(char *file);
int				ft_count_line(char *map);
int				ft_check_line(char *str);
int				ft_check_data(t_data *data);
int				ft_check_one_extension(char *map);
void			ft_skip_whitespaces(char **file, int *i, int *j);
int				ft_get_textures(char **file, t_data *data, int i, int j);
int				ft_get_textures_part2(char **file, t_data *data, int i, int j);
int				ft_set_textures_struct(t_data *data, char *file, char zone);

/*		PARSE_MAP*/
int				ft_check_map_closed(char **map);
int				ft_check_player(char **map);
void			ft_get_map(char **file, int *i, int j, t_data *data);

/*		INIT		*/
int				ft_clean_init_data(t_data *data);
int				ft_clean_init_player(t_data *data);
int				ft_clean_init_raycast(t_data *data);
void			ft_clean_init_move(t_data *data);
int				mlx_start(t_data *data);
int				mlx_window_init(t_data *data);
// int				ft_clean_init_mlx(t_data *data);

/*		UTILS		*/
size_t			ft_longest_line(char **map);
int				**ft_convert_map(char **map);
char			*ft_get_textures_path(char *path, char *entry);
char			*ft_join_to_comb_empty(char *line, size_t longest_line);

/*		FREE		*/
int				ft_free_img(t_mlx *mlx, int n);
int				ft_free_data(t_data *data);
int				ft_free_exit(t_data *data);
void			ft_free_mlx(t_mlx *mlx);

/*		CHECK_TEXTURES		*/
int				ft_check_textures(t_data *data);
int				ft_check_rgb(t_data *data);
t_img			*ft_init_img(t_mlx *mlx, char *path);

/*		CONVERT_MAP			*/
int				**ft_convert_map(char **map);

/*		RAYCASTING		*/
void			init_raycasting(t_data *data, int i);
void			ft_raycasting(t_data *data);
int				ft_get_player_pos(t_data *data);
int				ft_get_player_dir(t_data *data);

/*		DRAW				*/
void			draw_player_to_image(t_data *data);
void			put_texture(t_data *data, int i);
/*		DRAW UTILS			*/
void			put_pixel(t_img *img, int x, int y, int color);
void			put_img_to_img(t_data *data, t_img src, int x, int y);
int				load_background(t_data *data);
int				rgb_to_int(int r, int g, int b);
unsigned int	get_pixel(t_img img, int x, int y);

/*		MOVE				*/
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				ft_rotate(t_data *data);
int				ft_move(t_data *data);

int				ft_play(t_data *data);
void			ft_display_game(t_data *data);

#endif
