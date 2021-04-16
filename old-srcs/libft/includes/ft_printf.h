/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:36:58 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/17 00:19:50 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

# define PF_TYPES 		"cspdiuxX%"
# define PF_FLAGS		"-0+# "
# define PF_MF			"lh"

# define DEC_BASE 		"0123456789"
# define LOW_HEXA 		"0123456789abcdef"
# define UP_HEXA 		"0123456789ABCDEF"

enum
{
	PF_MINUS = (1 << 0),
	PF_ZERO = (1 << 1),
	PF_STAR = (1 << 2),
	PF_PRECIS = (1 << 3),
	PF_WIDTH = (1 << 4),
	PF_PLUS = (1 << 5),
	PF_SPACE = (1 << 6),
	PF_HASH = (1 << 7),
	PF_L = (1 << 8),
	PF_LL = (1 << 9),
	PF_H = (1 << 10),
	PF_HH = (1 << 11),
	PF_Z = (1 << 12)
};

/*
**	flags:			encoded with bitwise check define at top
**	width:			if has width
**	precision:		precision, if s print only number in precision
**	type:			conversion type (c|s|d|...)
**	content:		chained list contains all part of content
**	count:			position in format
**	format:			format input
**	va:				va_list containing flags input
*/

typedef	struct			s_pfinfo
{
	short				flags;
	int					width;
	int					prec;
	int					type;
	struct s_pfcontent	*content;
	size_t				count;
	char				*format;
	va_list				va;
}						t_pfinfo;

typedef struct			s_pfcontent
{
	size_t				size;
	char				*content;
	struct s_pfcontent	*next;
}						t_pfcontent;

/*
**	srcs/ft_printf.c
*/

int						ft_printf
(const char *format, ...) __attribute__((format(printf,1,2)));
int						pf_print(int fd, t_pfinfo *p);
int						ft_dprintf(int fd, const char *format, ...);
void					pf_convert(t_pfinfo *p);

/*
**	srcs/pf_parser.c
*/

void					pf_parse(t_pfinfo *p);

/*
**	srcs/pf_converter.c
*/

void					pf_convert_char(t_pfinfo *p, int is_pourcent);
void					pf_convert_string(t_pfinfo *p);
void					pf_convert_decimal(t_pfinfo *p, long long int number);
void					pf_convert_pointer(t_pfinfo *p);

void					pf_convert_unsigned(t_pfinfo *p, long long number);
void					pf_convert_hexa(t_pfinfo *p, char *base,
long long number);

/*
**	srcs/pf_content.c
*/

void					pf_charadd(t_pfinfo *p, int c);
void					pf_stradd(t_pfinfo *p, char *str);

/*
**	srcs/pf_utilities.c
*/

void					pf_addspaces(t_pfinfo *p, int width);
void					pf_addzeros(t_pfinfo *p, int width);

/*
**	srcs/bonus/pf_bonus.c
*/

void					pf_bind_ptr(t_pfinfo *p);
void					pf_convert_bonus(t_pfinfo *p);
void					pf_convert_dbonus(t_pfinfo *p);

#endif
