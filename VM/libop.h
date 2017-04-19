/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libop.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:33:11 by adzikovs          #+#    #+#             */
/*   Updated: 2017/03/30 15:04:06 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBOP_H
# define LIBOP_H
# include "../VM/corewar.h"
# include "libclist.h"
# include "libserv.h"
# include "libclist.h"
# include "unistd.h"

int			ft_run_op(unsigned char arena[2][4096],
			t_caret *proc, int vz, t_player **players);

typedef int	(*t_ops)(unsigned char *arena, t_caret *proc);

t_ops		*ft_op_arr_init(void);

int			ft_load(unsigned char *arena, t_caret *proc);

int			ft_store(unsigned char *arena, t_caret *proc);

int			ft_add(unsigned char *arena, t_caret *proc);

int			ft_sub(unsigned char *arena, t_caret *proc);

int			ft_and(unsigned char *arena, t_caret *proc);

int			ft_or(unsigned char *arena, t_caret *proc);

int			ft_xor(unsigned char *arena, t_caret *proc);

int			ft_zjmp(unsigned char *arena, t_caret *proc);

int			ft_load_index(unsigned char *arena, t_caret *proc);

int			ft_store_index(unsigned char *arena, t_caret *proc);

int			ft_fork(unsigned char *arena, t_caret *proc);

int			ft_long_load(unsigned char *arena, t_caret *proc);

int			ft_long_load_index(unsigned char *arena, t_caret *proc);

int			ft_long_fork(unsigned char *arena, t_caret *proc);

int			ft_aff(unsigned char *arena, t_caret *proc);

#endif
