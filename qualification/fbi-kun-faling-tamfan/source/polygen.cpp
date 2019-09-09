#include <bits/stdc++.h>
using namespace std;

int main(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    freopen("TC.txt", "w", stdout);
    srand(time(NULL));
    for (int i=0; i<=100000; i++){
        if (i==100000){
            printf("%d\n", rand()%256);
        } else {
            printf("%d ", rand()%256);                
        }
    }
    printf("\n\n\n\n");
    for (int i=0; i<=100000; i++){
        if (i==100000){
            printf("%d\n", rand()%256);
        } else {
            printf("%d ", rand()%256);                
        }
    }
    fclose(stdout);
    return 0;
}
