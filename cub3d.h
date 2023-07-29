/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:44:30 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/28 17:30:40 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
//# include "minilibx_opengl/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h"

# define MAP_SIDE 2
# define WIN_X 1900
# define WIN_Y 1040

typedef enum e_param_type
{
	INT_PARAM,
	STR_PARAM
}	t_param_type;

/*ERRORS*/

typedef enum e_err
{
	ERRMLX,
	ERRFILE,
	MISSING_PARAM,
	INVALID_PARAM,
	DOUBLE_PARAM,
	TOMANY_PARAM,
	PARAM_AFTER_MAP,
	NOMAP,
	NOPLAYER,
	MULTIPLE_PLAYERS,
	INVALID_MAP_CHARACTER,
	MAPHOLE,
	ERRCOLOR,
	ERRMAX,
}	t_err;

/*STRUCT*/

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_coordinates
{
	double	x;
	double	y;
}	t_coordinates;

typedef struct s_player
{
	t_coordinates	pos;
	double			angle;
}	t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

typedef struct s_minimap
{
	t_img	img;
	int		size_x;
	int		size_y;
}	t_minimap;

typedef struct s_param
{
	char			**map;
	char			*n_text;
	char			*s_text;
	char			*w_text;
	char			*e_text;
	int				*floor_color;
	int				*ceiling_color;
}	t_param;

typedef struct s_cub
{
	t_mlx		mlx;
	t_param		params;
	t_player	player;
	t_minimap	minimap;
	char		**errors;
}	t_cub;

/*PARSING*/
void	get_params(t_cub *cub, char *filename);
void	*get_param(t_cub *cub, char **file, char *param_name, int param_type);
void	get_map(t_cub *cub, char **file);
void	map_parse(t_cub *cub);
void	error_init(t_cub *cub);
void	error(t_cub *cub, int err, char *arg);

/*MINIMAP*/

/*UTILS*/
int		line_size(char *line);
int		map_size(char **map);
char	*extract_second_word(t_cub *cub, char **line);
int		get_color(t_cub *cub, const char *str);
void	freetab(void **tab);
bool	empty_line(char *line);
void	create_image(t_mlx *mlx, t_img *img, int width, int height);
void	pixel_to_img(t_img *img, int x, int y, int color);

#endif