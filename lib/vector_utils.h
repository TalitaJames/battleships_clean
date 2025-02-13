#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <vector>
#include <stddef.h>
#include <iostream>

/**
 * @brief Print a vector of type T to the console
 *
 * @tparam T the type of the vector
 * @param in the vector to be printed
 */
template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> in){
    os << "{";
    for (size_t i = 0; i < in.size(); i++){
        os << in[i];

        // if not the last element add a comma
        if (i != in.size()-1) os << ", ";
    }
    os << "}";
    return os;
}

/**
 * @brief Print a double vector of type T to the console
 *
 * @tparam T the type of the vector
 * @param in the vector to be printed
 */
template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<std::vector<T>> in){
    os << "{\n";
    for(std::vector<T> line : in){
        os << "\t" << line << std::endl;
    }
    os << "}" << std::endl;

    return os;
}


/**
 * @brief Split a vector of type T into n semi equal supdivisions
 * @copyright https://stackoverflow.com/a/37708514
 *
 * @tparam T type of vector inpit
 * @param vec inpput date to be split
 * @param n the number of subdivisions to be given
 * @return std::vector<std::vector<T>> the split vector
 */
template<typename T>
std::vector<std::vector<T>> splitVector(const std::vector<T>& vec, size_t n) {
    std::vector<std::vector<T>> outVec; // return value

    size_t length = vec.size() / n; // how many go evenly into the vector
    size_t remain = vec.size() % n; // and leftovers

    size_t begin = 0;
    size_t end = 0;

    // min ensures it does't try to subdivide more than there are elements in the original vector
    for (size_t i = 0; i < std::min(n, vec.size()); ++i) {

        end += (remain > 0) ? (length + !!(remain--)) : length;
        /* !!(remain--) checks if the value is greater than 0 then decrements it
            but converts it to a bool, so it only adds a max of one
            remain will allways be < n, so all elements will be captured
        */

        outVec.push_back(std::vector<T>(vec.begin() + begin, vec.begin() + end));

        begin = end;
    }

    return outVec;
}


/**
 * @brief change a 1D vector into a 2D
 * @tparam T the type of vector
 * @param in a 1D vector eg {3, 4, 6}
 * @return the vector in transformed into n vectors each seperatly holding the element,
 * ie {3, 4, 6} becomes {{3}, {4}, {6}}
 */
template <typename T> std::vector<std::vector<T>> vectorIntoVectorVector(std::vector<T> in){
    std::vector<std::vector<T>> result;
    for(T element : in){
        std::vector<T> elementVector = {element};
        result.push_back(elementVector);
    }

    return result;
}



#endif //VECTOR_UTILS_H