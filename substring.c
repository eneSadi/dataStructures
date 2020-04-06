#include<stdio.h>
#include<string.h>

int brute_force(char text[], char sub[]){

    int i, j, N, M;
    N = strlen(text);
    M = strlen(sub);

    for(i = 0 ; i <= N-M ; i++){
        j = 0;
        while((j < M) && (sub[j] == text[j+i])){
            j++;
        }
        if(j == M){
            return i;
        }
    }
    return -1;
}

void shiftTable(char sub[], int right[]){
    int i, M = strlen(sub);

    for(i = 0 ; i < 255 ; i++){
        right[i] = -1;
    }
    for(i = 0 ; i < M ; i++){
        right[sub[i]] = i;
    }
}

int boyer_moore(char text[], char sub[]){

    int right[256], i, j, skip = 0, N = strlen(text), M = strlen(sub);

    shiftTable(sub, right);

    for(i = 0 ; i < N-M ; i += skip){
        j = M -1;
        while((j >= 0) && (sub[j] == text[i+j])){
            j--;
        }
        if(j >= 0){
            skip = j - right[text[i+j]];
            if(skip < 0){
                skip = 1;
            }
        }
        else{
            return i;
        }
    }
    return -1;
}

int main(){

    char text[100];
    char sub[100];
    printf("Enter the text: ");
    scanf("%s",text);
    printf("Enter the substring: ");
    scanf("%s",sub);

    int index;
    index = brute_force(text, sub);
    if(index == -1){
        printf("\nBRUTE-FORCE ----> Substring does not exist!\n");
    }
    else{
        printf("\nBRUTE-FORCE ----> Substring starts at %d. position of text.\n",index);
    }
    
    index = boyer_moore(text, sub);
    if(index == -1){
        printf("\nBOYER-MOORE -----> Substring does not exist!\n");
    }
    else{
        printf("\nBOYER-MOORE -----> Substring starts at %d. position of text.\n",index);
    }

    return 0;
}