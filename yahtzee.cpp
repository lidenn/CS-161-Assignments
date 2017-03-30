/*Program:Yahtzee.cpp
 * Author: Dennis Li
 * Date:11/22/16
 * Description: This program runs the game yahtzee between 1 or 2 players. There are 16 categories for points. The categories are 1's, 2's, 3's, 4's, 5's, 6's, extra points, three of a kind, four of a kind, chance, full house, small straight, large straight, chance and yahtzee.
 * Input: Number of players.
 * Output: The score categories and the overall scores in the game of Yahtzee.*/




// STILL NEED TO COMPLETE 
// Command line

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>


using namespace std;


void roll_all_dice(int[]);
void show_dice(int []);
int roll_dice(int [], int);
void show_scoreboard(int [17]);
void set_scoreboard(int [17]);
void sum_number(int[], int[17], int);
void extra_points(int[17]);

void three_of_kind(int[], int[17]);
void four_of_kind(int [], int [17]);
void chance(int [], int [17]);
void full_house(int [], int [17]);
//void small_straight(int [], int [17]){
void large_straight(int [], int [17]);
void change_scoreboard(int[], int[17]);
void yahtzee(int[], int[17],int );
int pick_dice(int[]);
void find_score(int[17]);













int main(int argc, char* argv[]){
	srand(time(NULL));
	int num_players= atoi(argv[1]);
	if (num_players==2){
		int again=1;
		int valid;
		int dice_array[5];
		int *scoreboard;
		int *scoreboard2;
		scoreboard = new int[17];
		scoreboard2 = new int[17];
		while (again==1){
			set_scoreboard(scoreboard);
			set_scoreboard(scoreboard2);
			for (int round=1; round<=13;round++){	
				cout<< "Player 1: "<< endl;
				roll_all_dice(dice_array);
				show_dice(dice_array);
				pick_dice(dice_array);
				change_scoreboard(dice_array, scoreboard);
				show_scoreboard(scoreboard);
				cout<<" "<< endl;


				cout << "Player 2: "<< endl;
				roll_all_dice(dice_array);
				show_dice(dice_array);
				pick_dice(dice_array);
				change_scoreboard(dice_array, scoreboard2);
				show_scoreboard(scoreboard2);
				cout<<" "<< endl;
			}
			find_score(scoreboard);
			find_score(scoreboard2);
			cout<<"Player 1 score: "<<scoreboard[0]<<endl;
			cout<<"Player 2 score: "<<scoreboard2[0]<<endl;

			cout <<"Play again?"<<endl;
			cout<< "1 to play again, 2 to stop" << endl;
			cin>>again;
		}
		delete [] scoreboard;
		delete [] scoreboard2;
	}
	else if (num_players==1){
		int again=1;
		int valid;
		int dice_array[5];
		int *scoreboard;
		scoreboard = new int[17];
		while (again==1){
			set_scoreboard(scoreboard);
			for (int round=1; round<=13;round++){	
				cout<< "Player 1: "<< endl;
				roll_all_dice(dice_array);
				show_dice(dice_array);
				pick_dice(dice_array);
				change_scoreboard(dice_array, scoreboard);
				show_scoreboard(scoreboard);
				cout<<" "<< endl;


			}
			find_score(scoreboard);
			cout<<"Player 1 score: "<<scoreboard[0]<<endl;

			cout <<"Play again?"<<endl;
			cout<< "1 to play again, 2 to stop" << endl;
			cin>>again;

		}	
		delete [] scoreboard;
	}
	else{
		cout<<"Please enter 1 for 1 player or 2 for 2 players"<<endl;
	}
}

/*Function:roll_all_dice
 * Description:This function rolls all of the dice at the beginning and gives the intial set of 5 dice options.
 * Parameters:int []
 * Pre-condition:The input must be an array for the 5 dice.
 * Post-conditions:The output is an filled array with the dice values.
 * Return: Filled array with 5 indexes.*/
void roll_all_dice(int dice[]){
	for(int i=0;i<=4;i++){
		dice[i] = (rand()%6)+1;
	}
}


/*Function: show_dice
 * Description: Displace 5 dice to the user.
 * Parameters:int []
 * Pre-condition:Input must be an array with the 5 dice
 * Post-conditions:Prints out integer values in array
 * Return: None*/
