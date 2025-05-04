

HighScoreManager::HighScoreManager() : highScore(0) {
    loadHighScore(); // Load high score when manager is created
}

void HighScoreManager::loadHighScore() {
    std::ifstream infile("highscore.txt");
    if (infile.is_open()) {
        infile >> highScore; // Read the high score from the file
        infile.close();
    }
    else {
        highScore = 0; // Default value if file doesn't exist
    }
}

void HighScoreManager::saveHighScore(int score) {
    if (score > highScore) {
        highScore = score; // Update high score if current score is higher
        std::ofstream outfile("highscore.txt");
        if (outfile.is_open()) {
            outfile << highScore; // Write the high score to the file
            outfile.close();
        }
    }
}

int HighScoreManager::getHighScore() const {
    return highScore; // Return the current high score
}