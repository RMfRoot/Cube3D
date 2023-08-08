/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:52:18 by egeorgel          #+#    #+#             */
/*   Updated: 2023/08/05 22:39:41 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_to_minimap(t_cub *cub)
{
	int	y;
	int	i;
	int	line_start;
	int	line_size;

	y = cub->minimap.size_y / 2 - 5;
	line_start = cub->minimap.size_x / 2;
	line_size = 1;
	while (++y < cub->minimap.size_y / 2 - 1)
	{
		i = line_start - 1;
		while (++i < cub->minimap.size_x / 2 + line_size)
			pixel_to_img(&cub->minimap.img, i, y, MINIMAP_PLAYER_COLOR);
		line_start--;
		line_size++;
	}
	while (y < cub->minimap.size_y / 2 + 4)
	{
		i = line_start - 1;
		while (++i < cub->minimap.size_x / 2 + line_size)
			pixel_to_img(&cub->minimap.img, i, y, MINIMAP_PLAYER_COLOR);
		line_start++;
		line_size--;
		y++;
	}
}
//doing a red rotated scare on the minimap

static unsigned int	get_minimap_color(t_cub *cub, int y, int x)
{
	char	**map;

	x /= 24;
	y /= 24;
	map = cub->params.map;
	if (map[y][x] == '1')
		return (MINIMAP_WALL_COLOR);
	else if (ft_strchr("EWSN0", map[y][x]))
		return (MINIMAP_FLOOR_COLOR);
	return (MINIMAP_EMPTY_COLOR);
}

static void	print_angle(t_cub *cub)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	y = cub->minimap.size_y / 2;
	x = cub->minimap.size_x / 2;
	while (i++ < 20)
	{
		y -= cos(cub->player.angle / 180 * PI);
		x -= sin(cub->player.angle / 180 * PI);
		pixel_to_img(&cub->minimap.img, x, y, MINIMAP_PLAYER_COLOR);
	}
}

static void	print_minimap(t_cub *cub)
{
	int	i;
	int	j;
	int	y;
	int	x;

	i = -1;
	y = cub->player.pos.y - cub->minimap.size_y / 2;
	while (++i < cub->minimap.size_y)
	{
		j = -1;
		x = cub->player.pos.x - cub->minimap.size_x / 2;
		while (++j < cub->minimap.size_x)
		{
			pixel_to_img(&cub->minimap.img, j, i, get_minimap_color(cub, y, x));
			x++;
		}
		y++;
	}
}

void	minimap_update(t_cub *cub)
{
	print_minimap(cub);
	player_to_minimap(cub);
	print_angle(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.mlx_win,
		cub->minimap.img.img, WIN_X - cub->minimap.size_x, 0);
}