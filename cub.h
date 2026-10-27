/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:59:17 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/27 16:58:38 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <sys/time.h>

# define HEIGHT 668 // 768
# define WIDTH 1024
# define IMG_COUNT 21
# define PIXEL 48
# define FOV 0.66
// MOVE
# define ROT_SPEED 0.02
# define MOVE_SPEED 2.0 // cells per second
# define PLAYER_MARGIN 0.2
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Z 122
# define KEY_Q 113
# define KEY_ESC 65307
# define KEY_TAB 65289
# define KEY_M 109
# define KEY_R 114
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
// IMG
# define NO_TEXTURE 0
# define SO_TEXTURE 1
# define WE_TEXTURE 2
# define EA_TEXTURE 3
# define BACKGROUND 4
# define MINI_MAP 5
# define DOOR 16
# define PLAYER 6
// MINI_MAP
# define MINI_R 100
# define MINI_POS 10
# define MINI_SCALE 30
# define MINI_SCALE_MIN 10
# define MINI_SCALE_MAX 80
# define BIG_MARGIN 40
# define BIG_ZOOM_MAX 8
# define MINI_PLAYER 4
# define MINI_BORDER 3
# define MINI_WALL 0xbb8fce
# define MINI_FLOOR 0xabb2b9
# define MINI_FOG 0x22222c
# define MINI_DOOR_CLOSED 0xe8436f
# define MINI_DOOR_MOVING 0xf5b041
# define MINI_DOOR_OPEN 0x58d68d
# define MINI_FOV_COLOR 0xfff3b0
# define MINI_BORDER_COLOR 0xf6b5fd
# define MINI_PLAYER_COLOR 0xff0000
// ANIMATION
# define PAW_FRAME_MS 50
# define DOOR_FRAME_MS 100

# define HUD_W 190
# define HUD_LINES 5
# define HUD_LINE_H 16
# define HUD_BUF 64

// AMBIANCE (warm and muffled)
# define FOG_COLOR 0xa07ca8
# define FOG_DENSITY 0.12
# define LIGHT_COLOR 0xfff0e6
# define SIDE_LIGHT 0.7
# define CEIL_LIGHT 0.6
# define FLOOR_LIGHT 0.8
# define VIGNETTE 0.3

# define D_CLOSED 0
# define D_OPENING 1
# define D_OPEN 2
# define D_CLOSING 3

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct s_map
{
	int			height;
	int			width;
	char		**map_tab;
	int			**map_int;
	char		*seen;
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
	int			box[4];
}				t_img;

typedef struct s_player
{
	double		pos_y;
	double		pos_x;
	double		next_y;
	double		next_x;
}				t_player;

typedef struct s_doors
{
	double		x;
	double		y;
	int			state;
	int			nb;
	int			anim_frame;
	long		last;
	double		dist_to_player;
}				t_doors;

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
	int			lit[3];
	int			fog[3];
	int			door_hit;
	int			door_map_x;
	int			door_map_y;
	int			door_side;
	double		zbuf[WIDTH];
}				t_raycast;

typedef struct s_move
{
	int			z;
	int			s;
	int			q;
	int			d;
	int			l;
	int			r;
	long		last;
}				t_move;

typedef struct s_hud
{
	int			show;
	int			frames;
	int			fps;
	long		last_fps;
	double		frame_ms;
	double		center_dist;
}				t_hud;

typedef struct s_mini
{
	double		scale;
	double		big_zoom;
	int			rotate;
	int			big;
}				t_mini;

typedef struct s_view
{
	double		wx;
	double		wy;
	double		scale;
	int			rotate;
}				t_view;

typedef struct s_amb
{
	int				vig_x[WIDTH];
	int				vig_y[HEIGHT];
	unsigned int	bg[HEIGHT];
}					t_amb;

