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

/**
 * read_write(std::string file_path, double value, ReadWrite operation).
 *
 * @param file_path std::string -- a file path.
 * @param value double -- value - default 0.
 * @param operation ReadWrite -- read or write.
 *
 * @return the read value (if read), 1 if write, or 0 otherwise.
 */
double read_write(std::string file_path, double value, ReadWrite operation) {
    // Local Variable
    double retval;

    switch (operation) {
        case WRITE: {
            std::ofstream myfile;
            myfile.open(file_path);
            myfile << value;
            retval = 1;
            break;
        }

        case READ: {
            std::ifstream myfile;
            myfile.open(file_path);

            std::string l;
            getline(myfile, l);

            retval = (stod(l));
        }
        default:
            retval = 0;
    }

    return retval;
}