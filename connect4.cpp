#include <iostream>
/*Program: Connect4.cpp
 * Author: Dennis Li
 * Date: 12/4/16
 * Description: This program allows two players to play a game of connect four. The user can input the size of the board and the number of connections in a row to win.
 * Input: Row Size, Column Size, Number of connections
 * Output:Winner
 */


#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;
void init_board(char**, int, int);
void print_board(char **, int , int );
int place_x(char **, int , int, int );
int place_o(char **, int , int, int );
int run_game(char**, int, int, int);
int check_horizontal(char**, char ,int, int, int);
int check_vertical(char **, char, int, int, int, int);
int check_diagonal(char **, char, int, int, int, int);
bool check_command_line(char *[7]);
bool positive_int_error_check(string);

/*Function: main
 * Description: This function is the overall function to run the game dependent on the user's input of columns, size, and connect number. The game will run again if the user wants to play again.
 * Parameters: number of columns, rows, and connect number
 * Pre-conditions:The number of columns, rows, and connect number are used to create the board and determine the winner.
 * Post-conditions: Player 1 or 2 wins or a tie
 * Return: None
 */

int main(int argc, char *argv[]){	
	int check=1;
	int rows;//Int that runs through game and functions
	int columns;//Int that runs through game and functions
	int connect;//Int that runs through game a functions
	int game;//Determines the winner
	string second_row;//Initial input that is processed through integer check
	string second_column;//Initial input that is processed through integer check
	string second_connect;//Initial input that is processed through integer check
	bool integer_check;//True or false for integer check
	bool second;//Asks for another input of column, row, and connect
	bool again;//Play again
	char **board;//Game board
	
	if(check_command_line(argv)==false){
		exit(0);
	}

	for(int c=1;c<argc;c++){//Converts command line arguments
		if (strcmp(argv[c],"-r")==0){ 
			rows = atoi(argv[c+1]);
			cout<< "Rows: "<<rows<< endl;
		}
		if (strcmp(argv[c],"-c")==0){ 
			columns = atoi(argv[c+1]);
			cout<< "Columns: "<<columns<< endl;
		}
		if (strcmp(argv[c],"-p")==0){ 
			connect = atoi(argv[c+1]);
			cout<< "Connect: "<< connect<< endl;
		}
	}

	again=true;//Run game
	while (again ==true){
		if (second == true){//only run after you run through command line argument at least once
			integer_check=false;
			while (integer_check==false){//This while loop is to for checking for positive integer
				cout<<"Enter rows"<< endl;
				cin>>second_row;
				cout<<"Enter columns"<< endl;
				cin>> second_column;
				cout<< "Connect how many?"<<endl;
				cin>> second_connect;

				if((positive_int_error_check(second_row) ==false)||(positive_int_error_check(second_column) ==false)||(positive_int_error_check(second_connect) ==false)){
					cout<<"Enter a positive integer"<<endl;
					integer_check=false;
				
				}
				else{
					rows=atoi(second_row.c_str());
					columns=atoi(second_column.c_str());
					connect=atoi(second_connect.c_str());
					integer_check=true;
				}
			}	
		}

		board = new char*[rows];//This is used to create the dynamic 2D array
		for(int i=0; i<rows; i++){
			board[i]= new char [columns];
		}
		
		
		game = run_game(board, rows, columns, connect);//Function call runs game, returns a 1 if player 1 wins, returns 2 if player 2 wins.
		if (game==1){
			cout<<"Player x Wins"<<endl;
		}
		else if (game==2){
			cout<< "Player o Wins"<< endl;
		}
		else{
			cout<<"Tie Game"<< endl;
		}



		for(int d=0;d<columns;d++){ //To delete board
			delete[]board[d];
		}
		delete [] board;


		cout<<"Play again? (1-Yes, 0-No)"<<endl;
		cin>>again;
		if (again==1){
			again = true;
			second =true;
		}
		else if (again==0){
			again= false;
		}

	}
}


/*Function: init_board
 * Description: This function initializes the board with char ''.
 * Parameters: char**, int, int.
 * Pre-conditions: Program requires 2D array for the board and the number of columns and rows.
 * Post-conditions: Fills a 2D array with ''.
 * Return: None
 */
void init_board(char **board,int rows,int columns){
	int r;
	int c;
	for(r=0; r<rows; r++){
		for(c=0;c<columns;c++){
			board[r][c]=' ';

		}
	}
}

/*Function: print_board
 * Description: This function displays the boards in a 2D grid.
 * Parameters: char**, int, int.
 * Pre-conditions: Program requires 2D array for the board and the number of columns and rows.
 * Post-conditions: Prints out array indexs seperated witj "|". Then rows seperated with "---"
 * Return: None
 */
void print_board(char **board, int rows, int columns){
	int r;
	int c;
	for(r=0; r<rows; r++){
		for(c=0;c<columns;c++){
			cout<<"|"<<board[r][c];
		}
		cout<<"|"<< endl;
		for(c=0;c<columns;c++){
			cout<<"--";
		}
		cout<<" "<< endl;
	}
}

