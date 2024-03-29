#ifndef CE_FILE_H
# define CE_FILE_H

char	*read_file(const char *path)
{
	int     fd;
	size_t  fsize;
	char	*src;
	ssize_t	bytes;
	char	*ret;

	(void)	ret;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		print("ERROR: errno=%i for open(%s)\n", errno, path);
		return 0;
	}
	fsize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	src = (char*) malloc(fsize + 1);
	if (!src)
	{
		close(fd);
		return 0;
	}
	src[fsize] = 0;
	fsize = 0;
	while((bytes = read(fd, src + fsize++, 1)) > 0)
		;
	close(fd);
	if (bytes != 0)
	{
		print("ERROR: read=%i for %s\n", errno, path);
		free(src);
		return 0;
	}
	return src;
}
#endif
