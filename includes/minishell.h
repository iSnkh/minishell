/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:31:02 by amonteli          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/01/08 16:23:12 by amonteli         ###   ########lyon.fr   */
=======
/*   Updated: 2021/01/08 16:17:01 by wperu            ###   ########lyon.fr   */
>>>>>>> cad2946a17f25ec2ea71f32c22d5e88f304b42b7
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <ernno.h>
# include <Linux/limits.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"

<<<<<<< HEAD
typedef struct		s_ms
{
		char		**env;
}					t_ms;
=======
>>>>>>> cad2946a17f25ec2ea71f32c22d5e88f304b42b7

int		main(int argc, char **args, char **env);
void    built_in_cd(char *path);
void    build_in_pwd(void);

void	shell_loop();
#endif
