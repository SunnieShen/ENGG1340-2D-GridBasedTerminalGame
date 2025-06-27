#include "game_state.h"
#include "input.h"
#include "grid.h"
#include "game_logic.h"
#include "render.h"
#include "ui.h"
#include "utils.h"
#include <thread>
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {
    srand(time(nullptr));  // Seed the random number generator

    showStartScreen(); // Display the start screen
    initGrid(); // Initialize the game grid
 
    auto lastUpdate = steady_clock::now();
    auto lastDraw = steady_clock::now();
    auto magnetStartTime = steady_clock::now();
    int row_num = 0;

    magnet_row = rand() % 6 + 15; // Randomly generate the first row
    change_drct = rand() % 7 + 16; // Randomly generate the direction change row
    // Clear the screen and hide the cursor
    cout << "\033[2J\033[?25l";  

    thread inputHandler(inputThread); // Start the input thread

    // Main game loop
    // The game will run until the running flag is set to false
    // The game will also show exit stats if the showExitStats flag is set to true
    while (running) {
        auto now = steady_clock::now();

        processInput();

        if (isMagnetic && duration_cast<seconds>(now - magnetStartTime).count() >= 60) {
            isMagnetic = false;
            drct_status = 0;
        }

        if (duration_cast<milliseconds>(now - lastUpdate).count() >= UPDATE_INTERVAL_MS) {
            switch(drct_status) {
                case 0: shiftRowsDown(); break;
                case 1: shiftRowsUp(); break;
                case 2: shiftColsLeft(); break;
                case 3: shiftColsRight(); break;
            }

            row_num++;
            generateNewRow(row_num);
            checkCollisions();
            lastUpdate = now;
        }

        if (duration_cast<milliseconds>(now - lastDraw).count() >= DRAW_INTERVAL_MS) {
            updateScore();
            draw();
            lastDraw = now;
        }

        this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    cout << "\033[?25h"; 

    if (showExitStats) {
        showExitStatsScreen();
    }

    if (inputHandler.joinable()) {
        inputHandler.join();
    }

    return 0;
}
