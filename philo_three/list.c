/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 13:35:30 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/16 13:35:32 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*ft_lstnew(int content)
{
	t_list *ptr;

	if ((ptr = (t_list*)malloc(sizeof(*ptr))))
	{
		ptr->i = content;
		ptr->next = 0;
	}
	return (ptr);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *ptr;
	t_list *debut;

	if (new && alst)
	{
		if (!*alst)
			*alst = new;
		else
		{
			debut = *alst;
			ptr = ft_lstlast(debut);
			ptr->next = new;
			new->next = 0;
		}
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list *debut;
	t_list *suivant;

	if (lst && *lst)
	{
		debut = *lst;
		suivant = 0;
		while (debut)
		{
			suivant = (debut->next);
			free(debut);
			debut = suivant;
		}
		*lst = 0;
	}
}

void	add_write(int elem, t_glob *gen)
{
	t_list	*new;

	if (!(new = ft_lstnew(elem)))
		exit(0);
	ft_lstadd_back(&(gen->philo->print), new);
}
