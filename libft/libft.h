/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:20:13 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/04 17:22:06 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "unistd.h"
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_list	t_list;
struct					s_list
{
	void				*content;
	t_list				*next;
};

int		ft_next_prime(int n);
bool	ft_isprime(int n);
int		ft_arraylen(char **str);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);
size_t	ft_strlen(const char *str);
size_t	ft_strnlen(const char *s, size_t n);
void	*ft_memset(void *s, int c, size_t size);
void	ft_bzero(void *s, size_t size);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
void	*ft_memmove(void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *s1, const char *s2, size_t n);
int		ft_strcpy(char *dest, const char *src);
char	 *ft_strcat(char *dest, const char *src);
size_t	ft_strlcat(char *s1, const char *s2, size_t n);
void	ft_strncat(char **dest, const char *src, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int n);
char	*ft_strrchr(const char *s, int n);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strndup(const char *s, size_t n);
void	*ft_memchr(const void *s, int nmem, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
// printf
int		ft_printf(const char *s, ...);
void	ft_char(char c, va_list list, int *counter);
void	ft_number(char c, va_list list, int *counter);
void	ft_number_hexa(char s, va_list list, int *counter);
void	ft_pointer(va_list list, int *counter);
void	ft_place(char c, va_list list, int *counter);
void	ft_putnbr_hexa(unsigned long n, char *base, int *counter);
int		ft_signed_len(int nbr);
int		ft_unsigned_len(unsigned int nbr);
void	ft_unsigned_number(unsigned int nbr);
// Listes chainees
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// get next line
char	*get_next_line(int fd);
char	*ft_pickline(char *remainder);
char	*ft_read_file(int fd, char *rest);
char	*ft_free(char *buffer, char *buf);
char	*ft_update(char *rest);
#endif
