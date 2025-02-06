#include "boardIterator.h"

/**
 * @brief Splits the board sections into a threadCount sized vector of workers
 * @param threadCount the number of sections to create (must be a power of two)
 * @param workerVector vector of workers as a refference (they get updated)
*/
void dividePositions(int threadCount,std::vector<Worker> &workerVector){
    // TODO add capacity for many workers, with ryan's splitting things
    workerVector.clear();
    workerVector.reserve(threadCount);

    ShipPosition positionStart[FLEET_SIZE];
    ShipPosition positionEnd[FLEET_SIZE];
    setStartArray(positionStart);
    setEndArray(positionEnd);

    Worker soloWorker;
    std::copy(positionStart, positionStart+FLEET_SIZE, std::begin(soloWorker.start));
    std::copy(positionEnd, positionEnd+FLEET_SIZE, std::begin(soloWorker.end));
    workerVector.push_back(soloWorker);
};

/**
 * @brief Counts, for a given worker section of boards, the number of boards that match the hitmask
 * @param w a section of boards to check
 * @param hitM the hitmask for board comparisons
 * @param threadID an ID number for debugging
 */
void checkBoards(Worker &w, Hitmask hitM, int threadID){
    Board b = initBlankBoard();

    ShipPosition positionArray[FLEET_SIZE]; // position array
    std::copy(w.start, w.start+FLEET_SIZE, std::begin(positionArray));

    do{ // check all the boards from a workers start to end
        drawBoard(b,positionArray);
        if (b.isValid && checkCompatible(b, hitM)){ // if the board is a good board
            flattenBoardToProbabilityGrid(b,w.sub_probGrid);
        }
        nextShipPosArray(positionArray);
    } while (compareShipArray(positionArray, w.end) == 1); // while the current position array is behind the end

    if (verbose) std::cout << "CheckBoards " << threadID << " done" << std::endl;
};

void iterateBoardsToGenerateProbabilityGrid(Hitmask hitM, ProbabilityGrid &probGrid, unsigned int threadCount){
    std::vector<Worker> sweatshop;
    std::vector<std::thread> sweatshopThreads;

    auto startTime = std::chrono::high_resolution_clock::now();
    int threadID = 0;

    // Make and split a vector of Workers
    dividePositions(threadCount,sweatshop);
    if (verbose) std::cout << sweatshop << std::endl;

    for (auto &w : sweatshop){ // Start all the threads
        std::thread threadedFunction(checkBoards, std::ref(w), hitM, threadID++);
        sweatshopThreads.push_back(std::move(threadedFunction));
    }

    for (std::thread & th : sweatshopThreads){ // Wait for all the threads to be finished
        if (th.joinable())
            th.join();
    }

    // Sum it up and get time
    gatherProbabilityFromWorkers(probGrid, sweatshop);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto runTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

    if (verbose) std::cout << probGrid.totalGoodBoards << " boards found in " << runTime.count() <<" seconds\n" ;
}


/**
 * @brief Collates a vector of workers into a single probability grid
 * @param p reference to a probability grid
 * @param sweatshop a vector of workers
 */
void gatherProbabilityFromWorkers(ProbabilityGrid &p, std::vector<Worker> sweatshop){
    // reset all values to 0
    p.totalGoodBoards = 0;
    memset(p.shipGrid, 0, sizeof(p.shipGrid));
    memset(p.shipProb, 0, sizeof(p.shipProb));
    memset(p.pChange, 0, sizeof(p.pChange));

    // sum the worker probability data
    for (auto &w : sweatshop){
        appendWorkerToProbGrid(p,w);
    }
    calcProbabilityGrid(p);
};

/**
 * @brief Appends data from a single worker to a shared probability grid
 * @param p reference to a probability grid
 * @param w a worker
 */
void appendWorkerToProbGrid(ProbabilityGrid &p, Worker w){
    p.totalGoodBoards += w.sub_probGrid.totalGoodBoards;

    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            p.shipGrid[x][y]+=w.sub_probGrid.shipGrid[x][y];
            p.infoGain[x][y]+=w.sub_probGrid.infoGain[x][y];
        }
    }
};



/**
 * @brief toString for an individual Workers
 *
 * @param os stream
 * @param wrks worker
 * @return the worker as represented in a stream
 */
std::ostream& operator<<(std::ostream& os, Worker& worker){
    os <<"Worker with " << worker.sub_probGrid.totalGoodBoards <<" good boards\n";

    os << "\tStart: ";
    for (size_t j = 0; j < FLEET_SIZE; j++){
        os  << worker.start[j] << "\t";
    }

    os << "\n\t  End: ";

    for (size_t j = 0; j < FLEET_SIZE; j++){
        os  << worker.end[j] << "\t";
    }
    return os;
};


/**
 * @brief toString for vector of Workers
 *
 * @param os stream
 * @param wrks vector of workers
 * @return the workers as represented in a stream
 */
std::ostream& operator<<(std::ostream& os, std::vector<Worker>& wrks){
    os <<"Workers " << wrks.size()<<'\n';

    for (auto &w :wrks){
        os << w << '\n';
    }
    return os;
};