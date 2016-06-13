/*
https://cms.di.unipi.it/digit/#/task/printer/statement
http://www.cs.princeton.edu/~rs/AlgsDS07/19Tries.pdf
http://simplestcodings.blogspot.it/2012/11/trie-implementation-in-c.html
*/

#include <cstdio>
#include <cassert>

#include "auC.h"
#include "pwd.h"

#define BUF_SIZE 200

int main() {
	int i,n,N;
	int l=0,max=0;
	int contaLettere=0;
	lettera *radice;
	char **uList;
	char *parola;
	char *parolaLunga;
	//char flusso[BUF_SIZE]={'t','v','h','\b','r','u','\b','\b','h','e','\n'};
	char flusso[BUF_SIZE]={'t','v','h','e','\n'};
	char chiave[BUF_SIZE];
	char *puntaFlusso;
	char *fineChiave;
	char *puntaChiave;
	lettera *stack[BUF_SIZE];
	lettera **puntaStack;

#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	creaAlbero(&radice,&contaLettere);

	/* lettura /etc/passwd e popola il trie degli usernames */
	uList=userList(&N);
	for(i=0; i<N; i++) {
			parola=uList[i];
		#ifdef DEBUG
			printf("%s\n",parola);
		#endif
			aggiungiStringa(&radice,parola,0,&contaLettere);
	}

/* inizializzazioni */
	puntaFlusso=flusso;
	puntaStack=stack;
	fineChiave=chiave;

/* lettura del primo carattere */
	while (*puntaFlusso=='\b' || *puntaFlusso=='\n') puntaFlusso++;
	*fineChiave++=*puntaFlusso++;
	puntaChiave=chiave;
 	*puntaStack=cercaCarattere(radice->down,*puntaChiave++);
	*fineChiave='\0';
	printf("chiave: %s\n",chiave);
	/* autocompletamento: identico a quello delle lettere successive */
	if (*puntaStack!=NULL) {
		printf(" - completamento - ");
		while ((*puntaStack)->down->carattere!='\0') {
			printf("%c",(*puntaStack)->down->carattere);
			*puntaStack=(*puntaStack)->down;
		}
	printf("\n");
	}

		printf("*(puntaFlusso ): %c\n",*(puntaFlusso));
	/* lettura del resto dell' input */

	while (*puntaFlusso!='\n') {
	if (fineChiave==chiave) while (*puntaFlusso=='\b' || *puntaFlusso=='\n') puntaFlusso++;
	/* gestione carattere di backspace  e costruzione del vettore "chiave"*/
	if (fineChiave!=chiave) 
		if (*puntaFlusso!='\b') {
			*fineChiave++=*puntaFlusso++;
		} else {
			puntaFlusso++;
			fineChiave--;
		}
		printf("*(ripuntaFlusso -1): %c\n",*(fineChiave));
		*fineChiave='\0';
		/* ricerca con accesso al database della stringa contenuta nel vettore "chiave"*/
		printf("%s",chiave);
		printf("pippo\n");
		while (puntaChiave!=fineChiave) {
			/* questa versione tutte le lettere di "chiave" vengono cercate ad ogni nuovo ingresso
 			*  forse sarebbe meglio sarebbe memorizzarle in uno stack e applicare cercaLettera solo all'ultima */
			*puntaStack=cercaCarattere((*puntaStack++)->down,*puntaChiave++);
			if (*puntaStack==NULL) {
				printf("\n");break;
			}
		}
		/* autocompletamento: naviga direttamente il trie */
		if (*puntaStack!=NULL) {
			printf(" - completamento - ");
			while ((*puntaStack)->down->carattere!='\0') {
				printf("%c",(*puntaStack)->down->carattere);
				*puntaStack=(*puntaStack)->down;
			}
		printf("\n");
		}
	}
	return 0;
}
