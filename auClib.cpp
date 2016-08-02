#include <cstdio>
#include <cstdlib>

#include "auClib.h"

void makeTrie(letter **root) {
	*root = addLetterToTrie('\0',0);
}

letter *findCharacter(letter *currentLeaf, char character) {
	letter *pt;

	/* scorre verso destra fino all'ultima lettera del trie,
	* senza salire di localRoot, alla searchLetter di una lettera uguale
	* alla letter iniziale di character */

	while(1) {
		for (pt=currentLeaf;pt != NULL;pt=pt->dx) {
			if(pt->character==character) {
				return pt;
			}
		}
		return NULL;
	}
}

letter *readWord(letter *currentLeaf, char *word) {
	/* scorre verso destra fino all'ultima lettera del trie,
	* senza salire di localRoot, alla searchLetter di una letter uguale
	* alla letter iniziale di *word */

	while(1) {
		letter *nextLetter=NULL;
		letter *pt;

		for (pt=currentLeaf;pt != NULL;pt=pt->dx) {
			if(pt->character==*word) {
				nextLetter=pt;
				break;
			}
		}

		if (nextLetter==NULL) return NULL;

		if (*word=='\0') {
			letter *endOfString=pt;
			return pt;
		}

		currentLeaf=nextLetter->down;
		word++;
	}
}

letter *addLetterToTrie(char character, int sign) {
	//letter *nodo = NULL;
	letter* nodo=(letter *)malloc(sizeof(letter));

#ifdef DEBUG
	/* controllo di malloc */
	if (NULL == nodo) {printf("errore Malloc");return NULL;}
#endif

	nodo->character=character;
	nodo->dx=NULL;
	nodo->down=NULL;
	nodo->sign=sign;
	return nodo;
}

void addStringToTrie(letter **root, char *word, int sign) {
	letter *stringCursor;
	/* controllo root */
	if (NULL == *root) {printf("albero vuoto");return;}

#ifdef DEBUG
	printf("\nInserimento stringCursor: %s\n", word);
#endif
	stringCursor=(*root)->down;

	if (stringCursor==NULL) {
		for(stringCursor=*root;*word;stringCursor=stringCursor->down) {
			stringCursor->down=addLetterToTrie(*word,sign);
		#ifdef DEBUG
			printf("Ho inserito la lettera: [%c]\n", stringCursor->down->character);
		#endif
			word++;
		}

		stringCursor->down=addLetterToTrie('\0',sign);
	#ifdef DEBUG
		printf("\nInserimento carattere: [%c]\n",stringCursor->down->character);
	#endif
		return;
	}

	if(readWord(stringCursor, word)){
		printf("word %s duplicata!\n",word);
	}

	while(*word != '\0') {
		if (*word == stringCursor->character) {
			word++;
		#ifdef DEBUG
			printf("scorrimento del carattere: [%c]\n",stringCursor->down->character);
		#endif
			stringCursor=stringCursor->down;
		} else {
			break;
		}
	}

	while(stringCursor->dx) {
		if(*word == stringCursor->dx->character) {
			word++;
			addStringToTrie(&(stringCursor->dx),word,sign);
			return;
		}
		stringCursor=stringCursor->dx;
	}

	if (*word) {	//l'if avrebbe senso se volessi distinguere i casi in cui voglio attribuire a sign un valore diverso per i fine word
		stringCursor->dx=addLetterToTrie(*word,sign);
	} else {
		stringCursor->dx=addLetterToTrie(*word,sign);
	}

#ifdef DEBUG
	printf("Ho inserito la prima letter [%c] della nuova stringCursor a destra della letter [%c]\n",stringCursor->dx->character, stringCursor->character);
#endif

	if(!(*word)) return;
	word++;

	for(stringCursor=stringCursor->dx; *word; stringCursor=stringCursor->down) {
		stringCursor->down=addLetterToTrie(*word,sign);
	#ifdef DEBUG
		printf("Inserimento del character [%c]\n", stringCursor->down->character);
	#endif
	word++;
	}

	stringCursor->down=addLetterToTrie('\0',sign);
#ifdef DEBUG
	printf("Inserimento del character [%c]\n",stringCursor->down->character);
#endif
	return;
}

/* fine gestione dell'albero */

void completion(letter *completion) {
	printf(" - completion - ");
	while (completion->down->character!='\0') {
		printf("%c",completion->down->character);
		completion=completion->down;
	}
}
