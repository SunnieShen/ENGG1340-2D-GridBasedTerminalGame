#include "ui.h"
#include "game_state.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

// show the start screen and get user input for difficulty
void showStartScreen() { 
    cout << "\033[2J\033[H"; 
    cout << "--------------------------------\n";
    cout << "         Welcome to Game!       \n";
    cout << "--------------------------------\n";
    cout << "  Controls:\n";
    cout << "    W - Move Up\n";
    cout << "    S - Move Down\n";
    cout << "    A - Move Left\n";
    cout << "    D - Move Right\n";
    cout << "    Q - Quit Game\n";
    cout << "--------------------------------\n";
    cout << "Select Difficulty:\n";
    cout << "  1 - Easy\n";
    cout << "  2 - Medium\n";
    cout << "  3 - Hard\n";
    cout << "--------------------------------\n";
    cout << "Press the corresponding number to select difficulty...\n";

    char difficulty;
    while (true) {
        cin >> difficulty;
        if (difficulty == '1') {
            UPDATE_INTERVAL_MS = 600;
            DRAW_INTERVAL_MS = 50;
            break;
        } else if (difficulty == '2') {
            UPDATE_INTERVAL_MS = 400;
            DRAW_INTERVAL_MS = 50;
            break;
        } else if (difficulty == '3') {
            UPDATE_INTERVAL_MS = 300;
            DRAW_INTERVAL_MS = 50;
            break;
        } else {
            cout << "Invalid selection. Please choose 1, 2, or 3.\n";
        }
    }

    cout << "Press Enter to start...\n";
    cin.ignore();
    cin.get();
}

// save the current score to a file (keep only the last 10 scores)
void showExitStatsScreen() {
    vector<int> history = readHistoryScores();
    int historyMax = 0;
    if (!history.empty()) {
        historyMax = *max_element(history.begin(), history.end());
    }

    bool isNewRecord = (score > historyMax);
    saveCurrentScore(score);

    cout << "\033[2J\033[H"  
         << "--------------------------------\n"
         << "  You have gained \033[32m" << coin << "\033[0m coins\n"
         << "  Encountered \033[31m" << bomb << "\033[0m bombs\n"
         << "  Final score: \033[33m" << score << "\033[0m\n";

    if (isNewRecord) {
        cout << "  \033[1;32mNEW RECORD!\033[0m\n";
    } else {
        cout << "  History highest score: \033[33m" << historyMax << "\033[0m\n";
    }

    cout << "--------------------------------\n"
         << "      Thanks for playing!\n"
         << "--------------------------------\n";

    this_thread::sleep_for(chrono::milliseconds(1500));
}
