#include "../includes/rtv1.h"

// int count_spaces(char *str)
// {
// 	int n; //nuber of spaces
// 	int i;

// 	n = 0;
// 	while (str[i]!="\0")
// 	{
// 		if (str[i] == " " || str[i] == "\n" || str[i] == "\t")
// 			n++;
// 		i++;
// 	}
// 	return (n);
// }

// char *copy_str_without_spaces(char *str, char *new_str)
// {
// 	int i;
// 	int n;

// 	n = 0;
// 	i = 0;
// 	while (str[i] != "\0")
// 	{
// 		if (str[i] != " " || str[i] != "\n" || str[i] != "\t")
// 		{
// 			new_str[n] = str[i];
// 			n++;
// 		}
// 		i++;
// 	}
// 	new_str[n] = "\0";
// 	return (new_str);
// }

// char *ft_clean_spaces(char *str)
// {
// 	char *new_str;
// 	int i;
// 	int n; //nuber of spaces

// 	new_str = NULL;
// 	i = 0;
// 	int n = 0;
// 	n = count_spaces(str);
// 	new_str = malloc(sizeof(char) * (ft_strlen(str) - n));
// 	new_str = copy_str_without_spaces(str, new_str);
// 	free(str);
// }
void empty_file_error(char *str, char *buf)
{
	free(str);
	free(buf);
	write(1, "This file is empty\n", 20);
	exit(1);
}

char *copy_cat(char *buf,char *str, int total_read_size)
{

	if (total_read_size <= MAX_FILE_SIZE)
		str = ft_strcat(str, buf);
	else
	{
		free(str);
		write(1, "This file is too big\n", 22);
		exit(1);
	}
	return (str);
}
char *ft_read(char *str, char *buf, int fd)
{
	int ret;
	int total_read_size;
	int first_read_flag;

	first_read_flag = 0;
	ret = 0;
	total_read_size = 0;
	while ((ret = read(fd, buf, BUFF)) > 0) // или &buf???
	{
		first_read_flag = 1;
		buf[ret] = '\0';
		total_read_size = total_read_size + ret;
		str = copy_cat(buf,str,total_read_size);
	}
	if ((ret == 0) && (first_read_flag == 0))
			empty_file_error(str, buf);
	if (ret < 0)
		read_error();
	return (str);
}
char *read_file(char *file_name)
{
	char *str;
	char *buf;
	int fd;

	buf = NULL;
	str = NULL;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		read_error();
	if (!(str = malloc(sizeof(char) * (MAX_FILE_SIZE + 1))) || !(buf = malloc(sizeof(char) * (BUFF + 1))))
		memory_allocation_error();
	str = ft_read(str, buf, fd);
	close(fd);
	//str = ft_clean_spaces(str);
	return (str);
}

