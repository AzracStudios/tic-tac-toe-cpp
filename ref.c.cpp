#include <iostream>
using namespace std;

string formatBoard(int board[])
{
    bool newRow = false;
    string boardString;

    for (size_t i = 0; i < 9; i++)
    {
        string currentChar = " ";
        if (newRow == true)
            boardString += "|\n-------------\n";

        newRow = false;
        if (i == 2 || i == 5)
            newRow = true;

        if (board[i] == 1)
            currentChar = "O";
        else if (board[i] == 0)
            currentChar = "X";

        boardString += '|';
        boardString += ' ' + currentChar + ' ';
    }
    cout << endl;
    return boardString + "|\n";
}

int isWin(int board[], int player, int ai)
{
    // Horizontal
    if (
        (board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player))
    {
        return +10;
    }

    if (
        (board[0] == ai && board[1] == ai && board[2] == ai) ||
        (board[3] == ai && board[4] == ai && board[5] == ai) ||
        (board[6] == ai && board[7] == ai && board[8] == ai))
    {
        return -10;
    }

    // Vertical
    if (
        (board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player))
    {
        return +10;
    }

    if (
        (board[0] == ai && board[3] == ai && board[6] == ai) ||
        (board[1] == ai && board[4] == ai && board[7] == ai) ||
        (board[2] == ai && board[5] == ai && board[8] == ai))
    {
        return -10;
    }

    // Diagonal
    if (
        (board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player))
    {
        return +10;
    }

    if (
        (board[0] == ai && board[4] == ai && board[8] == ai) ||
        (board[2] == ai && board[4] == ai && board[6] == ai))
    {
        return -10;
    }

    // If no one wins
    return 0;
}

int gameOver(int board[])
{
    int state = 0;

    for (size_t i = 0; i < 9; i++)
    {
        if (board[i] != 2)
            state++;
    }

    return state == 9;
}

int minimax(int board[9], int depth, bool isMaximizing, int player, int ai)
{
    int score = isWin(board, player, ai);
    if (score == 10)
        return score;
    if (score == -10)
        return score;

    if (gameOver(board) == 0)
        return 0;

    if (isMaximizing)
    {
        int best = -1000;

        for (size_t i = 0; i < 9; i++)
        {
            if (board[i] == 2)
            {
                board[i] = player;
                best = max(best, minimax(board, depth + 1, !isMaximizing, player, ai));
                board[i] = 2;
            }
        }

        return best;
    }

    else
    {
        int best = 1000;

        for (size_t i = 0; i < 9; i++)
        {
            if (board[i] == 2)
            {
                board[i] = ai;
                best = min(best, minimax(board, depth + 1, !isMaximizing, player, ai));
                board[i] = 2;
            }
        }

        return best;
    }
}

int bestMove(int board[], int player, int ai)
{
    int bestVal = -1000;
    int bestMove = -1;

    for (size_t i = 0; i < 9; i++)
    {
        if (board[i] == 2)
        {
            board[i] = player;
            int moveVal = minimax(board, 0, false, player, ai);
            board[i] = 2;

            if (moveVal > bestVal)
            {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }

    return bestMove;
}

int main()
{
    cout << "Welcome to Tic Tac Toe!\n"
         << endl;

    // Select Side

    cout << "Choose your side! [X: 0  O: 1] ";
    int side;
    cin >> side;

    if (!(side == 1 || side == 0))
    {
        cout << "Invalid Side!" << endl;
        return 0;
    }

    string sideChar = "X";
    if (side == 1)
        sideChar = "O";

    cout << "You picked " << sideChar << "."
         << endl;

    // Game Loop
    int player = side;
    int ai = !side;

    int playerTurn = !side;
    int playing = 1;

    int board[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};

    while (playing)
    {
        if (playerTurn)
        {
            cout << "\n================================\n\nYour turn: ";
            cout << "\nChoose a spot [1 - 9]: ";

            // Get spot, validate it and make a move
            int spot;
            cin >> spot;

            if (spot < 1 || spot > 9)
                cout << "\nInvalid Spot!" << endl;
            else if (board[spot - 1] != 2)
                cout << "\nInvalid Spot!" << endl;

            else
            {
                board[spot - 1] = player;
                string fmtBoard = string(formatBoard(board));
                cout << "\n"
                     << fmtBoard << "\n";

                int win = isWin(board, player, ai);

                if (win == +10)
                {
                    cout << "\n================================\n\nYou Win!!!\n\n";
                    return 0;
                }

                if (win == -10)
                {
                    cout << "\n================================\n\nAI Wins!!!\n\n";
                    return 0;
                }

                int tie = gameOver(board);
                if (tie)
                {
                    cout << "\n================================\n\nIt's a draw!!!\n\n";
                    return 0;
                }

                playerTurn = !playerTurn;
            }
        }

        else
        {
            cout << "\n================================\n\nAI's turn: ";

            // Get best spot, validate it and make a move
            int spot;
            spot = bestMove(board, player, ai);
            cout << spot + 1 << endl;

            board[spot] = ai;
            string fmtBoard = string(formatBoard(board));
            cout << fmtBoard << "\n";

            int win = isWin(board, player, ai);
            if (win == +10)
            {
                cout << "\n================================\n\nYou Win!!!\n\n";
                return 0;
            }
            if (win == -10)
            {
                cout << "\n================================\n\nAI Wins!!!\n\n";
                return 0;
            }

            int tie = gameOver(board);
            if (tie)
            {
                cout << "\n================================\n\nIt's a draw!!!\n\n";
                return 0;
            }

            playerTurn = !playerTurn;
        }
    }

    return 0;
}
