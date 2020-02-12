/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mobius.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 00:21:08 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 20:40:47 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		normal_mobius(double pnt[4][1], double dst[4][1])
{
	double x;
	double y;
	double z;

	x = pnt[0][0];
	y = pnt[1][0];
	z = pnt[2][0];
	dst[0][0] = 2. * x * y - 4. * x * z - 2. * z;
	dst[1][0] = -(x * x) + 3. * (y * y) - 4. * y * z + (z * z) - 1.;
	dst[2][0] = -2. * (x * x) - 2. * x - 2. * (y * y) + 2. * y * z;
}

static void	calculate_coefficents(t_ray *tr, double c[4])
{
	t_vec3	o;
	t_vec3	d;
	t_vec3	oo;
	t_vec3	dd;

	o = v3(tr->ori.x, tr->ori.y, tr->ori.z);
	d = v3(tr->dir.x, tr->dir.y, tr->dir.z);
	oo = v3(o.x * o.x, o.y * o.y, o.z * o.z);
	dd = v3(d.x * d.x, d.y * d.y, d.z * d.z);
	c[3] = (dd.x) * d.y - 2. * (dd.x) * d.z + (dd.y * d.y) - 2. * (dd.y)
		* d.z + d.y * (dd.z);
	c[2] = (dd.x) * o.y - 2. * (dd.x) * o.z + 2 * d.x * d.y * o.x - 2. * d.x
		* d.z * 1.5 - 4. * d.x * d.z * o.x + 3. * (dd.y) * o.y - 2. * (dd.y)
		* o.z - 4. * d.y * d.z * o.y + 2. * d.y * d.z * o.z + (dd.z) * o.y;
	c[1] = -2. * d.x * 1.5 * o.z + 2 * d.x * o.x * o.y - 4. * d.x * o.x * o.z
		- d.y * (1.5 * 1.5) + d.y * (oo.x) + 3. * d.y * (oo.y) - 4. * d.y * o.y
		* o.z + d.y * (oo.z) - 2. * d.z * 1.5 * o.x - 2 * d.z * (oo.x) - 2.
		* d.z * (oo.y) + 2. * d.z * o.y * o.z;
	c[0] = -(1.5 * 1.5) * o.y - 2. * 1.5 * o.x * o.z + (oo.x) * o.y - 2.
		* (oo.x) * o.z + (oo.y * o.y) - 2. * (oo.y) * o.z + o.y * (oo.z);
}

void		intersect_ray_mobius(t_ray *r, t_obj *obj, double *t)
{
	t_ray	tr;
	int		mobius_hit;
	int		srf_hit[2];
	double	c[4];
	double	srf_t[3];

	tr = transform_ray(r, obj);
	calculate_coefficents(&tr, c);
	srf_hit[0] = cubic_solver(c, srf_t);
	srf_hit[1] = -1;
	mobius_hit = 0;
	while (++srf_hit[1] < srf_hit[0])
	{
		if (srf_t[srf_hit[1]] && extract_mobius(&tr, srf_t[srf_hit[1]]) == 1)
		{
			t[mobius_hit] = srf_t[srf_hit[1]];
			mobius_hit++;
		}
	}
	t[mobius_hit] = 0;
}
