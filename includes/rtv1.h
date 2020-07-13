#ifndef RTV1_H
# define RTV1_H

# define WIN_WIDTH		600
# define WIN_HEIGHT		600
# define VIEW_WIDTH		1
# define VIEW_HEIGHT	1
//# define KEY_ESCAPE		(0X35)
# define THREAD			8
# define BUFF			1000
# define MAX_FILE_SIZE	81920 //10 кбайт

# include <fcntl.h>
# include <stdio.h>//УДАЛИ МЕНЯ!!!
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"
# include "mlx.h"
# include <pthread.h>
# include "keys.h"
# include "structs.h"



void memory_allocation_error(void);
void read_error(void);

char *read_file(char *file_name);


# endif
