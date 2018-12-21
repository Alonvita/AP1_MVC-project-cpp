//
// Created by alon on 21/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_GENERICFUNCTIONS_H
#define AP1_SEMETSER_PROJECT_GENERICFUNCTIONS_H

#include <queue>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
bool indexWithinVectorRange(int index, const std::vector<T>& vector);

template <typename T, typename K>
std::pair<T, K> makePair(T lhs, K rhs);

template <typename T>
void vectorToQueue(const std::vector<T>&, std::queue<T>&);

#endif //AP1_SEMETSER_PROJECT_GENERICFUNCTIONS_H
