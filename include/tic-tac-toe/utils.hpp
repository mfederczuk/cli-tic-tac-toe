// include/tic-tac-toe/utils.hpp
/**
 * Header file for utility functions.
 *
 * Since: 2019-05-30
 * LastEdit: 2019-05-30
 */

#ifndef _TIC_TAC_TOE_UTILS_H
#define _TIC_TAC_TOE_UTILS_H

#include <string>

namespace tic_tac_toe::utils {

	/**
	 * Replaces every occurrence of the char SEARCH with the char REPLACE in STR
	 * and returns the result.
	 *
	 * Param const std::string& str:
	 *     The original string.
	 *
	 * Param char search:
	 *     The character to search for.
	 *
	 * Param char replace:
	 *     The character to replace every occurrence of SEARCH.
	 *
	 * Since: 2019-05-30
	 */
	std::string search_replace(const std::string& str, char search, char replace);

}

#endif /* _TIC_TAC_TOE_UTILS_H */
