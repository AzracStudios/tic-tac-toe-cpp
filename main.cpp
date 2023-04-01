#include <iostream>
#include "tictactoe.hpp"

using namespace tictactoe;

int read(std::string input)
{
    std::cout << input;
    int inp;
    std::cin >> inp;

    return inp;
}

int main()
{
    Game game = Game();

    int side = read("\nChoose side [X: 1 | O: 0] ");

    if (side != 0 && side != 1)
    {
        std::cout << "Invalid side! Exiting..." << std::endl;
        return 1;
    }

    game.start(side, !side);

    while (true)
    {
        game.print_board();
        int spot = read("Choose spot [1 - 9]: ");
        game.update(spot);
    }
};