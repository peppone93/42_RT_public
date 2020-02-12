/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:24:45 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 18:01:34 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	check_file_ext(char *av)
{
	char	*xml;
	char	*obj;
	int		check;
	int		i;
	int		j;

	xml = ".xml";
	obj = ".obj";
	i = ft_strlen(av) - 4;
	j = 0;
	while (av[i + j] != '\0')
	{
		check = 0;
		if (xml[j] && av[i + j] == xml[j])
			check = 1;
		if (obj[j] && av[i + j] == obj[j])
			check = 2;
		if (check == 0)
			return (0);
		j++;
	}
	return (check);
}

void		parse(t_scene *s, char **av, int ac)
{
	char	*usage;

	usage = "Usage:\n./RT [file.xml]\n./RT [file.obj] [mode]";
	if (ac < 2 || ac > 3)
		error(usage);
	else if (ac == 2 && check_file_ext(av[1]) == 1)
		parser_xml(s, av);
	else if (ac == 2 && check_file_ext(av[1]) == 2)
		error("Aviable mode for obj files: [render], [converter]");
	else if (ac == 3 && check_file_ext(av[1]) == 2)
		parser_obj(s, av);
	else
		error(usage);
}
