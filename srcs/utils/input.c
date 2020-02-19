/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:16:51 by hberger           #+#    #+#             */
/*   Updated: 2020/02/19 18:10:39 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** inputcontrol() vérifie que l'input est valide
** - s'il n'est pas vide
** - si la longueur est supérieure à 0
** - s'il n'y a que des espaces / tab ...
*/

/*
** UPDT : full espace re affiche le prompt
** En gros ici il faut coder la gestion des comportement que l'on a pas a gerer
*/

int		inputcontrol(char *input)
{
  int	i;
  int	space;

  if (input == 0)
    return (0);
  if (ft_strlen(input) == 0)
    return (0);
  i = -1;
  space = 0;
  while (input[++i] != '\0')
    if (input[i] == '\t' || input[i] == '\n' || input[i] == ' ')
      space++;
  if (space == i)
    return (0);
  return (1);
}
