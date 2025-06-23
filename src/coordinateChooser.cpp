#include "coordinateChooser.h"
#include "logger.h"
#include <sstream>

/// @brief global variable that translates coordinate chooser enum into human readable string
std::map<CoordinateChooser, std::string> coordinateChooserNames{
    {USER_INPUT, "USER-INPUT"},
    {RND, "RND"},
    {RND_W_PROB, "RND-W-PROB"},
    {P_MAX, "P-MAX"},
    {P_RND, "P-RND"},
    {INFOGAIN, "INFOGAIN"},
    {DIAGONAL, "DIAGONAL"},
    {INFOGAIN_COMBINED, "INFOGAIN-COMBINED"}
};

/**
 * @brief User chooses where to shoot
 * @param xReturn coordinate for shot
 * @param yReturn cordinate for shot
*/
void coordinate_userInput(int &xReturn, int &yReturn){
    std::cout << "X: ";
    std::cin >> xReturn;

    std::cout << "Y: ";
    std::cin >> yReturn;
};

/**
 * @brief Choses uniform random (x,y) to shoot
 * @param xReturn coordinate for shot
 * @param yReturn cordinate for shot
 * @param hitM hitmask to ensure shot hasn't been taken yet
*/
void coordinate_rnd(int &xReturn, int &yReturn, Hitmask hitM){
    std::random_device rdDev;
    std::mt19937 rng(rdDev());
    std::uniform_int_distribution<std::mt19937::result_type> udist(0,BOARD_SIZE-1);

    do {
        xReturn = udist(rng);
        yReturn = udist(rng);
    } while (isHit(hitM, xReturn, yReturn)); // While the random x,y coordinate has been hit, pick another random x,y
};

/**
 * @brief Choses a random (x,y) over a weighted distribution of shipGrid
 * @param xReturn coordinate for shot
 * @param yReturn cordinate for shot
 * @param pG probability grid for weighted distribution
 * @param hitM hitmask to ensure shot hasn't been taken yet
*/
void coordinate_rndWProb(int &xReturn, int &yReturn, ProbabilityGrid pG, Hitmask hitM){
    // 1d vector works better with a weighted distribution
    std::vector<unsigned long> flattened;
    for (auto & arrayProb : pG.shipGrid){
        for (auto & prob : arrayProb){
            flattened.push_back(prob);
        }
    }

    std::discrete_distribution<int> distribution(flattened.begin(), flattened.end());
    std::random_device rd;
    std::mt19937 gen(rd());

    do {
        int place1D = distribution(gen);
        xReturn = place1D / BOARD_SIZE;
        yReturn = place1D % BOARD_SIZE;
    } while (isHit(hitM,xReturn,yReturn));
};

/**
 * @brief Choses the shot (x,y) that maximises the shipGrid.
 * Choose where a ship is most likely to be.
 *
 * @param xReturn coordinate for shot
 * @param yReturn cordinate for shot
 * @param pG probability grid to find pMax value in the shipGrid array
 * @param hitM hitmask to ensure shot hasn't been taken yet
*/
void coordinate_pMax(int &xReturn, int &yReturn, ProbabilityGrid pG, Hitmask hitM){
    unsigned long min = -1;
    unsigned long max = 0;
    int minX = 0;
    int minY = 0;

    int maxX = 0;
    int maxY = 0;

    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (pG.shipGrid[x][y] < min && !isHit(hitM,x,y)){
                min = pG.shipGrid[x][y];
                minX = x;
                minY = y;
            }

            if (pG.shipGrid[x][y] > max && !isHit(hitM,x,y)){
                max = pG.shipGrid[x][y];
                maxX = x;
                maxY = y;
            }
        }
    }
    xReturn = maxX;
    yReturn = maxY;
};

/**
 * @brief Choses the shot (x,y) that maximises the shipGrid
 * multipled by a random double (introduce some variance)
 *
 * @param xReturn coordinate for shot
 * @param yReturn cordinate for shot
 * @param pG probability grid to find pMax with a random elelment
 * @param hitM hitmask to ensure shot hasn't been taken yet
*/
void coordinate_pRnd(int &xReturn, int &yReturn, ProbabilityGrid pG, Hitmask hitM){
    std::random_device rdDev;
    std::mt19937 rng(rdDev());

    double max = 0;
    int maxX = 0;
    int maxY = 0;

    std::uniform_real_distribution<> dis(0,1);

    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            double scaledProb = pG.shipProb[x][y]*dis(rng);
            if (scaledProb > max && !isHit(hitM,x,y)){
                max = scaledProb;
                maxX = x;
                maxY = y;
            }
        }
    }
    xReturn = maxX;
    yReturn = maxY;
};

