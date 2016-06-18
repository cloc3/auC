#ifndef auC_H
#define auC_H

typedef struct foglia lettera;

/* prototipi globali (utilizzati anche dalla funzione main) */
void creaAlbero(lettera**);
void aggiungiStringa(lettera**,char*,int);
lettera *cercaCarattere(lettera*,char);
lettera *ricerca(lettera*,char*);
void marcaParola(lettera *radice,const char *,int);
void dfs(lettera*,int*);
void cercaParolaLunga(char*,char*,int*);
void completion(lettera*);

/* prototipi locali (utilizzati internamente dalle funzioni)*/
lettera	*caricaLettera(char, int);

struct foglia {
	char carattere;
	int segno;
	lettera *dx;
	lettera *down;
};

#endif
