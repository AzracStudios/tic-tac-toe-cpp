#pragma once
#include <iostream>

namespace tictactoe
{
    class Cell
    {
    private:
        int type;

    public:
        Cell *set_type_o();
        Cell *set_type_x();
        Cell *set_type_empty();
        int get_type_as_int();
        char get_type_as_char();
        int is_empty();
    };

    class Board
    {
    private:
        Cell board[3][3];

    public:
        void make_board();
        void set_cell(int x, int y, int cell_type);
        Cell get_cell(int x, int y);
        int is_full();

        int check_row(int y, int check_for);
        int check_col(int x, int check_for);
        int is_win(int to_check);

        std::string format_board();
    };

    class Game
    {
        Board board;
        int player;
        int ai;

    public:
        int minimax(int depth, int is_maximizing);
        int best_move();
        void print_board();
        void start(int player, int ai);
        void update(int spot);
    };
};