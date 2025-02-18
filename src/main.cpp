#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <vector>
#include <stdlib.h>

#include "ships.h"
#include "board.h"
#include "hitmask.h"
#include "probabilityGrid.h"
#include "boardIterator.h"
#include "playGame.h"
#include "cartesianProduct.h"
#include "cartesianProduct_board.h"
#include "vector_utils.h"

void describeState(){
    std::cout << "BOARD_SIZE: " << BOARD_SIZE << "\t";
    std::cout << "FLEET_SIZE: " << FLEET_SIZE << "\t";
    std::cout << "THREAD_COUNT: " << THREAD_COUNT << std::endl;
    std::cout << "verbosity: " << verbose << "\t";
    std::cout << "CODE_VERSION: " << CODE_VERSION << "\t";
    std::cout << "FLEET: {";
    for (size_t i = 0; i < FLEET_SIZE; i++)
        std::cout << (int) FLEET[i] << ", " ;
    std::cout << "\b\b}" << std::endl;
}

int main(int argc, char* args[]) {
    describeState();

    makeProbGridFromCartesianProductOfAllShipPositions(1);


    printf("CODE DONE\n");

    return 0;
}


