/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:08:59 by nhaas             #+#    #+#             */
/*   Updated: 2021/07/19 15:19:28 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int static	ft_countsplits(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] == c && s[i] != '\0')
				i++;
		}
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	if (s[i - 1] == c)
		count--;
	return (count);
}

int static	ft_strtran(char const *s, char c, int i[2], char **array)
{
	int		j;
	int		k;
	char	*ar;

	ar = NULL;
	j = i[1];
	while (s[j] == c)
		j++;
	k = 0;
	while (s[j] != c && s[j] != '\0')
	{
		k++;
		j++;
	}
	array[i[0]] = ft_substr(&s[j - k], 0, k);
	if (array == NULL)
		return (0);
	while (s[j] == c)
		j++;
	return (j);
}

char static	**ft_zero(void)
{
	char	**array;

	array = (char **)malloc(sizeof(char *) * 1);
	array[0] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		splits;
	int		i[2];
	char	**array;

	if (s == NULL)
		return (NULL);
	if (s[0] == '\0' && c == '\0')
		return (ft_zero());
	splits = ft_countsplits(s, c);
	array = (char **)malloc(sizeof(char *) * (splits + 1));
	if (array == NULL)
	{
		free(*array);
		return (NULL);
	}
	i[0] = 0;
	i[1] = 0;
	while (i[0] < splits)
	{
		i[1] = ft_strtran(s, c, i, array);
		i[0]++;
	}
	array[splits] = NULL;
	return (array);
}
