#include "Game.h"
int main()
{
    //Initialize Random Seed
    srand(static_cast<unsigned>(time(0)));

    //Initialize Game Object
    Game game;

    //Game Loop
    while(game.running())
    {
        game.update();
        game.render();
    }

    // End of application 
    return 0;
}