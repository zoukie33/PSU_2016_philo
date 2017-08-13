/*
** pastisolophe.c for philosophes.c in /home/gadrat_r/delivery/PSU_2016_philo
**
** Made by Romain Gadrat
** Login   <gadrat_r@epitech.net>
**
** Started on  Mon Mar 13 19:48:11 2017 Romain Gadrat
** Last update Thu Mar 16 04:06:48 2017 zoukie
*/

#include "philo.h"

void		*table(void *infos)
{
  t_phil	*tabPhil;
  int		i;

  tabPhil = ((t_phil *)infos);
  i = tabPhil[0].num;
  tabPhil -= i;
  while (1)
    {
      usleep(100);
      if (tabPhil[i].etat == THINK)
	myThink(tabPhil, i);
      else if (tabPhil[i].etat == EAT)
	myEat(tabPhil, i);
      else if (tabPhil[i].etat == REST)
	myRest(tabPhil, i);
      exit_core(tabPhil, i);
    }
  return (NULL);
}

int		philosofication(t_phil *tabPhil, t_stats *infos)
{
  int	i;

  i = -1;
  while (++i != infos->nbPhilo)
    pthread_create(&tabPhil[i].phil, NULL, table, tabPhil + i);
  i = -1;
  while (++i != infos->nbPhilo)
    pthread_join(tabPhil[i].phil, NULL);
  i = -1;
  while (i++ != infos->nbPhilo)
    pthread_mutex_destroy(&tabPhil[i].mutex);
  free(tabPhil);
  return (0);
}

int		philosofion(t_stats infos)
{
  t_phil	*tabPhil;
  int		sas;

  sas = -1;
  if ((tabPhil = malloc(sizeof(t_phil) * 4096 + 1)) == NULL)
    return (0);
  while (++sas != infos.nbPhilo)
    {
      tabPhil[sas].num = sas;
      tabPhil[sas].nbPhil = infos.nbPhilo;
      tabPhil[sas].nbEat = infos.nbEat;
      if (sas % 2 == 0)
	tabPhil[sas].etat = THINK;
      else
	tabPhil[sas].etat = REST;
      pthread_mutex_init(&tabPhil[sas].mutex, NULL);
    }
  philosofication(tabPhil, &infos);
  return (0);
}

int		parsing(t_stats *infos, int argc, char **argv)
{
  int		i;

  i = 0;
  infos->nbPhilo = 0;
  infos->nbEat = 0;
  while (++i != argc)
    {
      if (argv[i][0] == '-')
	{
	  if (argv[i][1] == 'e')
	    infos->nbEat = atoi(argv[i+1]);
	  else if (argv[i][1] == 'p')
	    infos->nbPhilo = atoi(argv[i+1]);
	}
    }
  if (infos->nbPhilo < 2 || infos->nbEat < 1)
    return (1);
  return (0);
}

int	main(int argc, char **argv)
{
  t_stats	infos;

  RCFStartup(argc, argv);
  if (parsing(&infos, argc, argv))
    {
      printf("Bad Parameter.\n");
      return (0);
    }
  if (infos.nbEat == 0 && infos.nbPhilo == 0)
    return (0);
  philosofion(infos);
  RCFCleanup();
  return (0);
}
