#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <atomic>

constexpr int WIDTH = 14;
constexpr int HEIGHT = 14;
constexpr int PLAY_AREA_MIN = 0;
constexpr int PLAY_AREA_MAX = 13;

extern char grid[HEIGHT][WIDTH];
extern int drct_status;
extern int coord[2][4];
extern int playerX, playerY;
extern int score, coin, bomb, magnet_row, change_drct, baseline, change_coin;
extern bool visionBlockedMode;
extern std::atomic<bool> running;
extern std::atomic<char> inputKey;
extern std::atomic<bool> showExitStats;
extern std::atomic<bool> isMagnetic;
extern int UPDATE_INTERVAL_MS;
extern int DRAW_INTERVAL_MS;

#endif
