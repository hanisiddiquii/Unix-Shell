#ifndef SHELL_TOKENIZE
#define SHELL_TOKENIZE

char **getList(char *input); 
void replaceTabs(char **list);
void RemoveExtraSpaces(char **list);

#endif
