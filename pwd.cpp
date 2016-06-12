//#include <cstdio>
#include <cstdlib>
#include <pwd.h>
#include "pwd.h"

char **userList(int *nUsers) {

	struct passwd *cu;
	char *wordCursor,*word_Cursor;
	char **listCursor;
	char **uList;
	int i;
	int length;

	/* Number of users*/
	*nUsers=0;
	while ((cu = getpwent()) != NULL) (*nUsers)++;
	listCursor=uList=(char**)malloc((*nUsers)*sizeof(char*));

	/* read and copy pw_names*/
	setpwent();
	while ((cu = getpwent()) != NULL) {
		/* check word length*/
		wordCursor=cu->pw_name;
		while (*wordCursor++!='\0');
		*listCursor=(char*)malloc((int)(wordCursor - cu->pw_name)*sizeof(char));

		/* copy cu->pw_name in the userList*/
		wordCursor=cu->pw_name;
		word_Cursor=*listCursor++;
		while (*wordCursor!='\0') *word_Cursor++ = *wordCursor++;
		*word_Cursor = *wordCursor;
	}

	endpwent();
	return uList;
}

/*
int main() {

	int nUsers;
	char **uList;

	uList=userList(&nUsers);
	printf("main uList: %p\n",uList);
	for (int i=0;i<nUsers;i++) {
 		printf("main: [%d], %p %s\n",i,uList[i],uList[i]);
	}
	return 0;
}
*/
