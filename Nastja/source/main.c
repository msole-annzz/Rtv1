#include "../includes/rtv1.h"

void ft_put_pixel(t_scene *scene, double deep, int i, int j, int k)
{
	int p;
	p = 4 * (WIN_WIDTH * j  + i);
	/*if (deep == 0)
	{
	scene->image.data[p] =0x00;
	scene->image.data[p+1] =0x00;
	scene->image.data[p+2] =0x00;
	}
	else
	{*/
	if (deep != 0)
	{
	scene->image.data[p] = scene->object[k].color.r;
	scene->image.data[p+1] = scene->object[k].color.g;
	scene->image.data[p+2] = scene->object[k].color.b;
	}
}

void ft_init_scene(t_scene *scene)
{
	scene->camera.place.x=0;
	scene->camera.place.y=0;
	scene->camera.place.z=0;
	scene->object[0].R=0.5;
	scene->object[0].center.x=0;
	scene->object[0].center.y=0;
	scene->object[0].center.z=3;
	scene->object[0].type=1;
	scene->object[0].color.r = 0x85;
	scene->object[0].color.g = 0x00;
	scene->object[0].color.b = 0x00;
	scene->object[1].R=1;
	scene->object[1].center.x=1;
	scene->object[1].center.y=-1;
	scene->object[1].center.z=4;
	scene->object[1].type=1;
	scene->object[1].color.r = 0x00;
	scene->object[1].color.g = 0x80;
	scene->object[1].color.b = 0x00;
	scene->d = 1;
}

double ft_dotprod(t_coord v1, t_coord v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_coord ft_addv(t_coord v1, t_coord v2)
{
	t_coord t;
	t.x=v1.x+v2.x;
	t.y=v1.y+v2.y;
	t.z=v1.z+v2.z;
	return (t);
}

t_coord ft_substrv(t_coord v1, t_coord v2)
{
	t_coord t;

	t.x=v1.x-v2.x;
	t.y=v1.y-v2.y;
	t.z=v1.z-v2.z;
	return (t);
	}

double ft_quadrsolution(double a, double b, double c)
{
	double d;
	double s1;
	double s2;

	d = (b*b) - (4 * a * c);
	if (d<0)
	s1 = 0;
	else
	{
		s1= (-b +(double) sqrt(d))/(2*a);
		s2= (-b - (double) sqrt(d))/(2*a);
		if ((s1>1) && (s2 > 1) && (s2 < s1))
			s1=s2;
		if ((s1 < 1) && (s2 > 1))
			s1=s2;
		if ((s1<1) && (s2 < 1))
			s1=0;
	}
	return (s1);
}

double ft_intersect(t_scene *scene, int k)
{
	double a;
	double b;
	double c;
	double x;
	t_coord oc;

	oc = ft_substrv(scene->camera.place, scene->object[k].center);
	a = ft_dotprod(scene->cur_point, scene->cur_point);
	b = 2* ft_dotprod(oc, scene->cur_point);
	c = ft_dotprod(oc,oc) - scene->object[k].R * scene->object[k].R;
	x = ft_quadrsolution(a,b,c);
/*if (x>0)
{
printf("x=%f\n",scene->cur_point.x);
printf("y=%f\n",scene->cur_point.y);
printf("a=%f\n",a);
printf("b=%f\n",b);
printf("c=%f\n",c);
printf("x=%f\n",x);
printf("*******\n");
}
*/
	return (x);
}

void ft_conv2to3(t_scene *scene, int x, int y)
{
	scene->cur_point.x = x *(double) VIEW_WIDTH / WIN_WIDTH;
	scene->cur_point.y = y * (double) VIEW_HEIGHT / WIN_HEIGHT;
	scene->cur_point.z = scene->d;
}

void *ft_traceray(void *threadData)
{
	int i;
	int j;
	int k;
	double deep;
	t_scene *scene;

	k = 0;
	scene = (t_scene *)(threadData);
	deep = 0;
	i = scene->thrminwidth;
	j = 0;
	while (j < WIN_HEIGHT)
	{
		while (i < scene->thrmaxwidth)
		{
			while (k < 2)
			{
				ft_conv2to3(scene, i-WIN_WIDTH/2, j-WIN_HEIGHT/2);
				deep = ft_intersect(scene, k);
				ft_put_pixel(scene, deep, i, j, k);
				k++;
			}
			k=0;
			i++;
		}
		i=scene->thrminwidth;
		j++;
	}
	return (threadData);
}

void ft_threads(t_scene *scene)
{
	int i;
	pthread_t	threads[THREAD];
	t_scene		threadData[THREAD];

	i = 0;
	while (i < THREAD)
	{
		ft_memcpy((void *)&threadData[i], (void *)scene, sizeof(t_scene));
		threadData[i].thrminwidth=((double)(WIN_WIDTH / THREAD)) * i;
		threadData[i].thrmaxwidth=((double)(WIN_WIDTH / THREAD)) * (i+1);
		i=i+1;
	}
	i = 0;
	while (i < THREAD)
	{
		pthread_create(&(threads[i]), NULL, ft_traceray, &threadData[i]);
		i=i+1;
	}
	while (i--)
	{
		pthread_join(threads[i], NULL);
	}
	mlx_put_image_to_window(scene->mlx.init, scene->mlx.win,scene->mlx.img, 0, 0);
}

int scene_keys(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESCAPE)
			exit(0);
	if (keycode == KEY_ANSI_S)
	{
		scene->d = scene->d + 1;
	}
	return(0);
}

int main(int argc, char **argv)
{
	t_scene *scene;
	if ((argc == 2) && (ft_strequ(argv[1], "sfera")))
	{
		if (!(scene = (t_scene *)malloc(sizeof (t_scene))))
		{
			write (1,"error mem",9);
			exit(1);
		}
		else
		{
		//ft_init_scene(scene);
		//ft_traceray(scene);
			scene->mlx.init = mlx_init();
			scene->mlx.win = mlx_new_window(scene->mlx.init,WIN_WIDTH, WIN_HEIGHT, "RTV1");
			scene->mlx.img = mlx_new_image(scene->mlx.init, WIN_WIDTH,WIN_HEIGHT);
			scene->image.data = mlx_get_data_addr(scene->mlx.img,&scene->image.bpp, &scene->image.size, &scene->image.endian);
			ft_init_scene(scene);
			ft_threads(scene);
			mlx_hook(scene->mlx.win, 2, 0, scene_keys, scene);
			//mlx_hook(fractol->mlx.win, 4, 0, ft_mouse, fractol);
			//mlx_hook(fractol->mlx.win, 6, 0, ft_mousemove, fractol);
			mlx_loop(scene->mlx.init);
		}
	}
	return (0);
}
