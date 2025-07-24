/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_type_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:03:55 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/21 09:08:26 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"



/**
 * redir_type_to_str - Get string representatoin of a redirection type
 *
 * @type: redicretion type to be represented
 * Return: constant LATERAL string
 */
const char	*redir_type_to_str(t_redir_type type)
{
	if (type == R_INPUT)
		return ("<");
	else if (type == R_OUTPUT)
		return (">");
	else if (type == R_HERDOC)
		return (">>");
	else if (type == R_APPAND)
		return (">>");
	else
		return ("shit");
}
