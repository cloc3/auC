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
	int i,N;
	int contaLettere=0;
	lettera *radice;
	char **uList;
	char *parola;
	char flusso[BUF_SIZE]={'t','v','h','\b','r','u','\b','\b','h','e','\n'};
	//char flusso[BUF_SIZE]={'t','v','h','e','\n'};
	char chiave[BUF_SIZE];
	char *puntaFlusso;
	char *fineChiave;
	char *puntaChiave;
	lettera *stack[BUF_SIZE];
	lettera **puntaStack;
	lettera *completamento;

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
	printf("%s",chiave);
	/* autocompletamento: identico a quello delle lettere successive */
	if (*puntaStack!=NULL) {
		printf(" - completamento - ");
		completamento=*puntaStack;
		while (completamento->down->carattere!='\0') {
			printf("%c",completamento->down->carattere);
			completamento=completamento->down;
		}
	printf("\n");
	}

	/* lettura del resto dell' input */
	while (*puntaFlusso!='\n') {
		if (fineChiave==chiave) while (*puntaFlusso=='\b') puntaFlusso++;
		/* gestione carattere di backspace"*/
		if (*puntaFlusso=='\b') {
			puntaFlusso++;
			fineChiave--;
		} else {
			*fineChiave++=*puntaFlusso++;
			*fineChiave='\0';
			printf("%s",chiave);
			/* ricerca con accesso al database della stringa contenuta nel vettore "chiave"*/
			*puntaStack=cercaCarattere((*puntaStack++)->down,*(fineChiave-1));
			/* autocompletamento: naviga direttamente il trie */
			if (*puntaStack==NULL) puntaStack--;
			if ((*puntaStack)->carattere==*(fineChiave-1)) {
				completamento=*puntaStack;
				printf(" - completamento - ");
				while (completamento->down->carattere!='\0') {
					printf("%c",completamento->down->carattere);
					completamento=completamento->down;
				}
			}
			printf("\n");
		}
	}
	return 0;
}
