/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:41:00 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/21 14:02:12 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef	struct s_parsing {
	int	nbr_pipe;
	int	nbr_quote;
	int	len_line;
	int	nbr_redir;
	int	i;
}	t_parsing;

enum {
	DATA,
	INFILE,
	OUTFILE,
	HERE_DOC,
	APPEND,
};

/* ---- utils_parsing.c ----*/
void	init_structure(t_parsing *parsing);

int		parsing(char **line);

#endif