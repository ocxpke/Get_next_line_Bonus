/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:04:30 by jose-ara          #+#    #+#             */
/*   Updated: 2024/11/18 23:58:25 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_fildes
{
	int				fd;
	char			buffer[BUFFER_SIZE];
	char			*ptr;
	struct s_fildes	*next;
}					t_fildes;

/**
 * @brief Reads until the next \\n or EOF
 *
 * @param fd The file descriptor to read from
 * @return The readed line, \\n included, or NULL if something went wrong.
 */
char				*get_next_line(int fd);

/**
 * @brief Calculates th length of the string given
 *
 * @param s The string given
 * @return The length of the string or 0 if s == NULL
 */
ssize_t				ft_strlen(const char *s);

/**
 * @brief Concatenates the first len's bytes of str2 at the end of str1
 *
 * @param str1 Base of the new string
 * @param str2 String to concat atthe end
 * @param len Number of bytes to copy
 * @return Void
 */
void				concat_str(char *str1, char *str2, ssize_t len);

/**
 * @brief Sets the first len's bytes of str to zero
 *
 * @param str String to modify
 * @param len Number of bytes to copy
 * @return Void
 */
void				set_zero(char *str, ssize_t len);

/**
 * @brief Used to reset the static string
 *
 * @param str_sta String to reset
 * @param pos_nl The position of the new line \\n
 * @return Void
 */
void				reset_str_sta(char *str_sta, int pos_nl);

/**
 * Struct methods
 */
t_fildes			*init_add_nodes(t_fildes *static_struct, int fd);

t_fildes			*select_node(t_fildes *static_struct, int fd);

char				*free_node(t_fildes **static_struct, t_fildes *to_del);

#endif
