/*My kind of implementation for  'Puzzle 3: You Can Read Minds'.. You can get to know the problem 
from here, https://www.youtube.com/watch?v=zDHhHPZm2rc'*/
#include <math.h>
#include "Magician.h"
#include "Assistant.h"

/* As we are sorting only 3 numbers bubble sort
   is efficient
*/
void bubbleSort(int arr[], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            if(arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void getFirstCard(CardInfo cardInfo[], std::vector<int> pairedCardsIndex, int &secretCode){
    int n = cardInfo[pairedCardsIndex[0]].getCardRankIndex() - cardInfo[pairedCardsIndex[1]].getCardRankIndex();
    secretCode = n -  floor(n / 13.0) * 13;
    int hintCard;
    if(secretCode > 0 && secretCode <= 6){
        hintCard = pairedCardsIndex[1];
    }
    else{
        hintCard = pairedCardsIndex[0];
        secretCode = -n - floor(-n / 13.0) * 13;
    }

    std::cout << "First card is " << cardInfo[hintCard].card.rank << cardInfo[hintCard].card.suit << ".\n";
}

void getHelperCards(int helperCards[], int secretCode){
    int card1, card2, card3;
    switch(secretCode){
        case 1:
            card1 = helperCards[0];
            card2 = helperCards[1];
            card3 = helperCards[2];
            break;
        case 2:
            card1 = helperCards[0];
            card2 = helperCards[2];
            card3 = helperCards[1];
            break;
        case 3:
            card1 = helperCards[1];
            card2 = helperCards[0];
            card3 = helperCards[2];
            break;
        case 4:
            card1 = helperCards[1];
            card2 = helperCards[2];
            card3 = helperCards[0];
            break;
        case 5:
            card1 = helperCards[2];
            card2 = helperCards[0];
            card3 = helperCards[1];
            break;
        default:
            card1 = helperCards[2];
            card2 = helperCards[1];
            card3 = helperCards[0];
            break;
    }
    std::cout << "Second Card is " << deck[card1] << "\n";
    std::cout << "Third Card is " << deck[card2] << "\n";
    std::cout << "Fourth Card is " << deck[card3] << "\n";
}

/*finding index and also MODIFYING val for
  countering duplicate issues */
int findIndex(std::string str){
    for(int i = 0; i < sizeof(deck)/sizeof(deck[0]); i++){
        if(str == deck[i]){
        	deck[i] += ".";
        	return i;
		} 
    }
    return -1;
}

int main(){
	
	char userInput;
    
    do{
		std::cout << "Assist \n(A)Magician Helper \n\t\tor \n(B)Magician ? \n";
		std::cin >> userInput;
	}while(userInput != 'A' && userInput != 'B');
	
	if(userInput == 'A'){
		Assistant assistant;
		assistant.orderCards();
	}
    else{
    	Magician magician;
    	magician.findHiddenCard();																			
	}
	std::cout << '\n';
	system("pause");
    return 0;
}
