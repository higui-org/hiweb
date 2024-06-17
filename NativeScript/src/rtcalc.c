#include <stdio.h>
#include <stdlib.h>

void calc_write(int value)
{
	printf("The result is: %d\n", value);
}

int calc_read(char* s)
{
	char buffer[64];
	int value;

	printf("Enter an integer value for %s: ", s);

	fgets(buffer, sizeof(buffer), stdin);
	if (EOF == sscanf(buffer, "%d", &value))
	{
		printf("Error: invalid input for %s\n", buffer);
		exit(1);
	}

	return value;
}