// Mark Rizko
// Ahmed Amer
// Operating Systems
// MWF 8:00am
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
Program tries and compares three different disk scheduling algorithms.
While I am obviously not actually reading and writing data to a hard drive in this test,
I will be comparing these based on their seek distance.
 */
int track1[100] = {0};
int track2[100] = {0};
int track3[100] = {0}; 
//int track4[100] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0};
//^^track I used to test based off of an sample I did on paper
int CLOOK(int hp);
int SWEEP(); // sweep doesn't need to take head position because starts and ends at 0 or 100
int SSTF(int hp);
int isItDone(int *array);
void printArray(int *array);

int main(){
    int i, hp, lseek, sseek, tseek, index,numFilled; // head pointer, seek distances for each algorithm
    printf("Welcome to Mark Rizko's Operating Systems Project!\nThis program will be comparing the SSTF, C-LOOK, and SWEEP disk scheduling algorithms.\n");
    // initialize tracks by setting random bits from 0 to 1 to represent job
    srand(time(NULL));
    numFilled = (rand() % 50) + 25; // 25-75 will be filled with a 1, indicating job
    for (i = 0; i < numFilled; i++){
        index = (rand() % 100) - 1;
        track1[index] = 1;
        track2[index] = 1;
        track3[index] = 1;
    }
    hp = (rand() % 100) - 1; // randomize starting head positions
    //printf("\nhead: %d\n", hp);
    lseek = CLOOK(hp); // record 3 different seek times
    sseek = SWEEP();
    tseek = SSTF(hp);
    printf("\n\nSSTF Seek Distance: %d\n", tseek);
    printf("\nSWEEP Seek Distance: %d\n", sseek);
    printf("\nCLOOK Seek Distance: %d\n", lseek);
    return 0;
}

int CLOOK(int hp){
    int i,j,k;
    int skd = 0; // seek distance tracker
    for (i = 0; i < 100; i++){
        if (track1[i] == 1){
            break; // i = left end
        }
    }
    for (j = 99; j > 0; j--){
        if (track1[j] == 1){
            break; // j = right end
        }
    }
    if ((hp < 50 && hp > i) || hp > j){ // go left if head is on left side, or cannot go right
        for (k = hp; k >= i; k--){
            if (track1[k] == 1){
                track1[k] = 0;
            }
            skd++;
        }
        if (hp <= j){ // if head starts past rightmost job, then it's just one sweep left
        	for (k; k <= j; k++){
            if (track1[k] == 1){
                track1[k] = 0;
            }
            skd++;
        	}
        }
    }
    else{ // other way
        for (k = hp; k <= j; k++){
            if (track1[k] == 1){
                track1[k] = 0;
            }
            skd++;
        }
        if (hp > i){
        	for (k; k >= i; k--){
            if (track1[k] == 1){
                track1[k] = 0;
            }
            skd++;
        	}
        }
    }
    //printArray(track1);
    return skd;
    

}

int SWEEP(){
    int i;
    int hp = 0;
    int skd = 0;
    if (hp == 0){
        for (i = 0; i <= 99; i++){ // didn't need to program this, but the idea of the algorithm is i cycles from starting at 0 and 99
            if (track2[i] == 1){
                track2[i] = 0;
            }
            skd++;
        }
    }
    //printArray(track2);
    return skd;
}

int SSTF(int hp){
    int i,j,clost;
    int seekdist = 0;
    while (!isItDone(track3)){
        for (i = hp; i <= 99; i++){ // checking upper bound
            if (track3[i] == 1){
                break;
            }
        }
        for (j = hp; j >= 0; j--){ // lower bound
            if (track3[j] == 1){
                break;
            }
        }
        if (((i - hp) < (hp - j) && i != 100) || j == -1){ // logic written here to pick closest job to head
            clost = i;
        }
        else{
            clost = j;
        }
        //printf("\ni: %d\tj: %d\th: %d\tclost: %d\n", i,j,hp, clost);
        track3[clost] = 0;
        seekdist += abs(clost - hp);
        hp = clost;
    }
    //printArray(track3); testing that algorithms cover whole list
    return seekdist;
}
int isItDone(int *array){ // checks if scheduling is finished, used for SSTF
    int i;
    for (i = 0; i < 100; i++){
        if (array[i] == 1){
            return false;
        }
    }
    return true;
}

void printArray(int *array){ // prints array, for testing
    int i; 
    for (i = 0; i < 100; i++){
        printf("%d\n", array[i]);
    }
}