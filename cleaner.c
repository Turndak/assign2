#include "cleaner.h"
#include "scanner.h"

void cleanString(char *str)
{
	char *src = str, *dest = str;

	while (*src)
	{
		if(isspace((unsigned char)*src))
		{
			while(isspace((unsigned char)*src) || ispunct((unsigned char)*src) || isdigit((unsigned char)*src))
			{
				src++;
				*dest = ' ';
			}
		}
		else if (ispunct((unsigned char)*src) || isdigit((unsigned char)*src))
		{
			src++;
		}
		else if (isupper((unsigned char)*src))
		{
			*dest++ = tolower((unsigned char)*src);
			src++;
		}
		else if(src == dest)
		{
			src++;
			dest++;
		} 
		else
		{
			*dest++ = *src++;
		}
	}

	*dest = 0;
}

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
