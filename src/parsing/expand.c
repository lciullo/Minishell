/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:20:07 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/23 15:50:44 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(char **tab, t_env **lst_env)
{
	int	row;
	int	i;

	row = 0;
	(void)lst_env;
	while (tab[row])
	{
		i = 0;
		while (tab[row][i])
		{
			if (tab[row][i] == '\'')
				skip_quote(tab[row], &i, tab[row][i]);
			if (tab[row][i] && tab[row][i] == '$')
			{
				i++;
				while (tab[row][i] && ((tab[row][i] <= 9 && tab[row][i] >= 13) || tab[row][i] != ' ') && tab[row][i] != '\"')
				{
					ft_dprintf(1, "%c", tab[row][i]);
					i++;
				}
			}
			else if (tab[row][i]) 
				i++;
		}
		row++;
	}
}
