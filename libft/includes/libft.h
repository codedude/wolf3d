/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 22:22:13 by vparis            #+#    #+#             */
/*   Updated: 2018/04/25 02:51:48 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include "ft_type.h"
# include "ft_list.h"

/*
** Memory manipulation
*/

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_memalloc_fast(size_t size);
void				*ft_memchr_fast(const void *s, int c);
void				*ft_memccpy_fast(void *dest, const void *src, int c);
void				*ft_memrealloc(void *src, size_t old, size_t size);
void				*ft_memrealloc_fast(void *src, size_t old, size_t size);

/*
** String manipulation
*/

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
								size_t size);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_strtoupper(char *s1);
void				ft_strtolower(char *s1);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
void				ft_strrev(char *s);
char				*ft_strcat2(char *dest, const char *src1, const char *src2);
char				*ft_strnew_fast(size_t size);
char				**ft_strsplit_whitespaces(char const *s);
char				**ft_strsplit_str(char const *s, char const *charset);
void				ft_strsplit_free(char **str);

/*
** Number/String conversion
*/

int					ft_atoi(const char *nptr);
char				*ft_itoa(int n);
int					ft_atoi_base(char const *nptr, char const *base);
int					ft_atoi_s(const char *str, int *nb);
int					ft_atof_s(char *str, t_f64 *n);

/*
** ASCII Characters checking
*/

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isxdigit(int c);
int					ft_isspace(int c);
int					ft_isblank(int c);
int					ft_ispunct(int c);
int					ft_iscntrl(int c);
int					ft_isgraph(int c);
int					ft_ischarset(int c, char const *charset);

/*
** Outputs
*/

void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd_fast(char const *s, int fd);
void				ft_putendl_fd_fast(char const *s, int fd);
void				ft_putrevendl(char const *s);
void				ft_putrevendl_fd(char const *s, int fd);
void				ft_putrevstr(char const *s);
void				ft_putrevstr_fd(char const *s, int fd);
void				ft_putchar_nonprint(char c);
void				ft_putchar_nonprint_fd(char c, int fd);
void				ft_putstr_nonprint(char const *s);
void				ft_putstr_nonprint_fd(char const *s, int fd);

#endif
