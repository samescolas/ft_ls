/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 12:38:13 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 10:29:48 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*node;
	void	*new_content;

	node = ft_memalloc(sizeof(t_list));
	if (content)
	{
		new_content = ft_memalloc(content_size);
		if (!new_content || !node)
			return (NULL);
		ft_memcpy(new_content, content, content_size);
		node->content = new_content;
		node->content_size = content_size;
	}
	else
	{
		node->content = NULL;
		node->content_size = 0;
	}
	node->next = NULL;
	return (node);
}
