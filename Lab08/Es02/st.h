#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct symbletable *ST;
ST STinit(int maxN);
int STcount(ST st);
void STinsert(ST st, char *name);
int STgetIndex(ST st, char *name);
char *STgetName(ST st, int code);
void STfree(ST st);
void STprint(ST st);