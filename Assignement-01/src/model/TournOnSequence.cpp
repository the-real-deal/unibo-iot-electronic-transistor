#include "TournOnSequence.h"
#include <stdlib.h>
// #include <Arduino.h>
// #include <ctime>

#define CODE_LENGTH 4
#define SHUFFLE_COUNT 16

Game setupGame()
{
    // srand(time(0)); find an alternative for embedded systems
    Game g = {
        GameState::MENU,
        {1, 2, 3, 4},
        0,
        10000,
        {0, 0, 0, 0},
        250,
        0};

    return g;
}

void changeDifficulty(Game &game, Difficulty d)
{
    switch (d)
    {
    case Difficulty::EASY:
        game.reductionFactor = 250;
        break;
    case Difficulty::MEDIUM:
        game.reductionFactor = 500;
        break;
    case Difficulty::DIFFICULT:
        game.reductionFactor = 750;
        break;
    case Difficulty::HARD:
        game.reductionFactor = 1000;
        break;
    default:
        break;
    }
}

void shuffle(int *code, int length)
{
    for (int i = 0; i < SHUFFLE_COUNT; i++)
    {
        int tmp = code[i % length];
        int shuffle_idx = rand() % length;
        code[i % length] = code[shuffle_idx];
        code[shuffle_idx] = tmp;
    }
}

void generateCode(Game &game)
{
    shuffle(game.code, CODE_LENGTH);
}

bool reduceTime(Game &game)
{
    if (game.maxTime > game.reductionFactor)
    {
        game.maxTime -= game.reductionFactor;
        return true;
    }
    return false;
}

void addDigit(Game &game, int d)
{
    if (game.answerLength < CODE_LENGTH)
    {
        game.answer[game.answerLength] = d;
        game.answerLength++;
    }
}

bool checkAnswer(Game &game)
{
    /* Can either check at each addiction or all at the end*/
    for (int i = 0; i < game.answerLength; i++)
    {
        if (game.code[i] != game.answer[i])
        {
            return false;
        }
    }

    if (game.answerLength == CODE_LENGTH)
        game.answerLength = 0;

    return true;
}

void reset(Game &game)
{
    game.answerLength = 0;
    game.score = 0;
    game.maxTime = 10000;
    game.state = GameState::MENU;
}