/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 18:25:35 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 17:01:35 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_object_hit(t_scene *s)
{
	int		i;

	i = -1;
	s->hit.t = INFINITY;
	while (++i < s->hit.n_clt)
	{
		if (s->hit.clt[i].t > 0 && s->hit.clt[i].t < s->hit.t
				&& is_voided(s->void_regions, s->hit.clt[i].t)
				&& s->hit.clt[i].obj->neg != 1)
		{
			s->hit.t = s->hit.clt[i].t;
			s->hit.obj = s->hit.clt[i].obj;
		}
	}
	s->hit.isc = find_intersection_point(s->hit.ray, &s->hit.t);
	free_void_region(s);
}

void		collect_object_isc(t_scene *s, t_ray *r)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = -1;
	r->maxtime = &s->efc.maxtime;
	ft_bzero(s->hit.clt, sizeof(t_clt) * s->n_obj * GRADE);
	while (++i < s->n_obj)
	{
		ft_bzero(s->hit.tt, sizeof(int) * (GRADE + 1));
		object_intersection(&s->obj[i], r, s->hit.tt);
		j = 0;
		while (s->hit.tt[j] != 0)
		{
			s->hit.clt[k].t = s->hit.tt[j];
			s->hit.clt[k].obj = &s->obj[i];
			s->hit.clt[k].neg = s->obj[i].neg;
			j++;
			k++;
		}
	}
	s->hit.n_clt = k;
	get_void_region(s);
}

void		get_shadowfall_hit(t_scene *s, double dist)
{
	int		i;
	double	opacity;
	double	bias;

	opacity = 0;
	i = -1;
	while (++i < s->hit.n_clt)
	{
		bias = (s->hit.clt[i].obj->typ < 12) ? BIAS : L_BIAS;
		if (s->hit.clt[i].t > bias && s->hit.clt[i].t < dist
				&& is_voided(s->void_regions, s->hit.clt[i].t)
				&& s->hit.clt[i].obj->neg != 1)
		{
			if (i == 0)
				opacity += (1 - (s->hit.clt[i].obj->tcy));
			else if (s->hit.clt[i].obj->id != s->hit.clt[i - 1].obj->id)
				opacity += (1 - (s->hit.clt[i].obj->tcy));
		}
		if (opacity >= 1)
		{
			s->hit.shadowfall = 0;
			return ;
		}
	}
	s->hit.shadowfall = 1 - opacity;
}

void		collect_shadow_isc(t_scene *s, t_ray *r)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = -1;
	ft_bzero(s->hit.clt, sizeof(t_clt) * s->n_obj * GRADE);
	r->maxtime = &s->efc.maxtime;
	while (++i < s->n_obj)
	{
		ft_bzero(s->hit.tt, sizeof(int) * (GRADE + 1));
		shadow_intersection(&s->obj[i], r, s->hit.tt);
		j = 0;
		while (s->hit.tt[j] != 0)
		{
			s->hit.clt[k].t = s->hit.tt[j];
			s->hit.clt[k].obj = &s->obj[i];
			s->hit.clt[k].neg = s->obj[i].neg;
			j++;
			k++;
		}
	}
	s->hit.n_clt = k;
	get_void_region(s);
}
