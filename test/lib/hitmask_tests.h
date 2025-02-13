#ifndef HITMASK_TESTS_H
#define HITMASK_TESTS_H

#include "hitmask.h"
#include "test_utils.h"

bool TEST_HITMASK_initHitmask();
bool TEST_HITMASK_hitBoard();
bool TEST_HITMASK_findHitmaskDifference();
bool TEST_HITMASK_howManyTurnsTaken();
bool TEST_HITMASK_checkCompatible();
bool TEST_HITMASK_turnsToShotmask();

bool TEST_HITMASK_isHitmaskSolved();
bool TEST_HITMASK_isHit();
bool TEST_HITMASK_operatorEqual();

#endif //HITMASK_TESTS_H