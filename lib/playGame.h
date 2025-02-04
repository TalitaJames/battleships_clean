#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <chrono>

#include "board.h"
#include "hitmask.h"
#include "probabilityGrid.h"
#include "coordinateChooser.h"
#include "json/json.h"
#include "json/json_utils.h"

//TODO add testcases
void takeTurn(CoordinateChooser playStyle, Board board, Hitmask &hitmask, ProbabilityGrid &, int &, int &, Json::Value &);

unsigned int playGame_fromStart(CoordinateChooser playStyle, Board board);
unsigned int playGame_fromStart(CoordinateChooser playStyle, Board board, Json::Value &gamePlayHistory);

unsigned int playGame_fromHitmask(CoordinateChooser playStyle, Board board, Hitmask hitmask);
unsigned int playGame_fromHitmask(CoordinateChooser playStyle, Board board, Hitmask hitmask, Json::Value &gamePlayHistory);

unsigned int saveGame(CoordinateChooser playStyle, Board board);
void repeatGames(CoordinateChooser, unsigned int);

#endif //PLAYGAME_H