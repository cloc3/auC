#ifndef auC_H
#define auC_H

typedef struct foglia lettera;

/* prototipi globali (utilizzati anche dalla funzione main) */
void creaAlbero(lettera**,int*);
void aggiungiStringa(lettera**,char*,int,int*);
lettera *cercaCarattere(lettera*,char);
lettera *ricerca(lettera*,char*);
void marcaParola(lettera *radice,const char *,int);
void dfs(lettera*,int*);
void cercaParolaLunga(char*,char*,int*);

/* prototipi locali (utilizzati internamente dalle funzioni)*/
lettera	*caricaLettera(char parola, int segno, int *contaLettere);

struct foglia {
	char carattere;
	int segno;
	lettera *dx;
	lettera *down;
};

#endif
