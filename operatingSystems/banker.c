#include<stdio.h>

int main(){
    int n,m,i,j,k;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter number of resources: ");
    scanf("%d",&m);

    int allocation[n][m], max[n][m], need[n][m];
    int available[m];
    int finish[n], safeseq[n], work[m];

    printf("\nEnter Allocation Matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d",&allocation[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d",&max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(j=0;j<m;j++){
        scanf("%d",&available[j]);
    }

    /* Calculate Need Matrix */
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("\nNeed Matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }

    /* Initialize finish and work */
    for(i=0;i<n;i++){
        finish[i] = 0;
    }

    for(j=0;j<m;j++){
        work[j] = available[j];
    }

    int count = 0;

    while(count < n){
        int found = 0;

        for(i=0;i<n;i++){
            if(finish[i] == 0){

                int possible = 1;

                for(j=0;j<m;j++){
                    if(need[i][j] > work[j]){
                        possible = 0;
                        break;
                    }
                }

                if(possible){
                    for(k=0;k<m;k++){
                        work[k] += allocation[i][k];
                    }

                    safeseq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0){
            printf("\nSystem is UNSAFE\n");
            return 0;
        }
    }

    printf("\nSystem is SAFE\nSafe sequence: ");
    for(i=0;i<n;i++){
        printf("P%d ",safeseq[i]);
    }

    printf("\n");

    return 0;
}