void show_dice(int dice[]){
	int i;
	cout<<"Dice: ";
	for(i=0;i<=4; i++){
		cout << dice[i]<< " ";
	}
	cout << " "<< endl;
}


/*Function: roll_dice
 * Description: Rolls a specific dice.
 * Parameters:int [], int
 * Pre-condition:Input must be an array with the 5 dice, and the integer for the dice number.
 * Post-conditions:Rolls a dice value in the array at the number
 * Return: changed indexes*/
int roll_dice(int dice[], int dice_number){
	dice[dice_number] = (rand()%6)+1;
}

/*Function: pick_dice
 * Description: Picks the specific dice you want to roll. (Uses roll_dice function)
 * Parameters:int []
 * Pre-condition:Input must be an array with the 5 dice
 * Post-conditions:Rolls specific dice values at the indexes provided by the user
 * Return: changed indexes*/
int pick_dice(int dice[]){ 
	for (int roll = 1;  roll <3; roll++){
		int pick;
		int number;
		cout << "Number of dice you want to re-roll? (0-5)" << endl;
		cin >> number;
		if (number>5){
			cout<<"Enter number less than 5"<< endl;	
		}
		else{
			for (int i=1;i<=number;i++){
				cout <<"Roll which specific dice?: (1-5)"<< endl;
				cin >> pick;
				cout << "Rolling die "<<i+1<< endl;
				if (pick == 1){
					roll_dice(dice,0);
				}
				else if (pick == 2){
					roll_dice(dice,1);
				}
				else if (pick == 3){
					roll_dice(dice,2);
				}
				else if (pick == 4){
					roll_dice(dice,3);
				}
				else if (pick == 5){
					roll_dice(dice,4);
				}
				else{
					break;
				}
			}
		}
		show_dice(dice);
	}
}

/*Function: set_scoreboard
 * Description: Sets a indexes in the scoreboard array all to -1.
 * Parameters:int[]
 * Pre-condition:Input must be an array with the scoreboard, size[17]
 * Post-conditions:Sets all indexes in the scoreboard to -1
 * Return: changed indexes*/
void set_scoreboard(int scoreboard[17]){
	for (int c=0; c<17; c++){
		scoreboard[c]=-1;
	}
}

/*Function: show_scoreboard
 * Description: Prints out the scoreboard to display to the user.
 * Parameters:int[]
 * Pre-condition:Input must be an array with the scoreboard, size[17]
 * Post-conditions:Prints out all the indexes/scores in the scoreboard array.
 * Return: none*/
void show_scoreboard(int scoreboard[17]){
	//	cout <<"Sum: "<<scoreboard[0]<<endl;
	cout <<"1's: "<<scoreboard[1]<<endl;
	cout <<"2's: "<<scoreboard[2]<<endl;
	cout <<"3's: "<<scoreboard[3]<<endl;
	cout <<"4's: "<<scoreboard[4]<<endl;
	cout <<"5's: "<<scoreboard[5]<<endl;
	cout <<"6's: "<<scoreboard[6]<<endl;
	cout <<"Extra points: "<<scoreboard[7]<<endl;
	cout <<"Three of a kind: "<<scoreboard[8]<<endl;
	cout<<"Four of a kind: "<<scoreboard[9]<<endl;
	cout<<"Full House: "<<scoreboard[10]<<endl;
	cout<<"Small Straight: "<<scoreboard[11]<<endl;
	cout<<"Large Straight: " <<scoreboard[12]<<endl;
	cout<<"Chance: " <<scoreboard[13]<<endl;
	cout<<"Yahtzee: "<<scoreboard[14]<<endl;
	cout<<"Extra Yahtzee 2: "<<scoreboard[15]<<endl;
	cout<<"Extra Yahtzee 3: "<<scoreboard[16]<<endl;

}


/*Function: sum_number
 * Description: Depending on the user input (1,2,3,4,5,6), it will add all of the user inputs in the array. It basically multiplies the amount of the number by the number.
 * Parameters:int[], int[], int
 * Pre-condition:The input must be an array with the 5 dice, the array of complete score board, and the number to serach for.
 * Post-conditions:changes the score in the scoreboard
 * Return: changed index in the scoreboard*/
