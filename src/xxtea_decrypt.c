/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xxtea_decrypt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:14:34 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/31 10:31:48 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>

#define DELTA 0x9e3779b9
#define MX (((z >> 5) ^ (y << 2)) + ((y >> 3) ^ (z << 4))) ^ ((sum ^ y) + (key[(p & 3) ^ e] ^ z))

void	xxtea_decrypt(uint32_t *data, size_t len, const uint32_t *key)
{
/*	while (len)
	{
		*data = ~(*data);
		data++;
		len--;
	}
	key = NULL;
	if (!key)
		return;*/
	uint32_t	rounds = 6 + 52 / len;
	uint32_t	n = (uint32_t)len - 1;
	uint32_t	y = data[0];
	uint32_t	sum = rounds * DELTA;
	uint32_t	z;
	uint32_t	p;
	uint32_t	e;

	if (n < 1)
		return ;
	while (sum != 0)
	{
		e = sum >> 2 & 3;
		for (p = n; p > 0; p--)
		{
			z = data[p - 1];
			y = data[p] -= MX;
		}
		z = data[n];
		y = data[0] -= MX;
		sum -= DELTA;
	}
}
