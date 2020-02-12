/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:28:28 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/12 18:42:29 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <pthread.h>
# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "vec.h"
# include "matrix.h"
# include "multidata.h"
# include "parser.h"
# include "loader.h"

# define THREAD 4
# define GRADE 4
# define OBJ 14
# define MAXRFL 4
# define MAXRFR 8
# define AIR_IOR 1
# define CAM_CORRECTION 1

# define BIAS 1e-9
# define L_BIAS 1e-4
# define CAM_BIAS 1e-7
# define REC_BIAS 1e-5
# define ANULL 1e-15
# define EPSILON 1e-5
# define ID_OFFSET 1e6
# define AMBIENT_CORRECTION 0.0035
# define F3 0.333333333f
# define G3 0.166666667f

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	char			*pst;
	void			*pim;
	char			*sst;
	void			*sim;
	char			*title;
	int				hei;
	int				wid;
	int				b;
	int				s;
	int				e;
	int				button_alt;
	void			*loader_ptr;
	char			*loader_str;
	int				event_enable;
}					t_mlx;

typedef struct		s_glare
{
	int				select;
	int				*shadow;
	t_obj			*fakeplane;
}					t_glare;

typedef struct		s_cam
{
	int				select;
	double			fov;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			rot;
	t_vec3			u;
	t_vec3			v;
	t_vec3			w;
	t_vec3			bottleft;
	t_vec3			vi_x;
	t_vec3			vi_y;
	t_glare			glr;
}					t_cam;

typedef struct		s_efc
{
	int				select;
	int				aa;
	int				toon;
	int				clrm;
	int				blu[2];
	double			maxtime;
	double			gly[2];
	t_vec3			rotaxe;
}					t_efc;

typedef struct		s_perlin
{
	int				perl;
	t_vec3i			offset;
	t_vec3			pos0;
	t_vec3i			posijk;
	t_vec4			noise_corners;
	t_vec3i			offijk[2];
	t_vec3			offxyz[3];
	unsigned char	perm[512];
	t_vec3			grad[16];
}					t_perlin;

typedef	struct		s_ray
{
	t_vec3			ori;
	t_vec3			dir;
	double			time;
	double			*maxtime;
}					t_ray;

typedef struct		s_nhit
{
	double			dist_st;
	double			dist_lt;
	t_obj			*obj;
	struct s_nhit	*next;
}					t_nhit;

typedef	struct		s_clt
{
	t_obj			*obj;
	double			t;
	int				neg;
}					t_clt;

typedef	struct		s_hit
{
	double			tt[GRADE + 1];
	int				n_clt;
	t_clt			*clt;
	double			t;
	t_obj			*obj;
	t_vec3			isc;
	t_ray			*ray;
	t_vec3			nrm;
	int				maxrfl;
	int				maxrfr;
	double			i_ior;
	double			shadowfall;
}					t_hit;

typedef	struct		s_pix
{
	double			amb;
	int				clr;
}					t_pix;

typedef struct		s_scene
{
	int				strt;
	int				n_obj;
	int				n_lht;
	int				n_wht;
	int				n_prt;
	t_perlin		p;
	t_obj			*obj;
	t_lht			*lht;
	t_cam			cam;
	t_cam			rstcam;
	t_mlx			mlx;
	t_hit			hit;
	t_nhit			*void_regions;
	t_pix			pix;
	t_efc			efc;
	int				var_obj;
	int				var_light;
	t_vec3			grp_mod[2];
	int				done;
	int				id;
}					t_scene;

/*
**	Fonction pointer
*/
typedef int			(*t_render)(t_scene*, t_ray*, double, double);
typedef void		(*t_normal)(double[4][1], double[4][1]);
typedef double		(*t_shader)(t_scene*, t_vec3);

