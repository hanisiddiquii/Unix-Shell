#include "header.h"
#include "tokenize.h"
#include "helper.h"

char **getList(char *input)
{
    char **list = (char **)malloc(100 * sizeof(char *));
    num_command = 0; 
    char *temp = strtok(input, ";");
    while (temp != NULL)
    {
        list[num_command] = temp;
        if (temp[0] != '\n')
            num_command++;
        temp = strtok(NULL, ";");
    }
    replaceTabs(list);
    RemoveExtraSpaces(list);
    return list;
}
void replaceTabs(char **list)
{
    for (int i = 0; i < num_command; i++)
    {
        for (int j = 0; j < strlen(list[i]); j++)
        {
            if (list[i][j] == '\t')
                list[i][j] = ' ';
        }
    }
}
void RemoveExtraSpaces(char **list)
{
    for (int itr = 0; itr < num_command; itr++)
    {
        char *string = list[itr];
        char cpyCommand[name_len];
        int j = 0;
        while (string[j] == ' ')
            j++;

        bool prevspace = false;
        int i = 0;
        while (1)
        {
            if (string[j] != ' ')
            {
                cpyCommand[i] = string[j];
                j++;
                i++;
                prevspace = false;
            }
            else if (string[j] == ' ' && prevspace == false)
            {
                cpyCommand[i] = string[j];
                j++;
                i++;
                prevspace = true;
            }
            else
            {
                j++;
            }
            if (j == strlen(string))
                break;
        }
        if (cpyCommand[i - 1] == ' ')
            cpyCommand[i - 1] = '\0';
        else
            cpyCommand[i] = '\0';
        // copy the string to original store placeholder
        strcpy(list[itr], cpyCommand);
    }
}
