#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myLib.c"  // printfile, exec
#include "sort.c"   // sort

void main(){
    printf("i like to sort number!\n");
    while (1) {
        int n;
        printf("please enter n, denoting the number to sort (additionally enter -1 to exit or enter 0 to print source code): ");
        scanf("%d", &n);
        if (n == -1){
            break;
        } else if (n == 0){
            printfile("main.c");
            continue;
        } else if (n<-1) {
            printf("please enter a valid option :(\n");
            continue;
        } else {
            if (n > 100000){
                printf("please enter a smaller number (<=100000)\n");
                continue;
            }
            int num[n];
            for (int i=0; i<n; i++)
                scanf("%d", &num[i]);  
            long long int call = 0;
            sort(num, 0, n-1, &call);
            if (call >= 150000){
                exec();    
                break;                
            }
             for (int i=0; i<n; i++)
                printf("%d ", num[i]);    
            printf("\n");
        }    
    }
    return;
}