# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/25 16:07:40 by gbianco           #+#    #+#              #
#    Updated: 2020/02/06 09:18:45 by lucmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
FLAG = -Wall -Wextra -Werror
FRAM = -framework OpenGL -framework AppKit
SANI = -g
MTHR = -lpthread -lm

SRCD = ./srcs/
PRSD = ./srcs/parser/
LOSD = ./srcs/loader/
VOSD = ./srcs/void/
OBTD = ./srcs/objects/
TXTD = ./srcs/textures/
INCD = ./includes/
OBJD = ./compiled/
LFTD = ./libs/libft/
VECD = ./libs/libvector/
MTXD = ./libs/libmatrix/
MLXD = ./libs/libmlxmac/

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Linux)
FRAM = -lX11 -lXext -lbsd
MLXD = ./libs/libmlxlinux/
else
FRAM = -framework OpenGL -framework AppKit
MLXD = ./libs/libmlxmac/
endif

VECF = $(VECD)vec.a
LIBF = $(LFTD)libft.a
MLXF = $(MLXD)libmlx.a
MTXF = $(MTXD)matrix.a

FILE := afterparser.c afterparser_imp.c anaglyph.c antialiasing.c camera.c \
	   camera_qtn.c cartoon.c color_anaglyph.c color_effects.c damier.c \
	   deal_order.c errors.c events_keys.c events_mouse.c fresnel.c \
	   help_noise.c hit.c intersections.c light.c light_cam.c light_rct.c \
	   main.c noises.c random_textures.c reflect_refract.c
FILE += render.c render_distributed.c render_single.c render_timed_cam.c \
	   render_timed_obj.c
FILE += saveimageppm.c \
	   shaders.c shaders_cartoon.c shaders_color.c\
	   solver_cubic.c solver_quartic.c \
	   transform.c transform_trn.c
FILE += cone.c cube.c cylinder.c disk.c hyperboloid1.c hyperboloid2.c \
		mobius.c paraboloid1.c paraboloid2.c plane.c sphere.c torus.c triangle.c
FILE += debug.c parser.c \
		obj_converter.c obj_faces.c obj_indexing.c obj_parser.c \
		obj_splitalloc.c obj_triangles.c obj_render.c\
		xml_assigner.c xml_assignerb.c xml_assignersp.c xml_count.c \
		xml_counttags.c xml_deepcount.c xml_deepcountb.c xml_equality.c \
		xml_nested.c xml_parser.c xml_split.c xml_split_alloc.c \
		xml_split_effect.c xml_split_group.c xml_split_group_light.c \
		xml_split_group_rotation.c xml_split_group_utils.c \
		xml_split_light.c xml_split_mesh.c xml_split_mesh_group.c \
		xml_split_primit.c xml_split_triang.c xml_split_white.c xml_validity.c
FILE += void_sort.c void_regions.c
FILE += loader_main.c loader_colors.c loader_graphic.c
FILE += bexel.c texel.c texture.c texture_map.c

INCL = $(INCD)rtv1.h
ALLI = -I $(INCD) -I $(LFTD) -I $(VECD) -I $(MLXD) -I $(MTXD)

# Colors
CLRR = \033[0;31m
CLRG = \033[0;32m
CLRB = \033[0;34m
CLRC = \033[0;36m
CLRW = \033[0m
LIBC = $(CLRC)[LIBFT]$(CLRW)
VECC = $(CLRC)[LBVEC]$(CLRW)
MTXC = $(CLRC)[LBMTX]$(CLRW)
RTVC = $(CLRB)[RT]$(CLRW)

OBJF = $(addprefix $(OBJD), $(FILE:.c=.o))


all : $(NAME)

$(NAME) : $(LIBF) $(VECF) $(MLXF) $(MTXF) $(OBJD) $(OBJF)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "$(NAME) compiled" "✘"
	@gcc $(FRAM) $(SANI) $(MTHR) -o $@ $(OBJF) $(LIBF) $(VECF) $(MLXF) $(MTXF)
	@printf	"\r$(RTVC)$(CLRG)%-53s$(CLRW) [$(CLRG)%s$(CLRW)]\n" "$(NAME) compiled" "✔"

# Shortcuts
$(LIBF) :
	#@sh scripts/showlogo.sh
	@make -j -C $(LFTD)
$(VECF) :
	@ make -j -C $(VECD)
$(MLXF) :
	@ make -j -s -C $(MLXD)
$(MTXF) :
	@ make -j -s -C $(MTXD)

$(OBJD) :
	@mkdir -p $(OBJD)
	@printf	"$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Repository: compiled created" "✔"

$(OBJD)%.o: $(SRCD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(PRSD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(OBTD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(LOSD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(VOSD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"
$(OBJD)%.o: $(TXTD)%.c $(INCL)
	@printf	"$(RTVC)%-53s [$(CLRR)%s$(CLRW)]" "Object: $@ created" "✘"
	@gcc $(FLAG) $(SANI) -c $< -o $@ $(ALLI)
	@printf	"\r$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Object: $@ created" "✔"

clean:
	@make -C $(LFTD) clean
	@make -C $(VECD) clean
	@make -C $(MLXD) clean
	@make -C $(MTXD) clean
	@rm -rf $(OBJD)
	@printf	"$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "Objects removed" "∙"

fclean: clean
	@rm -f $(LIBF)
	@printf	"$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "File: libft.a removed" "∙"
	@rm -f $(VECF)
	@printf	"$(VECC)%-50s [$(CLRG)%s$(CLRW)]\n" "File: vec3.a removed" "∙"
	@rm -f $(MTXF)
	@printf	"$(MTXC)%-50s [$(CLRG)%s$(CLRW)]\n" "File: matrix.a removed" "∙"
	@rm -rf $(NAME)
	@printf	"$(RTVC)%-53s [$(CLRG)%s$(CLRW)]\n" "File: $(NAME) removed" "∙"

re: fclean all

.PHONY : clean fclean re
.NOTPARALLEL : $(LIBF)
