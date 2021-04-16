/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 17:17:50 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/17 00:00:41 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**	pf_parse_flags(struct printf_infos)
**	@description:		parse flags and put in @param
**	@param:				struct t_pfinfo
*/

static	void			pf_parse_flags(t_pfinfo *p)
{
	while (p->format[p->count] && ft_strchr(PF_FLAGS, p->format[p->count]))
	{
		if (p->format[p->count] == '-')
			p->flags |= PF_MINUS;
		else if (p->format[p->count] == '+')
			p->flags |= PF_PLUS;
		else if (p->format[p->count] == '0')
			p->flags |= PF_ZERO;
		else if (p->format[p->count] == '#')
			p->flags |= PF_HASH;
		else if (p->format[p->count] == ' ')
			p->flags |= PF_SPACE;
		p->count++;
	}
}

/*
**	pf_parse_size(struct printf_infos)
**	@description:		parse size and put in @param
**	@param:				struct t_pfinfo
*/

static	void			pf_parse_size(t_pfinfo *p)
{
	if (p->format[p->count] == '*')
	{
		p->flags |= PF_WIDTH;
		p->width = va_arg(p->va, int);
		p->count++;
	}
	else if (ft_isdigit(p->format[p->count]))
	{
		p->flags |= PF_WIDTH;
		p->width = ft_atoi(p->format + p->count);
		p->count += ft_numlen(p->width);
	}
	if (p->format[p->count] == '.' && (p->flags |= PF_PRECIS))
	{
		p->count++;
		if (p->format[p->count] == '*' && (p->count++))
			p->prec = va_arg(p->va, int);
		else if (ft_isdigit(p->format[p->count]))
		{
			p->prec = ft_atoi(p->format + p->count);
			while (ft_isdigit(p->format[p->count]))
				p->count++;
		}
	}
}

/*
**	pf_parse_type(struct printf_infos)
**	@description:		parse type with bonus "l,ll,h,hh"
**	@param:				struct t_pfinfo
*/

static	void			pf_parse_type(t_pfinfo *p)
{
	while (p->format[p->count] && ft_strchr(PF_MF, p->format[p->count]))
	{
		if (p->format[p->count] == 'l')
		{
			if (p->format[p->count + 1] == 'l')
				p->flags |= PF_LL;
			else
				p->flags |= PF_L;
		}
		if (p->format[p->count] == 'h')
		{
			if (p->format[p->count + 1] == 'h')
				p->flags |= PF_HH;
			else
				p->flags |= PF_H;
		}
		p->count++;
	}
	p->type = p->format[p->count];
	p->count++;
}

/*
**	pf_parse(struct printf_infos)
**	@description:		parse format for ft_printf
**	@param:				struct t_pfinfo
*/

void					pf_parse(t_pfinfo *p)
{
	if (p->format[p->count] == '%')
		p->count++;
	pf_parse_flags(p);
	pf_parse_size(p);
	pf_parse_type(p);
	if (p->width < 0)
	{
		p->width *= -1;
		p->flags |= PF_MINUS;
	}
	if (p->prec < 0)
		p->flags &= ~PF_PRECIS;
}
