//Blackjack Project 1, Nick Feibel
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dealing();
void playing(double*, int*);
void ending(double, int*);
void beginning(double*, int*);
void drawCard(int);
void newGame(double*, int*);
void printGamerecord(int*);

//main() function initializes main variables and plays the game(s).
int main(){
	
	//Seed the random number
	srandom((unsigned int)(time(NULL)));
	
	//Initialize main variables.
	double bankroll;
	int gamerecord[4];
	char cOrQ;
	
	//Start by opening save file
	beginning(&bankroll, gamerecord);
	
	//Then continue playing until they either quit or run out of money
	do{
		
		playing(&bankroll, gamerecord);
		
		if(bankroll < 10){
			printf("\nYou do not have enough money to continue! Game will exit! \n");
			cOrQ = 'q';
		}
		else{
			do{
				printf("\nBankroll: $%.2lf \n", bankroll); 
				printGamerecord(gamerecord);
				
				printf("\nWould you like to play another game? (C = Continue, Q = Quit): ");
				scanf(" %c", &cOrQ);
				if(cOrQ != 'Q' && cOrQ != 'q' && cOrQ != 'C' && cOrQ != 'c'){
					printf("Please reconfirm as you did not provide a valid option. \n");
				}
			}while(cOrQ != 'Q' && cOrQ != 'q' && cOrQ != 'C' && cOrQ != 'c');
		}
	}while(cOrQ != 'q' && cOrQ != 'Q');
	
	//End game to save file
	ending(bankroll, gamerecord);
	
	return(1);
}

//dealing deals 1 random card from 1-10, with 1 becoming 11 if dealt.
int dealing() {
	
	int cardDealt;
	
	//Deals random card
	cardDealt = 1 + (random() % 10);
	
	//If card is 1, gives it value of 11
	if(cardDealt == 1)
		cardDealt = 11;
	
	return(cardDealt);
}

