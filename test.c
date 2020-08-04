#include <stdio.h>

void print_sum()
{
    int i = 1;
    for(;i<10;i++){
        int j = 1;
        for(;j<=i;j++){
            printf("%d * %d = %d\t",j,i,j*i);
            if(i==j){
                printf("\n");
            }
        }
    }
}

int main()
{
    print_sum();
    return 0;
}
