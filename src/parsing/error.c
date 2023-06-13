/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:49:06 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/12 19:16:59 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int error_code)
{
	if (error_code == MALLOC_ERR)
		ft_dprintf(2, "minishell : a malloc failed during the parsing\n");
	else if (error_code == HERE_DOC_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'<<\'\n");
	else if (error_code == APPEND_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'>>\'\n");
	else if (error_code == IN_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'<\'\n");
	else if (error_code == OUT_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'>\'\n");
	else if (error_code == PIPE_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'|\'\n");
	else if (error_code == S_QUOTE_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'\'\'\n");
	else if (error_code == D_QUOTE_ERR)
		ft_dprintf(2, "minishell : syntax error near unexpected token \'\"\'\n");
}
