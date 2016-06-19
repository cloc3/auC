/*
https://cms.di.unipi.it/digit/#/task/printer/statement
http://www.cs.princeton.edu/~rs/AlgsDS07/19Tries.pdf
http://simplestcodings.blogspot.it/2012/11/trie-implementation-in-c.html
*/

#include <cstdio>
#include <unistd.h>
#include <termios.h>

#include <cassert>

#include "auClib.h"
#include "pwd.h"

#define BUF_SIZE 200

int getch(void);

int main() {
	int i,N;
	int lockFlag=0;
	lettera *root;
	char **uList;
	char *parola;
	char stream[BUF_SIZE]={'t','v','h','e','\b','e','a','r','u','\b','\b','d','e','\n'};
	char buffer[BUF_SIZE];
	char *streamPointer;
	char *bufferEnd;
	char *bufferPointer;
	lettera *stack[BUF_SIZE];
	lettera **stackPointer;

#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	creaAlbero(&root);

	/* lettura /etc/passwd e popola il trie degli usernames */
	uList=userList(&N);
	for(i=0; i<N; i++) {
			parola=uList[i];
		#ifdef DEBUG
			printf("%s\n",parola);
		#endif
			aggiungiStringa(&root,parola,0);
	}

/* inizializzazioni */
	streamPointer=stream;
	stackPointer=stack;
	bufferEnd=buffer;

/* lettura del primo carattere */
	*streamPointer=getch();
	while (*streamPointer=='\b' || *streamPointer=='\n') streamPointer++;
	*bufferEnd++=*streamPointer++;
	bufferPointer=buffer;
 	*stackPointer=cercaCarattere(root->down,*bufferPointer++);
	*bufferEnd='\0';
	printf("%s",buffer);
	/* autocompletion: identico a quello delle lettere successive */
	completion(*stackPointer);
	printf("\n---\n");

	/* lettura del resto dell' input */
	while (*streamPointer!='\n') {
		*streamPointer=getch();
		if (bufferEnd==buffer) while (*streamPointer=='\b') streamPointer++;
		/* gestione carattere di backspace"*/
		if (*streamPointer=='\b') {
			streamPointer++;
			bufferEnd--;
			*bufferEnd='\0';
			printf("%s",buffer);
			if (lockFlag>1) lockFlag--;
			else if (lockFlag==1) {
				completion(*(stackPointer));
				lockFlag=0;
			}
			else completion(*(--stackPointer));
		} else {
			*bufferEnd++=*streamPointer++;
			*bufferEnd='\0';
			printf("%s",buffer);
			/* ricerca con accesso al database della stringa contenuta nel vettore "buffer"*/
			*stackPointer=cercaCarattere((*stackPointer++)->down,*(bufferEnd-1));
			/* autocompletion: naviga direttamente il trie */
			if (*stackPointer!=NULL) {
				completion(*stackPointer);
			} else {
				lockFlag++;
				stackPointer--;
			}
			}
		printf("\n---\n");
	}
	return 0;
}

int getch(void)
{
  int ch;
  struct termios oldt;
  struct termios newt;
  tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
  newt = oldt; /* copy old settings to new settings */
  newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
  ch = getchar(); /* standard getchar call */
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
  return ch; /*return received char */
}


