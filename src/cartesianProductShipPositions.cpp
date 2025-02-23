#include "cartesianProductShipPositions.h"

/**
 * @brief For a vector of ship positions, turn them into a a probability grid
 *
 * @param probGrid the probability grid to be filled
 * @param shipPositions a vector of "boards" (in the form of a vector of ship positions)
 */
void makeProbGridFromVectorOfShipPositions(ProbabilityGrid &probGrid, std::vector<std::vector<ShipPosition>> shipPositions){

    Board board = initBlankBoard();

    for (std::vector<ShipPosition> shipPosVector : shipPositions){
        ShipPosition shipPosArray[shipPosVector.size()];
        shipVectorToArray(shipPosVector, shipPosArray, shipPosVector.size());

        drawBoard(board, shipPosArray, shipPosVector.size());
        if(!board.isValid) std::cout << "ERROR BOARD INVALID" << std::endl;

        flattenBoardToProbabilityGrid(board, probGrid);
    }
}

/**
 * @brief make a vector used to generate all the
 * different permutations of ship positions
 *
 * @param memoryDivisions numbers from [0, memoryDivisions) in the inner vector ie 3 would return {0,1,2}
 * @param fleetSize size of the outer vector, ie how many coppies of baseRow
 * @return std::vector<std::vector<int>> a vector fleetSize long containing all numbers [0, memoryDivisions) at each element,
 * ie for 3, 2 the output is {{0,1,2}, {0,1,2}}
 */
std::vector<std::vector<int>> generateMemoryDivisionVector(int memoryDivisions, int fleetSize) {
    // Create a single row with values from 0 to memoryDivisions-1
    std::vector<int> baseRow(memoryDivisions);
    for (int j = 0; j < memoryDivisions; ++j) {
        baseRow[j] = j;
    }

    // Replicate the same row fleetSize times
    return std::vector<std::vector<int>>(fleetSize, baseRow);
}

/**
 * @brief generate in memory all posible boards for a given game state, then calculate the probability of each cell
 *
 * @return a probability grid with all possible boards for the given fleet
 */
ProbabilityGrid makeProbGridFromCartesianProductOfAllShipPositions(){
    return makeProbGridFromCartesianProductOfAllShipPositions(1);
}

/**
 * @brief generate in memory all posible boards for a given game state, then calculate the probability of each cell
 *
 * @param memoryDivisions how many ways to split the memory (though this technically runs fleetSize^memoryDivisions times)
 * @return a probability grid with all possible boards for the given fleet
 */
ProbabilityGrid makeProbGridFromCartesianProductOfAllShipPositions(int memoryDivisions){
    return makeProbGridFromCartesianProductOfAllShipPositions(BOARD_SIZE, FLEET, FLEET_SIZE, memoryDivisions);
}

/**
 * @brief generate in memory all posible boards for a given game state, then calculate the probability of each cell
 *
 * @param boardSize the size of the board
 * @param fleet the ships to be placed on the board
 * @param fleetSize number of ships in the fleet
 * @return a probability grid with all possible boards for the given fleet
 */
ProbabilityGrid makeProbGridFromCartesianProductOfAllShipPositions(int boardSize, const ShipData fleet[], const int fleetSize){
    return makeProbGridFromCartesianProductOfAllShipPositions(boardSize, fleet, fleetSize, 1);
}

/**
 * @brief generate in memory all posible boards for a given game state, then calculate the probability of each cell
 *
 * @param boardSize the size of the board
 * @param fleet the ships to be placed on the board
 * @param fleetSize number of ships in the fleet
 * @param memoryDivisions how many ways to split the memory (though this technically runs fleetSize^memoryDivisions times)
 * @return a probability grid with all possible boards for the given fleet
 */
ProbabilityGrid makeProbGridFromCartesianProductOfAllShipPositions(int boardSize, const ShipData fleet[], const int fleetSize, int memoryDivisions){

    ProbabilityGrid returnedProbGrid;
    std::function<bool(std::vector<ShipPosition>)> shipFilter = areShipsValidInBoardVector;


    // Sort out memory saving things
    std::vector<std::vector<int>> memoryDivisionSeperated = generateMemoryDivisionVector(memoryDivisions, fleetSize); // a vector fleet size of
    std::vector<std::vector<int>> memoryDivisionPermutations = cartesianProduct(memoryDivisionSeperated); // all permutations of the numbers [0,memoryDivisions) fleetSize times

    //[each ship in the fleet][all valid positions]
    std::vector<std::vector<ShipPosition>> allSingleShipPositions = allShipPositions(boardSize, fleet, fleetSize);
    // return returnedProbGrid; //early testing return

    // [each ship in the fleet][all valid positions][split into n divisions]
    // [which ship in fleet][which subdivision to look in][which specific position]
    std::vector<std::vector<std::vector<ShipPosition>>> allSingleShipPositionsSubDivided;
    for (int i = 0; i < fleetSize; i++){
        allSingleShipPositionsSubDivided.push_back(splitVector(allSingleShipPositions[i], memoryDivisions));
    }

    /*
        for each permutation of individual boards, get the cartesian product
        then sum the probabilities and append to the  returnedProbGrid
    */
    for (auto singlePermutation : memoryDivisionPermutations ){
        std::vector<std::vector<ShipPosition>> specificPermutationOfShipPositions;
        for (size_t i = 0; i < singlePermutation.size(); i++){
            specificPermutationOfShipPositions.push_back(allSingleShipPositionsSubDivided[i][singlePermutation[i]]);
        }

        std::vector<std::vector<ShipPosition>> resultFiltered = cartesianProduct(specificPermutationOfShipPositions, shipFilter);


        makeProbGridFromVectorOfShipPositions(returnedProbGrid, resultFiltered); //FIXME this only gets the last permutation of probGrids
        printf("\nTotal boards:%li", resultFiltered.size());
        std::cout << returnedProbGrid << std::endl;
    }


    return returnedProbGrid;
}