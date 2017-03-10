#include "cleanString.h"
#include "scanner.h"

char *cleanUp(FILE *fp)
{
	if(stringPending(fp))
	{
		return readString(fp);
	}
	else
	{
		return readToken(fp);
	}
}

int main(void)
{
	FILE *fp = fopen("test.txt","r");
	fprintf(stdout, "%s\n", cleanUp(fp));
}