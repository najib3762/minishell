/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:32:22 by namoussa          #+#    #+#             */
/*   Updated: 2024/08/04 12:30:40 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define FILENAME "/tmp/"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	conver_hex(char *buffer, char **filename, int fd)
{
	int		i;
	int		len;
	char	hex[2];
	char	*arr;

	arr = "0123456789ABCDEF";
	i = 0;
	close(fd);
	ft_strcpy(*filename, FILENAME);
	len = ft_strlen(buffer);
	while (i < len)
	{
		hex[0] = arr[(ft_abs(buffer[i]) % 16)];
		hex[1] = '\0';
		*filename = m_strjoin(*filename, hex);
		i++;
	}
}

char	*random_file(void)
{
	char	*filename;
	char	buffer[10];
	int		fd;
	int		j;

	j = 0;
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (NULL);
	}
	j = read(fd, buffer, sizeof(buffer));
	filename = malloc(strlen(FILENAME) + sizeof(buffer) + 1);
	addback_node_free(&g_global->address, newnode_free(filename));
	if (!filename)
	{
		perror("malloc");
		return (NULL);
	}
	conver_hex(buffer, &filename, fd);
	return (filename);
}
