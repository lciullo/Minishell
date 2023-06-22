/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:25:27 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/22 11:36:42 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_export_end_according_cases(t_export *stat, \
			char *name, char *value)
{
	if (stat->in_env == TRUE && stat->equal == FALSE && stat->plus == FALSE)
		free(name);
	else if (stat->in_env == TRUE && stat->equal == TRUE && stat->plus == FALSE)
	{
		free(name);
		free(value);
	}
	else if (stat->in_env == TRUE && stat->equal == TRUE && stat->plus == TRUE)
	{
		free(name);
		free(value);
	}
}
