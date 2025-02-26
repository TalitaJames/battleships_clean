/**
 * @file
 * @author Talita
 * @brief Generating, counting and applying symmetries to boards
 * @date 2025-02-24
 */
#ifndef SYMMETRIES_TESTS_H
#define SYMMETRIES_TESTS_H

#include "symmetries.h"
#include "test_utils.h"

bool TEST_SYMMETRIES_rotateBoard90();
bool TEST_SYMMETRIES_rotateBoard180();
bool TEST_SYMMETRIES_rotateBoard270();

bool TEST_SYMMETRIES_flipBoardX();
bool TEST_SYMMETRIES_flipBoardY();
bool TEST_SYMMETRIES_flipBoardXY();
bool TEST_SYMMETRIES_flipBoardYX();

bool TEST_SYMMETRIES_applySymmetry();



#endif //SYMMETRIES_TESTS_H
