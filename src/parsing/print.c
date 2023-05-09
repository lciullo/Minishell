/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:03:45 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/09 10:10:57 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list	*a)
{
	printf(" data        | type\n");
	printf("-------------------\n");
	while (a)
	{
		print_tab(a->data);
		printf("%d\n", a->type);
		if (a->next != NULL)
			printf("------------------\n");
		a = a->next;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s | ", tab[i]);
		i++;
	}
}

void	list_print(t_list *lst)
{
	while (lst)
	{
		print_tab(lst->data);
		printf("\n");
		printf("%d\n", lst->type);
		//ft_dprintf(1, "%d\n", lst->type);
		lst = lst->next;
	}
	ft_dprintf(1, "\n");
}