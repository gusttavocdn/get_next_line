/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guda-sil <guda-sil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 11:52:31 by guda-sil@st       #+#    #+#             */
/*   Updated: 2022/05/03 00:13:02 by guda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	read_and_store(int fd, char **accumulator, char *buffer);
static	char* create_line(char **accumulator);
static	void	update_acummulator(char **accumulator, char *new_buffer);
static	size_t	find_nl(const char *str, int c);

char *get_next_line(int fd)
{
	static char *accumulator = NULL;
	char *buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	read_and_store(fd, &accumulator, buffer);
	line = create_line(&accumulator);
	free(buffer);
	return (line);
}

static	void	read_and_store(int fd, char **accumulator, char *buffer)
{
	int readed_bytes;

	readed_bytes = read(fd, buffer, BUFFER_SIZE);
	if (readed_bytes > 0)
	{
		if (*accumulator == NULL)
			*accumulator = ft_strdup("");
		buffer[readed_bytes] = '\0';
		update_acummulator(accumulator, ft_strjoin(*accumulator, buffer));
		while (readed_bytes > 0 && ft_strchr(buffer, '\n') == NULL)
		{

			readed_bytes = read(fd, buffer, BUFFER_SIZE);
			buffer[readed_bytes] = '\0';
			update_acummulator(accumulator, ft_strjoin(*accumulator, buffer));
		}
	}
}

static	char* create_line(char **accumulator)
{
	char *new_line;
	size_t line_len;

	if (*accumulator == NULL)
		return (NULL);
	line_len = find_nl(*accumulator, '\n') + 1;
	new_line = ft_substr(*accumulator, 0, line_len);
	update_acummulator(accumulator, ft_substr(*accumulator, line_len, ft_strlen(*accumulator)));
	if (*accumulator[0] == '\0')
		update_acummulator(accumulator, NULL);
	return (new_line);
}

static	void	update_acummulator(char **accumulator, char *new_buffer)
{
	char *temp;
	temp = *accumulator;
	*accumulator = new_buffer;
	free(temp);
}

static	size_t	find_nl(const char *str, int c)
{
	size_t	size;

	size = 0;
	while (str[size])
	{
		if ((unsigned char) str[size] == (unsigned char) c)
			return (size);
		size++;
	}
	return (size);
}
