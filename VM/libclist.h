/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libclist.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:54:18 by adzikovs          #+#    #+#             */
/*   Updated: 2017/03/25 15:49:49 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCLIST_H
# define LIBCLIST_H
# define REG_NUMBER 16
# include <stdlib.h>

t_caret			*ft_create_proc(int *reg, int pc, int info[2]);

void			ft_clist_pb(t_caret *begin, int *reg, int pc, int info[2]);

void			ft_clist_delone(t_caret **begin, int n);

void			ft_clist_del(t_caret **begin);

#endif
