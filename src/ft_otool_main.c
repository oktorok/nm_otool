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

	if ((fd = open(filename, O_RDONLY)) < 0)
		nm_error(ERROR_OPEN);
	fstat(fd, &stat);
	*filesize = stat.st_size;
	if ((content_file = mmap(0, *filesize, PROT_READ, MAP_PRIVATE,
							fd, 0)) == MAP_FAILED)
		nm_error("ERROR_ALLOC");
	close(fd);
	return (content_file);
}

int	main(int argn, char **argv)
{
	int				i;
	unsigned char	*content_file;
	size_t			filesize;

	if (argn < 2)
	{
		content_file = read_file("a.out", &filesize);
		if (!choose_format(content_file, "a.out"))
			nm_error(ERROR_FORMAT);
	}
	else
	{
		i = 1;
		while (i < argn)
		{
			if (argn > 2)
				ft_printf("\n%s:\n", argv[i]);
			content_file = read_file(argv[i], &filesize);
			if (!choose_format(content_file, argv[i]))
				nm_error(ERROR_FORMAT);
			if (munmap(content_file, filesize))
				nm_error(ERROR_FREE);
			i++;
		}
	}
	return (0);
}
