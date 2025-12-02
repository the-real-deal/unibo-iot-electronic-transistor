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
    Difficulty difficulty;
};

/*
 * Function that initializes the Game structure
 * Parameters:
 *  - const unsigned long seed: seed for random number generation
 * Returns:
 *  - Game: initialized Game structure
 */
Game setupGame(const unsigned long seed);

/*
 * Function that changes the difficulty of the game
 * Parameters:
 *  - Game &game: reference to the Game structure
 *  - Difficulty d: new difficulty level
 */
void changeDifficulty(Game &game, Difficulty d);

/*
 * Function that generates a new code.
 * Parameters:
 * - Game &game: reference to the Game structure
 */
void generateCode(Game &game);

/*
 * Function that reduces the available time according to the difficulty
 * Parameters:
 * - Game &game: reference to the Game structure
 */
bool reduceTime(Game &game);

/*
 * Function that adds a digit to the current answer
 * Parameters:
 * - Game &game: reference to the Game structure
 * - int d: digit to add
 */
void addDigit(Game &game, int d);

/*
 * Function that checks if the current answer is correct
 * Parameters:
 * - Game &game: reference to the Game structure
 * Returns:
 * - bool: true if the answer is correct, false otherwise
 */
bool checkAnswer(Game &game);

/*
 * Function that resets the game state
 * Parameters:
 * - Game &game: reference to the Game structure
 */
void reset(Game &game);

#endif