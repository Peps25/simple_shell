#include "shell.h"

/**
 * input_buf – The buffers chained commands
 * @info: Parameter structure
 * @buf: Buffer address
 * @len: len variable address
 *
 * Return: Bytes that are read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t p = 0;
	size_t len_s = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		p = getline(buf, &len_s, stdin);
#else
		p = _getline(info, buf, &len_s);
#endif
		if (p > 0)
		{
			if ((*buf)[p - 1] == '\n')
			{
				(*buf)[p - 1] = '\0'; /* remove trailing newline */
				p--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = p;
				info->cmd_buf = buf;
			}
		}
	}
	return (p);
}

/**
 * get_input – Will get line minus the newline
 * @info: Parameter structure
 *
 * Return: Bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t ui, j, len;
	ssize_t p = 0;
	char **buf_s = &(info->arg), *s;

	_putchar(BUF_FLUSH);
	p = input_buf(info, &buf, &len);
	if (p == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = ui; /* init new iterator to current buf position */
		s = buf + ui; /* get pointer for return */

		check_chain(info, buf, &j, ui, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		ui = j + 1; /* increment past nulled ';'' */
		if (ui >= len) /* reached end of buffer? */
		{
			ui = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_s = s; /* pass back pointer to current command position */
		return (_strlen(s)); /* return length of current command */
	}

	*buf_s = buf; /* else not a chain, pass back buffer from _getline() */
	return (p); /* return length of buffer from _getline() */
}

/**
 * read_buf – Will read buffer
 * @info: Parameter structure
 * @buf: Buffer
 * @ui: Size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *ui)
{
	ssize_t r = 0;

	if (*ui)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*ui = r;
	return (r);
}


/**
 * _getline – Will get next line of input from STDIN
 * @info: Parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t ui, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (ui == len)
		ui = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + ui, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + ui, k - ui);
	else
		_strncpy(new_p, buf + ui, k - ui + 1);

	s += k - ui;
	ui = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


/**
 * sigintHandler – Will block ctrl-C
 * @sig_num: Signal number
 *
 * Return: Void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

