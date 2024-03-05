/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:12:52 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/22 11:27:09 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <fcntl.h>

# define PATH_ERROR	"PATH acces error"
# define ERROR_IN "error infile: No such file or directory: "
# define ERROR_OUT "error outfile: No such file or directory: "
# define ERROR_CMD "command not found"
# define ERROR_PIPE "error creating pipe"
# define ERROR_SPIPE "syntax error near unexpected token `|'"
# define ERROR_DQUOTE "syntax error near unexpected token `\"'"
# define ERROR_SQUOTE "syntax error near unexpected token `''"
# define ERROR_ENDLINE "syntax error near unexpected token `newline'"
# define ERROR_INFCAR "syntax error near unexpected token `<'"
# define ERROR_DINCAR "syntax error near unexpected token `<<'"
# define ERROR_DOUTCAR "syntax error near unexpected token `>>'"
# define ERROR_OUTCAR "syntax error near unexpected token `>'"
# define ERROR_INOUTCAR "syntax error near unexpected token `<>"
# define ERROR_TRIPINF "syntax error we don't need to implement `<<<'"
# define ERROR_HER_HIP "option `<<-' not implemented, \
it will be treated as `<<'"	
# define ERROR_AMB "ambiguous redirect"
# define FRIENDLY_MSG "please check permissions"

int		ft_err_msg(char *str1, char *str2, char *str3, int ernb);
int		ft_err_msg_n(char *str1, char *str2, char *str3, int ernb);

#endif