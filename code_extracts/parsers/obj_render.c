/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:42:12 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 16:17:37 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	obj_init_scene(t_scene *s)
{
	s->n_lht = 1;
	s->lht = (t_lht*)ft_secmemalloc(sizeof(t_lht) * s->n_lht);
	s->lht[0].p = (t_plt*)ft_secmemalloc(sizeof(t_plt));
	s->lht[0].p->pos = v3(0, 100, -100);
	s->lht[0].typ = 1;
	s->lht[0].pow = 20000;
	s->lht[0].clr = 0xffffff;
	s->cam.pos = v3(0, 0, -5);
	s->cam.dir = v3(0, 0, 1);
	s->cam.fov = 70;
	s->efc.select = 0;
	s->mlx.title = "obj file";
	s->mlx.wid = 500;
	s->mlx.hei = 500;
	s->pix.amb = 0.5;
}

void		obj_data_associer(t_scene *s, t_objw *objw)
{
	int i;

	s->obj = (t_obj*)ft_secmemalloc(sizeof(t_obj) * objw->n_triangle);
	i = -1;
	while (++i < objw->n_triangle)
	{
		s->obj[i].tr = (t_trn*)ft_secmemalloc(sizeof(t_trn));
		s->obj[i].tr->v0 = objw->v_vertex[objw->d_trn[i].v0 - 1];
		s->obj[i].tr->v1 = objw->v_vertex[objw->d_trn[i].v1 - 1];
		s->obj[i].tr->v2 = objw->v_vertex[objw->d_trn[i].v2 - 1];
		if (objw->n_normal && objw->n_normal >= objw->d_trn[i].n0)
			s->obj[i].dir = objw->v_normal[objw->d_trn[i].n0 - 1];
		s->obj[i].blur = v3(0, 0, 0);
		s->obj[i].clr = 0xffffff;
		s->obj[i].id = -1;
		s->obj[i].typ = 5;
		s->obj[i].tra = v3(0, 0, 0);
		s->obj[i].rot = v3(-15, 75, 10);
	}
	s->n_obj = objw->n_triangle;
	s->n_prt = objw->n_triangle;
	obj_init_scene(s);
}
