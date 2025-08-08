/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:46:47 by logkoege          #+#    #+#             */
/*   Updated: 2025/08/08 16:35:31 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
 
int	add(const char **str);
 
int	error = 0;
 
int	parse_error(const char c)
{
	if (c)
		printf("Wrong char %c\n", c);
	else
		printf("Wrong end\n");
	error = 1;
	return (0);
}
 
int	parsus(const char **str)
{
	if (**str == '(')
	{
		(*str)++;
		int	value = add(str);
		if (error == 1)
			return (0);
		if (**str != ')')
			return (parse_error(**str));
		(*str)++;
		return (value);
	}
	if (isdigit(**str))
	{
		int	tmp = **str - '0';
		(*str)++;
		return (tmp);
	}
	return (parse_error(**str));
}

int	multi(const char **str)
{
	int	value = parsus(str);
	if (error == 1)
		return (0);
	while (**str == '*')
	{
		(*str)++;
		value *= parsus(str);
		if (error == 1)
			return (0);
		}
		return (value);
	}
	
	int	add(const char **str)
	{
		int	value = multi(str);
		if (error == 1)
			return (0);
		while (**str == '+')
		{
			(*str)++;
			value += multi(str);
			if (error == 1)
				return (0);
		}
		return (value);
	}
 
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
 
	const char	*str = argv[1];
	int			result = add(&str);
 
	if (error == 0 && *str != '\0')
	{
		parse_error(*str);
		return (1);
	}
	if (error == 1)
		return (1);
	printf("%d\n", result);
	return (0);
}
