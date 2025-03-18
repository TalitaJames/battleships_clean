# Starting script to puppet the battleship game
# Made by Talita James, on 2024-07-2

import os
import socket
import argparse
import time
import json


def updateGameSettings(boardSize: int, fleet: list, memory: int, threadCount: int):
    ''' Updates the C++ code to match the given parameters
        - boardSize (int)
        - fleet (list of ints) ie [2,3] each representing the length of the ships
        - memory, maximum number of boards to remember when iterating board states
        - threadcount (int) number of threads c++ will make
    '''
    fleetString = convertToCArray(fleet)
    memoryStr = convertToCInt(memory)
    filename = "lib/constants.h"

    # Change the header file to the new input args
    os.system(f'sed -r -i -E  "s/^\#define BOARD_SIZE .*$/\#define BOARD_SIZE {boardSize}/" {filename}')
    os.system(f'sed -r -i  "s/^const ShipData FLEET\[\] =.*;/const ShipData FLEET[] = {fleetString};/" {filename}')
    os.system(f'sed -r -i  "s/^#define THREAD_COUNT .*/#define THREAD_COUNT {threadCount}/" {filename}')
    os.system(f'sed -r -i  "s/^#define MAX_REMEMBERED_BOARDS .*/#define MAX_REMEMBERED_BOARDS {memoryStr}/" {filename}')

    # Note: the python version on the iHPCs can't support {variable=} in f-strings
    print(f"Game with boardSize={boardSize} and fleet={fleet}, running "+\
          f"threadCount={threadCount}, memory={memory}\n-----------")


def convertToCArray(listInput: list) -> str:
    '''Turns a list of numbers into the C style [2,3] becomes {2, 3}'''
    return "{" + ", ".join([str(x) for x in listInput]) + "}"

def convertToCInt(n: int) -> str:
    '''Turns an int into an int with single quotes delimiting each three digits
    f string formats commas for hudreds, then replace the commas to single quotes
    '''
    return f"{n:,}".replace(",", "\'")

def build(clean = False):
    '''Compiles the code, with an optional initial cleaning (removes pre compiled files)'''
    if clean:
        os.system("make clean")
    os.system("make")


def runTests():
    '''Runs the unittests then exits'''
    os.system("make clean")
    os.system("make tests")
    os.system("./build/tests/test_runner")
    exit()


def calculateTotalBoards(boardSize: int, fleet: list) -> int:
    ''' Counts the total number of starting permutations that may fit in a given board size
        Doesn't account for collisions.
    '''
    allGoodBoards = 0

    for boat in fleet:
        row = boardSize-boat # ie a boat len 4 in a 10x10 grid may fit 6 times when starting from the left going right
        allGoodBoards += row * boardSize * 2 # accounts for each board row (ie ten down) *2 to account for the columns

    # calculate the total number of boards
    return allGoodBoards


if __name__ == "__main__":
    with open("defaultSettings.json") as f:
        defaultSettings = json.load(f)

    # Initialise the command line arguments
    parser = argparse.ArgumentParser(description="Settings to change the running of the battleship computation code")
    parser.add_argument('-t', '--threads', type=int, help="num of threads", default=defaultSettings["threadCount"])
    parser.add_argument('-s', '--size', type=int,  default=defaultSettings["boardSize"], help="The board size")
    parser.add_argument('-f', '--fleet', type=str,  default=defaultSettings["fleet"])
    parser.add_argument('-m', '--memory', type=int,  default=defaultSettings["maxRememberedBoards"],
                         help="the maximum number of boards remember in memory when iterating board states")

    parser.add_argument('-c', '--clean', action='store_true', help="Will the build files get cleaned?")
    parser.add_argument('--utest', action='store_true', help="run the tests")
    args = parser.parse_args()
    #end command line arguments

    if args.utest:
        runTests()

    fleet = [int(x) for x in args.fleet.split(",")] #turn "2,3" into [2,3]

    updateGameSettings(boardSize=args.size, fleet=fleet, memory=args.memory,
                       threadCount=args.threads)
    build(args.clean)

    # run the game
    timestamp = time.strftime("%Y%m%d-%H%M%S",time.localtime())
    logFilename = f"./out/logs/{timestamp}_{socket.gethostname()}.log" #creates a log file named "YYYMMDD-HHMMSS_computername.log"
    returnVal = os.system(f"./build/src/runner 2>&1 | tee {logFilename}")

    if (returnVal != 0):
        print(f"\nERROR {returnVal}")
    else:
        print(f"\nDone! Logged in {logFilename}")