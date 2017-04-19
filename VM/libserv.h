/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libserv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:29:18 by adzikovs          #+#    #+#             */
/*   Updated: 2017/04/19 15:55:30 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSERV_H
# define LIBSERV_H

int				ft_get_ind(unsigned char *arena, int pc, short addr, int idx);

int				ft_get_val(unsigned char *arena, int n, int start);

void			ft_mem_read(void *arena, void *var, int n, int start);

void			ft_mem_write(void *arena, void *var, int n, int start);

int				ft_reg_check(unsigned char *arena, int pc, int n);

int				*ft_get_args(unsigned char *arena, unsigned char *acb, int pc,
				int *reg);

void			ft_alw_init(int *alw, int n1, int n2, int n3);

unsigned char	*ft_read_acb(unsigned char *acb);

int				ft_acb_check(unsigned char *acb, unsigned char *arena, int pc,
				int *alw);

#endif
