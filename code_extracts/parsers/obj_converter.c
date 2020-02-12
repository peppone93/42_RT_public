/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:25:00 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 23:26:07 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	fill_start_part(int fd)
{
	ft_putstr_fd("<?xml version=\"1.0\" encoding=\"ASCII\"?>\n\
<scene>\n\t<camera>\n\
\t\t<position>0, 0, 0</position>\n\
\t\t<direction>0, 0, 1</direction>\n\
\t\t<rotation>0, 0, 0</rotation>\n\
\t\t<fov>60.0</fov>\n\
\t</camera>\n\t<window>\n\
\t\t<title>converted_obj</title>\n\
\t\t<dimension>500, 500</dimension>\n\
\t\t<ambient>0.5</ambient>\n\
\t</window>\n\
\t<light>\n\
\t\t<position>0, 0, -100</position>\n\
\t\t<intensity>50000</intensity>\n\
\t\t<color>0xffffff</color>\n\
\t\t<type>point</type>\n\
\t</light>\n\
\t<mesh>\n\
\t\t<type>triangle_mesh</type>\n\
\t\t<color>0xffffff</color>\n\
\t\t<shine>0, 0</shine>\n\
\t\t<rotation>0, 0, 0</rotation>\n\
\t\t<translation>0, 0, 0</translation>\n", fd);
}

static void	put_vector(t_vec3 *v, int fd)
{
	char	*temp;

	temp = ft_ftoa(v->x);
	ft_putstr_fd(temp, fd);
	ft_putstr_fd(", ", fd);
	ft_strdel(&temp);
	temp = ft_ftoa(v->y);
	ft_putstr_fd(temp, fd);
	ft_putstr_fd(", ", fd);
	ft_strdel(&temp);
	temp = ft_ftoa(v->z);
	ft_putstr_fd(temp, fd);
	ft_strdel(&temp);
}

void		fill_middle_part(t_objw *o, int fd)
{
	int i;

	i = -1;
	while (++i < o->n_triangle)
	{
		ft_putstr_fd("\t\t<part>\n", fd);
		ft_putstr_fd("\t\t\t<vertex1>", fd);
		put_vector(&o->v_vertex[o->d_trn[i].v0 - 1], fd);
		ft_putstr_fd("</vertex1>\n", fd);
		ft_putstr_fd("\t\t\t<vertex2>", fd);
		put_vector(&o->v_vertex[o->d_trn[i].v1 - 1], fd);
		ft_putstr_fd("</vertex2>\n", fd);
		ft_putstr_fd("\t\t\t<vertex3>", fd);
		put_vector(&o->v_vertex[o->d_trn[i].v2 - 1], fd);
		ft_putstr_fd("</vertex3>\n", fd);
		ft_putstr_fd("\t\t\t<normal>", fd);
		if (o->n_normal && o->n_normal >= o->d_trn[i].n0)
			put_vector(&o->v_normal[o->d_trn[i].n0 - 1], fd);
		ft_putstr_fd("</normal>\n", fd);
		ft_putstr_fd("\t\t</part>\n", fd);
	}
}

static int	empty_file(char *name)
{
	char	*str[2];
	char	*filename;
	int		i;
	int		fd;

	str[0] = "_converted";
	str[1] = ".xml";
	i = 10 + ft_strlen(name) - 4 + 4;
	filename = (char*)ft_secmemalloc(sizeof(char) * (i + 1));
	ft_strncpy(filename, name, ft_strlen(name) - 4);
	ft_strcpy(&filename[ft_strlen(name) - 4], str[0]);
	ft_strcpy(&filename[ft_strlen(name) - 4 + 10], str[1]);
	filename[ft_strlen(name) + 10] = '\0';
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	ft_strdel(&filename);
	if (fd == -1)
		ft_putstr("error saving scene\n");
	return (fd);
}

void		obj_data_converter(char *name, t_objw *objw)
{
	int	fd;

	fd = empty_file(name);
	fill_start_part(fd);
	fill_middle_part(objw, fd);
	ft_putstr_fd("\t</mesh>\n</scene>", fd);
	ft_putstr("Conversion finished\n");
	exit(EXIT_SUCCESS);
	return ;
}
