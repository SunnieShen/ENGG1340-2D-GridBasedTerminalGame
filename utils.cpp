#include "utils.h"
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Read history scores from a file and return them as a vector
// If the file does not exist or is empty, return an empty vector
// If there are more than 10 scores, keep only the last 10
// The scores are stored in a file named "history.txt"
vector<int> readHistoryScores() {
    vector<int> scores;
    ifstream file("history.txt");
    
    if (file) {
        int score;
        while (file >> score) {
            scores.push_back(score);
        }
        
        if (scores.size() > 10) {
            scores.erase(scores.begin(), scores.end() - 10);
        }
    }
    
    return scores;
}

// Save the current score to a file
// If the file does not exist, create it
// If the file is full (more than 10 scores), remove the oldest score
void saveCurrentScore(int currentScore) {
    vector<int> history = readHistoryScores();
    history.push_back(currentScore);
    
    if (history.size() > 10) {
        history.erase(history.begin());
    }
    
    ofstream file("history.txt");
    if (file) {
        for (int score : history) {
            file << score << "\n";
        }
    }
}
