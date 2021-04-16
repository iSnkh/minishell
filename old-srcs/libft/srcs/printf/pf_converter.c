/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_converter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:57:06 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/17 00:00:41 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**	pf_convert_uminus 	:: static void (struct printf_info)
**	@description:	converter functions for unsigned int with flag '-'
**	@params:		struct t_pfinfo *p
*/

static void		pf_convert_uminus(t_pfinfo *p, char *str)
{
	int				len;

	if (p->flags & PF_PRECIS && p->prec
	&& p->prec > (int)ft_strlen(str))
		pf_addzeros(p, (int)ft_strlen(str) - p->prec);
	pf_stradd(p, str);
	len = ft_strlen(str);
	if (p->prec > (int)ft_strlen(str))
		len = p->prec;
	if (p->flags & PF_WIDTH && p->width > (int)ft_strlen(str) &&
	!(p->flags & PF_PRECIS || p->prec))
		return (pf_addspaces(p, p->width - (ft_strlen(str))));
	if (p->flags & PF_WIDTH && p->width >= len)
		return (pf_addspaces(p, p->width - len));
}

/*
**	pf_convert_unsigned 	:: static void (struct printf_info, number)
**	@description:	converter functions for unsigned integer.
**	@params:		struct t_pfinfo *p
*/

void			pf_convert_unsigned(t_pfinfo *p, long long number)
{
	const	char		*str = ft_ulltoa_base(number, DEC_BASE);
	int					len;

	if (!p->flags)
		return (pf_stradd(p, (char *)str));
	if (p->flags & PF_PRECIS && !p->prec && !number)
	{
		free((char *)str);
		return (pf_addspaces(p, p->width));
	}
	if (p->flags & PF_MINUS)
		return (pf_convert_uminus(p, (char *)str));
	len = ft_strlen(str);
	if (p->prec > (int)ft_strlen(str))
		len = p->prec;
	if (p->flags & PF_WIDTH && p->width >= len &&
	(!(p->flags & PF_ZERO) || p->flags & PF_PRECIS))
		pf_addspaces(p, p->width - len);
	if (p->flags & PF_WIDTH && p->width >= len
	&& p->flags & PF_ZERO && !(p->flags & PF_PRECIS))
		pf_addzeros(p, p->width - len);
	if (p->flags & PF_PRECIS && p->prec > (int)ft_strlen(str))
		pf_addzeros(p, ft_strlen(str) - p->prec);
	return (pf_stradd(p, (char *)str));
}

/*
**	pf_convert_pointer 	:: static void (struct printf_info)
**	@description:	converter functions for pointer and address
**	@params:		struct t_pfinfo *p
*/

void			pf_convert_pointer(t_pfinfo *p)
{
	const	intptr_t	ptr = (intptr_t)va_arg(p->va, void *);
	char				*str;

	if (p->flags & PF_PRECIS && !ptr)
		str = ft_strdup("0x");
	else
		str = ft_strjoin(ft_strdup("0x"),
		ft_ulltoa_base((unsigned long long)ptr, LOW_HEXA));
	if (p->flags & PF_WIDTH && !(p->flags & PF_MINUS)
	&& p->width > (int)ft_strlen(str))
		pf_addspaces(p, p->width - ft_strlen(str));
	pf_stradd(p, str);
	if (p->flags & PF_WIDTH && p->flags & PF_MINUS
	&& p->width > (int)ft_strlen(str))
		pf_addspaces(p, p->width - ft_strlen(str));
}

/*
**	pf_convert_char 	:: static void (struct printf_info, bool is_pourcent)
**	@description:	converter functions for char and %
**	@params:		struct t_pfinfo *p
*/

void			pf_convert_char(t_pfinfo *p, int is_pourcent)
{
	const char	c = is_pourcent ? '%' : va_arg(p->va, int);

	if (p->flags & PF_MINUS)
	{
		pf_charadd(p, c);
		if (p->width > 1)
			pf_addspaces(p, p->width - 1);
		return ;
	}
	if (p->width > 1 && p->flags & PF_ZERO)
		pf_addzeros(p, p->width - 1);
	else if (p->flags & PF_WIDTH && p->width > 1)
		pf_addspaces(p, p->width - 1);
	pf_charadd(p, c);
}

/*
**	pf_convert_string 	:: static void (struct printf_info)
**	@description:	converter functions for string.
**	@params:		struct t_pfinfo *p
*/

void			pf_convert_string(t_pfinfo *p)
{
	char	*str;

	str = va_arg(p->va, char *);
	if (!str)
		str = "(null)";
	str = ft_strdup(str);
	if (!p->flags)
		return (pf_stradd(p, str));
	if (p->flags & PF_PRECIS)
		str = ft_strncpy(ft_calloc(p->prec + 1, sizeof(char)), str,
		p->prec);
	if (p->flags & PF_MINUS)
	{
		pf_stradd(p, str);
		if (p->flags & PF_WIDTH && p->width > (int)ft_strlen(str))
			pf_addspaces(p, p->width - (int)ft_strlen(str));
		return ;
	}
	if (p->flags & PF_WIDTH && p->width > (int)ft_strlen(str))
		pf_addspaces(p, p->width - (int)ft_strlen(str));
	pf_stradd(p, str);
}
