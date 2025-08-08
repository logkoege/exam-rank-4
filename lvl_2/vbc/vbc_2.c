/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:10:42 by logkoege          #+#    #+#             */
/*   Updated: 2025/08/08 16:35:29 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

void err(const char *msg)
{
	while (*msg)
		if (write(2, msg++, 1) < 0)
			exit(1);
	exit(1);
}

int expr(const char *s, int *i);

int factor(const char *s, int *i)
{
	int res;

	if (s[*i] == '(')
	{
		(*i)++;
		res = expr(s, i);
		if (s[*i] != ')')
			err("unexpected token ')'\n");
		(*i)++;
		return res;
	}
	if (isdigit(s[*i]))
		return s[(*i)++] - '0';
	if (s[*i] == '\0')
		err("unexpected end of input\n");
	return 0;
}

int term(const char *s, int *i)
{
	int res = factor(s, i);
	while (s[*i] == '*')
	{
		(*i)++;
		res *= factor(s, i);
	}
	return res;
}

int expr(const char *s, int *i)
{
	int res = term(s, i);
	while (s[*i] == '+')
	{
		(*i)++;
		res += term(s, i);
	}
	return res;
}

int main(int ac, char **av)
{
	int i = 0, res;

	if (ac != 2)
		return 1;
	res = expr(av[1], &i);
	if (av[1][i])
	{
		if (av[1][i] == ')')
			err("unexpected token ')'\n");
		else
			err("unexpected token\n");
	}
	if (printf("%d\n", res) < 0)
		exit(1);
	return 0;
}