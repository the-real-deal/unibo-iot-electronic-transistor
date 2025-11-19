#ifndef TOURNONSEQUENCE_H
#define TOURNONSEQUENCE_H

#define CODE_LENGTH 4

/*
 * Final State Machine States
 */
enum GameState
{
    MENU,
    GAME,
    GAMEOVER,
    WIN,
    SLEEP
};

/*
 * Game Difficulty Levels
 */
enum Difficulty
{
    EASY = 1,
    MEDIUM,
    DIFFICULT,
    HARD
};

/*
 * Game Structure
 */
struct Game
{
    GameState state;
    int code[CODE_LENGTH];
    int score;
    unsigned maxTime;
    int answer[CODE_LENGTH];
    unsigned reductionFactor;
    int answerLength;
};

/*
 * Function that initializes the Game structure
 */
Game setupGame(const unsigned long seed);

/*
 * Function that changes the difficulty of the game
 */
void changeDifficulty(Game &game, Difficulty d);

/*
 * Function that generates a new code.
 */
void generateCode(Game &game);

/*
 * Function that reduces the available time according to the difficulty
 */
bool reduceTime(Game &game);

/*
 * Function that adds a digit to the current answer
 */
void addDigit(Game &game, int d);

/*
 * Function that checks if the current answer is correct
 */
bool checkAnswer(Game &game);

/*
 * Function that resets the game state
 */
void reset(Game &game);

#endif