//playing() function plays 1 game.
void playing(double *bankroll, int *gamerecord){
	
	int dealerHand, dealerCurrentCard, playerCurrentCard, playerHand, lossCondition = 0,winCondition = 0, blackJackCondition = 0;
	double bet = 0;
	char hitOrStand;	
	
	printf("\nPlease confirm bet (between $10 - $1000, do not include $ symbol): ");
	
	//Ensures proper bet is made (10 < bet < 1000, and bet < bankroll).
	do{	
	
		scanf("%lf", &bet);
		
		if(bet < 10 || bet > 1000 || bet > *bankroll){
			if(bet > *bankroll){
				printf("Please reconfirm bet, you do not have that much money: ");
			}
			else if(bet < 10){
				printf("Please reconfirm bet, needs to be more than $10: ");
			}
			else if(bet > 1000){
				printf("Please reconfirm bet, needs to be less than $1000: "); 
			}
		}
	}while(bet < 10 || bet > *bankroll || bet > 1000);
	
	//Dealer and Player hands are initialized to ensure fresh round and hitOrStand condition reset.
	dealerHand=0, playerHand=0, hitOrStand=NULL;
	
	/*Deals hands and displays them. Ensuring totals are tallied as well.*/
	//Player First Card:
	playerCurrentCard = dealing();
	printf("Player's First Card: \n");
	drawCard(playerCurrentCard);
	playerHand = playerCurrentCard;
	
	//Player Second Card:
	playerCurrentCard = dealing();
	printf("Player's Second Card: \n");
	drawCard(playerCurrentCard);
	playerHand += playerCurrentCard;
	
	//Dealer First Card:
	dealerCurrentCard = dealing();
	printf("Dealer's First Card: \n");
	drawCard(dealerCurrentCard);
	dealerHand = dealerCurrentCard;
	
	//Dealer hole card is dealt but not displayed yet.
	dealerCurrentCard = dealing();
	
	//If player gets blackjack, the win is confirmed and gamerecord updated
	if(playerHand == 21){
		
		printf("Player Total: %d \nPlayer Gets Blackjack! \n", playerHand);
		printf("Let's see if the Dealer has Blackjack as well...\n");
		dealerHand += dealerCurrentCard;
		printf("Dealer's Hole Card: \n");
		drawCard(dealerCurrentCard);
		printf("Dealer Total (with hole card value): %d \n", dealerHand);
			
		//We check if dealer gets 21 with their hole card.
		if(dealerHand == 21){
			
			printf("\nDealer also has 21! \n");
			gamerecord[2] = gamerecord[2]+1;
			
			//win and loss conditions set to 1 to confirm tie and ensure player/dealer do not play more cards.
			winCondition = 1; 
			lossCondition = 1;
		}
		else{
			gamerecord[0]++;
			gamerecord[2]++;
			winCondition = 1;
			blackJackCondition = 1;
		}
	} //We also check if they have more than 21 as that can happen with 2 Aces.
	else if(playerHand > 21){
		printf("\nCard total: %d \nPlayer busted! You lose! \n", playerHand);
		lossCondition = 1;
		gamerecord[1]++;
		gamerecord[3]++;
	}
	
	//Continue playing until loss condition met or they stand.	
	while(lossCondition ==0 && winCondition == 0 && (hitOrStand != 's' && hitOrStand != 'S')){
		
		//Confirms totals and asks for hit or stand option.
		printf("Player Total: %d \n", playerHand);
		printf("Dealer (without hole card value): %d \n", dealerHand);
		do{
			printf("\nWould you like to hit or stand? (H = Hit, S = Stand): ");
			scanf(" %c", &hitOrStand);
			
			if(hitOrStand != 'h' && hitOrStand != 'H' && hitOrStand != 's' && hitOrStand != 'S'){
				printf("Please reconfirm as you did not provide a valid option. \n");
			}
		}while(hitOrStand != 'h' && hitOrStand != 'H' && hitOrStand != 's' && hitOrStand != 'S');				
		
		//If they would like to hit, a card is dealt below and we check whether they bust.
		if(hitOrStand == 'h' || hitOrStand == 'H'){
			
			playerCurrentCard = dealing(); 
			playerHand += playerCurrentCard;
			printf("\nPlayer's New Card: \n");
			drawCard(playerCurrentCard);
			
			//If they bust, gamerecord is immediately updated and we break out of loop.
			if(playerHand > 21) {
				printf("\nCard total: %d \nPlayer busted! You lose! \n", playerHand);
				lossCondition = 1;
				gamerecord[1]++;
				gamerecord[3]++;
				break;
			}
		}
	} 
	
	//If they did not win or lose, the dealer hits until they have 17 or more.
	if(winCondition != 1 && lossCondition != 1){
		
		//Hole card and dealer total is revealed.
		dealerHand += dealerCurrentCard;
		printf("\nDealer's Hole Card: \n");
		drawCard(dealerCurrentCard);
		printf("Dealer Total (with hole card value): %d \n", dealerHand);
		
		//This loop continues until the dealer has at least 17 total.
		while(dealerHand < 17){
			dealerCurrentCard = dealing();
			dealerHand += dealerCurrentCard;
			printf("\nDealer's New Card: \n");
			drawCard(dealerCurrentCard);
			printf("Dealer Total (with new card value): %d \n", dealerHand);
		}
		
		/*Once loop condition is met above, we can go ove the possible end conditions for the game,
		 *such as dealer busting, dealer having less than player, dealer having more than player,
		 *and if player ties. */
		if(dealerHand > 21){
			printf("\nDealer busted! You win! \n");
				winCondition = 1;
				gamerecord[0]++;
				
		}
		else if(dealerHand < playerHand){
			printf("\nPlayer total: %d, Dealer total: %d \nPlayer Wins! \n", playerHand, dealerHand);
			winCondition = 1;
			gamerecord[0]++;
			
		}
		else if(dealerHand > playerHand){
			printf("\nPlayer total: %d, Dealer total: %d \nDealer Wins! \n", playerHand, dealerHand);
			lossCondition = 1;
			gamerecord[1]++;
			
		}
		else{
			printf("\nPlayer total: %d, Dealer total: %d \nIt's a tie, no one wins! You get your bet back! \n", playerHand, dealerHand);
		}
	}
	
	//Calculates bankroll based on tie/win/loss condition.
	if(lossCondition == 1 && winCondition == 1){
		printf("\nPlayer total: %d, Dealer total: %d \nIt's a tie, no one wins! You get your bet back! \n", playerHand, dealerHand);
	}
	else if(lossCondition == 1){
		*bankroll = *bankroll - bet; 
		printf("\nYou lose $%.2lf. \n", bet);
	}
	else if(winCondition == 1){
		//We also check for blackjack condition to confirm updated win amount of 1.5 times the bet.
		if(blackJackCondition == 1){
			*bankroll = *bankroll + (bet * 1.5);
			printf("\nYou win $%.2lf! \n", (bet*1.5));
		}
		else{
			*bankroll = *bankroll + bet;
			printf("\nYou win $%.2lf! \n", bet);
		}
	}
	
}

/*ending() reports the current bank roll value, and loss/win/blackjack/bust counts.
 *The results are also saved in a text file. */
void ending(double bankroll, int *gamerecord){
	
	FILE *save = fopen("BlackJack_Save.txt", "w");
		
	//Confirms bankroll and gamerecord.
	printf("\nYou ended with $%.2lf bankroll. \n", bankroll);	
	printGamerecord(gamerecord);
	
	//Saves bankroll and gamerecord to save file.
	fprintf(save, "%.2lf \n", bankroll);
	fprintf(save, "%d \n", gamerecord[0]);
	fprintf(save, "%d \n", gamerecord[1]);
	fprintf(save, "%d \n", gamerecord[2]);
	fprintf(save, "%d \n", gamerecord[3]);
	fclose(save);
}

