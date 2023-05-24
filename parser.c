#include "shell.h"


/**
 * is_cmd – Will determine if a file is an executable cmd
 * @info: Info structure
 * @path: The path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;


	(void)info;
	if (!path || stat(path, &st))
		return (0);


	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


/**
 * dup_chars – Will duplicate chars
 * @pathstr: Path str
 * @start: The starting index
 * @stop: The stopping index
 *
 * Return: Pointer to the new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int ui = 0, k = 0;


	for (k = 0, ui = start; ui < stop; ui++)
		if (pathstr[ui] != ':')
			buf[k++] = pathstr[ui];
	buf[k] = 0;
	return (buf);
}


/**
 * find_path – Will find this command in the path str
 * @info: Info structure
 * @pathstr: Path str
 * @cmd: Command to be found
 *
 * Return: The full path of command if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int ui = 0, curr_pos = 0;
	char *path;


	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[ui] || pathstr[ui] == ':')
		{
			path = dup_chars(pathstr, curr_pos, ui);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[ui])
				break;
			curr_pos = ui;
		}
		ui++;
	}
	return (NULL);
}

