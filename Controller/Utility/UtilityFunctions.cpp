//
// Created by alon on 06/12/18.
//

#include "UtilityFunctions.h"

/**
 * remove_if(T beg, T end, P pred).
 *7
 * @tparam T template<typename T> -- a template of type T.
 * @tparam P template<typename P> -- a template of type T.
 * @param beg P -- the beginning of a container.
 * @param end T -- the end of a container.
 * @param pred -- whatever you want to remove.
 *
 * @return a modified container, after removing all preds from it.
 *
 * source: https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
 */
template<typename T, typename P>
T remove_if(T beg, T end, P pred) {
    T dest = beg;

    for (T itr = beg; itr != end; ++itr)
        if (!pred(*itr))
            *(dest++) = *itr;

    return dest;
}