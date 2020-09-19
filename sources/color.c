/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 15:21:45 by msole             #+#    #+#             */
/*   Updated: 2020/09/12 18:04:49 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_put_pixel(t_scene *scene, int i, int j)
{
	int p;

	p = 4 * (WIN_WIDTH * j + i);
	// scene->image.data[p + 2] = scene->cur_prop.color.r;
	// scene->image.data[p + 1] = scene->cur_prop.color.g;
	// scene->image.data[p] = scene->cur_prop.color.g;

	scene->image.data[p + 2] = (scene->cur_prop.color.r * .393) + (scene->cur_prop.color.g *.769) + (scene->cur_prop.color.g * .189);
	scene->image.data[p + 1] = (scene->cur_prop.color.r * .349) + (scene->cur_prop.color.g *.686) + (scene->cur_prop.color.g * .168);
	scene->image.data[p] = (scene->cur_prop.color.r * .272) + (scene->cur_prop.color.g *.534) + (scene->cur_prop.color.g * .131);
}

void	ft_changecolor(t_scene *scene, t_color color, double deep)
{
	if (deep > 1)
		deep = 1;
	scene->cur_prop.color.r = color.r + deep * 90;
	scene->cur_prop.color.g = color.g + deep * 90;
	scene->cur_prop.color.b = color.b + deep * 90;
}

void	ft_initcolor(t_scene *scene)
{
	scene->cur_prop.color.r = scene->bkg_color.r;
	scene->cur_prop.color.g = scene->bkg_color.g;
	scene->cur_prop.color.b = scene->bkg_color.b;
}