/*beginning() opens a text file that has the saved game information to continue the game.
 *If there is no file or it is blank, it starts a fresh game and reports whether it is "new game"
  or "continual game".*/
void beginning(double *bankroll, int *gamerecord){
	
	FILE *save = fopen("BlackJack_Save.txt", "r");
	char continueOrNew;
	
	//Checks whether file has been made or not.
	if (save != NULL){
		fscanf(save, "%lf", &*bankroll);
		fscanf(save, "%d", &gamerecord[0]);
		fscanf(save, "%d", &gamerecord[1]);
		fscanf(save, "%d", &gamerecord[2]);
		fscanf(save, "%d", &gamerecord[3]);
		
		//If they have less than $10 it starts a new save.
        if(*bankroll < 10){
			save = fopen("BlackJack_Save.txt", "w");
			printf("\nYou have less than $10, we will start a fresh game and wipe your game record. \nHere is $1000. \n");
			
			*bankroll = 1000.00;
			gamerecord[0] = 0;
			gamerecord[1] = 0;
			gamerecord[2] = 0;
			gamerecord[3] = 0;
			
			//Defaults are updated in save file to ensure fresh game.
			fprintf(save, "%.2lf \n", *bankroll);
			fprintf(save, "%d \n", gamerecord[0]);
			fprintf(save, "%d \n", gamerecord[1]);
			fprintf(save, "%d \n", gamerecord[2]);
			fprintf(save, "%d \n", gamerecord[3]);
			
		}
		else{ //If not, it asks whether you would like to continue the file or start a new game.
			
			printf("\nI see you have a save file.");
			
			do{
				
				printf("\nWould you like to continue your save or start a new game? \nIf you would like, you can also see the bankroll and game history from the save. (C = Continue, N = New Game, S = Save Info): ");
				scanf(" %c", &continueOrNew);
			
				if(continueOrNew != 'c' && continueOrNew != 'C' && continueOrNew != 'n' && continueOrNew != 'N' && continueOrNew != 's' && continueOrNew != 'S'){
					printf("Please reconfirm as you did not provide a valid option. \n");
				}
				else if(continueOrNew == 's' || continueOrNew == 'S'){ //I include an option to check the save data as well.
					
					printf("\nIf you continued your save, you would start with $%.2lf bankroll.\n", *bankroll);					
					printGamerecord(gamerecord);
					
				}
			}while(continueOrNew != 'c' && continueOrNew != 'C' && continueOrNew != 'n' && continueOrNew != 'N');
			if(continueOrNew == 'c' || continueOrNew == 'C'){
								
				printf("\nContinual Game. \nYou start with $%.2lf bankroll. \n", *bankroll);
				printGamerecord(gamerecord);
				
			}
			else if(continueOrNew == 'n' || continueOrNew == 'N'){
				
				printf("\nYou selected new game, we will start a fresh game. \nHere is $1000. \n");
				newGame(&*bankroll, gamerecord);
				
			}
		}
		
    }
	else { //If no file has been made, it starts a fresh game and confirms this.
		
		printf("\nYou have no save, we will start a fresh game. \nHere is $1000. \n");
		newGame(&*bankroll, gamerecord);
		
	}
	fclose(save);
} 

//Made a function to draw the card, just for fun practice!
void drawCard(int currentCard){
	
	printf(" ___ \n");
	printf("|   |\n");
	
	if(currentCard == 11){
		printf("| A |\n");
	}
	else if(currentCard == 10){
		printf("| 10|\n");
	}
	else{
		printf("| %d |\n", currentCard);
	}
	
	printf("|___|\n");	
}

/*newGame() simply makes a new game! I noticed I had this done in a couple of
  places so I made it into a function.*/
void newGame(double *bankroll, int *gamerecord){
	FILE *save = fopen("BlackJack_Save.txt", "w");
	
	//Defaults are set.	
	*bankroll = 1000.00;
	gamerecord[0] = 0;
	gamerecord[1] = 0;
	gamerecord[2] = 0;
	gamerecord[3] = 0;
	
	//New file is also saved below with defaults for future use.
	fprintf(save, "%.2lf \n", *bankroll);
	fprintf(save, "%d \n", gamerecord[0]);
	fprintf(save, "%d \n", gamerecord[1]);
	fprintf(save, "%d \n", gamerecord[2]);
	fprintf(save, "%d \n", gamerecord[3]);
	fclose(save);
}

/*printGamerecord() made for same reason as newGame, I had this done a few times
  so this is to consolidate it. Simply prints the gamerecord values*/
void printGamerecord(int *gamerecord){
	printf("Wins: %d \n", gamerecord[0]);
	printf("Losses: %d \n", gamerecord[1]);
	printf("Blackjacks: %d \n", gamerecord[2]);
	printf("Busts: %d \n", gamerecord[3]);
}
