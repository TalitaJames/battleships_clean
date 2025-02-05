#ifndef CARTESIANPRODUCT_H
#define CARTESIANPRODUCT_H

#include <vector>
#include <array>
#include <functional>


// template declarations
template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<T> setA, std::vector<T> setB);
template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<T> setA, std::vector<T> setB, std::function<bool(std::vector<T>)> filter);
template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> setA, std::vector<T> setB);
template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> setA, std::vector<T> setB,std::function<bool(std::vector<T>)> filter);
template <typename T> std::vector<std::vector<T>> vectorIntoVectorVector(std::vector<T> set);


// template definitions


template <typename T> std::vector<std::vector<T>> vectorIntoVectorVector(std::vector<T> set){
    std::vector<std::vector<T>> result;
    for(T element : set){
        std::vector<T> elementVector = {element};
        result.push_back(elementVector);
    }

    return result;
}

template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<T> setA, std::vector<T> setB){
    return cartesianProduct(vectorIntoVectorVector(setA), setB);
}

template <typename T> std::vector<std::vector<T>> cartesianProduct(std::vector<T> setA, std::vector<T> setB, std::function<bool(std::vector<T>)> filter){
    return cartesianProduct(vectorIntoVectorVector(setA), setB, filter);
}



template <typename T>
std::vector<std::vector<T>> cartesianProduct(std::vector<std::vector<T>> setA, std::vector<T> setB){
    std::function<bool(std::vector<T>)> trueLambdaFn = [](std::vector<T>){ return true; };
    return cartesianProduct(setA, setB, trueLambdaFn);
}


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


#endif //CARTESIANPRODUCT_H