/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:45:32 by jagarcia          #+#    #+#             */
/*   Updated: 2020/11/26 18:43:23 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

unsigned char	*read_file(char *filename, size_t *filesize)
{
	int				fd;
	unsigned char	*content_file;
	struct stat		stat;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		nm_error(ERROR_OPEN);
	fstat(fd, &stat);
	*filesize = stat.st_size;
	content_file = mmap(0, *filesize, PROT_READ,
			MAP_PRIVATE, fd, 0);
	if (content_file == MAP_FAILED)
		nm_error("ERROR_ALLOC");
	close(fd);
	return (content_file);
}

static void	print_help_message(void)
{
	ft_printf("USAGE: ft_otool [options] <input files>\n\n \
OPTIONS:\n \
\t-h: print this message\n");
}

static void	loop_resources(char **argv)
{
	unsigned char	*content_file;
	size_t			filesize;
	while (*argv)
	{
		content_file = read_file(*argv, &filesize);
		if (!choose_format(content_file, *argv))
			nm_error(ERROR_FORMAT);
		if (munmap(content_file, filesize))
			nm_error(ERROR_FREE);
		argv++;
	}
}

int	main(int argn, char **argv)
{
	unsigned char	*content_file;
	size_t			filesize;

	argv = set_flags(argv, &argn);
	if (get_flags("-h"))
	{
		print_help_message();
		return (0);
	}
	if (argn < 2)
	{
		ft_printf("%s:\n", "a.out");
		content_file = read_file("a.out", &filesize);
		if (!choose_format(content_file, "a.out"))
			nm_error(ERROR_FORMAT);
	}
	else
		loop_resources(argv);
	return (0);
}
