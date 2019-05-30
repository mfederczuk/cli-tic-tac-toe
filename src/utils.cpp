// src/utils.cpp
/**
 * utils.hpp implementation.
 * Source file for utility functions.
 *
 * Since: 2019-05-30
 * LastEdit: 2019-05-30
 */

#include <tic-tac-toe/utils.hpp>

namespace tic_tac_toe::utils {

	std::string search_replace(const std::string& str, char search, char replace) {
		std::string res = str;

		for(size_t i = 0, l = res.length(); i < l; ++i) {
			if(res[i] == search) res[i] = replace;
		}

		return res;
	}

}
