/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 00:22:10 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 22:21:12 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		normal_sphere(double pnt[4][1], double dst[4][1])
{
	dst[0][0] = pnt[0][0];
	dst[1][0] = pnt[1][0];
	dst[2][0] = pnt[2][0];
}

static void	equation(t_vec3 *coef, double *disc, double *t)
{
	t[0] = (sqrt(*disc) - coef->y) / (2.0 * coef->x);
	t[1] = (-sqrt(*disc) - coef->y) / (2.0 * coef->x);
	t[2] = 0;
}

void		intersect_ray_sphere(t_ray *r, t_obj *o, double *t)
{
	double	disc;
	t_vec3	coef;
	t_ray	tr;

	tr = transform_ray(r, o);
	coef.x = v3_dot(tr.dir, tr.dir);
	coef.y = 2. * v3_dot(tr.dir, tr.ori);
	coef.z = v3_dot(tr.ori, tr.ori) - 1.;
	disc = coef.y * coef.y - 4. * coef.x * coef.z;
	equation(&coef, &disc, t);
}
