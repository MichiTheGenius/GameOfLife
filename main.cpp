#include <iostream>
#include <random>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "cell.h"
using namespace std;

const int SCREEN_SIZE = 600;
const int CELL_SIZE = 4;
const int CELL_COUNT = SCREEN_SIZE / CELL_SIZE;

int get_neighbor_count(int cell_row, int cell_col, Cell cells[CELL_COUNT][CELL_COUNT]);

int main()
{
    srand(getpid());

    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Conway's Game of Life");

    window.setFramerateLimit(30);

    Cell cells[CELL_COUNT][CELL_COUNT];

    for (int row = 0; row < CELL_COUNT; row++)
    {
        for (int col = 0; col < CELL_COUNT; col++)
        {
            cells[row][col].set_size(CELL_SIZE - 1);
            cells[row][col].set_position(col * CELL_SIZE, row * CELL_SIZE);
        }
    }


    for (int row = 0; row < CELL_COUNT; row++)
    {
        for (int col = 0; col < CELL_COUNT; col++)
        {
            if(rand() % 5 == 1) // 1/5 chance that a cell will be alive
            {
                cells[row][col].is_alive = true;
            }
        }
    }

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

        // go through each cell
        // check the neighbor count
        // apply the rules of John Conway
        // set the value of the will_be_alive variable
        // reason: all of the cells have to be updated all at once per turn

        for (int row = 0; row < CELL_COUNT; row++)
        {
            for (int col = 0; col < CELL_COUNT; col++)
            {
                // rules are from the Wikipedia page of Conway's game of life
                // https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

                int neighbor_count = get_neighbor_count(row, col, cells);
                Cell *current_cell = &cells[row][col];

                if (current_cell->is_alive)
                {
                    // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
                    if (neighbor_count < 2)
                    {
                        current_cell->will_be_alive = false;
                    }

                    // Any live cell with two or three live neighbours lives on to the next generation.
                    else if (neighbor_count == 2 || neighbor_count == 3)
                    {
                        current_cell->will_be_alive = true;
                    }

                    // Any live cell with more than three live neighbours dies, as if by overpopulation.
                    else if (neighbor_count > 3)
                    {
                        current_cell->will_be_alive = false;
                    }
                }
                else if (!current_cell->is_alive)
                {
                    // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
                    if (neighbor_count == 3)
                    {
                        current_cell->will_be_alive = true;
                    }
                }
            }
        }

        // after that go through all of the cells again and update the is_alive variable with the
        // value of the will_be_alive variable
        for (int row = 0; row < CELL_COUNT; row++)
        {
            for (int col = 0; col < CELL_COUNT; col++)
            {
                Cell *current_cell = &cells[row][col];

                if (current_cell->will_be_alive)
                {
                    current_cell->is_alive = true;
                }
                else
                {
                    current_cell->is_alive = false;
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

int get_neighbor_count(int cell_row, int cell_col, Cell cells[CELL_COUNT][CELL_COUNT])
{
    int count = 0;

    // check all of the neighbors of a given cell
    // left, right, up, down, diagonal can be neighbors
    // check each cell whether it is on the edge of the map
    // a cell at the very top for example can't have a neighbor above it!

    if (cell_row > 0)
    {
        if (cells[cell_row - 1][cell_col].is_alive) // north
        {
            count += 1;
        }

        if (cell_col < CELL_COUNT - 1)
        {
            if (cells[cell_row - 1][cell_col + 1].is_alive) // northeast
            {
                count += 1;
            }
        }
    }

    if (cell_col < CELL_COUNT - 1)
    {
        if (cells[cell_row][cell_col + 1].is_alive) // east
        {
            count += 1;
        }
        if (cell_row < CELL_COUNT - 1)
        {
            if (cells[cell_row + 1][cell_col + 1].is_alive) // southeast
            {
                count += 1;
            }
        }
    }

    if (cell_row < CELL_COUNT - 1)
    {
        if (cells[cell_row + 1][cell_col].is_alive) // south
        {
            count += 1;
        }
        if (cell_col > 0)
        {
            if (cells[cell_row + 1][cell_col - 1].is_alive) // southwest
            {
                count += 1;
            }
        }
    }

    if (cell_col > 0)
    {
        if (cells[cell_row][cell_col - 1].is_alive) // west
        {
            count += 1;
        }
        if (cell_row > 0)
        {
            if (cells[cell_row - 1][cell_col - 1].is_alive) // northwest
            {
                count += 1;
            }
        }
    }

    return count;
}