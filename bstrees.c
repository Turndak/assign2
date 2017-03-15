#include "integer.h"
#include "bst.h"
#include "vbst.h"
#include "rbt.h"
//#include "cleaner.h"
#include "scanner.h"
#include "string.h"
#include <string.h>
#include <ctype.h>
#include "comparator.h"
#include <stdio.h>
#include <stdlib.h>

static char *cleanUp(FILE *fp)
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

static void cleanString(char *str)
{
	char *src = str, *dest = str;
	while (*src)
	{
		if(isspace((unsigned char)*src))
		{
			while(isspace((unsigned char)*src) || ispunct((unsigned char)*src) || isdigit((unsigned char)*src))
			{
				src++;
			}
			
			*dest++ = ' ';
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

void readVBST_file(FILE *fp, vbst *a)
{
	char *str = cleanUp(fp);
	while (!feof(fp))
	{
		cleanString(str);
		if (strcmp(str,"") != 0)
		{
			insertVBST(a, newString(str));
		}
		str = cleanUp(fp);
	}
}

void readRBT_file(FILE *fp, rbt *a)
{
	char *str = cleanUp(fp);
	while (!feof(fp))
	{
		cleanString(str);
		if (strcmp(str,"") != 0)
		{
			insertRBT(a, newString(str));
		}
		str = cleanUp(fp);
	}
}

void VBST_commands(FILE *fp, vbst *a, FILE *out)
{
	char *str = cleanUp(fp);
	while(!feof(fp))
	{
		cleanString(str);
		if(strcmp(str, "s") == 0)
		{
			displayVBST(out, a);
		}
		else if(strcmp(str, "r") == 0)
		{
			statisticsVBST(a, out);
		}
		else if(strcmp(str, "f") == 0)
		{
			str = cleanUp(fp);
			cleanString(str);
			fprintf(out, "Frequency of \"%s\": %d\n",str, findVBST(a, newString(str)));
		}	
		else if(strcmp(str, "d") == 0)
		{
			str = cleanUp(fp);
			cleanString(str);
			deleteVBST(a, newString(str));
		}
		else if(strcmp(str, "i") == 0)
		{
			str = cleanUp(fp);
			cleanString(str);
			if(strcmp(str, "") != 0)
			{
				insertVBST(a, newString(str));
			}
		}
		str = cleanUp(fp);
	}
}

void RBT_commands(FILE *fp, rbt *a, FILE *out)
{
	char *str = cleanUp(fp);
	while(!feof(fp))
	{
		cleanString(str);
		if(strcmp(str, "s") == 0)
		{
			displayRBT(out, a);
		}
		else if(strcmp(str, "r") == 0)
			statisticsRBT(a, out);
		else if(strcmp(str, "f") == 0)
		{
			str = cleanUp(fp);
			cleanString(str);
			fprintf(out, "Frequency of \"%s\": %d\n",str, findRBT(a, newString(str)));
		}	
		else if(strcmp(str, "i") == 0)
		{
			str = cleanUp(fp);
			cleanString(str);
			if(strcmp(str, "") != 0)
			{
				insertRBT(a, newString(str));
			}
		}
		str = cleanUp(fp);
	}
}

int main (int argc, char **argv) {
    FILE *corpus = NULL;
    FILE *commands = NULL;
    FILE *output = NULL;

    corpus = fopen(argv[2], "r");
    commands = fopen(argv[3], "r");

    if (argc == 5) 
    {
        output = fopen(argv[4], "w");
    }
    else {
        output =  stdout;
    }

    if (strcmp(argv[1],"-v") == 0) {
        vbst *v = newVBST(displayString,stringComparator);
        readVBST_file(corpus,v);
        VBST_commands(commands, v, output);
    }
    else if (strcmp(argv[1],"-r") == 0) {
        rbt *r = newRBT(displayString,stringComparator);
        readRBT_file(corpus,r);
        RBT_commands(commands, r, output);
    }
    else
        fprintf(stderr,"%s is not valid!\n",argv[1]);
    
    fclose(corpus);
    fclose(commands);
    fclose(output);      
    return 0;
}

