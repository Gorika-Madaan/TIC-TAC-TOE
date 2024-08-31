#include <iostream>
#include <cmath>
#include <string>
#include<windows.h>

#define Dimension 3

using namespace std;

// defining a class
class Player
{
private:
    string name; 
public:
// constructor
    Player(string n)
    {
        name = n;
    }
    string PlayerName()
    {
        return this->name;
    }
};
// Another class
class Game
{
private:
    char gameboard[Dimension][Dimension];
    int count;

public:

    void CreateBoard()
    {
        for (int i = 0; i < Dimension; i++)
        {
            for (int j = 0; j < Dimension; j++)
                gameboard[i][j] = ' ';
        }
        showBoard();
    }

void showBoard()
{
        cout<<"\n\n";
        for (int i = 0; i < Dimension; i++)
        {
            cout << "\t\t\t";
            for (int j = 0; j < Dimension; j++)
                cout << " | " << gameboard[i][j];
            cout << " |\n\t\t\t----------------" << endl;
        }
}



void PlayerTurn(Player &player)
{
        int position;
        int row;
        cout << "Turn of " << player.PlayerName() <<":"<<endl;
        cout << "Enter the position to be marked: ";
        cin >> position;
        row = ceil((float)position / Dimension);
        int col = (position - 1) % Dimension;
        if (gameboard[row - 1][col] != ' ')
        {
            cout << "Position already marked. Please select another position" << endl;

            PlayerTurn(player);
        }
        else
        {
            player.PlayerName().compare("Player I") == 0 ? gameboard[row - 1][col] = 'X' : gameboard[row - 1][col] = 'O';
            cout << " Marked at position: " << position << endl;
            count++;
        }
        showBoard();
}



void MachineTurn()
{

        int random_position;
        cout << "Turn of Machine: " << endl;
        random_position = rand() % (Dimension * Dimension + 1);
        int row = ceil((float)random_position / Dimension);
        int col = (random_position - 1) % 3;
        if (gameboard[row - 1][col] != ' ')
        {
            MachineTurn();
        }
        else
        {
            cout << " Marked at position: " << random_position << endl;
            gameboard[row - 1][col] = 'O';
            count++;
        }

        showBoard();
}

string CheckWin()
    {
        int r1 = 0, r2 = 0;
        int c1 = 0, c2 = 0;
        int d1 = 0, d2 = 0;
        char x = 'X';
        char O = 'O';
        for (int i = 0; i < Dimension; i++)
        {
            r1 = 0, r2 = 0;
            c1 = 0, c2 = 0;
            if (gameboard[i][i] == x)
            {
        
                d1++;
            }
            else if (gameboard[i][i] == O)
            {
                
                d2++;
            }
            for (int j = 0; j < Dimension; j++)
            {
                if (gameboard[i][j] == x)
                {
                    r1++;
                }
                else if (gameboard[i][j] == O)
                {
                    r2++;
                }
                if (gameboard[j][i] == x)
                {
                    c1++;
                }
                else if (gameboard[j][i] == O)
                {
                    c2++;
                }
            }

            if (r1 == Dimension || r2 == Dimension)
            {
                return (r1 == Dimension) ? "Player I" : "Player 2";
            }

            else if (c1 == Dimension || c2 == Dimension)
            {
                return (c1 == Dimension) ? "Player I" : "Player 2";
            }
            else if (d1 == Dimension || d2 == Dimension)
            {
                return (d1 == Dimension) ? "Player I" : "Player 2";
            }
        }
        if (count == Dimension * Dimension)
        {
            return "Draw";
        }
        return "";
    }
};

int main()
{
    Game *game = new Game;
    int ch;
    game->CreateBoard();
    cout << "Press 1 for single-player and 2 for a two-player game" << endl;
    cin >> ch;
    string fin = "";
    bool flag = true;
    switch (ch)
    {//single player
    case 1:
    {
        Player player("Player I");
        while (flag)
        {
            // Player turn
            game->PlayerTurn(player);
            fin = game->CheckWin();
            if (fin != "")
            {
                goto point;
            }
            // Machine turn
            game->MachineTurn();
            fin = game->CheckWin();
        point:
            if (fin == "Player I")
            {
                cout << " Player 1 win";
                flag = false;
            }
            else if (fin == "Player 2")
            {
                cout << "Computer Wins";
                flag = false;
            }
            else if (fin == "Draw")
            {
                cout << "The game ended in a draw";
                flag = false;
            }
        }
    }
    case 2:
    {
        Player player("Player I");
        Player player2("Player 2");
        while (flag)
        {
            game->PlayerTurn(player);
            fin = game->CheckWin();
            if (fin != "")
            {
                goto point2;
            }
            game->PlayerTurn(player2);
            fin = game->CheckWin();
        point2:
            if (fin == "Player I")
            {
                cout << " Player 1 win";
                flag = false;
            }
            else if (fin == "Player 2")
            {
                cout << "Computer Wins";
                flag = false;
            }
            else if (fin == "Draw")
            {
                cout << "The game ended in a draw";
                flag = false;
            }
        }
    }
    default:
    {
        exit(0);
    }
    }
    return 0;
}


