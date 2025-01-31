#include <stdio.h>
#include <stdbool.h>
#include <string>

#include "ships.h"
#include "board.h"

extern int threadCount;
extern bool verbose;
extern std::string codeVersion;

int main(int argc, char* args[]) {
    Board b = rndBoard();

    BoardDimensions bTen = {10, 10};

    return 0;
}


