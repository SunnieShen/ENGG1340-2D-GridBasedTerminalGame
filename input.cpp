#include "input.h"
#include "game_state.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <atomic>
#include <cctype>
using namespace std;
 
struct termios original_settings; // Store original terminal settings


void enableRawMode() { // Enable raw mode for keyboard input
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    original_settings = term;
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}
 
void disableRawMode() { // Disable raw mode
    tcsetattr(STDIN_FILENO, TCSANOW, &original_settings);
}
 
void processInput() { // Process keyboard input
    char key = inputKey.exchange(0);
    switch (tolower(key)) {
        case 'w': if ((drct_status > 1) && (playerY > PLAY_AREA_MIN)) playerY--; break;
        case 's': if ((drct_status > 1) && (playerY < PLAY_AREA_MAX)) playerY++; break;
        case 'a': if ((drct_status < 2) && (playerX > PLAY_AREA_MIN)) playerX--; break;
        case 'd': if ((drct_status < 2) && (playerX < PLAY_AREA_MAX)) playerX++; break;
        case 'q':
            running = false;
            showExitStats = true;
            break;
    }
}
 
void inputThread() { // Read input from keyboard in a separate thread
    enableRawMode();
    while (running) {
        char ch = 0;
        if (read(STDIN_FILENO, &ch, 1) > 0) {
            inputKey.store(ch);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    disableRawMode();
}
