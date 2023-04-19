/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:04:05 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/19 11:45:41 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_structure(t_parsing *parsing)
{
	parsing->nbr_pipe = 0;
	parsing->len_line = 0;
	parsing->nbr_quote = 0;
	parsing->nbr_redir = 0;
}