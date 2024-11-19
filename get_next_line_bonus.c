/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:04:19 by jose-ara          #+#    #+#             */
/*   Updated: 2024/11/19 00:23:13 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

/**
 * @brief Reads the string until it finds the \\n
 *
 * @param buffer String to read
 * @return The position of '\n' or -1
 */
static int	contains_new_line(char *buffer)
{
	int	cont;

	cont = 0;
	if (!buffer)
		return (-1);
	while (buffer[cont])
	{
		if (buffer[cont] == '\n')
			return (cont + 1);
		cont++;
	}
	return (-1);
}

/**
 * @brief Used to reset the static string
 *
 * @param ptr A pointer to the location of the string were
 * we save the line in case of not having found the \\n
 * @param str_sta The static string
 * @param pos_nl The position of the new line \\n
 * @param cont In case of failure at reading
 * @return The final string to send
 */
static char	*final_ret(t_fildes *node, int pos_nl, ssize_t cont)
{
	int		ptr_len;
	char	*aux;

	if (pos_nl != -1)
		ptr_len = (pos_nl);
	else
		ptr_len = (ft_strlen(node->buffer));
	aux = (char *)malloc(ft_strlen(node->ptr) + ptr_len + 1);
	if ((!ft_strlen(node->ptr) && !ft_strlen(node->buffer)) || cont == -1
		|| !aux)
	{
		free(aux);
		free(node->ptr);
		free(node);
		return (NULL);
	}
	set_zero(aux, ft_strlen(node->ptr) + ptr_len + 1);
	concat_str(aux, node->ptr, ft_strlen(node->ptr));
	concat_str(aux, node->ptr, ptr_len);
	free(node->ptr);
	reset_str_sta(node->buffer, pos_nl);
	return (aux);
}

/**
 * @brief Used to reallocate the line readed with the others lines readed
 *
 * @param ptr A pointer to the location of the string were
 * we save the line in case of not having found the \\n
 * @param str_sta Static string
 * @param pos_nl The position of the new line \\n
 * @return Void
 */
static void	ft_realloc(t_fildes *node, int pos_nl)
{
	int		len;
	char	*aux;

	if (pos_nl == -1)
		len = ft_strlen(node->buffer);
	else
		len = pos_nl;
	if (node->ptr)
		len += ft_strlen(node->ptr);
	aux = (char *)malloc(len + 1);
	if (!aux)
		return ;
	set_zero(aux, len + 1);
	concat_str(aux, node->ptr, ft_strlen(node->ptr));
	concat_str(aux, node->buffer, len - ft_strlen(node->ptr));
	free(node->ptr);
	reset_str_sta(node->buffer, pos_nl);
	node->ptr = aux;
}

char	*get_next_line(int fd)
{
	static t_fildes	*str_fildes;
	ssize_t			cont;
	t_fildes		*act;

	cont = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str_fildes = init_add_nodes(str_fildes, fd);
	act = select_node(str_fildes, fd);
	act->ptr = NULL;
	if (contains_new_line(act->buffer) != -1)
		return (final_ret(act, contains_new_line(act->buffer), 0));
	else if (ft_strlen(act->buffer) > 0)
		ft_realloc(act, -1);
	while ((cont > 0) && (contains_new_line(act->ptr) == -1))
	{
		cont = read(fd, act->buffer, BUFFER_SIZE);
		ft_realloc(act, contains_new_line(act->buffer));
		if (!(act->ptr))
			return (NULL);
	}
	if (contains_new_line(act->ptr) != -1)
		return (act->ptr);
	return (final_ret(act, contains_new_line(act->buffer), cont));
}
/*
int	main(void)
{
	int		fd;
	char	*p;

	fd = open("../../francinette/tests/get_next_line/fsoares/variable_nls.txt",
			O_RDONLY);
	p = "a";
	while (p)
	{
		p = get_next_line(fd);
		//printf("%s", p);
		free(p);
	}
}
*/