/*
**	Render
*/
void				*select_image_mode(void *s);
void				multithr_single_image(t_scene *s);
void				anaglyph_multi_image(t_scene *s);
int					single_ray(t_scene *s, t_ray *r, double x, double y);
int					distribuited_rays(t_scene *s, t_ray *r, double x, double y);
void				color_secondary_pix(t_scene *s, int x, int y);
void				error(char *str);
void				effects_error(int check);
void				after_parse_error(int check);
void				after_parse_error2(int check);
/*
**	Camera
*/
void				precalc_camera(t_scene *s);
t_vec3				orientate_axes(t_scene *s, double x, double y);
t_vec3				quaternion_rotation_x(t_scene *s, t_vec3 dir);
t_vec3				quaternion_rotation_y(t_scene *s, t_vec3 dir);
t_vec3				quaternion_rotation_z(t_scene *s, t_vec3 dir);
t_vec3				quaternion_rotation_vec(t_vec3 a, t_vec3 b, double angle);
/*
**	Light and shading
*/
int					light(t_scene *s, t_shader f);
double				point_light(t_scene *s, t_lht *l, t_shader f);
double				direction_light(t_scene *s, t_lht *l, t_shader f);
double				spot_light(t_scene *s, t_lht *l, t_shader f);
double				rectangle_light(t_scene*s, t_lht *l, t_shader f);
t_vec3				center_of_sample(t_int2 k, t_lht *l);
double				camera_light(t_scene *s, int color);
void				init_camlight_data(t_scene *s);
int					get_color(t_scene *s, double *en, int clr, double amb);
double				classic_shader(t_scene *s, t_vec3 il);
double				cartoon_shader(t_scene *s, t_vec3 il);
double				camera_shader(t_scene *s, t_vec3 il);
double				camera_shader(t_scene *s, t_vec3 il);
t_vec3				get_texel(double u, double v, t_texture *texture);
t_texture			*load_texture(t_scene *s, char *filename);
double				*cylindre_map(t_vec3 p, double stretch);
double				*spherical_map(t_vec3 p, double stretch);
t_vec3				world_to_obj(t_hit *hit);
t_vec3				get_texel_plane(t_scene *s);
t_vec3				get_texel_cylinder(t_scene *s);
t_vec3				get_texel_cone(t_scene *s);
t_vec3				get_texel_sphere(t_scene *s);
void				init_textures(t_scene *s);
/*
**	Intersections and normals
**	 Reflaction and Refraction
*/
int					recursive_ray(t_scene *s, t_ray r, t_shader f);
int					mix_fresnel_case(t_scene *s, t_ray *r, t_shader f);
int					clr_scp(int clr, double coef);
int					clr_add(int clr_a, int clr_b);
int					bi_rate_color(int cl_a, int cl_b, double r_a, double r_b);
t_ray				compute_refracted(t_scene *s, t_ray r);
t_ray				compute_reflected(t_scene *s, t_ray r);
void				collect_object_isc(t_scene *s, t_ray *r);
void				collect_shadow_isc(t_scene *s, t_ray *r);
void				get_object_hit(t_scene *s);
void				get_shadow_hit(t_scene *s);
void				get_shadowfall_hit(t_scene *s, double d);
void				object_intersection(t_obj *o, t_ray *r, double *t);
void				shadow_intersection(t_obj *o, t_ray *r, double *t);
void				intersect_ray_plane(t_ray *r, t_obj *o, double *t);
void				intersect_ray_disk(t_ray *r, t_obj *o, double *t);
void				intersect_ray_sphere(t_ray *r, t_obj *o, double *t);
void				intersect_ray_cylinder(t_ray *r, t_obj *o, double *t);
void				intersect_ray_cone(t_ray *r, t_obj *o, double *t);
void				intersect_ray_triangle(t_ray *r, t_obj *o, double *t);
void				intersect_ray_cube(t_ray *r, t_obj *o, double *t);
void				intersect_ray_hyperboloid_1s(t_ray *r, t_obj *o, double *t);
void				intersect_ray_hyperboloid_2s(t_ray *r, t_obj *o, double *t);
void				intersect_ray_paraboloid_el(t_ray *r, t_obj *o, double *t);
void				intersect_ray_paraboloid_hy(t_ray *r, t_obj *o, double *t);
void				intersect_ray_torus(t_ray *r, t_obj *o, double *t);
void				intersect_ray_mobius(t_ray *r, t_obj *o, double *t);
t_vec3				find_intersection_point(t_ray *r, double *t);
t_vec3				get_norm(t_scene *s, t_hit *dat, t_ray *r);
t_vec3				normal_at(t_scene *s, t_hit *hit, t_normal f);
void				normal_sphere(double m[4][1], double d[4][1]);
void				normal_cylinder(double m[4][1], double d[4][1]);
void				normal_cone(double m[4][1], double d[4][1]);
void				normal_cube(double m[4][1], double d[4][1]);
void				normal_hyperboloid(double m[4][1], double d[4][1]);
void				normal_paraboloid1(double m[4][1], double d[4][1]);
void				normal_paraboloid2(double m[4][1], double d[4][1]);
void				normal_torus(double m[4][1], double d[4][1]);
void				normal_mobius(double m[4][1], double d[4][1]);
t_vec3				normal_triangle(t_hit *dat, t_ray *r);
t_vec3				normal_plane(t_scene *s, t_hit *hit);
void				add_pert(t_scene *s, t_vec3 *vectr_nrm);
void				add_bump(t_scene *s, t_vec3 *vectr_nrm);
t_vec3				get_bump_sphere(t_scene *s);
t_vec3				get_bump_cylinder(t_scene *s);
t_vec3				get_bump_plane(t_scene *s);
t_vec3				get_bump_cone(t_scene *s);
/*
** Equation Solvers
*/
int					quartic_solver(double c[5], double *t);
int					cubic_solver(double c[4], double *t);
void				get_void_region(t_scene *s);
int					is_voided(t_nhit *void_region, double dist);
void				free_void_region(t_scene *s);
void				sort_clt(t_scene *s);
/*
**	Matrix transformations + translations + rotations
*/
void				add_transform_to_obj(t_obj *o);
t_ray				transform_ray(t_ray *r, t_obj *o);
void				obj_translation(t_obj *obj);
void				obj_rotations(t_obj *obj, double rot[4][4]);
void				rotate_triangle(t_obj *obj, t_vec3 *center);
void				rotate_mesh(t_scene *s, int *i);
void				rotate_xyz(t_vec3 *org, t_vec3 *rot);
/*
**	Color effects
*/
int					color_nored(int clr);
int					color_nocyan(int clr);
int					color_sepia(int clr);
int					color_negative(int clr);
int					color_grayscale(int clr);
/*
**	Visual effects
*/
int					aa_x2(t_scene *s, t_ray *r, t_crd2 c, t_render f);
int					aa_x4(t_scene *s, t_ray *r, t_crd2 c, t_render f);
void				time_switch(t_ray *r, t_obj *obj);
int					timed_rays(t_scene *s, t_ray *r, double x, double y);
int					global_blur(t_scene *s, t_ray *r, double x, double y);
double				determinate_max_time(t_scene *s);
int					cartoon_effect(t_scene *s, t_ray *r, double x, double y);
int					antialiasing(t_scene *s, t_ray *r, double x, double y);
int					average_color(int *rgb, int n);
/*
**	Events
*/
int					finish(void);
int					key_press_loop(int k, t_scene *s);
int					key_release_loop(int k, t_scene *s);
int					mouse_loop(int k, int x, int y, t_scene *s);
void				clean_scene(t_scene *s);
void				saving_image_ppm(t_scene *s);
/*
**	Parser
*/
void				parse(t_scene *s, char **av, int ac);
/*
** -> xml
*/
void				parser_xml(t_scene *s, char **av);
void				obj_realloc(t_scene *s, int old_size);
void				count_tags(t_scene *s, char *str);
void				mesh_cycle(t_scene *s, char *scene);
void				objects_cycle(t_scene *s, char *scene, int i);
void				group_cycle(t_scene *s, char *scene);
void				process_group(t_scene *s, char *group, int id
		, t_vec3 mod[2]);
