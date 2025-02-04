#include "playGame.h"


/**
 * @brief Given a method, shoot a hitmask, then gather related data
 * @param playStyle which method is used to pick the next shot
 * @param b game board with positions of all games
 * @param hitM hitmask of current game, to be used as reference when picking shot and updated after shot
 * @param probGrid grid that holds the game probabilities
 * @param x coordinate to shoot
 * @param y coordinate to shoot
*/
void takeTurn(CoordinateChooser playStyle, Board board, Hitmask &hitM, ProbabilityGrid &probGrid, int &x, int &y, Json::Value & gamePlayHistory){
    if(isHitmaskSolved(hitM)) return;
    // gather data
    if(playStyle != RND) runThreads(hitM, probGrid, THREAD_COUNT);

    do{ // decide where to shoot
        switch(playStyle){
        case RND:
            coordinate_rnd(x,y,hitM);
            break;
        case RND_W_PROB:
            coordinate_rndWProb(x,y,probGrid,hitM);
            break;
        case P_MAX:
            coordinate_pMax(x,y,probGrid,hitM);
            break;
        case P_RND:
            coordinate_pRnd(x,y,probGrid,hitM);
            break;
        case INFOGAIN:
            coordinate_infoGain(x,y,probGrid,hitM);
            break;
        case DIAGONAL:
            coordinate_diagonal(x,y,probGrid,hitM);
            break;
        case FLEXI:
            double totalIG;
            totalIG = coordinate_infoGain(x,y,probGrid,hitM);
            if (totalIG < 0.00001){
            // if (verbose) std::cout <<"pMax now!\n";
            coordinate_pMax(x,y,probGrid,hitM);
            }
            break;
        case USER_INPUT:
        default:
            coordinate_userInput(x,y);

        }

        if (isHit(hitM, x, y)){
            if(verbose) std::cout << "You already hit (" << x << ", " << y << ")\n";
        }
        if (verbose) std::cout << "You entered (" << x << ", " << y << ") using " << coordinateChooserNames[playStyle] << std::endl;
        std::cout << std::flush;
    } while (isHit(hitM, x, y)); // repeat until the hit is valid (ie cell isn't yet hit)

    // Take the shot
    hitBoard(board, hitM, x, y);

    // record information gathered
    // Json::Value currentCoords(Json::arrayValue);
    // currentCoords.append(x);
    // currentCoords.append(y);
    // gamePlayHistory["shotRecord"].append(currentCoords);
    // gamePlayHistory["probabilityGrid"].append(jsonArrayAdder(probGrid.shipGrid));
    // gamePlayHistory["infoGainGrid"].append(jsonArrayAdder(probGrid.infoGain));
    // TODO add which shot style was used in array form (note the playGame method details the errors and reasons this is commented out)

    if (verbose){ // potentialy update user
        std::cout << "\nPROBABILITY GRID:\n" << probGrid << std::endl;
        std::cout << "\nHITMASK:\n" << hitM << std::endl;
    }
};


/**
 * @brief Plays an entire game of battleship from the an empty board
 * @param playStyle the method used to shoot at the board
 * @param board the specific board to be played
 * @return the number of turns the game takes to play
*/
unsigned int playGame_fromStart(CoordinateChooser playStyle, Board board){
    Json::Value rubishJSON; //Don't care about storing json data
    return playGame_fromStart(playStyle, board, rubishJSON);
}


/**
 * @brief Plays an entire game of battleship from the an empty board
 * @param playStyle the method used to shoot at the board
 * @param board the specific board to be played
 * @param gamePlayHistory a json dictionary that records the game outcomes
 * @return the number of turns the game takes to play
*/
unsigned int playGame_fromStart(CoordinateChooser playStyle, Board board, Json::Value &gamePlayHistory){
    Hitmask blankHitmask;
    return playGame_fromHitmask(playStyle, board, blankHitmask, gamePlayHistory);
};


/**
 * @brief Plays the end half of a battleship game given an unfinished hitmask
 * @param playStyle the method used to shoot at the board
 * @param board the specific board to be played
 * @param hitmask the turns taken thusfar
 * @return the number of turns the game takes to play
*/
unsigned int playGame_fromHitmask(CoordinateChooser playStyle, Board board,  Hitmask hitmask){
    Json::Value rubishJSON;
    return playGame_fromHitmask(playStyle, board, hitmask, rubishJSON);
};


