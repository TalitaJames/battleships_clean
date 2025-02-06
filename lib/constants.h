/**
 * @file
 * @author Talita
 * @brief Variables usefull to the whole system
 * @date 2025-02-06
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BOARD_SIZE 10
#define BOARD_DEFAULT -1

typedef unsigned int Ship;
const Ship FLEET[] = {2, 3, 3, 4, 5};
const short FLEET_SIZE = sizeof(FLEET)/sizeof(FLEET[0]);

#define THREAD_COUNT 8
#define CODE_VERSION "V5c"

#define verbose true

#endif //CONSTANTS_H