void				white_cycle(t_scene *s);
void				lights_cycle(t_scene *s, char *scene, int i);
void				split_all_tags(t_scene *s, char *all);
void				split_allocated_tags(t_scene *s, char *scene);
void				split_primitive_tags(t_scene *s, char *obj, int i);
void				split_triangle_tags(t_scene *s, char *obj, int i);
void				split_point_light(t_scene *s, char *light, int i);
void				split_directional_light(t_scene *s, char *light, int i);
void				split_spot_light(t_scene *s, char *light, int i);
void				split_rectangle_light(t_scene *s, char *light, int i);
void				split_mesh_group(t_scene *s, char *grp, char *cm[], int *i);
void				prcss_effects_tags(t_scene *s, char *scene);
/*
**	-> obj
*/
void				parser_obj(t_scene *s, char **av);
void				obj_data_associer(t_scene *s, t_objw *objw);
void				split_group_light_dispatcher(t_scene *s, t_lht *light
		, t_vec3 mod[1]);
/*
**	After parser
*/
void				after_parser(t_scene *s);
void				improve_data(t_scene *s);
/*
**	Loader
*/
void				start_program(t_scene *s, int per, int oldper, int add);
void				compute_gradient(float percent, int (*color1)[3]
		, int (*color2)[3], int (*out)[3]);
void				printf_completion(int percentage);
void				update_visual(t_scene *s, int percentage);
/*
**	DEBUG / TODO : to delete
*/
void				print_vector(t_vec3 v, char *name);
void				print_void(t_scene *s);

double				cloud(t_scene *s, double noise);
void				deal_pert(t_scene *s);
double				noise3d(t_scene *s, double x, double y, double z);
void				perm_corn1(t_scene *sc, t_vec3 *g);
void				perm_corn2(t_scene *sc, t_vec3 *g);
void				perm_corn3(t_scene *sc, t_vec3 *g);
void				perm_corn4(t_scene *sc, t_vec3 *g);
void				fix_corner_other(t_scene *sc);
t_vec3				fix_vec(double x, double y, double z);
void				grad3(t_scene *s, int hash, t_vec3 *g);
void				init_grad(t_scene *s);
void				init_perm(t_scene *sc);
double				noises(double noise, t_scene *s, int i);
int					fastfloor(double x);

#endif
