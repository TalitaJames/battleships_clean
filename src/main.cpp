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
#include "cartesianProductShipPositions.h"
#include "vector_utils.h"
#include "symmetries.h"

void describeState(){
    std::cout << "BOARD_SIZE: " << BOARD_SIZE << "\t";
    std::cout << "FLEET_SIZE: " << FLEET_SIZE << "\t";
    std::cout << "THREAD_COUNT: " << THREAD_COUNT << std::endl;

    std::cout << "verbosity: " << verbose << "\t";
    std::cout << "CODE_VERSION: " << CODE_VERSION << "\t";
    std::cout << "MAX_REMEMBERED_BOARDS: " << MAX_REMEMBERED_BOARDS << "\t";
    std::cout << "FLEET: {";
    for (size_t i = 0; i < FLEET_SIZE; i++)
        std::cout << (int) FLEET[i] << ", " ;
    std::cout << "\b\b}" << std::endl;
}

int main(int argc, char* args[]) {
    describeState();

    std::vector<CoordinateChooser> playStyles = {
        CoordinateChooser::RND,
        CoordinateChooser::RND_W_PROB,
        CoordinateChooser::P_MAX,
        // CoordinateChooser::P_RND,
        CoordinateChooser::INFOGAIN,
        CoordinateChooser::INFOGAIN_COMBINED,
        CoordinateChooser::DIAGONAL,
    };
    repeatGames(playStyles, 100);

    printf("CODE DONE\n");

    return 0;
}


