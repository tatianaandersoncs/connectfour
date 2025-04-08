#include<iostream>
using namespace std;

static int x = 7 , y = 7 , allowed = y;
static int board[7][7]; 

void init(){
	int i , j;
	for(i=1; i < x ; i++)
		for(j=0; j < y ; j++)
			board[i][j] = 0;

	for(j=0; j < y ; j++)
			board[0][j] = 6;
}

void drawer(){
	int i , j;
	for(i=1; i < x ; i++){
		for(j=0; j < y ; j++)
			cout << board[i][j];
		cout<< "\n";
	}
	cout<<"\n-------------\n";	
}

int user_input(int user){
	int user_value;
	cout<< "user"<<user <<"\'s turn!\nPlease enter the number of column you want to drop your disc to: ";
	cin >> user_value;
	user_value--; 
	
	if(user_value > 6 || user_value < 0){
		drawer();
		cout<<"Please Enter a valid number!\n";
		user_value = user_input(user);
	}
	
	return user_value;
}

void gamer(int column , int user){
	if(board[0][column] != -1){
		if(board[0][column] > 1){
			board[board[0][column]][column] = user;
			board[0][column]--;
		}
		else{
			board[board[0][column]][column] = user;
			board[0][column] = -1;
			allowed--;
		}
	}
	else{
		drawer();
		cout<<"This column is full! Try another one!\n";
		gamer(user_input(user) , user);  
	}
}

bool isWon(int row , int col){
	int val = board[row][col]; 
	int winHor=1, winVer=1, winDiag1=1, winDiag2=1;

	if(val == 0) return 0;

	// Horizontal check
	int i = col;
	while(i<y-1){
	   if(board[row][i+1] == val)
	        winHor++;
	   else
	        break;
	   i++;
	}
	i=col;
	while(i>0){
	   if(board[row][i-1] == val)
	        winHor++;
	   else
	        break;
	   i--;
	}
	if(winHor > 3) return 1;

	// Vertical check
	i = row;
	while(i<6){
	   if(board[i+1][col] == val)
	        winVer++;
	   else
	        break;
	   i++;
	}
	if(winVer > 3) return 1;

	// Diagonal 1: Top-left to bottom-right
	i = 1;
	while(row - i >= 1 && col - i >= 0){
		if(board[row - i][col - i] == val)
			winDiag1++;
		else
			break;
		i++;
	}
	i = 1;
	while(row + i < x && col + i < y){
		if(board[row + i][col + i] == val)
			winDiag1++;
		else
			break;
		i++;
	}
	if(winDiag1 > 3) return 1;

	// Diagonal 2: Bottom-left to top-right
	i = 1;
	while(row + i < x && col - i >= 0){
		if(board[row + i][col - i] == val)
			winDiag2++;
		else
			break;
		i++;
	}
	i = 1;
	while(row - i >= 1 && col + i < y){
		if(board[row - i][col + i] == val)
			winDiag2++;
		else
			break;
		i++;
	}
	if(winDiag2 > 3) return 1;

	return 0;
}

void end(int c){
	drawer();
	switch (c) {
		case 0:
			cout<<"WoW!\nYou two are both great masters!\nI should now announce that this game has reached a draw!";
			break;
		case 1:
			cout<<"And now...\nThe champion of the game...\nuser1 won!!!";
			break;
		case 2:
			cout<<"And now...\nThe champion of the game...\nuser2 won!!!";
			break;
	}
}

int main(){
	init();
	int turn = 1 , column = 0, result = 0;

	while(1){
		drawer();
		if(allowed == 0){
			result = 0;
			break;
		}
		if(turn == 1){ 
			column = user_input(1);
			gamer(column , 1);
		}
		else{ 
			column = user_input(2);
			gamer(column , 2);
		}
		if(isWon(board[0][column] + 1 , column)){
			result = turn;
			break;
		}
		turn = (turn == 1) ? 2 : 1;
	}
	end(result);
	return 0;
}
