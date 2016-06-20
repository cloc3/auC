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
	char c;
	int lockFlag=0;
	lettera *root;
	char **uList;
	char *parola;
	char buffer[BUF_SIZE];
	char *bufferEnd;
	lettera *stack[BUF_SIZE];
	lettera **stackPointer;

#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	makeTrie(&root);

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
	stackPointer=stack;
	bufferEnd=buffer;
	c='\0';

	/* lettura del resto dell' input */
	while (c!='\n') {
		if (bufferEnd==buffer) {
			*stackPointer=NULL;
			while (*stackPointer==NULL) {
				*buffer=getch();
				if (*buffer=='\n') return 0;
 				*stackPointer=cercaCarattere(root->down,*buffer);
			}
			*(++bufferEnd)='\0';
			printf("%s",buffer);
			completion(*stackPointer);
		} else {
			/* gestione carattere di backspace"*/
			c=getch();
			if (c=='\x7f') {
				if (stackPointer>stack) {
					*(--bufferEnd)='\0';
					printf("%s",buffer);
					if (lockFlag>1) lockFlag--;
					else if (lockFlag==1) {
						completion(*(stackPointer));
						lockFlag=0;
					}
					else completion(*(--stackPointer));
				} else {
					*buffer='\0';
					bufferEnd--;
				}
			} else {
				*bufferEnd++=c;
				*bufferEnd='\0';
				printf("%s",buffer);
				/* ricerca con accesso al database della stringa contenuta nel vettore "buffer"*/
				*stackPointer=cercaCarattere((*stackPointer++)->down,c);
				/* autocompletion: naviga direttamente il trie */
				if (*stackPointer!=NULL) {
					completion(*stackPointer);
				} else {
					lockFlag++;
					stackPointer--;
				}
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


