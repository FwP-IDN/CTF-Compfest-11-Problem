#include <stdio.h>

void printfile(char file[]){
    FILE *f;
    char ch;
    f = fopen(file, "r");
    while((ch = fgetc(f)) != EOF)
        printf("%c", ch);
    printf("\n");
    fclose(f);
    return;
}

void exec(){
    printf("SORT() CALL LIMIT EXCEEDED, ENTERING COMMAND MODE\npress '-1' to exit\n");
    while (1){
        char command[255];
        fgets(command, 255, stdin);
        if ((strlen(command) > 0) && (command[strlen (command) - 1] == '\n'))
            command[strlen (command) - 1] = '\0';
        if (strcmp(command, "-1") == 0)
            break;
        system(command);
    }
    return;
}