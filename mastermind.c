/*
 * mastermind.c
 *
 *  Created on: 2021/12/27
 *      Author: new-kensyu
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void printarr(int*, int);
void clearbuf();

int main(){
	//Game parameters
	int slots = 0;
	int range = 0;

	//Data arrays
	char *board;
	char *user_in;
	int val_total[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int val_count[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	//Others
	int rncount = 0, rpcount = 0, tries = 0;
	int i;

	//Get user input
	printf("     Mastermind\n====================\nInput the number of slots: ");
	while(!scanf("%d", &slots)){
		printf("Try again:");
		clearbuf();
	}
	if(slots < 1){
		exit(EXIT_SUCCESS);
	}
	if(slots > 20){
		printf("Are you sure?\n");
		slots = 20;
	}

	printf("Input number of unique tokens: ");
	scanf("%d", &range);
	if(range < 2){
		range = 2;
	} else if(10 < range){
		range = 10;
	}

	board = malloc(slots * sizeof(char));
	user_in = malloc(slots * sizeof(char));

	//Setup board
	srand(time(0));

	for(i = 0; i < slots; i++){
		board[i] = rand() % range;
		val_total[(int) board[i]] ++;
	}

	system("cls");

	printf("The possible range of numbers is 0 - %d\n", (range - 1));
	printf("Type quit to exit\n\n");

	//Start game
	while(rpcount != slots){
		rncount = 0;
		rpcount = 0;
		tries++;

		//Print the prompt
		for(i = 0; i < slots; i++){
			printf("X ");
		}
		putchar('\n');

		//Get user input
		for(i = 0; i < slots; i++){
			if(!scanf("%1d", &user_in[i])){
				if(getchar() == 'q'){
					free(board);
					free(user_in);
					exit(EXIT_SUCCESS);
				}else{
					printf("Invalid input\n\n");
				}
				break;
			}
		}

		clearbuf();

		if(i != slots){
			continue;
		}

		//Calculate the right position count
		for(i = 0; i < slots; i++){
			if(user_in[i] > (range - 1)){
				printf("Invalid number %d\nTry again\n\n", user_in[i]);
				tries--;
				break;
			}
			if(user_in[i] == board[i]){
				rpcount++;
			}
		}

		if(rpcount == slots || i != slots) continue;

		//Calculate the right number count
		//Clear previous input
		for(i = 0; i < 10; i++){
			val_count[i] = 0;
		}

		//First find the totals of different numbers input
		for(i = 0; i < slots; i++){
			val_count[(int) user_in[i]] ++;
		}

		//printarr(val_total, 10);
		//printarr(val_count, 10);

		//Add up the smallest number between the two sets
		for(i = 0; i < 10; i++){
			rncount += val_total[i] > val_count[i] ? val_count[i]: val_total[i];
		}

		//Print the result
		printf("Count of correct places = %d\n", rpcount);
		printf("Count of correct numbers = %d\n\n", rncount);
	}

	printf("You got it! Number of tries = %d\n", tries);

	getchar();

	free(board);
	free(user_in);
	return 0;
}

void printarr(int* arr, int count){
	int i;

	for(i = 0; i < count; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void clearbuf(){
	while('\n' != getchar());
}
