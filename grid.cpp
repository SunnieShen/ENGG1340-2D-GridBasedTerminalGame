#include "grid.h"
#include "game_state.h"
#include <numeric>
#include <random>
#include <algorithm>
#include <chrono>
#include <vector>
#include <iostream>
#include <unistd.h>
 
using namespace std;
 
void initGrid() { // Initialize the game area
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            grid[i][j] = ' ';
}
 
void generateNewRow(int row_num) {
    static int coin_row = 0, bomb_row = 0;
    vector<int> positions(WIDTH);
    iota(positions.begin(), positions.end(), 0);
     
    // Randomly shuffle the positions
    // Use a random device to seed the random number generator
    // and shuffle the positions vector
    random_device rd;
    mt19937 g(rd() ^ static_cast<unsigned int>(
        chrono::system_clock::now().time_since_epoch().count()));
     
    shuffle(positions.begin(), positions.end(), g);
 
    if (drct_status > 1) {  // Down or Up
        for (int i = 0; i < 4; i++) {
            coord[0][i] = positions[i];
            coord[1][i] = baseline;
        }
    } else if (drct_status < 2) {  // Left or Right
        for (int i = 0; i < 4; i++) {
            coord[1][i] = positions[i];
            coord[0][i] = baseline;
        }
    }
 
    fill_n(grid[baseline], WIDTH, ' '); 
 
    if (coin_row == row_num % 7) { // randomly generate coins
        grid[coord[0][0]][coord[1][0]] = '$';
        static mt19937 gen(random_device{}());
        uniform_int_distribution<int> dist(0, 6);
        coin_row = dist(gen);
    }
 
    if (bomb_row == row_num % 2) { // randomly generate bombs
        grid[coord[0][1]][coord[1][1]] = '*';
        static mt19937 gen(random_device{}());
        uniform_int_distribution<int> dist(0, 1);
        bomb_row = dist(gen);
    }
 
    if (row_num == magnet_row) { // randomly generate magnets
        grid[coord[0][2]][coord[1][2]] = '&';
    }
 
    if (change_drct == row_num && drct_status == 0) { // randomly generate mode of flows
        const char drct[] = { 'L', 'R', 'U' };
        static mt19937 gen(random_device{}());
        uniform_int_distribution<int> dist(0, 2);
        grid[coord[0][3]][coord[1][3]] = drct[dist(gen)];
    }
 
    if (change_coin == 5) {
        // If 5 coins are collected, return to land
        baseline = 0;
        playerY = 13;
        
        cout<<"\033[9;30H"<<"                                                 "<<"\033[10;30H"<<"                                                      "<<endl;
        cout<<"\033[8;30H"<<"\033[34mBack to land!              \033[0m"<<endl;
        sleep(1.5);
        cout<<"\033[8;30H"<<"                                                                                                                 "<<endl;

        drct_status = 0; 
        change_coin = 0;
        change_drct = rand() % 7 + row_num;
    }
 
    if (drct_status == 0) {
        playerY = 13;
    }
}
 
void shiftRowsDown() { // Shift all rows down
    for (int i = HEIGHT - 1; i > 0; i--) {
        copy(begin(grid[i - 1]), end(grid[i - 1]), begin(grid[i]));
    }
}
 
void shiftRowsUp() { // Shift all rows up
    for (int i = 0; i < HEIGHT - 1; i++) {
        copy(begin(grid[i + 1]), end(grid[i + 1]), begin(grid[i]));
    }
}
 
void shiftColsRight() { // Shift all columns right
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = WIDTH - 1; x > 0; x--) {
            grid[y][x] = grid[y][x - 1];
        }
        grid[y][0] = ' ';
    }
}
 
void shiftColsLeft() { // Shift all columns left
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH - 1; x++) {
            grid[y][x] = grid[y][x + 1];
        }
        grid[y][WIDTH - 1] = ' ';
    }
}
