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
	char flusso[BUF_SIZE]={'t','v','h','\b','r','u','\b','\b','h','e','\n'};
	//char flusso[BUF_SIZE]={'t','v','h','e','\n'};
	char chiave[BUF_SIZE];
	char *puntaFlusso;
	char *fineChiave;
	char *puntaChiave;
	lettera *stack[BUF_SIZE];
	lettera **puntaStack;
	lettera **punta2;
	lettera *auC;

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
		auC=*puntaStack;
		while (auC->down->carattere!='\0') {
			printf("%c",auC->down->carattere);
			auC=auC->down;
		}
	printf("\n!!!\n");
	}
			for (punta2=stack;punta2<=puntaStack;punta2++) {
				if (*punta2==NULL) printf("punta2: %p,*punta2: %p\n",punta2,*punta2);
				else if (*punta2!=NULL && (*punta2)->down==NULL) printf("punta2: %p,*punta2: %p,(*punta2)->carattere: %d,(*punta2)->carattere: %c\n",punta2,*punta2,(*punta2)->carattere,(*punta2)->carattere);
				else printf("punta2: %p,*punta2: %p,(*punta2)->carattere: %d,(*punta2)->down->carattere: %c,(*punta2)->carattere: %d,(*punta2)->down->carattere: %c\n",punta2,*punta2,(*punta2)->carattere,(*punta2)->down->carattere,(*punta2)->carattere,(*punta2)->down->carattere);
			}
	printf("\n:!!!\n");

	/* lettura del resto dell' input */
	while (*puntaFlusso!='\n') {
		if (fineChiave==chiave) while (*puntaFlusso=='\b') puntaFlusso++;
		/* gestione carattere di backspace"*/
		if (*puntaFlusso=='\b') {
			puntaFlusso++;
			fineChiave--;
			//printf("\npuntaStack: %p,*puntaStack: %p,(*puntaStack)->carattere: %d,(*puntaStack)->carattere: %c\n",puntaStack,*puntaStack,(*puntaStack)->carattere,(*puntaStack)->carattere);
		} else {
			*fineChiave++=*puntaFlusso++;
			*fineChiave='\0';
			printf("%s\n",chiave);
			//printf("%s",chiave);
			/* ricerca con accesso al database della stringa contenuta nel vettore "chiave"*/
			for (punta2=stack;punta2<=puntaStack;punta2++) {
				if (*punta2==NULL) printf("punta2: %p,*punta2: %p\n",punta2,*punta2);
				else if (*punta2!=NULL && (*punta2)->down==NULL) printf("punta2: %p,*punta2: %p,(*punta2)->carattere: %d,(*punta2)->carattere: %c\n",punta2,*punta2,(*punta2)->carattere,(*punta2)->carattere);
				else printf("punta2: %p,*punta2: %p,(*punta2)->carattere: %d,(*punta2)->down->carattere: %c,(*punta2)->carattere: %d,(*punta2)->down->carattere: %c\n",punta2,*punta2,(*punta2)->carattere,(*punta2)->down->carattere,(*punta2)->carattere,(*punta2)->down->carattere);
			}
			printf("\n---\n");
			*puntaStack=cercaCarattere((*puntaStack++)->down,*(fineChiave-1));
			printf("stack %p,*stack: %p\n",stack,*stack);
			for (punta2=stack;punta2<=puntaStack;punta2++) {
				if (*punta2==NULL) printf("punta2: %p,*punta2: %p\n",punta2,*punta2);
				else if (*punta2!=NULL && (*punta2)->down==NULL) printf("punta2: %p,*punta2: %p,(*punta2)->carattere: %d,(*punta2)->carattere: %c\n",punta2,*punta2,(*punta2)->carattere,(*punta2)->carattere);
				else printf("punta2: %p,*punta2: %p,(*punta2)->carattere: %d,(*punta2)->down->carattere: %c,(*punta2)->carattere: %d,(*punta2)->down->carattere: %c\n",punta2,*punta2,(*punta2)->carattere,(*punta2)->down->carattere,(*punta2)->carattere,(*punta2)->down->carattere);
			}
				printf("%s\n",chiave);
			/* autocompletamento: naviga direttamente il trie */
			if (*puntaStack==NULL) {
				puntaStack--;
				//*puntaStack=auC;
				printf("\n");
			} else {
				auC=*puntaStack;
				printf(" - completamento - ");
				while (auC->down->carattere!='\0') {
					printf("%c",auC->down->carattere);
					auC=auC->down;
				}
			printf("\n");
			}
		}
	}
	return 0;
}
