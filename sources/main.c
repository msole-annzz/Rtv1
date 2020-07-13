#include "../includes/rtv1.h"


void read_error(void)
{
	write(1, "There are some problems with readding file\n", 45);
	exit(1);
}

void memory_allocation_error(void)
{
	write(1, "There are some problems with memory allocation\n", 48);
	exit(1);
}

void file_error(void)
{
	write(1, "Please, add one file: ./RTv1 <file_name>\n", 42);
	exit(1);
}


int main(int argc, char **argv)
{
	//t_rtv1 *rt;
	char *str;

	str = NULL;
	//rt = NULL;
	if (argc != 2)
		file_error();
	//if (!(rt = (t_rtv1 *)malloc(sizeof(t_rtv1))))
	//	memory_allocation_error();
	str = read_file(argv[1]);

	printf("%s",str);
	free(str);
	return (0);
}
