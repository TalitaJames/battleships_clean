/**
 * @file
 * @author Talita
 * @brief Interaction between the cartesian product and board states to generate all boards
 *
 * @date 2025-02-10
 */
#ifndef CARTESIANPRODUCTSHIPPOSITIONS_H
#define CARTESIANPRODUCTSHIPPOSITIONS_H

#include <vector>

#include "ships.h"
#include "probabilityGrid.h"
#include "vector_utils.h"
#include "cartesianProduct.h"


// Iterate thru a vector of vector of ship positions and make probGrid
void makeProbGridFromVectorOfShipPositions(ProbabilityGrid&, std::vector<std::vector<ShipPosition>>);
std::vector<std::vector<int>> generateMemoryDivisionVector(int memoryDivisions, int fleetSize);

// Group of functions to generate all possible boards and store them in memory, then calculate the probability of each cell
ProbabilityGrid makeProbGridFromCartesianProductOfAllShipPositions();
ProbabilityGrid makeProbGridFromCartesianProductOfAllShipPositions(int memoryDivisions);
ProbabilityGrid makeProbGridFromCartesianProductOfAllShipPositions(int boardSize, const ShipData fleet[], const int fleetSize);
ProbabilityGrid makeProbGridFromCartesianProductOfAllShipPositions(int boardSize, const ShipData fleet[], const int fleetSize, int memoryDivisions);


// The "Karl method" of having all
void todoKarlMethod(std::vector<std::vector<ShipPosition>>);


#endif //CARTESIANPRODUCTSHIPPOSITIONS_H