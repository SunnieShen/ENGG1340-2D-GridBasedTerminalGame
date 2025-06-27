#include "game_state.h"

char grid[HEIGHT][WIDTH];
int drct_status = 0; // 0: down, 1: up, 2: left, 3: right
int coord[2][4];
int playerX = 7, playerY = 13;
int score = 0, coin = 0, bomb = 0, magnet_row, change_drct, baseline = 0, change_coin = 0;
bool visionBlockedMode = false; // block vision mode switch
std::atomic<bool> running(true);
std::atomic<char> inputKey(0);
std::atomic<bool> showExitStats(false);
std::atomic<bool> isMagnetic(false); // New flag for magnetic state

int UPDATE_INTERVAL_MS; // define the frequency of the game update (milliseconds)
int DRAW_INTERVAL_MS;   // define the frequency of the game draw (milliseconds)
