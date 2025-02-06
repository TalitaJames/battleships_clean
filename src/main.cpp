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
        for(T element : line){
            std::cout << element << ", ";
        }
        std::cout << "}\n";
    }
        std::cout << std::endl;
}


int main(int argc, char* args[]) {
    Board board = rndBoard();

    int i = 0;

    std::vector<std::vector<ShipPosition>> allSingleShipPositions;
    for(size_t i =0; i < FLEET_SIZE; i++){
        allSingleShipPositions[i] = singleShipPositions(BOARD_SIZE, FLEET[i]);
	}

    std::function<bool(std::vector<ShipPosition>)> shipFilter = areShipsValid;

    // Now compile them all
    std::vector<std::vector<ShipPosition>> resultFiltered = cartesianProduct(allSingleShipPositions[0], allSingleShipPositions[1], shipFilter);
    printf("Started with %li combinations\n", resultFiltered.size());

    for(size_t i = 2; i < FLEET_SIZE; i++){
        resultFiltered = cartesianProduct(resultFiltered, allSingleShipPositions[i], shipFilter);
        printf("Added %li and now there are %li combinations\n", i, resultFiltered.size());
	}

    printf("\n\nTotal boards:%li\n", resultFiltered.size());

    return 0;
}


