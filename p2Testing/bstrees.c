#include "integer.h"
#include "bst.h"
#include "vbst.h"
#include "rbt.h"
#include "scanner.h"
#include "string.h"
#include <string.h>
#include <ctype.h>
#include "comparator.h"
#include <stdio.h>
#include <stdlib.h>

//supplied by Dr. Lusth along with all other scanner.c functions in this file
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

//cleans the input string/words
//the base for this code was suppled from a stack overflow post
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
		else if (!isalpha((unsigned char)*src))
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

//passes in string or word and while not at the end of the file 
//passes the string through cleanstring and inserts it into the vbst
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

//passes in string or word and while not at the end of the file 
//passes the string through cleanstring and inserts it into the rbt
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

//takes in the command file, cleans it, and executes the command in order
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
		{
			statisticsRBT(a, out);
		}
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