/**
 * @brief for each unocupied cell, create the possible situations it could be
 * in a hitmask, for calculating the infogain
 *
 * @param hitM the boards shot reccord
 * @return std::vector<InfogainTask> A list of "tasks" with data about hitmask,
 * location (x,y) and an attached probability grid
 */
std::vector<InfogainTask> makeInfogainTasks(Hitmask hitM){

    LOG_DEBUG(logLvl, "Making infogain tasks");

    std::vector<InfogainTask> tasks; // all the threads and IG spots to simulate
    std::vector<cellStatus> options = {MISS, HIT, SUNK};

    // Make all tasks
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){ // for each cell

            if (!isHit(hitM, x,y)){ // if the cell hasn't been hit yet
                for (auto opt : options){ // simulate each type of shot

                    // if testing sunk, and there aren't any surounding hits, don't check (because it can't have sunk)
                    if(opt == SUNK &&
                        !(((x-1) >= 0 && hitM.hitmask[x-1][y] == HIT ) || ((x+1<=BOARD_SIZE) && hitM.hitmask[x+1][y] == HIT)
                        || ((y-1)>= 0 && hitM.hitmask[x][y-1] == HIT ) || ((y+1<=BOARD_SIZE) && hitM.hitmask[x][y+1] == HIT )))
                        { break; }

                    // if surounding is all miss or all sunk, don't check (because it must be a miss)
                    if (((x-1) >= 0 && (hitM.hitmask[x-1][y] == MISS || hitM.hitmask[x-1][y] == SUNK)) &&
                        ((x+1 <= BOARD_SIZE) && (hitM.hitmask[x+1][y] == MISS || hitM.hitmask[x+1][y] == SUNK)) &&
                        ((y-1) >= 0 && (hitM.hitmask[x][y-1] == MISS || hitM.hitmask[x][y-1] == SUNK)) &&
                        ((y+1 <= BOARD_SIZE) && (hitM.hitmask[x][y+1] == MISS || hitM.hitmask[x][y+1] == SUNK)))
                        { break; }

                    for (int i=0; i<FLEET_SIZE; i++){ // for each ship that could be sunk
                        // Copy the existing hitmask, then simulate the new shot
                        // and make a new ProbabilityGrid for this simulation
                        Hitmask infoHitmask = hitM;
                        infoHitmask.hitmask[x][y] = opt;
                        ProbabilityGrid infoPG;

                        if (opt == SUNK){ // if testing sunk, set the next ship as sunk
                            std::memset(infoHitmask.shipSunk, 0, FLEET_SIZE);
                            infoHitmask.shipSunk[i]=1;
                        }

                        InfogainTask thisCellTask{infoHitmask, infoPG, x, y};
                        tasks.push_back(thisCellTask);

                        if (opt != SUNK) break; // if not testing sunk don't repeat for another ship
                    }
                }
            } // end if not hit
        }
    }

    return tasks;
}


/**
 * @brief Given a list of infogain tasks, sum the
 * information into one probability grid
 *
 * @param tasks the list of tasks
 * @param probGrid grid of information
 * @param xReturn x position to hit, updated by reference here
 * @param yReturn y position to hit, updated by reference here
 * @param hitM hitmask, to avoid shooting in a spot already checked
 * @return infoGainSum the total infogain inform
 */
double collateInfogainData(std::vector<InfogainTask>& tasks, ProbabilityGrid &probGrid,
                            int &xReturn, int &yReturn, Hitmask hitM){
    LOG_DEBUG(logLvl, "Collating IG Data");
    long totalGoodBoards = probGrid.totalGoodBoards;
    // clearProbabilityGrid(probGrid);

    // Combine all data from done threads
    for(auto& t : tasks){
        double probOptionIsTrue = ((double) t.probGrid.totalGoodBoards)/((double) totalGoodBoards);
        probGrid.infoGain[t.x][t.y] += (1 - probOptionIsTrue) * probOptionIsTrue;

        std::ostringstream debugCollatedGrids;
        // debugCollatedGrids << t.hitmask << "\nprobgrid is:\n" << t.probGrid;
        debugCollatedGrids << "found prob of " << probOptionIsTrue << "=" << t.probGrid.totalGoodBoards << "/" << totalGoodBoards;
        std::string debugCollatedGridsStr = debugCollatedGrids.str();
        LOG_DEBUG(logLvl, debugCollatedGridsStr);
    }

    double max = 0;
    int maxX = 0;
    int maxY = 0;
    double infoGainSum = 0; // the total information gained by shooting at this board (indicates if there are things still to learn about the game)

    std::ostringstream probGridData;
    probGridData << probGrid << std::endl;
    std::string probGridDataStr = probGridData.str();
    LOG_DEBUG(logLvl, probGridDataStr);

    // go through the probgrid infogain to find the max, and find infogain sum
    for (size_t y = 0; y < BOARD_SIZE; y++){
        for (size_t x = 0; x < BOARD_SIZE; x++){
             infoGainSum += probGrid.infoGain[x][y]; // add the info gained from this cell to the total infomation gained

            if (probGrid.infoGain[x][y] >= max && !isHit(hitM, x, y)){ // if the IG here is greater than the current max, point at the new cell
                max = probGrid.infoGain[x][y];
                maxX = x;
                maxY = y;
            }
        }
    }

    xReturn = maxX;
    yReturn = maxY;
    LOG_DEBUG(logLvl, "DONE COLLATION " + std::to_string(xReturn) + ", " + std::to_string(yReturn));

    return infoGainSum;
}

