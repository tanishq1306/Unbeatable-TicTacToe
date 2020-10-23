#include <bits/stdc++.h>
using namespace std;

// global variables
char gameBoard[3][3];
char winner;

// reset GameBoard and Winner
void resetBoard();
void resetWinner();
void reset();

// setters and getters
void setChar(char symbol, int i);
void setChar(char symbol, int i, int j);
char getChar(int i);
char getChar(int i, int j); 

// possible moves
bool isMovePossible();
vector<int> allPossibleMoves();

// check winner
bool checkWinner(char symbol);

// do move
void doMove(char symbol, int index);

// print the board
void printBoard();

// player 
struct Player 
{
	string name;
	int id;	// [0 - human] [1 - bot]
    char symbol;
} p1, p2;

// move
struct Move
{
    int index;
    long score;
};

// human player move
int HumanPlayerMove();

// bot's move
int BotMove();

// play
void play();

// minimax Algorithm
Move minimax(char curr_player);

int main() 
{
	int mode;	
	char choice;
	
	do
    {
		system ("cls");
        cout << "\t\tSelect Game Mode\n"
			 << "\t\t================\n"
			 <<	"\t\t1. Human v/s Human\n"
			 <<	"\t\t2. Human v/s BOT\n"
			 <<	"\t\t3. Bot v/s BOT\n"
			 << "\nEnter Mode : ";	 
		cin >> mode;
		
		system ("cls");
			
		switch (mode)
        {
			case 1:
				cout <<	"\t\t1. Human v/s Human\n";
				cout <<	"\t\t==================\n";
				p1.id = 0;
				p2.id = 0;
				break;

			case 2:
				cout <<	"\t\t1. Human v/s BOT\n";
				cout <<	"\t\t==================\n";
				p1.id = 0;
				p2.id = 1;
				break;

			case 3:
				cout <<	"\t\t1. BOT v/s BOT\n";
				cout <<	"\t\t==================\n";
				p1.id = 1;
				p2.id = 1;
				break;

			default:
				cout << "Wrong choice\n";
        }
		
		//let's play
		play ();
        
        cout << "\nDo You Want To Play again (y / n) : ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
	
    return 0;
} 

// Reset GameBoard and Winner
void resetBoard()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			gameBoard[i][j] = ' ';
		}
	}
}

void resetWinner() 
{ 
	winner = ' ';
}

void reset()
{
	resetBoard();
	resetWinner();
}


// setters and getters
void setChar(char symbol, int i) 
{ 
	gameBoard[i / 3][i % 3] = symbol; 
}

void setChar(char symbol, int i, int j) 
{ 
	gameBoard[i][j] = symbol; 
}

char getChar(int i) 
{ 
	return gameBoard[i / 3][i % 3];
}

char getChar(int i, int j) 
{ 
	return gameBoard[i][j];
}

// possible moves
bool isMovePossible()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (gameBoard[i][j] == ' ')
			{
				return true;
			}
		}
	}
	return false;
}

vector<int> allPossibleMoves()
{
	vector<int> move_set;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (gameBoard[i][j] == ' ')
			{
				move_set.push_back(3 * i + j);
			}
		}
	}
	return move_set;
}

// check winner
bool checkWinner(char symbol)
{
	// horizontal check
	for (int i = 0; i < 3; i++)
	{
		if (gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2] && gameBoard[i][2] == symbol)
			return true;
	}

	// vertical check
	for (int i = 0; i < 3; i++)
	{
		if (gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i] && gameBoard[2][i] == symbol)
			return true;
	}

	// diagonal 1 check
	if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2] && gameBoard[1][1] == symbol)
		return true;

	// diagonal 2 check
	if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0] && gameBoard[1][1] == symbol)
		return true;

	return false;
}

// do move
void doMove(char symbol, int index)
{
	int i = index / 3, j = index % 3;
	gameBoard[i][j] = symbol;

	if (checkWinner(symbol))
	{
		winner = symbol;
	}
}

void printBoard()
{
	for (int i = 0; i <= 6; i += 3)
	{
		cout << "\n\t\t\t " << getChar(i) << "  | " << getChar(i + 1) << " | " << getChar(i + 2);
		//boundary condition
		if (i != 6)	
		{
			cout << "\n\t\t\t " << "---" << " --- " << "---";
		}
	}
}	

// human player move
int HumanPlayerMove(char symbol)
{
	int index;
	while (1)
	{
		cout << "\nPlayer " << symbol << " Enter index: ";
		cin >> index;

		if (getChar(index - 1) == ' ')
			return index - 1;

		cout << "Wrong Move";
	}
}

// bot's move
int BotMove(char id)
{
	Move trialMove;
	srand(time(0));

	if ((int)allPossibleMoves().size() == 9)
		trialMove.index = rand() % 9;
	else
		trialMove = minimax(id);

	return trialMove.index;
}

// minmax
Move minimax(char curr_player)
{
	char max_player = (curr_player == 'X') ? 'X' : '0';
	char other_player = (curr_player == 'X') ? 'O' : 'X';
	Move best, current;

	// base condition for win - lose
	if (winner == other_player)
	{
		best.score = (int)allPossibleMoves().size() + 1;
		if (other_player != max_player)
			best.score = -best.score;
		return best;
	}
	
	// base condtion for draw
	if (!isMovePossible())
	{
		best.score = 0;
		return best;
	}

	if (curr_player == max_player)
		best.score = -1000000;
	else
		best.score = 1000000;

	vector<int> move_set = allPossibleMoves();

	for (int i = 0; i < (int)move_set.size(); i++)
	{
		doMove(curr_player, move_set[i]);
		current = minimax(other_player);
		setChar(' ', move_set[i]);
		resetWinner();
		current.index = move_set[i];

		if (curr_player == max_player)
		{
			if (current.score > best.score)
				best = current;
		}
		else
		{
			if (current.score < best.score)
				best = current;
		}
	}
	
	return best;
}

void play()
{
    int index;
    reset();
    
    int chance = 1;	//1 player chance
    p1.symbol = 'X';
    p2.symbol = 'O';
    
    while (isMovePossible())
    {
		char letter = chance ? p1.symbol : p2.symbol;
		
        if (chance)
            index = (p1.id == 0 ? HumanPlayerMove(p1.symbol) : BotMove(p1.symbol));
        else
            index = (p2.id == 0 ? HumanPlayerMove(p2.symbol) : BotMove(p2.symbol));
		
        doMove(letter, index);
        cout << endl << letter << " makes move to " << index + 1 << endl;
        printBoard();
        
        if (checkWinner(letter))
        {
            cout << endl << letter << " wins!\n";
            return;
        }

        chance = 1 - chance;
    }
    
    cout << endl << "Draw!\n";
}