/*Function:check_horizontal 
 * Description:checks horizontally for number or x's or o's in a row. This function checks the last letter that was placed.
 * Parameters: char**, char, int, int, int. 
 * Pre-conditions:This function requires a 2D array for the board, a letter to test for, number of connections, and the column and row number where the letter was last placed.
 * Post-conditions: Returns a 1 if there is a horizontal 4 in a row(user dependent).
 * Return: Returns 1 if it is satisfied. Returns 0 if not satisfied.
 */
int check_horizontal(char **board, char test_letter, int start_row, int start_column, int connect_num){
	int count = 1;
	int i=1;
	while(board[start_row][start_column+i]==test_letter){ //This checks to the right of position where the character was placed
		count++;
		i++;
	}
	i=1;	
	while(board[start_row][start_column-i]==test_letter){ //This checks to the left of position where the character was placed
		count++;
		i++;
	}

	if (count==connect_num){
		return 1;
	}
	else{ 
		return 0;
	}

}


/*Function:check_vertical
 * Description:checks vertically for number or x's or o's in a row. This function checks the last letter that was placed.
 * Parameters: char**, char, int, int, int. 
 * Pre-conditions:This function requires a 2D array for the board, a letter to test for, number of connections, and the column and row number where the letter was last placed.
 * Post-conditions: Returns a 1 if there is a vertical 4 in a row(user dependent).
 * Return: Returns 1 if it is satisfied. Returns 0 if not satisfied.
 */
int check_vertical(char **board, char test_letter, int rows, int start_row, int start_column, int connect_num){
	int count = 0;
	while(start_row<rows){//This loop checks every row below the designated index, but will not go out of range
		if (board[start_row][start_column]==test_letter){
			count++;
			start_row++;
			if (count==connect_num){
				return 1;//Returns 1 if satisfies
			}
		}
		else{
			break;
		}
	}
	return 0;//Returns 2 if fails
}



/*Function:check_diagonal
 * Description:checks diagonal for number or x's or o's in a row. This function checks the last letter that was placed.
 * Parameters: char**, char, int, int, int. 
 * Pre-conditions:This function requires a 2D array for the board, a letter to test for, number of connections, and the column and row number where the letter was last placed.
 * Post-conditions: Returns a 1 if there is a diagonal 4 in a row(user dependent).
 * Return: Returns 1 if it is satisfied. Returns 0 if not satisfied.
 */
int check_diagonal(char **board, char test_letter, int row, int start_row, int start_column, int connect_num){
	int count_up=1;
	int count_down=1;
	int r = 1;	
	int c = 1;
	while(start_row-r>=0&&board[start_row-r][start_column+c]==test_letter){/////////First two while loops are used to check diagonal going from bottom left to top right = (/)
		count_up++;
		r++;
		c++;
	}
	r = 1;	
	c = 1;
	while(start_row+r<row&&board[start_row+r][start_column-c]==test_letter){
		count_up++;
		r++;
		c++;
	}


	r = 1;	
	c = 1;
	while(start_row+r<row&&board[start_row+r][start_column+c]==test_letter){///////Second two loops are used to check for top left to bottom right = (\)
		count_down++;
		r++;
		c++;
	}
	r = 1;	
	c = 1;
	while(start_row-r>=0&&board[start_row-r][start_column-c]==test_letter){
		count_down++;
		r++;
		c++;
	}
	if (count_up==connect_num||count_down==connect_num){
		return 1;
	}
	else{ 
		return 0;
	}

}

/*Function: place_x
 * Description: This function is used to place the letter x onto the board. When the user wants the place a letter in the column, it checks if the column is within range and checks if the column is full. Every time a letter is placed, the letter is checked for horizontal, vertical, and diagonal letters in a row.
 * Parameters: char**, int, int, int
 * Pre-conditions:The pre-conditions are the board and the number of rows and columns.
 * Post-conditions: The post condition is an 'x' at the designated index.   
 * Return: Return 1, if the checks are satisfied. 
 */
int place_x(char **board, int rows, int columns, int connect_num){
	string choice;
	int choice_int;//String choice become choice_int after check
	int r;
	int check=1;
	int horizontal;
	int vertical;
	int diagonal;

	while(check==1){
		bool spell = false;
		cout<<"Which column would you like to put X in? 0-"<<columns-1<< endl;
		cin>>choice;
		if( positive_int_error_check(choice) ==false){  //Error checking for positive integer
			cout<<"Not a positive integer"<<endl;
		}	
		else if (positive_int_error_check(choice)==true){
			choice_int=atoi(choice.c_str());// convert choice to choice int because it is an integer now
			for(r=rows-1; r>=0; r--){
				if (board[r][choice_int] ==' '){
					board[r][choice_int]='x';
					horizontal = check_horizontal(board,'x', r, choice_int, connect_num);
					vertical = check_vertical(board, 'x', rows ,r, choice_int, connect_num);
					diagonal = check_diagonal(board, 'x', rows, r, choice_int, connect_num);
					if (horizontal==1||vertical==1||diagonal==1){
						return 1;
					}
					check=0;
					return 0;
				}
			}

			cout<<"Number not in range or column full"<<endl;
		}
	}
}
/*Function: place_o
 * Description: This function is used to place the letter o onto the board. When the user wants the place a letter in the column, it checks if the column is within range and checks if the column is full. Every time a letter is placed, the letter is checked for horizontal, vertical, and diagonal letters in a row.
 * Parameters: char**, int, int, int
 * Pre-conditions:The pre-conditions are the board and the number of rows and columns.
 * Post-conditions: The post condition is an 'o' at the designated index.   
 * Return: Return 1, if the checks are satisfied. 
 */
