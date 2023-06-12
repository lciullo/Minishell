/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:49:06 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/12 11:53:49 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int error_code)
{
	if (error_code == MALLOC_ERR)
		ft_dprintf(2, "minishell : a malloc failed during the parsing\n");
}