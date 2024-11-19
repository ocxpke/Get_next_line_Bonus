/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:43:39 by jose-ara          #+#    #+#             */
/*   Updated: 2024/11/19 00:20:25 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @brief Inicialise the structure, and adds new node if it is necessary
 */
t_fildes	*init_add_nodes(t_fildes *static_struct, int fd)
{
	t_fildes	*aux;
	t_fildes	*iter;

	aux = (t_fildes *)malloc(sizeof(t_fildes));
	if (!aux)
		return (NULL);
	aux->fd = fd;
	set_zero(aux->buffer, BUFFER_SIZE);
	aux->ptr = NULL;
	aux->next = NULL;
	if (!static_struct)
		return (aux);
	else
	{
		iter = static_struct;
		while (iter->next && (iter->fd) != fd)
			iter = iter->next;
		if ((iter->fd) != fd)
			iter->next = aux;
		else
			free(aux);
	}
	return (static_struct);
}

t_fildes	*select_node(t_fildes *static_struct, int fd)
{
	t_fildes	*iter;

	if (!static_struct)
		return (NULL);
	iter = static_struct;
	while (iter->fd != fd && iter)
		iter = iter->next;
	if (iter->fd == fd)
		return (iter);
	else
		return (NULL);
}

char	*free_node(t_fildes **static_struct, t_fildes *to_del)
{
	t_fildes	*iter;

	if ((*static_struct) == to_del)
	{
		if ((*static_struct)->next)
			(*static_struct) = (*static_struct)->next;
		else
			(*static_struct) = NULL;
		free(to_del->ptr);
		free(to_del->buffer);
		free(to_del->next);
		return (NULL);
	}
	iter = (*static_struct);
	while ((iter->next) != to_del)
		iter = iter->next;
	iter->next = to_del->next;
	free(*static_struct);
	return (NULL);
}


ssize_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

void	set_zero(char *str, ssize_t len)
{
	ssize_t	cont;

	if (!str)
		return ;
	cont = 0;
	while (cont < len)
	{
		str[cont] = 0;
		cont++;
	}
}

/**
 * No establezco el \0 al final por la implementacion del metodo set_zero
 * donde establece los valores a 0 por ende el final ya es 0
 */
void	concat_str(char *str1, char *str2, ssize_t len)
{
	ssize_t	cont;

	cont = 0;
	if (!str1 || !str2)
		return ;
	while (*str1)
		str1++;
	while (cont < len && str2[cont] != '\0')
	{
		str1[cont] = str2[cont];
		cont++;
	}
	str1[cont] = 0;
}

void	reset_str_sta(char *str_sta, int pos_nl)
{
	char	*aux;
	ssize_t	iter;

	if (pos_nl == -1)
		return (set_zero(str_sta, BUFFER_SIZE));
	aux = (char *)malloc(ft_strlen(str_sta) + 1);
	if (!aux)
		return (set_zero(str_sta, BUFFER_SIZE));
	set_zero(aux, ft_strlen(str_sta) + 1);
	iter = -1;
	while ((iter++) < (ft_strlen(str_sta) - pos_nl))
		aux[iter] = str_sta[iter + pos_nl];
	set_zero(str_sta, BUFFER_SIZE);
	iter = -1;
	while ((iter++) < ft_strlen(aux))
		str_sta[iter] = aux[iter];
	free(aux);
}