/**
 * @brief Find the position that maximises the information gain.
 * For every unknown cell in the hitmask, simulate each possible outcome
 * (miss, hit and sink (for each possible boat)).
 *
 * The information gain for that cell is equal to the sum
 * (num of boards matching option * probability of option) for each outcome
 *
 * @param xReturn coordinate for shot
 * @param yReturn cordinate for shot
 * @param pG probability grid to record infoGain data
 * @param hitM hitmask to ensure shot hasn't been taken yet
*/
double coordinate_infoGain(int &xReturn, int &yReturn, ProbabilityGrid &pG, Hitmask hitM){
    LOG_INFO(logLvl, "Starting Infogain at " + return_current_time_and_date() + "! Didn't remember any boards");
    std::vector<InfogainTask> tasks = makeInfogainTasks(hitM);

    for(auto& t: tasks){
        iterateBoardsToGenerateProbabilityGrid(t.hitmask, t.probGrid, THREAD_COUNT);
    }

    double infoGainSum = collateInfogainData(tasks, pG, xReturn, yReturn, hitM);
    return infoGainSum;
}

/**
 * @brief Find the position that maximises the information gain.
 * For every unknown cell in the hitmask, simulate each possible outcome
 * (miss, hit and sink (for each possible boat)).
 *
 * The information gain for that cell is equal to the sum
 * (num of boards matching option * probability of option) for each outcome
 *
 * @param xReturn coordinate for shot
 * @param yReturn cordinate for shot
 * @param pG probability grid to record infoGain data
 * @param hitM hitmask to ensure shot hasn't been taken yet
 * @param rememberedBoards a potentially empty vector of boards to speed up checking
*/
double coordinate_infoGain(int &xReturn, int &yReturn, ProbabilityGrid &pG, Hitmask hitM, std::vector<Board> rememberedBoards){

    // if you don't remember anything, call the other function
    if(rememberedBoards.size() == 0){
        return coordinate_infoGain(xReturn, yReturn, pG, hitM);
    }

    LOG_INFO(logLvl, "Starting Infogain at " + return_current_time_and_date() +
        "! Rememembered " + std::to_string(rememberedBoards.size()) + " num of boards");

    // Make all tasks
    std::vector<InfogainTask> tasks = makeInfogainTasks(hitM);

    // Start all tasks as threads, then join the threads
    std::vector<std::thread> threads;

    for(auto& t : tasks){
        std::thread threadedFunction(checkThenUpdateVectorOfBoards_IG, std::ref(rememberedBoards),
                                    std::ref(t.probGrid), t.hitmask);
        threads.push_back(std::move(threadedFunction));

    }
    for (auto& th : threads) th.join();

    double infoGainSum = collateInfogainData(tasks, pG, xReturn, yReturn, hitM);
    return infoGainSum;
};

/**
 * @brief Choses the position by findng largest unsolved ship,
 * then hiting in a diagonal following that pattern
 *
 * @param xReturn coordinate for shot
 * @param yReturn cordinate for shot
 * @param pG probability grid for the backup (if all diagonals are done then do pMax as a backup)
 * @param hitM hitmask to ensure shot hasn't been taken yet
*/
void coordinate_diagonal(int &xReturn, int &yReturn, ProbabilityGrid pG, Hitmask hitM){ //as with infogain above
    int largestShip = *std::max_element(FLEET , FLEET + FLEET_SIZE);

    int tempX = 0;
    int tempY = 0;

    coordinate_pMax(tempX, tempY, pG, hitM);

    // if a ship is definitely at that position (ie probability == 1) shoot it anyway, before diagonals
    if (1 == pG.shipProb[tempX][tempY]){
        xReturn = tempX;
        yReturn = tempY;
        return;
    }

    while (largestShip>0) {
        int subBoxCount = BOARD_SIZE/largestShip;

        for (int y = 0; y < subBoxCount; y++){
            for (int x = 0; x < subBoxCount; x++){
                for (int i = 0; i < largestShip; i++){
                    xReturn = i + x*largestShip;
                    yReturn = i + y*largestShip;

                    if (!isHit(hitM, xReturn, yReturn)) return;
                }
            }
        }
        largestShip--;
    }
};
