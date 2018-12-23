//
// Created by alon on 20/12/18.
//

#include "GenericFunctions.h"

/**
 * indexWithinVectorRange(int index, const std::vector<T>& vector)
 *
 * @tparam T template <typename T> -- a template of typename T.
 * @param index int -- an integer
 * @param vector const std::vector<T>& -- a const reference to a vector of types T.
 *
 * @return true if the given index is between 0 and vector.size().
 */
template <typename T>
bool indexWithinVectorRange(unsigned index, const std::vector<T>& vector) {
    return 0 <= index && index <= vector.size();
}

/**
 * vectorToQueue(const std::vector<T>&, std::queue<T>&).
 *
 * pushes all the items in a given vector FROM END TO BEGIN into the outQueue.
 *
 * @tparam T template <typename T> -- a template of typename T.
 *
 * @param vector const std::vector<T>& -- a const ref to a vector of type T.
 * @param outQueue std::queue<T>& -- a reference to a queue to push the items to.
 */
template <typename T>
void pushFromVectorToQueue(const std::vector<T> &vector, std::queue<T> &outQueue) {
    std::vector<T> cpy = vector;

    std::reverse(cpy.begin(), cpy.end());

    for(T item : cpy) {
        outQueue.push(item);
    }
}