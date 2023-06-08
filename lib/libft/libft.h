/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:24:46 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/22 02:18:37 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// struct

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef struct s_list_int
{
	int					content;
	struct s_list_int	*next;
	int					count;
}						t_list_int;

//functions
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_isprint(int c);
int			ft_isascii(int c);
int			ft_intlen(unsigned long nb);
int			ft_atoi(const char *str);
long		ft_atol(const char *str);
size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		ft_strrev(char *str);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
size_t		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
int			ft_putnbr_fd(int n, int fd);
char		*ft_tohex(unsigned long nb, int cap);
int			ft_putuint(unsigned int n);
int			ft_putformat(const char *str, va_list args);
int			ft_printf(const char *str, ...);
char		*ft_strdup_gnl(char *s1);
char		*ft_strjoin_gnl(char *s1, char const *s2);
char		*get_next_line(int fd);

// linked list
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new_node);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new_node);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list_int	*ft_lstnew_int(int content);
void		ft_lstadd_back_int(t_list_int **lst, t_list_int *new_node);
void		ft_lstdelone_int(t_list_int *lst);
void		ft_lstclear_int(t_list_int **lst);
int			ft_lstsize_int(t_list_int *lst);
#endif
