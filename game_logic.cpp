#include "game_logic.h"
#include "game_state.h"
#include <iostream>
#include <unistd.h>

using namespace std;

// check collisions
void checkCollisions() {
    switch (grid[playerY][playerX]) {
        case '*': // when collide with bomb
            drct_status != 0 ? score -= 2 : score--; 
            bomb++;
            grid[playerY][playerX] = ' ';
            if (bomb >= 5) { // Activate vision blocked mode
                visionBlockedMode = true;
                cout<<"\033[12;31H" <<"\033[30mOops! Vision Block Mode!\033[0m";
                cout<<"\033[13;31H"<<"\033[30mOne coin = one bomb removed.\033[0m";
                cout<<"\033[14;31H"<<"\033[30mCollect them to lift the block!\033[0m"<<endl;
            }
            break;
        
        case '$': 
            if (visionBlockedMode) {
                if (bomb > 0){
                    bomb--; // Remove a bomb
                    if (drct_status != 0) change_coin++; // Increment change coin if not in down direction
                }
                if (bomb == 0) {
                    visionBlockedMode = false; // Exit vision blocked mode
                    cout<<"\033[12;31H"<<"                                                                                            "<<endl;
                    cout<<"\033[13;31H"<<"                                                                                           "<<endl;
                    cout<<"\033[14;31H"<<"\033[32mYou have lifted the block successfully!:)\033[0m"<<endl;
                    sleep(2);
                    cout<<"\033[14;31H"<<"                                                                                            "<<endl;
                }
                grid[playerY][playerX] = ' ';
            } 
            else {
                drct_status != 0 ? change_coin++, score += 2 : score++;
                coin++;
                grid[playerY][playerX] = ' '; 
            }
            break;
        
        case '&': // activate magnet
            magnet();
            isMagnetic = true; // Set magnetic state
            break;
        case 'U': // change to underflow mode
            grid[playerY][playerX] = ' ';
            baseline = 13;
            playerY = 0;
            drct_status = 1;
            cout<<"\033[8;31H"<<"\033[34mUpperFlow!"<<"\033[9;31H"<<"Coins worth 2 points!"<<"\033[10;31H"<<"5 coins return you to land!\033[0m"<<endl;
            break;
        case 'L': // change to leftflow mode
            grid[playerY][playerX] = ' ';
            baseline = 13;
            playerX = 0;
            drct_status = 2;
            cout<<"\033[8;31H"<<"\033[34mLeftFlow!"<<"\033[9;31H"<<"Coins worth 2 points!"<<"\033[10;31H"<<"5 coins return you to land!\033[0m"<<endl;
            break;
        case 'R': // change to rightflow mode
            grid[playerY][playerX] = ' ';
            baseline = 0;
            playerX = 13;
            drct_status = 3;
            cout<<"\033[8;31H"<<"\033[34mRightFlow!"<<"\033[9;31H"<<"Coins worth 2 points!"<<"\033[10;31H"<<"5 coins return you to land!\033[0m"<<endl;
            break;
    }
}

// magnet function
void magnet() {
    int magnet_coin = 0;
    for (int y = 5; y < 14; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x] == '$') 
            {
                score++;
                coin++;
                magnet_coin++;
                grid[y][x] = ' ';
            }
        }
    }
    cout << "\033[15;31H" << "\033[32mMagnet grabbed! "<<endl;
    cout << "\033[16;31H" << magnet_coin << " coins collected from the first three rows!\033[0m" << endl;
    sleep(1.8);
    cout << "\033[15;31H" << "                                                                                              "<<endl;
    cout << "\033[16;31H" << "                                                                                              "<<endl;
}