void sum_number(int dice[], int scoreboard[17], int number){
	int count = 0;
	int result;
	for (int d=0; d<=4; d++){
		if (dice[d]== number){
			count++;
		}
		else{
		}
	}
	result = count*number;
	scoreboard[number]=result; 



}


/*Function: extra_points
 * Description: If the sum of the score from 1's, 2's, 3's, 4's, 5's, 6's are over 63, then there score will change to 35.
 * Parameters:int[]
 * Pre-condition:Input must be an array with the scoreboard, size[17]
 * Post-conditions:Changes the scoreboard and adds 35 to specific category
 * Return: changed indexes for extra points*/
void extra_points(int scoreboard[17]){
	int sum;
	sum = scoreboard[1]+scoreboard[2]+scoreboard[3]+scoreboard[4]+scoreboard[5]+scoreboard[6];
	if (sum>=63){
		scoreboard[7]=35;
	}
	else{
		scoreboard[7]=0;
	}	
}


/*Function: Three_of_kind
 * Description: It analyses for three of a kind and if there is three of a kind, the score changes from 0 to 35.
 * Parameters:int[], int[]
 * Pre-condition:The input must be an array with the 5 dice, the array of complete score board.
 * Post-conditions:changes the score in the scoreboard for three of a kind.
 * Return: changed index in the scoreboard.*/
void three_of_kind(int dice[], int scoreboard[17]){
	for(int test=1; test<=6; test++){
		int satisfy=0;
		for(int d=0;d<5;d++){	
			if (dice[d]==test){
				++satisfy;
				//				cout<< "satisfy: "<<satisfy<<" for "<< test<< endl;
			}
		}
		if (satisfy>=3){
			scoreboard[8]=dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
			break;
		}
		else{
			scoreboard[8]=0;
		}
	}
}

/*Function: four_a_kind
 * Description: It analyses for four of a kind and if there is four of a kind, the score changes from 0 to 35.
 * Parameters:int[], int[]
 * Pre-condition:The input must be an array with the 5 dice, the array of complete score board.
 * Post-conditions:changes the score in the scoreboard for four of a kind.
 * Return: changed index in the scoreboard.*/
void four_of_kind(int dice[], int scoreboard[17]){
	for(int test=1; test<=6; test++){
		int satisfy=0;
		for(int d=0;d<5;d++){	
			if (dice[d]==test){
				++satisfy;
			}
		}
		if (satisfy>=4){
			scoreboard[9]=dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
			break;
		}
		else{
			scoreboard[9]=0;
		}
	}
}

/*Function: full_house
 * Description: First counts to check dice array for a number that has appeared greater than 3. Then counts for a number that has appeared greater than 2
 * Parameters:int[], int[]
 * Pre-condition:The input must be an array with the 5 dice, the array of complete score board.
 * Post-conditions:changes the score in the scoreboard for full house.
 * Return: changed index in the scoreboard.*/
void full_house(int dice[], int scoreboard[17]){
	int count1=0;
	int count2=0;
	int triple_num;
	for (int d=0;d<5;d++){
		for (int d1=0;d1<5;d1++){
			if (d!=d1 && dice[d]==dice[d1]){
				++count1;
				if (count1==2){
					triple_num=dice[d];
					//					cout <<"Triple Num"<< endl; Check the number with 3 digits
				}
			}
			//			cout <<"count: "<< count1<< endl; Used to check the count
		}
		if(count1==2){
			break;
		}
		else{
			count1=0;	
		}
	}
	// This part is for the 2	
	if (count1==2){
		for (int d2=0;d2<5;d2++){
			for (int d3=0;d3<5;d3++){
				if (d2!=d3 && dice[d2]==dice[d3]&&dice[d3]!=triple_num){
					++count2;	
				}
				//				cout <<"count2: "<< count2<< endl; Used to check the count of the number with 2
			}
			if (count2==1){
				break;
			}
			else{
				count2=0;
			}
		}
		if (count2==1){
			scoreboard[10]=25;
		}
		else{
			scoreboard[10]=0;
		}


	}
	else{
		scoreboard[10]=0;

	}

}

