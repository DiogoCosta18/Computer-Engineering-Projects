#pragma once
#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <fstream>
#include <string>

class HighScoreManager {
public:
    HighScoreManager();
    void loadHighScore();
    void saveHighScore(int score);
    int getHighScore() const;

private:
    int highScore;

};

#endif // HIGHSCOREMANAGER_H