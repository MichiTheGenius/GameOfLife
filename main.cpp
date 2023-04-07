#include <iostream>
#include <SFML/Graphics.hpp>
#include "cell.h"
using namespace std;

int main()
{
    const int SCREEN_SIZE = 800;
    const int CELL_SIZE = 10;
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Conway's Game of Life");

    const int CELL_COUNT = SCREEN_SIZE / CELL_SIZE;
    Cell cells[CELL_COUNT][CELL_COUNT];

    for (int i = 0; i < CELL_COUNT; i++)
    {
        for (int j = 0; j < CELL_COUNT; j++)
        {
            cells[i][j].set_size(CELL_SIZE - 1);
            cells[i][j].set_position(j*CELL_SIZE, i*CELL_SIZE);
        }
    }

    cells[0][1].is_alive = true;
    cells[0][2].is_alive = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear();
        for (int i = 0; i < CELL_COUNT; i++)
        {
            for (int j = 0; j < CELL_COUNT; j++)
            {
                cells[i][j].draw(window);
            }
        }
        window.display();
    }
    return 0;
}