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

void	conver_hex(char *buffer, char **filename)
{
	int		i;
	int		len;
	char	*arr;
	int		k;

	k = 0;
	arr = "0123456789ABCDEF";
	i = 0;
	ft_strcpy(*filename, FILENAME);
	k = ft_strlen(*filename);
	len = ft_strlen(buffer);
	while (i < len)
	{
		(*filename)[k++] = arr[(ft_abs(buffer[i]) % 16)];
		i++;
	}
	(*filename)[k] = '\0';
}

char	*random_file(void)
{
	char	*filename;
	char	buffer[20];
	int		fd;
	int		j;

	j = 0;
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (NULL);
	}
	j = read(fd, buffer, 10);
	buffer[j] = '\0';
	close(fd);
	filename = malloc(strlen(FILENAME) + (10 + 1));
	addback_node_free(&g_global->address, newnode_free(filename));
	if (!filename)
	{
		perror("malloc");
		return (NULL);
	}
	conver_hex(buffer, &filename);
	return (filename);
}
