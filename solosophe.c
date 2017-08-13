/*
** solosophe.c for solosophe in /home/zoukie/epitech/PSU_2016_philo
**
** Made by zoukie
** Login   <romain.gadrat@epitech.eu>
**
** Started on  Thu Mar 16 04:05:45 2017 zoukie
** Last update Fri Mar 17 16:21:06 2017 Maxence Lauqué
*/

#include "philo.h"

void		exit_core(t_phil *tabPhil, int i)
{
  int           j;

  j = -1;
  while (++j < tabPhil[i].nbPhil)
    if (tabPhil[j].nbEat <= 0)
      pthread_exit(NULL);
}

void		myThink(t_phil *tabPhil, int i)
{
  tabPhil[i].etat = THINK;
  if (pthread_mutex_trylock(&tabPhil[i].mutex) == 0)
    {
      lphilo_take_chopstick(&tabPhil[i].mutex);
      lphilo_think();
      lphilo_release_chopstick(&tabPhil[i].mutex);
      pthread_mutex_unlock(&tabPhil[i].mutex);
      tabPhil[i].etat = EAT;
    }
}

void		myEat(t_phil *tabPhil, int i)
{
  int           suivant;

  tabPhil[i].etat = EAT;
  suivant = (i + 1) % tabPhil[i].nbPhil;
  if (pthread_mutex_trylock(&tabPhil[i].mutex) == 0)
    {
      lphilo_take_chopstick(&tabPhil[i].mutex);
      if (pthread_mutex_trylock(&tabPhil[suivant].mutex) == 0)
	{
	  lphilo_take_chopstick(&tabPhil[suivant].mutex);
	  lphilo_eat();
	  tabPhil[i].nbEat = tabPhil[i].nbEat - 1;
	  lphilo_release_chopstick(&tabPhil[suivant].mutex);
	  pthread_mutex_unlock(&tabPhil[suivant].mutex);
	  tabPhil[i].etat = REST;
	}
      lphilo_release_chopstick(&tabPhil[i].mutex);
      pthread_mutex_unlock(&tabPhil[i].mutex);
    }
}

void		myRest(t_phil *tabPhil, int i)
{
  tabPhil[i].etat = REST;
  lphilo_sleep();
  tabPhil[i].etat = THINK;
}
