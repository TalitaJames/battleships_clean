#include "coordinateChooser.h"
#include "logger.h"

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
    std::vector<Board> emptyVector;
    return coordinate_infoGain(xReturn, yReturn, pG, hitM, emptyVector);
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
 * @param rememberedBoards a potentially empty vector of boards to speed up checking//TODO spelling
*/
double coordinate_infoGain(int &xReturn, int &yReturn, ProbabilityGrid &pG, Hitmask hitM, std::vector<Board> rememberedBoards){
    double max = 0;
    int maxX = 0;
    int maxY = 0;
    double infoGainSum = 0; // the total information gained by shooting at this board (indicates if there are things still to learn about the game)

    std::vector<cellStatus> options = {MISS, HIT, SUNK};

    std::string logMessage = "Starting Infogain at "+ return_current_time_and_date() +
        "! Rememembered " + std::to_string(rememberedBoards.size()) + " num of boards";
    LOG_INFO(logLvl, logMessage);

    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){ // for each cell
            pG.infoGain[x][y] = 0;

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

                    // Copy the existing hitmask, then simulate the new shot
                    // and make a new ProbabilityGrid for this simulation
                    Hitmask infoHitmask = hitM;
                    infoHitmask.hitmask[x][y] = opt;
                    ProbabilityGrid infoPG;
                    double infoGainPart = 0;

                    for (int i=0; i<FLEET_SIZE; i++){ // for each ship that could be sunk
                        if (opt == SUNK){ // if testing sunk, set the next ship as sunk
                            std::memset(infoHitmask.shipSunk, 0, FLEET_SIZE);
                            infoHitmask.shipSunk[i]=1;
                        }


			            // Check the probability grid here, using one of two methods
                        if(rememberedBoards.size() > 0){
                            checkThenUpdateVectorOfBoards(rememberedBoards, infoPG, infoHitmask);
                        } else{
                            iterateBoardsToGenerateProbabilityGrid(infoHitmask, infoPG, THREAD_COUNT);
                        }

                        double probOptionIsTrue = ((double) infoPG.totalGoodBoards)/((double) pG.totalGoodBoards);
                        infoGainPart += (1 - probOptionIsTrue) * probOptionIsTrue;

                        if (opt != SUNK) break; // if not testing sunk don't repeat for another ship
                    }

                    pG.infoGain[x][y] += infoGainPart;
                }

                infoGainSum += pG.infoGain[x][y]; // add the info gained from this cell to the total infomation gained

                if (pG.infoGain[x][y] >= max){ // if the IG here is greater than the current max, point at the new cell
                    max = pG.infoGain[x][y];
                    maxX = x;
                    maxY = y;
                }
            }
        }
    }

    xReturn = maxX;
    yReturn = maxY;

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
