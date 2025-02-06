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

bool intFilter(std::vector<int> input){
    return input[0] % 2;
}

template <typename T>
void printDoubleVector(std::vector<std::vector<T>> in){
    for(std::vector<T> line : in){
        std::cout << "{";
        for (size_t i = 0; i < line.size(); i++){
            std::cout << line[i];
            if (i != line.size()-1){
                std::cout << ", ";
            }
        }
        std::cout << "}\n";
    }
    std::cout << std::endl;
}


int main(int argc, char* args[]) {
    Board board = rndBoard();

    std::function<bool(std::vector<ShipPosition>)> shipFilter = areShipsValid;
    auto allSingleShipPositions = allShipPositions(BOARD_SIZE, FLEET, FLEET_SIZE);

    // Now compile them all
    std::vector<std::vector<ShipPosition>> resultFiltered = cartesianProduct(allSingleShipPositions, shipFilter);
    printf("Started with %li combinations\n", resultFiltered.size());

    printf("\n\nTotal boards:%li\n", resultFiltered.size());
    printf("CODE DONE\n");

    return 0;
}


