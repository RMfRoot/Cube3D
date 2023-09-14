/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:43:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/14 16:37:03 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialize(t_cub *cub)
{
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		error(cub, ERRMLX, NULL);
	cub->mlx.mlx_win = mlx_new_window(cub->mlx.mlx, WIN_X, WIN_Y, "cub3D");
	if (SIZE_OF_CASES % 24 != 0)
		error(cub, INVALID_PARAM, " SIZE_OF_CASES must be multiple of 24 in cub3d.h");
	cub->player.pos.x = 0;
	cub->player.pos.y = 0;
	cub->keys.w = false;
	cub->keys.a = false;
	cub->keys.s = false;
	cub->keys.d = false;
	cub->keys.r_left = false;
	cub->keys.r_right = false;
	cub->WIN_X = WIN_X;
	cub->WIN_Y = WIN_Y;
}

static void	free_cub(t_cub *cub)
{
	freetab((void **)cub->errors);
	freetab((void **)cub->params.map);
	free(cub->params.n_text);
	free(cub->params.s_text);
	free(cub->params.e_text);
	free(cub->params.w_text);
	free(cub->params.ceiling_color);
	free(cub->params.floor_color);
	mlx_destroy_image(cub->mlx.mlx, cub->params.texture_east.img.img);
	mlx_destroy_image(cub->mlx.mlx, cub->params.texture_north.img.img);
	mlx_destroy_image(cub->mlx.mlx, cub->params.texture_south.img.img);
	mlx_destroy_image(cub->mlx.mlx, cub->params.texture_west.img.img);
	mlx_destroy_image(cub->mlx.mlx, cub->minimap.img.img);
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.mlx_win);
}
//for unkown reasons if cub is not freed, leaks are present.

static int	run_game(t_cub *cub)
{
	if (movement(cub))
	{
		render(cub);
		mlx_clear_window(cub->mlx.mlx, cub->mlx.mlx_win);
        mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.mlx_win, cub->view.img, 0, 0);
		minimap_update(cub);
	}
	return (0);
}

static int	end(void)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	error_init(&cub);
	if (argc != 2)
		error(&cub, NB_ARG, NULL);
	initialize(&cub);
	get_params(&cub, argv[1]);
	minimap_initialize(&cub);
	create_image(&cub.mlx, &cub.view, WIN_X, WIN_Y);
	minimap_update(&cub);
	render(&cub);
    mlx_put_image_to_window(cub.mlx.mlx, cub.mlx.mlx_win, cub.view.img, 0, 0);
	mlx_hook(cub.mlx.mlx_win, 17, 0L, end, &cub);
	mlx_hook(cub.mlx.mlx_win, 02, 1L << 0, key_press, &cub);
	mlx_key_hook(cub.mlx.mlx_win, key_release, &cub);
	mlx_loop_hook(cub.mlx.mlx, run_game, &cub);
	mlx_loop(cub.mlx.mlx);
	free_cub(&cub);
}