/*Function: small_straight
 * Description: The small straight function checks for 4 consecutive dice. It analyzes the dice array for 4 numbers in a row.
 * Parameters:int[], int[]
 * Pre-condition:The input must be an array with the 5 dice, the array of complete score board.
 * Post-conditions:changes the score in the scoreboard for small straight.
 * Return: changed index in the scoreboard.*/
void small_straight(int dice[], int scoreboard[17]){
	int count1=0;
	int count2=0;
	int count3=0;
	int count4=0;
	int count5=0;
	int count6=0;
	int correct;
	for (int i=0;i<5;i++){
		if (dice[i]==1)
			count1++;
		if (dice[i]==2)
			count2++;
		if (dice[i]==3)
			count3++;
		if (dice[i]==4)
			count4++;
		if (dice[i]==5)
			count5++;
		if (dice[i]==6)
			count6++;
	}
	//	cout<<"Count is: "<<count1<< " "<<count2<<" "<<count3<<" "<<count4<<" "<<count5<<" "<<count6<<endl;	this is to check for count
	if (count3>=1&&count4>=1){
		if(count2>=1){
			if (count1>=1 or count5>=1){
				scoreboard[11]=30;
			}
			else{
				scoreboard[11]=0;
			}
		}
		else if(count1>=1){
			if (count2>=1){
				scoreboard[11]=30;
			}
			else{
				scoreboard[11]=0;
			}
		}
		else if(count6>=1){
			if (count5>=1){
				scoreboard[11]=30;
			}
			else{
				scoreboard[11]=0;
			}
		}
		else{
			scoreboard[11]=0;
		}
	}
	else{	
		scoreboard[11]=0;
	}
}



/*Function: large_straight
 * Description: The small straight function checks for all consecutive dice. It analyzes the dice array for numbers in a row.
 * Parameters:int[], int[]
 * Pre-condition:The input must be an array with the 5 dice, the array of complete score board.
 * Post-conditions:changes the score in the scoreboard for large straight.
 * Return: changed index in the scoreboard.*/
void large_straight(int dice[], int scoreboard[17]){
	int count=0;
	for (int d=0;d<5;d++){
		for (int d1=0;d1<5;d1++){
			if (d!=d1 && dice[d]==dice[d1]){
				count++;	
			}
			//			cout <<"count: "<< count<< endl; Used to check the count or basically repeated numbers
		}
	}
	if (count!=0){
		scoreboard[12]=0;
	}
	else if (count==0){
		if (dice[0]+dice[1]+dice[2]+dice[3]+dice[4]==15){
			scoreboard[12]=40;
		}
		else if (dice[0]+dice[1]+dice[2]+dice[3]+dice[4]==20){
			scoreboard[12]=40;
		}
		else{
			scoreboard[12]=0;
		}
	}
}

/*Function: chance
 * Description:This function is a sum of all the dice.
 * Parameters:int[], int[]
 * Pre-condition:The input must be an array with the 5 dice, the array of complete score board.
 * Post-conditions:changes the score in the scoreboard for chance.
 * Return: changed index in the scoreboard.*/
void chance(int dice[], int scoreboard[17]){
	scoreboard[13] = dice[0]+dice[1]+dice[2]+dice[3]+dice[4];

}



/*Function: yahtzee
 * Description:This function checks for 5 of a kind for a specific dice. 
 * Parameters:int[], int[]
 * Pre-condition:The input must be an array with the 5 dice, the array of complete score board.
 * Post-conditions:changes the score in the scoreboard for yahtzee.
 * Return: changed index in the scoreboard. It gives 50 points if true.*/
void yahtzee(int dice[], int scoreboard[17], int category){
	for(int test=1; test<=6; test++){
		int satisfy=0;
		for(int d=0;d<5;d++){	
			if (dice[d]==test){
				++satisfy;
			}
		}
		if (satisfy==5){
			scoreboard[category]=dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
			break;
		}
		else{
			scoreboard[category]=0;
		}
	}

}



/*Function: change_scoreboard
 * Description:This program allows the user to pick a category to apply the array of dice to. This will cause a change in the scoreboard based on the user input and the dice array.
 * Parameters:int[], int[]
 * Pre-condition:The input must be an array with the 5 dice, the array of complete score board, user input for category.
 * Post-conditions:changes the score in category depending on user.
 * Return:Completes and fills the scoreboard*/