/**
 * @brief Plays the end half of a battleship game given an unfinished hitmask
 * @param playStyle the method used to shoot at the board
 * @param board the specific board to be played
 * @param hitmask the turns taken thusfar
 * @param gamePlayHistory a json dictionary that records the game outcomes
 * @return the number of turns the game takes to play
*/
unsigned int playGame_fromHitmask(CoordinateChooser playStyle, Board board,  Hitmask hitmask, Json::Value &gamePlayHistory){
    if(verbose) std::cout << "Playing game from hitmask " << board << hitmask << std::endl;
    hitmask = turnsToShotmask(board, hitmask); // converts any "turn"s into the outcome //TODO decide how 'turns' should work?

    // init JSON //BUG when these variables don't exist the json doesn't get updated,
    // despite it being called directly from the gamePlayHistory rather than the created json values
    Json::Value shotRecordJson = gamePlayHistory["shotRecord"];
    Json::Value probabilityGridJson = gamePlayHistory["probabilityGrid"];
    Json::Value infoGainGridJson = gamePlayHistory["infoGainGrid"];

    // init misc
    auto startTime = std::chrono::high_resolution_clock::now(); //start timing
    ProbabilityGrid probGrid;
    unsigned int turns = 0;

    while (!isHitmaskSolved(hitmask)){
        int x = 0;
        int y = 0;

        takeTurn(playStyle, board, hitmask, probGrid, x,y, gamePlayHistory);
        turns++;

        // Update gameJSON (//FIXME without these updating like this, they return as null at the end)
        Json::Value currentCoords(Json::arrayValue);
        currentCoords.append(x);
        currentCoords.append(y);
        shotRecordJson.append(currentCoords);
        probabilityGridJson.append(jsonArrayAdder(probGrid.shipGrid));
        infoGainGridJson.append(jsonArrayAdder((probGrid.infoGain)));
    }

    //BUG see the begining of playGame to see the error
    gamePlayHistory["shotRecord"] = shotRecordJson;
    gamePlayHistory["probabilityGrid"] = probabilityGridJson;
    gamePlayHistory["infoGainGrid"] = infoGainGridJson;
    gamePlayHistory["turnsTaken"] = howManyTurnsTaken(hitmask);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto runTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

    int fleetPositionCount = 0;
    for (size_t i = 0; i < FLEET_SIZE; i++) fleetPositionCount += FLEET[i];

    std::cout << "\tGAME OVER! you took a total of " << howManyTurnsTaken(hitmask) << " turns in "
            << runTime.count() <<" seconds.\n\tshot success rate: " << (double)(fleetPositionCount)/(double)(turns) << std::endl;

    return howManyTurnsTaken(hitmask);
};


/**
 * @brief saves a game by playing it then exporting the info in a json file
 * @param playstyle the method used to shoot at the board
 * @param b the specific board to be played
 * @param playstyleTurnCount how many turns of that playStyle to use before defaulting to pMax
 * @param igExtra an extra string used for describing infoGain turns only
 * @return the number of turns the game takes to play
*/
unsigned int saveGame(CoordinateChooser playStyle, Board board){

    // filename in the form: boardSize_fleetSize_boardID_playStyle_version_randomChars.json
    std::string filename; //= std::tmpnam(nullptr);

    filename = "./out/gamePlay/"+std::to_string(BOARD_SIZE)+"_"+std::to_string(FLEET_SIZE)+"_"
                            // +std::to_string(board.shipPositionsInt)+"_" //FIXME need a hash of the board
                            +coordinateChooserNames[playStyle]+"_"
                            +CODE_VERSION+"_";
                            // +filename.substr(9, filename.length())+".json"; //FIXME add back in

    Json::Value gamePlayHistory; //FIXME this could be in its own method, but i think it only needs to happen once here
    gamePlayHistory["FLEET_SIZE"] = FLEET_SIZE;
    gamePlayHistory["FLEET"] = jsonArrayAdder(FLEET, FLEET_SIZE);
    gamePlayHistory["BOARD_SIZE"] = BOARD_SIZE;
    gamePlayHistory["board"] = jsonArrayAdder(board.board);
    gamePlayHistory["version"] = CODE_VERSION;
    gamePlayHistory["shotMethod"] = coordinateChooserNames[playStyle];

    int turnCounter = playGame_fromStart(playStyle, board, gamePlayHistory);

    jsonFileoutput(filename, gamePlayHistory);
    std::cout<< "\tsaving to " << filename << "\n" << std::endl;

    return turnCounter;
};


/**
 * @brief Plays a number of games repeatedly
 * @param playStyles which coordinate choosing methods should be chosen
 * @param repeats how many times it should repeat
*/
void repeatGames(CoordinateChooser playStyle, unsigned int repeats){
    Board board;
    for (size_t i = 0; i < repeats; i++){
        board = rndBoard();
        saveGame(playStyle, board);
    }
};