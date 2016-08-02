#ifndef auC_H
#define auC_H

typedef struct leaf letter;

/* prototipi globali (utilizzati anche dalla funzione main) */
void makeTrie(letter**);
void addStringToTrie(letter**,char*,int);
letter *findCharacter(letter*,char);
letter *searchLetter(letter*,char*);
void completion(letter*);

/* prototipi locali (utilizzati internamente dalle funzioni)*/
letter	*addLetterToTrie(char, int);

struct leaf {
	char character;
	int sign;
	letter *dx;
	letter *down;
};

#endif
