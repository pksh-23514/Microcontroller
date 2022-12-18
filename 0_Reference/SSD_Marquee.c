#include <stdio.h>

unsigned char digit [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_', '_'};
unsigned char ssd [4] = {'0', '0', '0', '0'};

void display (char ssd [])
{
	for (int i = 0; i < 4; i++)
	{
		printf ("%c ", ssd [i]);
	}
	printf ("\n");
}

int main()
{
	unsigned int wait = 1, opt = 1, count = 0, flag, flag_count = 0, prev;
	unsigned int ch = 1;

	display (ssd);

	while (ch == 1)
	{
		printf ("Enter the Pattern Option: ");
		scanf ("%d", &flag);

		if (flag == 1 || flag == 2)
		{
			if (flag != opt)
			{
				if (flag == 2)
					count += 1;
				else
					count -= 1;
			}
			opt = flag;
		}
		if (flag == 3)
		{
			flag_count += 1;
			if (flag_count % 2 == 1)
			{
				prev = opt;
				opt = flag;
			}
			else
			{
				flag_count = 0;
				opt = prev;
			}
		}

		if (wait++ == 1)
		{
			if (opt == 1)
			{
				if (count == 12)
					count = 0;
				printf ("%d\n", count);
				ssd [0] = digit [count % 12];
				ssd [1] = digit [(count + 1) % 12];
				ssd [2] = digit [(count + 2) % 12];
				ssd [3] = digit [(count + 3) % 12];

				count += 1;
				wait = 1;
			}
			else if (opt == 2)
			{
				if (count < 3)
					count = 16 - count;
				printf ("%d\n", count);
				ssd [3] = digit [count % 12];
				ssd [2] = digit [(count - 1) % 12];
				ssd [1] = digit [(count - 2) % 12];
				ssd [0] = digit [(count - 3) % 12];

				count -= 1;
				wait = 1;
			}
			else if (opt == 3)
			{
				wait = 1;
			}
		}

		display (ssd);

		printf ("Continue? ");
		scanf ("%d", &ch);
	}

	return 0;
}
