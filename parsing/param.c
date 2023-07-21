/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:43:32 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/22 00:17:35 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	starts_with(char *line, char *param_name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i + j] && param_name[j] && line[i + j] == param_name[j])
		j++;
	if (!param_name[j])
		return (true);
	return (false);
}

static char	*find_param(t_cub *cub, char **file, char *param_name)
{
	int		i;
	char	*res;

	i = 0;
	while (file[i] && !starts_with(file[i], param_name))
		i++;
	if (!file[i])
		error(cub, MISSING_PARAM, param_name);
	res = extract_second_word(cub, &file[i]);
	return (res);
}

static void	*convert_param(t_cub *cub, char *res)
{
	int	i;
	int	*int_res;

	i = 0;
	while (res[i] && ft_isdigit(res[i]))
		i++;
	if (res[i])
		return (res);
	int_res = malloc(sizeof(int));
	*int_res = my_atoi(cub, res);
	free(res);
	return (int_res);
}

void	*get_param(t_cub *cub, char **file, char *param_name)
{
	char	*res;

	res = find_param(cub, file, param_name);
	return (convert_param(cub, res));
}