int place_o(char **board, int rows, int columns, int connect_num){
	string choice;
	int choice_int;//String choice become choice_int after check
	int r;
	int check=1;
	int horizontal;
	int vertical;
	int diagonal;

	while(check==1){
		bool spell = false;
		cout<<"Which column would you like to put X in? 0-"<<columns-1<< endl;
		cin>>choice;

		if( positive_int_error_check(choice) ==false){  //Error checking for positive integer
			cout<<"Not a positive integer"<<endl;
		}	
		else if (positive_int_error_check(choice)==true){
			choice_int=atoi(choice.c_str());
			for(r=rows-1; r>=0; r--){
				if (board[r][choice_int] ==' '){
					board[r][choice_int]='o';
					horizontal = check_horizontal(board,'o', r, choice_int, connect_num);
					vertical = check_vertical(board, 'o', rows ,r, choice_int, connect_num);
					diagonal = check_diagonal(board, 'o', rows, r, choice_int, connect_num);
					if (horizontal==1||vertical==1||diagonal==1){
						return 1;
					}
					check=0;
					return 0;
				}
			}

			cout<<"Number not in range or column full"<<endl;
		}
	}
}

/*Function: run_game
 * Description: This function fully runs the game and fills the board completely unless a winner is determined beforehand.
 * Parameters: char**, int, int, int
 * Pre-conditions:The board and the number of rows and columns are needed to play the game. The connect_num is needed to determine how many letters in a row are needed to win.
 * Post-conditions: This function will return a 1 if player 1 wins or 2 if player 2 wins
 * Return:1 or 2. 
 */
int run_game(char **board,  int rows, int columns, int connect_num){
	int turns;
	int player_1_win;
	int player_2_win;

	turns = (rows*columns)/2;	
	init_board(board, rows, columns);
	if ((rows*columns)%2==0){
		while(turns>0){
			player_1_win = place_x(board, rows, columns, connect_num);
			print_board(board, rows, columns);
			if (player_1_win==1){
				return 1;
			}
			player_2_win = place_o(board, rows, columns, connect_num);
			print_board(board, rows, columns);
			if (player_2_win==1){
				return 2;
			}
			turns--;

		}
	}


	else if((rows*columns)%2==1){
		place_x(board, rows, columns, connect_num);
		print_board(board, rows, columns);
		while(turns>0){	
			player_1_win = place_o(board, rows, columns, connect_num);
			print_board(board, rows, columns);
			if (player_1_win==1){
				return 2;
			}
		player_2_win = place_x(board, rows, columns, connect_num);
			print_board(board, rows, columns);
			if (player_2_win==1){
				return 1;
			}
			turns--;

		}

	}
	return 0;
}


/*Function: check_command_line
 * Description: This function will check to see if the command line arguments for column, rows, and connect number are positive integers.
 * Parameters: char**.
 * Pre-conditions:The array that the inputs are located in are needed for the function.
 * Post-conditions: This function will return a false if the input is not a positive integer. Return true if it satisfies.
 * Return:true or false. 
 */
bool check_command_line(char *argv[7]){
	int i;

	
	for (i=0; i<strlen(argv[2]);i++){
		if(!(argv[2][i]>='0'&&argv[2][i]<='9')){
			cout<<"Input positive integers for column, rows, and connect number. (ex: -r 6 -r 6 -p 4)"<<endl;
			return false;
		}
	}
	for (i=0; i<strlen(argv[4]);i++){
		if(!(argv[4][i]>='0'&&argv[4][i]<='9')){
			cout<<"Input positive integers for column, rows, and connect number. (ex: -r 6 -r 6 -p 4)"<<endl;
			return false;
		}
	}
	for (i=0; i<strlen(argv[6]);i++){
		if(!(argv[6][i]>='0'&&argv[6][i]<='9')){
			cout<<"Input positive integers for column, rows, and connect number. (ex: -r 6 -r 6 -p 4)"<<endl;
			return false;
		}
	}
	return true;
}


/*Function: positive_int_error_check
 * Description: This function will check for positive integers.
 * Parameters: string
 * Pre-conditions: The string that is being checked.
 * Post-conditions: This function will returnf false if the input is not a positive integer. Return true if it satisfies.
 * Return:true or false. 
 */
bool positive_int_error_check(string input){
	for (int i=0; i<input.length(); i++){
		if(!(input.at(i)>='0'&&input.at(i)<='9')){
			return false;
		}
		else{
			return true;
		}
	}	
}
