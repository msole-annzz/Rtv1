#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_img
{
	char		*data;
	int			size;
	int			endian;
	int			bpp;
}				t_img;

typedef struct	s_mlx
{
	void	*init;
	void	*win;
	void	*img;
}				t_mlx;

typedef struct	s_coord
{
	double	x;
	double	y;
	double	z;
}				t_coord;

typedef struct	s_rotate
{
	int	anglex;
	int	angley;
	int	anglez;
}				t_rotate;

typedef struct	s_camera
{
	t_coord		place;
	t_rotate	rotate;
}				t_camera;

// type 1--sfera
// type 2--plan

typedef struct	s_color
{
	char	r;
	char	g;
	char	b;
}				t_color;

typedef struct	s_object
{
	int		type;
	double	R;
	t_coord	center;
	t_color	color;
}				t_object;


typedef struct s_scene
{
	t_mlx		mlx;
	t_img		image;
	t_camera	camera;
	t_object	object[2];
	t_coord		cur_point;
	double		d;
	int			thrminwidth;
	int			thrmaxwidth;
}				t_scene;

# endif