void change_scoreboard(int dice_array[], int scoreboard[17]){
	int category;
	int valid=1;
	cout<<"1: One's"<< endl;
	cout<<"2: Two's"<< endl;
	cout<<"3: Three's"<< endl;
	cout<<"4: Four's"<< endl;
	cout<<"5: Five's"<< endl;
	cout<<"6: Six's"<< endl;
	cout<<"7: Three of a Kind"<< endl;
	cout<<"8: Four of a Kind"<< endl;
	cout<<"9: Full House"<< endl;
	cout<<"10: Small Straight"<< endl;
	cout<<"11: Large Straight"<< endl;
	cout<<"12: Chance"<< endl;
	cout<<"13: Yahtzee"<< endl;
	while (valid==1){//Or use switch case
		cout<<"Enter in category to input: "<< endl;
		cin>> category;
		if (category ==1&&scoreboard[1]==-1){		//One
			sum_number(dice_array, scoreboard,1);
			valid=0;
		}
		else if (category ==2&& scoreboard[2]==-1){	//Twos
			sum_number(dice_array, scoreboard,2);
			valid=0;
		}	
		else if (category ==3&&scoreboard[3]==-1){	//Threes
			sum_number(dice_array, scoreboard,3);
			valid=0;
		}
		else if (category ==4&&scoreboard[4]==-1){	//Fours
			sum_number(dice_array, scoreboard,4);
			valid=0;
		}	
		else if (category ==5&&scoreboard[5]==-1){	//Fives
			sum_number(dice_array, scoreboard,5);
			valid=0;
		}	
		else if (category ==6&&scoreboard[6]==-1){	//Sixes
			sum_number(dice_array, scoreboard,6);
			valid=0;
		}	
		else if (category ==7&&scoreboard[8]==-1){	//Three of a Kind
			three_of_kind(dice_array, scoreboard);
			valid=0;
		}	
		else if (category ==8&&scoreboard[9]==-1){	//Four of a kind
			four_of_kind(dice_array, scoreboard);
			valid=0;
		}	
		else if (category ==9&&scoreboard[10]==-1){	//Full House
			full_house(dice_array, scoreboard);
			valid=0;
		}	

		else if (category ==10&&scoreboard[11]==-1){	//Small Straight
			small_straight(dice_array, scoreboard);
			valid=0;
		}	

		else if (category ==11&&scoreboard[12]==-1){	//Large Straight
			large_straight(dice_array, scoreboard);
			valid=0;
		}	

		else if (category ==12&&scoreboard[13]==-1){	//Chance
			chance(dice_array, scoreboard);
			valid=0;
		}	
		else if (category ==13&&scoreboard[14]==-1){	//Yahzee
			yahtzee(dice_array, scoreboard, 14);
			valid=0;
		}	

		else {
			valid=1;		
		}
	}
	///////////////////////////
	if(scoreboard[1]>-1&&scoreboard[2]>-1&&scoreboard[3]>-1&&scoreboard[4]>-1&&scoreboard[5]>-1&&scoreboard[6]>-1){	//Checks for sum after the 1,2,3,4,5,6 category is filled
		extra_points(scoreboard);
	}

	if(scoreboard[15]==-1 ||scoreboard[15]==0){ 		//For the extra Yahtzee, it is constantly checking to add it
		if (scoreboard[14]==50){
		yahtzee(dice_array, scoreboard, 15);
		}
	}
	if(scoreboard[15]>0){					//For the second extra, it is constantly checking
		yahtzee(dice_array, scoreboard, 16);
	}

}


/*Function: find_score
 * Description: This function sums of the entire scoreboard.
 * Parameters:int[]
 * Pre-condition:The array of complete score board.
 * Post-conditions:Changes scoreboard[0].
 * Return:Completes scoreboard at 0.*/
void find_score(int scoreboard[17]){
	for(int i=0;i<17;i++){
		if (scoreboard[i]<0){
			scoreboard[i]=0;
		}
		scoreboard[0]=scoreboard[0]+scoreboard[i];
	}
}
