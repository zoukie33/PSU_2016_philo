/*
** philo.h for philo h in /home/gadrat_r/delivery/PSU_2016_philo/include
** 
** Made by Romain Gadrat
** Login   <gadrat_r@epitech.net>
** 
** Started on  Mon Mar 13 19:57:00 2017 Romain Gadrat
** Last update Thu Mar 16 04:09:14 2017 zoukie
*/

#ifndef PHILO_H_
# define PHILO_H_

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "extern.h"

typedef enum			e_etat
  {
    THINK,
    EAT,
    REST
  }				e_etat;

typedef struct		s_phil
{
  int			num;
  int			nbPhil;
  int			nbEat;
  e_etat		etat;
  pthread_t		phil;
  pthread_mutex_t	mutex;
}			t_phil;

typedef struct		s_stats
{
  int			nbPhilo;
  int			nbEat;
}			t_stats;

void	exit_core(t_phil *tabPhil, int i);
void	myThink(t_phil *tabPhil, int i);
void	myEat(t_phil *tabPhil, int i);
void	myRest(t_phil *tabPhil, int i);
void	*table(void *infos);
int	philosofication(t_phil *tabPhil, t_stats *infos);
int	philosofion(t_stats infos);
int	parsing(t_stats *infos, int argc, char **argv);

#endif /* !PHILO_H_ */
