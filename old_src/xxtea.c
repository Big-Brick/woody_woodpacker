#include <stdint.h>
#include <stddef.h>

#define DELTA 0x9e3779b9
#define MX (((z >> 5) ^ (y << 2)) + ((y >> 3) ^ (z << 4))) ^ ((sum ^ y) + (key[(p & 3) ^ e] ^ z))

void	xxtea_encrypt(uint32_t *data, size_t len, const uint32_t *key)
{
	uint32_t	rounds = 6 + 52 / len;
	uint32_t	n = (uint32_t)len - 1;
	uint32_t	z = data[n];
	uint32_t	sum = 0;
	uint32_t	y;
	uint32_t	p;
	uint32_t	e;

	if (n < 1)
		return ;
	while (rounds-- > 0)
	{
		sum += DELTA;
		e = sum >> 2 & 3;
		for (p = 0; p < n; p++)
		{
			y = data[p + 1];
			z = data[p] += MX;
		}
		y = data[0];
		z = data[n] += MX;
	}
}

void	xxtea_decrypt(uint32_t *data, size_t len, const uint32_t *key)
{
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
