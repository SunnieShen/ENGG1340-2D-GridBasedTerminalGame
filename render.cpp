#include "render.h"
#include "game_state.h"
#include <iostream>
#include <string>
 
using namespace std;
 
void updateScore() {
    // Clear the old score and display the new score
    cout << "\033[1;32H" << "\033[1mScoreboard\033[0m" << endl;
    cout << "\033[2;31H" << "+----+----+" << endl;
     
    cout << "\033[3;32H" << "Score:      ";
    cout << "\033[3;32H" << "Score: " << score << ' ' << endl;
     
    cout << "\033[4;32H" << "\033[32mCoin:\033[0m       ";
    cout << "\033[4;32H" << "\033[32mCoin:\033[0m  " << coin << endl;
     
    cout << "\033[5;32H" << "\033[31mBomb:\033[0m       ";
    cout << "\033[5;32H" << "\033[31mBomb:\033[0m  " << bomb << endl;
     
    cout << "\033[6;31H" << "+----+----+" << endl;
}
 
void draw() {
    string buffer; 
    buffer.reserve(HEIGHT * (WIDTH * 2 + 1)); 
     
    buffer += "\033[1;1H+---------------------------+\n";
 
    for (int y = 0; y < HEIGHT; y++) {
        buffer += " ";
         
        for (int x = 0; x < WIDTH; x++) {
            bool replaceWithX = false;
             
            if (visionBlockedMode) { // if vision block mode is on
                // Check the direction of the player
                // and determine which cells to replace with 'X'
                // The player is at (playerX, playerY)
                // and the direction is given by drct_status
                // 0: down, 1: up, 2: left, 3: right
                // Check the cells around the player
                // and replace them with 'X' if they are in the vision block area
                switch (drct_status) {
                    case 0:  
                        if (y == playerY - 2 || y == playerY - 3)
                            replaceWithX = true;
                        else if (x == playerX - 2 || x == playerX + 2 || 
                                x == playerX - 3 || x == playerX + 3)
                            replaceWithX = true;
                        break;
                         
                    case 1:  
                        if (y == playerY + 2 || y == playerY + 3)
                            replaceWithX = true;
                        else if (x == playerX - 2 || x == playerX + 2 || 
                                x == playerX - 3 || x == playerX + 3)
                            replaceWithX = true;
                        break;
                         
                    case 2:  
                        if (x == playerX - 2 || x == playerX - 3)
                            replaceWithX = true;
                        else if (y == playerY - 2 || y == playerY + 2 || 
                                y == playerY - 3 || y == playerY + 3)
                            replaceWithX = true;
                        break;
                         
                    case 3:  
                        if (x == playerX + 2 || x == playerX + 3)
                            replaceWithX = true;
                        else if (y == playerY - 2 || y == playerY + 2 || 
                                y == playerY - 3 || y == playerY + 3)
                            replaceWithX = true;
                        break;
                }
            }
 
            if (x == playerX && y == playerY) {
                buffer += "\033[33mP\033[0m ";
            } else if (replaceWithX) {
                buffer += "X ";
            } else {
                switch (grid[y][x]) {
                    case '$': 
                        buffer += "\033[32m$\033[0m ";
                        break;
                    case '*': 
                        buffer += "\033[31m*\033[0m ";
                        break;
                     case '&': 
                         buffer += "\033[36m&\033[0m "; 
                         break;
                    case 'U': 
                        buffer += "\033[34m↑\033[0m "; 
                        break;
                    case 'L': 
                        buffer += "\033[34m←\033[0m ";
                        break;
                    case 'R': 
                        buffer += "\033[34m→\033[0m ";
                        break;
                    default: 
                        buffer += ". ";
                }
            }
        }
        buffer += "\n"; 
    }
     
    buffer += "\033[16;1H+---------------------------+";
     
    cout << buffer << flush; // Output the buffer
}
