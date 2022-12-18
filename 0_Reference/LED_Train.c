#include <stdio.h>

int convert (unsigned char n)
{
	for (int i = 7; i >= 0; i--)
	{
		if (n & (1 << i))
			printf ("X ");
		else
			printf ("O ");
	}
	printf ("\n");
}

int main()
{
	unsigned char pos = 1;
	unsigned int wait = 1;
	unsigned char bias = 8;
	unsigned char res = 0;

	unsigned int count = 96;
	while (count--)
	{
		if (wait++ == 1)
		{
			if (pos <= 8)
			{
				//printf ("Pos: %d\n", pos);
				res = (1 << pos) - 1;
				convert (res);
			}
			else if (pos <= 16)
			{
				//printf ("Pos: %d\n", pos);
				res = res << 1;
				convert (res);
			}
			else if (pos <= 24)
			{
				//printf ("Pos: %d\t Bias: %d\n", pos, bias);
				res = res | (1 << (bias - 1));
				convert (res);
			}
			else if (pos <= 32)
			{
				//printf ("Pos: %d\t Bias: %d\n", pos, bias);
				res = res >> 1;
				convert (res);
			}

			wait = 1;
			pos += 1;
			if (pos == 17)
				res = 0;
			if (pos > 17 && pos <= 25)
			{
				bias -= 1;
				if (bias < 1)
					bias = 8;
			}
			if (pos > 32)
			{
				printf ("------------------\n");
				pos = 1;
			}
		}
	}

	return 0;
}
