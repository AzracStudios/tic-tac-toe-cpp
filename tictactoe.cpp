#include "tictactoe.hpp"

/*
======
 CELL
======
*/

tictactoe::Cell *tictactoe::Cell::set_type_o()
{
    (*this).type = 0;
    return this;
}

tictactoe::Cell *tictactoe::Cell::set_type_x()
{
    (*this).type = 1;
    return this;
}

tictactoe::Cell *tictactoe::Cell::set_type_empty()
{
    (*this).type = -1;
    return this;
}

int tictactoe::Cell::get_type_as_int()
{
    return (*this).type;
}

char tictactoe::Cell::get_type_as_char()
{
    if ((*this).type == 0)
        return 'O';
    else if ((*this).type == 1)
        return 'X';
    else
        return ' ';
}

int tictactoe::Cell::is_empty()
{
    return (*this).type == -1;
};

/*
=======
 BOARD
=======
*/

void tictactoe::Board::make_board()
{
    for (size_t y = 0; y < 3; y++)
    {
        for (size_t x = 0; x < 3; x++)
        {
            (*this).board[y][x] = *Cell().set_type_empty();
        }
    }
}

void tictactoe::Board::set_cell(int x, int y, int cell_type)
{
    Cell cell_to_place = Cell();

    switch (cell_type)
    {
    case 1:
        cell_to_place.set_type_x();
        break;
    case 0:
        cell_to_place.set_type_o();
        break;
    case -1:
        cell_to_place.set_type_empty();
        break;
    };

    (*this).board[y][x] = cell_to_place;
};

tictactoe::Cell tictactoe::Board::get_cell(int x, int y)
{
    return (*this).board[y][x];
}

int tictactoe::Board::is_full()
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if ((*this).board[i][j].is_empty())
                return 0;
        }
    }

    return 1;
}

// 0 => row not in win state
// 1 => row in win state
int tictactoe::Board::check_row(int y, int check_for)
{
    for (size_t x = 0; x < 3; x++)
    {
        Cell cell_to_check = (*this).get_cell(x, y);
        if (cell_to_check.get_type_as_int() != check_for)
            return 0;
    }

    return 1;
}

// 0 => col not in win state
// 1 => col in win state
int tictactoe::Board::check_col(int x, int check_for)
{
    for (size_t y = 0; y < 3; y++)
    {
        Cell cell_to_check = (*this).get_cell(x, y);
        if (cell_to_check.get_type_as_int() != check_for)
            return 0;
    }

    return 1;
}

// 0 => board not in win state
// 1 => board in win state
int tictactoe::Board::is_win(int to_check)
{
    for (size_t y = 0; y < 3; y++)
    {
        int row = (*this).check_row(y, to_check);
        if (row)
            return row;

        for (size_t x = 0; x < 3; x++)
        {
            int col = (*this).check_col(x, to_check);
            if (col)
                return col;
        }
    }

    return -1;
}

std::string tictactoe::Board::format_board()
{
    std::string board_string = "";
    for (size_t y = 0; y < 3; y++)
    {
        board_string += "+---+---+---+\n";
        for (size_t x = 0; x < 3; x++)
        {
            board_string += "| ";
            board_string += get_cell(x, y).get_type_as_char();
            board_string += " ";
            if (x == 2)
                board_string += "|\n";
        }
    }
    board_string += "+---+---+---+\n";
    return board_string;
}

int tictactoe::Game::minimax(int depth, int is_maximizing)
{
    int player_win = (*this).board.is_win((*this).player);
    int ai_win = (*this).board.is_win((*this).ai);

    if (player_win || ai_win)
        return 1;

    if ((*this).board.is_full())
        return 0;

    if (is_maximizing)
    {
        int best = -1000;

        for (size_t y = 0; y < 3; y++)
        {
            for (size_t x = 0; x < 3; x++)
            {
                if ((*this).board.get_cell(x, y).get_type_as_int() == 2)
                {
                    if ((*this).player == 0)
                        (*this).board.get_cell(x, y).set_type_o();
                    else
                        (*this).board.get_cell(x, y).set_type_x();

                    best = std::max(best, minimax(depth + 1, !is_maximizing));
                    (*this).board.get_cell(x, y).set_type_empty();
                }
            }
        }

        return best;
    }

    else
    {
        int best = 1000;

        for (size_t y = 0; y < 3; y++)
        {
            for (size_t x = 0; x < 3; x++)
            {
                if ((*this).board.get_cell(x, y).get_type_as_int() == 2)
                {
                    if ((*this).player == 0)
                        (*this).board.get_cell(x, y).set_type_o();
                    else
                        (*this).board.get_cell(x, y).set_type_x();

                    best = std::max(best, minimax(depth + 1, !is_maximizing));
                    (*this).board.get_cell(x, y).set_type_empty();
                }
            }
        }

        return best;
    }
}

int tictactoe::Game::best_move()
{
    int best_val = -1000;
    int _x = 0;
    int _y = 0;

    for (size_t y = 0; y < 3; y++)
    {
        for (size_t x = 0; x < 3; x++)
        {
            if ((*this).board.get_cell(x, y).get_type_as_int() == 2)
            {
                if ((*this).player == 0)
                    (*this).board.get_cell(x, y).set_type_o();
                else
                    (*this).board.get_cell(x, y).set_type_x();

                int move_val = minimax(0, false);
                (*this).board.get_cell(x, y).set_type_empty();

                if (move_val > best_val)
                {
                    _x = x;
                    _y = y;

                    best_val = move_val;
                }
            }
        }
    }

    return _x + (3 * (_y + 1));
}

void tictactoe::Game::print_board()
{
    std::cout << "\n"
              << (*this).board.format_board() << std::endl;
}

void tictactoe::Game::update(int spot)
{
    int x = (spot - 1) % 3;
    int y = ((spot - 1) % 10) / 3;

    if (!(*this).board.get_cell(x, y).is_empty())
    {
        std::cout << "Spot already contains '" << (*this).board.get_cell(x, y).get_type_as_char() << "' \n";
        return;
    }

    (*this).board.set_cell(x, y, (*this).player);

    int move = 0;
    move = best_move();
    std::cout << move;

    int ai_x = (move - 1) % 3;
    int ai_y = ((move - 1) % 10) / 3;

    (*this).board.set_cell(ai_x, ai_y, (*this).ai);
}

void tictactoe::Game::start(int player, int ai)
{
    (*this).player = player;
    (*this).ai = ai;

    (*this).board = Board();
    (*this).board.make_board();
}
