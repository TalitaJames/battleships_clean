#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <iostream>
#include <fstream>

#include "json/json.h"
#include "constants.h"

void jsonFileoutput(std::string filename, Json::Value jsonOut);


/**
 * @brief add a vector to a json array
 *
 * @tparam T type of vector data
 * @param inVector a vector of some type (T) that can be converted to a string
 * @return Json::Value an array type with added data
 */
template <typename T> Json::Value jsonArrayAdder(std::vector<T> inVector) {
    Json::Value resultArray(Json::arrayValue);

    for (T val : inVector){
        resultArray.append(val);
    }

    return resultArray;
};


/**
 * @brief put a BOARD_SIZE-ed 2d array in a json array
 *
 * @tparam T type of array data data
 * @param inputArray an of some type (T) that can be converted to a string
 * @return Json::Value an array type with added data
 */
template <typename T> Json::Value jsonArrayAdder(T inputArray[BOARD_SIZE][BOARD_SIZE]){
    Json::Value resultArray(Json::arrayValue);

    for (int y = 0; y < BOARD_SIZE; y++){
        Json::Value resultArray_row(Json::arrayValue);
        for (int x = 0; x < BOARD_SIZE; x++){
            resultArray_row.append(inputArray[x][y]);
        }
        resultArray.append(resultArray_row);
    }

    return resultArray;
};

/**
 * @brief put an array in a json array object
 *
 * @tparam T type of vector data
 * @param inputArray an array of some type (T) and some size that can be converted to a string
 * @param size the array size
 * @return Json::Value an array type with added data
 */
template <typename T> Json::Value jsonArrayAdder(T inputArray[], const size_t size){
    Json::Value resultArray(Json::arrayValue);

    for (size_t i = 0; i < size; i++){
        resultArray.append(inputArray[i]);
    }

    return resultArray;
};


#endif //JSON_UTILS_H


