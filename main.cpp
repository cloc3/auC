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
	char chiave[BUF_SIZE];
	char *puntaFlusso;
	char *fineChiave;
	char *puntaChiave;
	lettera *puntaLettera;

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
	fineChiave=chiave;

/* lettura input */
	while (*puntaFlusso!='\n') {
	/* gestione carattere di backspace  e costruzione del vettore "chiave"*/
		if (*puntaFlusso!='\b') *fineChiave++=*puntaFlusso++;
		else {
			puntaFlusso++;
			fineChiave--;
		}
		*fineChiave='\0';
		/* ricerca con accesso al database della stringa contenuta nel vettore "chiave"*/
		puntaChiave=chiave;
		printf("%s",chiave);
	 	puntaLettera=cercaCarattere(radice->down,*puntaChiave++);
		while (puntaChiave!=fineChiave) {
			/* questa versione tutte le lettere di "chiave" vengono cercate ad ogni nuovo ingresso
 			*  forse sarebbe meglio sarebbe memorizzarle in uno stack e applicare cercaLettera solo all'ultima */
			puntaLettera=cercaCarattere((puntaLettera)->down,*puntaChiave++);
			if (puntaLettera==NULL) {
				printf("\n");break;
			}
		}
		/* autocompletamento: naviga direttamente il trie */
		if (puntaLettera!=NULL) {
			printf(" - completamento - ");
			while (puntaLettera->down->carattere!='\0') {
				printf("%c",(puntaLettera)->down->carattere);
				puntaLettera=puntaLettera->down;
			}
		printf("\n");
		}
	}
	return 0;
}
