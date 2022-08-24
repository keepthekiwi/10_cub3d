/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:26:23 by nhaas             #+#    #+#             */
/*   Updated: 2022/07/26 19:37:16 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, const int n)
{
	int		i;
	char	*ptr;

	i = 0;
	i = ft_strlen(str);
	if (i < n)
		ptr = malloc ((sizeof(char) * i + 1));
	else
		ptr = malloc ((n + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i <= n)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/**
int	main (void)
{
	char	src[] = "String";
	char	*dest;
	char	*dest2;

	dest = ft_strdup(src);
	dest2 = strdup(src);

	printf("--- ft_strdup.c ------------------\n\n");
	printf("src string: %s\ndest ow: %s\ndest or: %s\n\n", src, dest, dest2);
	return (0);
}
**/
