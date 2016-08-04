/*
https://cms.di.unipi.it/digit/#/task/printer/statement
http://www.cs.princeton.edu/~rs/AlgsDS07/19Tries.pdf
http://simplestcodings.blogspot.it/2012/11/trie-implementation-in-c.html
*/

#include <cstdio>
#include <unistd.h>
#include <termios.h>

#include "auClib.h"
#include "pwd.h"

#define BUF_SIZE 200
#define DEL '\x7f'

int getch(void);

int main() {
	int i,N;
	char c='\0';
	int lockFlag=0;
	letter *root;
	char **uList;
	char *username;
/*
  	char stream[BUF_SIZE]={'t','v','h','\b','\b','h','v','\b','\b','e','\b','e','a','r','u','\b','\b','d','e','\n'};
*/
	char buffer[BUF_SIZE]; /*bufferize input characters*/
	char *bufferEnd;
	letter *stack[BUF_SIZE]; /*memorize current autocompletion characters*/
	letter **stackPointer;

	/* make username trie */
	makeTrie(&root);
	uList=userList(&N);
	for(i=0; i<N; i++) {
			username=uList[i];
			addStringToTrie(&root,username,0);
	}

	stackPointer=stack;
	(*stackPointer++)=root;
	bufferEnd=buffer;

	/* autocompletion start */
	printf("type your username (return to exit)\n");
	while (c!='\n') {
/*
 * prima di tutto acquisisco un nuovo carattere e aggiorno il buffer
*/
		c=getch();
		if (c==DEL) {
			if (buffer<bufferEnd) *(--bufferEnd)='\0';
			printf("%s",buffer);
			if (lockFlag) {
				if (--lockFlag);
				else {
					if (buffer<bufferEnd) completion(*(stackPointer-1));
				}
			}
			else {
				if (stack<stackPointer-1) stackPointer--;
				if (buffer<bufferEnd) completion((*(stackPointer-1)));
			}
		} else {
			if (c=='\n') return 0;
			*bufferEnd++=c;
			*bufferEnd='\0';
			printf("%s",buffer);
	/* prima di ogni azione verifico lo stato di blocco */
		if (lockFlag) lockFlag++;
		else {
			*stackPointer=findCharacter((*(stackPointer-1))->down,c);
			if (*stackPointer==NULL) {
				lockFlag=1;
			} else {
				completion(*(stackPointer++));
			}
		}
		} printf("\n---\n");
	}
	return 0;
}

/* getchar with no echo */
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


