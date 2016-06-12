#include <cstdio>
#include <cstdlib>

#include "auC.h"

void creaAlbero(lettera **radice,int *contaLettere) {
	*radice = caricaLettera('\0',0,NULL);
}

void marcaParola(lettera *radice, const char *parola, int segno) {
	lettera *livello=radice;
	lettera *stringa=NULL;

	while(1) {
		lettera *trovato=NULL;
		lettera *pt;

		for (pt=livello;pt != NULL;pt=pt->dx) {
			if(pt->carattere==*parola) {
				trovato=pt;
				pt->segno=segno;
				break;
			}
		}

		if (trovato==NULL) return;

		if (*parola=='\0') {
			stringa=pt;
			pt->segno=segno;
			return;
		}

		livello=trovato->down;
		parola++;
	}
}

lettera *cercaCarattere(lettera *radice, char carattere) {
	lettera *livello=radice;
	lettera *pt;

	/* scorre verso destra fino all'ultima lettera del trie,
	* senza salire di livello, alla ricerca di una lettera uguale
	* alla lettera iniziale di carattere */

	while(1) {
		for (pt=livello;pt != NULL;pt=pt->dx) {
			if(pt->carattere==carattere) {
				return pt;
			}
		}
		return NULL;
	}
}

lettera *completamento(lettera *radice, char *parola) {
	lettera *livello=radice;
	lettera *stringa=NULL;

	/* scorre verso destra fino all'ultima lettera del trie,
	* senza salire di livello, alla ricerca di una lettera uguale
	* alla lettera iniziale di *parola */

	while(1) {
		lettera *trovato=NULL;
		lettera *pt;

		for (pt=livello;pt != NULL;pt=pt->dx) {
			if(pt->carattere==*parola) {
				trovato=pt;
				break;
			}
		}

		if (trovato==NULL) return NULL;

		if (*parola=='\0') {
			stringa=pt;
			return stringa;
		}

		livello=trovato->down;
		parola++;
	}
}

lettera *caricaLettera(char carattere, int segno,int *contaLettere) {
	lettera *nodo = NULL;
	nodo=(lettera *)malloc(sizeof(lettera));

#ifdef DEBUG
	/* controllo di malloc */
	if (NULL == nodo) {printf("errore Malloc");return NULL;}
#endif

	nodo->carattere=carattere;
	nodo->dx=NULL;
	nodo->down=NULL;
	nodo->segno=segno;
	if (contaLettere!=NULL) (*contaLettere)++;
	return nodo;
}

void aggiungiStringa(lettera **radice, char *parola, int segno, int *contaLettere) {
	lettera *stringa;
	/* controllo radice */
	if (NULL == *radice) {printf("albero vuoto");return;}

#ifdef DEBUG
	printf("\nInserimento stringa: %s\n", parola);
#endif
	stringa=(*radice)->down;

	if (stringa==NULL) {
		for(stringa=*radice;*parola;stringa=stringa->down) {
			stringa->down=caricaLettera(*parola,segno,contaLettere);
		#ifdef DEBUG
			printf("Ho inserito la lettera: [%c]\n", stringa->down->carattere);
		#endif
			parola++;
		}

		stringa->down=caricaLettera('\0',segno,contaLettere);
	#ifdef DEBUG
		printf("\nInserimento carattere: [%c]\n",stringa->down->carattere);
	#endif
		return;
	}

	if(completamento(stringa, parola)){
		printf("parola %s duplicata!\n",parola);
	}

	while(*parola != '\0') {
		if (*parola == stringa->carattere) {
			parola++;
		#ifdef DEBUG
			printf("scorrimento del carattere: [%c]\n",stringa->down->carattere);
		#endif
			stringa=stringa->down;
		} else {
			break;
		}
	}

	while(stringa->dx) {
		if(*parola == stringa->dx->carattere) {
			parola++;
			aggiungiStringa(&(stringa->dx),parola,segno,contaLettere);
			return;
		}
		stringa=stringa->dx;
	}

	if (*parola) {	//l'if avrebbe senso se volessi distinguere i casi in cui voglio attribuire a segno un valore diverso per i fine parola
		stringa->dx=caricaLettera(*parola,segno,contaLettere);
	} else {
		stringa->dx=caricaLettera(*parola,segno,contaLettere);
	}

#ifdef DEBUG
	printf("Ho inserito la prima lettera [%c] della nuova stringa a destra della lettera [%c]\n",stringa->dx->carattere, stringa->carattere);
#endif

	if(!(*parola)) return;
	parola++;

	for(stringa=stringa->dx; *parola; stringa=stringa->down) {
		stringa->down=caricaLettera(*parola,segno,contaLettere);
	#ifdef DEBUG
		printf("Inserimento del carattere [%c]\n", stringa->down->carattere);
	#endif
	parola++;
	}

	stringa->down=caricaLettera('\0',segno,contaLettere);
#ifdef DEBUG
	printf("Inserimento del carattere [%c]\n",stringa->down->carattere);
#endif
	return;
}

/* fine gestione dell'albero */

void cercaParolaLunga(char *parola, char *parolaLunga, int *max) {
	char *tmp,*pMax;
	int n;

	n=0;
	pMax=parola;
	while (*parola++) n++;
	if (*max < n) {
		*max=n;
		tmp=parolaLunga;
		while (*pMax != '\0') {
			*tmp=*pMax++;
			tmp++;
		}
		*tmp='\0';
	}
	return;
}