typedef struct s_data
{
	t_map		*map;
	t_mlx		*mlx;
	t_player	*player;
	t_raycast	*raycast;
	t_doors		*doors;
	t_move		move;
	t_hud		hud;
	t_mini		mini;
	t_amb		amb;
	t_color		*texture_f;
	t_color		*texture_c;
	int			anim_frame;
	int			anim_running;
	long		anim_last;
	int			color_c;
	int			color_f;
	int			exit;
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
int				ft_set_textures_struct(t_data *data, char *file, char zone);
int				ft_get_textures_part2(char **file, t_data *data, int i, int j);

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
int				ft_clean_init_elements(t_data *data);
// int				ft_clean_init_mlx(t_data *data);

/*		UTILS		*/
size_t			ft_longest_line(char **map);
int				**ft_convert_map(char **map);
char			*ft_get_textures_path(char *path, char *entry);
char			*ft_join_to_comb_empty(char *line, size_t longest_line);
int				ft_counter(char **map, char element);

/*		FREE		*/
int				ft_free_img(t_mlx *mlx, int n);
int				ft_free_data(t_data *data);
// int				ft_free_exit(t_data *data);
void			ft_free_mlx(t_mlx *mlx);
void			ft_free_elements(t_data *data);

/*		CHECK_TEXTURES		*/
int				ft_check_textures(t_data *data);
int				ft_check_rgb(t_data *data);
t_img			*ft_init_img(t_mlx *mlx, char *path);
t_img			*ft_init_new_img(t_mlx *mlx, int width, int height);

/*		CONVERT_MAP			*/
int				ft_get_max_width(char **map);
int				**ft_convert_map(char **map);

/*		RAYCASTING		*/
void			init_raycasting(t_data *data, int i);
void			ft_raycasting(t_data *data);
int				ft_get_player_pos(t_data *data);
int				ft_get_player_dir(t_data *data);

/*		DRAW				*/
void			draw_player_to_image(t_data *data);
long			get_time_ms(void);
void			draw_background_column(t_data *data, int x);
void			put_texture(t_data *data, int i);

/*		DRAW UTILS			*/
void			put_pixel(t_img *img, int x, int y, int color);
void			put_img_to_img(t_data *data, t_img *src);
// void			put_img_to_img(t_data *data, t_img src, int x, int y);
// int				load_background(t_data *data);
int				rgb_to_int(int r, int g, int b);
unsigned int	get_pixel(t_img *img, int x, int y);
void			put_shade(t_data *data, int i, int y);

/*		AMBIANCE			*/
void			init_ambiance(t_data *data);
void			init_vignette(t_data *data);
void			column_light(t_data *data);
unsigned int	shade_pixel(t_data *data, unsigned int c, int x, int y);

/*		MOVE				*/
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				ft_rotate(t_data *data);
int				ft_move(t_data *data);

void			ft_display_game(t_data *data);
int				mouse_move(int x, int y, t_data *data);

/*		MINI_MAP			*/
void			load_mini_map(t_data *data);
void			draw_mini_north(t_data *data);
void			draw_big_map(t_data *data);
void			map_keys(int keycode, t_data *data);
void			map_zoom(t_data *data, int zoom_in);
unsigned int	map_pixel(t_data *data, t_view *v, int x, int y);
unsigned int	mix(unsigned int a, unsigned int b);

int				animation_paws(t_data *data);
int				animation_doors(t_data *data);
t_doors			*get_door(t_data *data, int x, int y);
void			set_door_texture(t_data *data);
void			set_door_state(t_data *data, t_doors *door, int state);
int				door_blocks(t_data *data, double x, double y);
int				player_in_door(t_data *data, t_doors *door);
int				door_along_y(t_data *data, int cx, int cy);
t_doors			*door_in_front(t_data *data);

/*		HUD					*/
void			hud_update(t_data *data);
void			hud_draw_box(t_data *data);
void			hud_draw_text(t_data *data);
void			hud_cat_int(char *buf, long n);
void			hud_cat_double(char *buf, double v);
void			hud_darken(t_img *img, int x0, int y0);
int				mouse_press(int button, int x, int y, t_data *data);

#endif
