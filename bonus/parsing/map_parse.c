/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:58:54 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/17 20:16:37 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_player(t_cub *cub, char **map, int i, int j)
{
	cub->player.pos.y = i * SIZE_OF_CASES + SIZE_OF_CASES / 2;
	cub->player.pos.x = j * SIZE_OF_CASES + SIZE_OF_CASES / 2;
	if (map[i][j] == 'N')
		cub->player.angle = 90;
	else if (map[i][j] == 'W')
		cub->player.angle = 180;
	else if (map[i][j] == 'S')
		cub->player.angle = 270;
	else
		cub->player.angle = 0;
}

static void	spaces_to_0(char **map)
{
	int	start;
	int	end;
	int	i;

	i = -1;
	while (map[++i])
	{
		start = 0;
		end = ft_strlen(map[i]) - 1;
		while (map[i][start] && map[i][start] != '1')
			start++;
		while (end >= 0 && map[i][end] != '1')
			end--;
		while (map[i][start] && start < end)
		{
			if (map[i][start] == ' ')
				map[i][start] = '0';
			start++;
		}
	}
}

static void	check_element(t_cub *cub, char **map, int i, int j)
{
	if (map[i][j] == '0' && ((!map[i][j + 1] || map[i][j + 1] == ' ')
		|| map[i][j - 1] == ' ' || map[i - 1][j] == ' '
		|| (!map[i + 1][j] || map[i + 1][j] == ' ')))
	{
		error(cub, MAPHOLE, NULL);
	}
	if (!ft_strchr("10EWNS ", map[i][j]))
	{
		error(cub, INVALID_MAP_CHARACTER, NULL);
	}
	if (!cub->player.pos.x && !cub->player.pos.y
		&& ft_strchr("EWNS", map[i][j]))
	{
		get_player(cub, map, i, j);
	}
	else if (ft_strchr("EWNS", map[i][j]))
		error(cub, MULTIPLE_PLAYERS, NULL);
}

static void	map_parcour(t_cub *cub, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_element(cub, map, i, j);
			j++;
		}
		i++;
	}
	if (!cub->player.pos.x && !cub->player.pos.y)
		error(cub, NOPLAYER, NULL);
}

void	map_parse(t_cub *cub)
{
	char	**map;

	map = cub->params.map;
	spaces_to_0(map);
	map_parcour(cub, map);
}
