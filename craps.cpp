/* Program: Craps
 * Author: Dennis Li
 * Date: 10/6/2016
 * Description: Play the game of craps with initial balance and wager
 * Input: Balance and Wager
 * Output: resulting balance after a game of craps
 */


#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;
void get_balance_bank (double &);
void get_wager_amount (double &);
int check_wager_amount (double, double);

int roll_die (void);
int calculate_sum_dice(int, int);
int is_win_loss_or_point (int);
int is_point_loss_or_neither (int, int);
void adjust_bank_balance(double &, double, int);


int main(){
	cout <<"Welcome to Craps!" << endl;
	double balance;
	double wager;
	int roll1;
	int roll2;
	int roll3;
	int roll4;
	int dice1;
	int dice2;
	int dice3;
	int dice4;
	int wagercheck=1;
	int sum1;
	int sum2;
	int add_or_subtract;	
	int add_or_subtract2;	
	int again =1;


	get_balance_bank(balance);
	while (again ==1){
		get_wager_amount(wager);
		while (wagercheck==1){
			wagercheck = check_wager_amount(balance, wager);
			if (wagercheck == 1){
				get_wager_amount(wager);
			}
		}
		cout << "Press 1 to Roll" << endl;
		cin>> roll1;
		if  (roll1 = 1){
			dice1 = roll_die();
		}
		cout << "Press 1 to Roll" << endl;
		cin >> roll2;
		if (roll2 == 1){
			dice2 = roll_die();
		}
		sum1 = calculate_sum_dice(dice1, dice2);
		add_or_subtract = is_win_loss_or_point(sum1);



		if (add_or_subtract == 1){
			adjust_bank_balance(balance, wager, 1);
		}
		else if (add_or_subtract ==0){	
			adjust_bank_balance(balance, wager, 0);
		}
		else if (add_or_subtract ==-1){
			cout << "Press 1 to Roll" << endl;
			cin>> roll3;
			if  (roll3 = 1){
				dice3 = roll_die();
			}
			cout << "Press 1 to Roll" << endl;
			cin >> roll4;
			if (roll4 == 1){
				dice4 = roll_die();
			}
			sum2 = calculate_sum_dice(dice3, dice4);
			add_or_subtract2 = is_point_loss_or_neither (sum2, sum1);
			adjust_bank_balance(balance, wager, add_or_subtract2);
			
		}	
		cout <<"balance: "<<balance<< endl;
		cout <<"Roll again? "<< endl;
		cout << "Press 1 to use again, press 2 to stop" << endl;
		cin >> again;
	}

}







//////////////////////////////////////////////////////////////////////////////////////////////////////
/*Function: Get Bank Balance
 * Description: Retrieve bank balance from user
 * Parameters:	Double
 * Preconditions: The inputs must be a positive number
 * postconditions: The returning conditions is a positive double that the user input
 * Return:The user input for bank balance
 */

void get_balance_bank (double &balance){
	cout << "Enter Balance: "<< endl;
	cin >> balance;
	cout << "Balance: "<<balance<< endl;
}

/*Function: Get wager
 * Description: Retrieve wager balance from user
 * Parameters:	Double
 * Preconditions: The inputs must be a positive number
 * postconditions: The returning conditions is a positive double that the user input
 * Return:The user input for bank wager
 */
void get_wager_amount (double &wager){
	cout << "Enter Wager: "<< endl;
	cin >> wager;
	cout << "Wager: " <<wager<< endl;
}
/*Function:Check wager amount
 * Description:Checks to see if wager amount is less than the balance
 * Parameters:double, double
 * Preconditions:input the balance and wager
 * postconditions:checks and returns an int
 * Return:Returns 0 if satisfies, return 1 if it doesn't.
 */
int check_wager_amount (double balance, double wager){
	if (wager<=balance){
		cout << "Wager is less than balance" << endl;
		return 0;
	}
	else{
		cout <<"Wager greater than balance" << endl;
		return 1;
	}

}
/*Function:roll die
 * Description:uses a random number generator to generate a number between 1-6 as the dice
 * Parameters:none
 * Preconditions: Must be able to get an interger from 1-6
 * postconditions: positive integer is returned
 * Return:int
 */
int roll_die (void){
	int die;
	srand(time(NULL));
	die = (rand()%6)+1;
	return die;
}
/*Function: calculate sum dice
 * Description: Adds dice 1 and dice 2
 * Parameters:int, int
 * Preconditions:inputs must be two integers
 * postconditions:The result of the sum is an integer between 2 and 12
 * Return:the sum, which is and integer
 */
int calculate_sum_dice(int dice1, int dice2){
	int sum;
	sum = dice1 + dice2;
	cout << "Sum dice: "<< sum<< endl;
	return sum;
}
/*Function:win loss or point
 * Description: If the number is 7 or 11, it is a win, if it is 2, 3, or 12, it is a loss, and if it is anything else it is a point.
 * Parameters:int
 * Preconditions:the input must be an integer from 2-12 from the sum of two dice
 * postconditions:returns an integer 0,1, or -1
 * Return:in 0,-1,2
 */
int is_win_loss_or_point (int sum_dice){
	if (sum_dice == 7 || sum_dice ==11) {
		return 1;
	}
	else if (sum_dice == 2 || sum_dice == 3 || sum_dice == 12){
		return 0;
	}
	else{
		return -1;
	}
}
/*Function:point, loss, or neither
 * Description:After first sum, it compares a the new sum with the first sum. If the same number is rolled, it is a point. If 7 is rolled, it is a loss. If neither is rolled, it is neither.
 * Parameters:int, int
 * Preconditions:One of the integer is the original sum, and the other on is the second sum. It will compare the two.
 * postconditions: The post condition is an integer
 * Return:0,-1,1
 */
int is_point_loss_or_neither (int sum_dice, int point_value){
	if (sum_dice == point_value){
		return 1;
	}
	else if (sum_dice == 7){
		return 0;
	}
	else{
		return -1;
	}
}
/*Function:adjust bank balance
 * Description: Based off of the results, the balance will either add, subtract, or stay constant. If it is 1, it will add. If it is 0, it will subtract. Finally, if it is -1, t will be constant.
 * Parameters:double, double, int
 * Preconditions:The function involves a bank balance, wager amount, and the results from the gam
 * postconditions:It will adjust the balance by the wager
 * Return:double balance
 */
void adjust_bank_balance(double &bank_balance, double wager_amount, int add_or_subtract){
	if (add_or_subtract == 1){
		bank_balance = bank_balance + wager_amount;	
		if (bank_balance <= 0){
			cout << "No more money" << endl;
		}
	}
	else if (add_or_subtract == 0){		
		bank_balance = bank_balance - wager_amount;	
		if (bank_balance <= 0){
			cout << "No more money" << endl;
		}
	}
	else if (add_or_subtract == -1){		
		bank_balance = bank_balance;	
		if (bank_balance <= 0){
			cout << "No more money" << endl;
		}
	}

}



