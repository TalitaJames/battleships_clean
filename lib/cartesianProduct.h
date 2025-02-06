/**
 * @file
 * @author Talita
 * @brief Calculates cartesian products
 * @version 0.1
 * @date 2025-02-06
 */
#ifndef CARTESIANPRODUCT_H
#define CARTESIANPRODUCT_H

#include <vector>
#include <array>
#include <functional>


// template declarations
template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> sets);
template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> sets, std::function<bool(std::vector<T>)> filter);

template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<T> setA, std::vector<T> setB);
template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<T> setA, std::vector<T> setB, std::function<bool(std::vector<T>)> filter);

template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> setA, std::vector<T> setB);
template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> setA, std::vector<T> setB,std::function<bool(std::vector<T>)> filter);

template <typename T> std::vector<std::vector<T>> vectorIntoVectorVector(std::vector<T> set);


// template definitions

/**
 * @brief given a vector of "sets"(each vector in the vector is a list of things to check the cartesian product of)
 * return the cartesian product of the sets eg {{a,b}, {c,d}} would return {{a,c}, {a,d}, {b, c}, {b, d}}
 *
 * @tparam T The type of elements in the sets.
 * @param sets a vector of vectors that contain elements to get the cartesian product of
 * @return a cartesian product of each elements in every set with the other sets
 */
template <typename T>
std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> sets){
    std::function<bool(std::vector<T>)> alwaysTrue = [](std::vector<T>){ return true; };
    return cartesianProduct(sets, alwaysTrue);
}

/**
 * @brief aiven a vector of "sets"(each vector in the vector is a list of things to check the cartesian product of)
 *
 * @tparam T The type of elements in the sets.
 * @param sets a vector of vectors that contain elements to get the cartesian product of
 * @param filter A function that determines which combinations should be included.
 * @return a filtered cartesian product of each elements in every set with the other sets
 */
template <typename T>
std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> sets, std::function<bool(std::vector<T>)> filter){
    std::vector<std::vector<T>> result = cartesianProduct(sets[0], sets[1], filter); //cartesian product of the first two

    for(size_t i = 2; i < sets.size(); i++){ //update the result to append the next ship positions
        result = cartesianProduct(result, sets[i], filter);
	}

    return result;
};


/**
 * @brief Computes the Cartesian product of two sets.
 *
 * Takes two 1D vectors and returns their Cartesian product,
 * represented as a vector of vectors.
 *
 * @tparam T The type of elements in the sets.
 * @param setA The first set.
 * @param setB The second set.
 * @return A vector of vectors representing the Cartesian product of setA and setB.
 */
template <typename T>
std::vector<std::vector<T>> cartesianProduct(std::vector<T> setA, std::vector<T> setB){
    return cartesianProduct(vectorIntoVectorVector(setA), setB);
}

/**
 * @brief Computes the filtered Cartesian product of two sets.
 *
 * Takes two vectors and a filter function.
 * The Cartesian product is computed, only elements satisfying the filter
 * are included in the result.
 *
 * @tparam T The type of elements in the sets.
 * @param setA The first set.
 * @param setB The second set.
 * @param filter A function that determines which combinations should be included.
 * @return A vector of vectors representing the filtered Cartesian product.
 */
template <typename T>
std::vector<std::vector<T>> cartesianProduct(std::vector<T> setA, std::vector<T> setB, std::function<bool(std::vector<T>)> filter){
    return cartesianProduct(vectorIntoVectorVector(setA), setB, filter);
}


/**
 * @brief Computes the filtered Cartesian product of two sets.
 *
 * @tparam T The type of elements in the sets.
 * @param setA The first set (as a vector of vectors).
 * @param setB The second set.
 * @return A vector of vectors representing the Cartesian product.
 */
template <typename T>
std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> setA, std::vector<T> setB){
    // function that always returns true  (ie include everything)
    std::function<bool(std::vector<T>)> alwaysTrue = [](std::vector<T>){ return true; };
    return cartesianProduct(setA, setB, alwaysTrue);
}

/**
 * @brief Computes the Cartesian product of two sets with filtering.
 *
 * It iterates through all combinations of elements from setA and setB,
 * applying a filtering function to determine which results should be included.
 *
 * @tparam T The type of elements in the sets.
 * @param setA The first set (as a vector of vectors).
 * @param setB The second set.
 * @param filter A function that determines which combinations should be included.
 * @return A vector of vectors representing the filtered Cartesian product.
 */
template <typename T>
std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> setA, std::vector<T> setB,std::function<bool(std::vector<T>)> filter){

    std::vector<std::vector<T>> result;

    for (std::vector<T> a : setA){ // for each element in setA
        for (T b : setB){
            std::vector<T> productAB = a;
            productAB.push_back(b);

            if (filter(productAB)){
                result.push_back(productAB);
            }
        }
    }

    return result;
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


#endif //CARTESIANPRODUCT_H