// include/tic-tac-toe/tic-tac-toe.hpp
/**
 * Main header file for the Tic-Tac-Toe game.
 *
 * Since: 2019-05-30
 * LastEdit: 2019-05-30
 */

#ifndef _TIC_TAC_TOE_H
#define _TIC_TAC_TOE_H

#include <array>

namespace tic_tac_toe {

	typedef unsigned short int symbol_t;
	inline namespace symbol {
		constexpr symbol_t NONE = 0;
		constexpr symbol_t X    = 1;
		constexpr symbol_t Y    = 2;
	}

	typedef unsigned short int pos_t;
	inline namespace pos {
		constexpr pos_t UPPER_LEFT   = 0;
		constexpr pos_t UPPER_MIDDLE = 1;
		constexpr pos_t UPPER_RIGHT  = 2;
		constexpr pos_t MIDDLE_LEFT  = 3;
		constexpr pos_t MIDDLE       = 4;
		constexpr pos_t MIDDLE_RIGHT = 5;
		constexpr pos_t LOWER_LEFT   = 6;
		constexpr pos_t LOWER_MIDDLE = 7;
		constexpr pos_t LOWER_RIGHT  = 8;

		constexpr pos_t MIN = UPPER_LEFT;
		constexpr pos_t MAX = LOWER_RIGHT;
	}

	typedef std::array<symbol_t, 9> field_t;

	/**
	 * Sets SYMBOL to FIELD at POS.
	 *
	 * Param tic_tac_toe::symbol_t symbol:
	 *     The symbol to set.
	 *
	 * Param tic_tac_toe::pos_t pos:
	 *     The position to set the symbol to.
	 *
	 * Param tic_tac_toe::field_t& field:
	 *     Reference to a field to set the symbol in.
	 *
	 * Since: 2019-05-30
	 */
	void set_symbol(symbol_t symbol, pos_t pos, field_t& field);
	/**
	 * Checks if a symbol has won.
	 *
	 * Param const tic_tac_toe::field_t& field:
	 *     The field to check for a win.
	 *
	 * Return: tic_tac_toe::symbol_t
	 *     The symbol that has won, or NONE if no symbol has won yet.
	 *
	 * Since: 2019-05-30
	 */
	symbol_t checkwin(const field_t& field);
	/**
	 * Checks if the field is in a stalemate.
	 *
	 * Param const tic_tac_toe::field_t& field:
	 *     The field to check in.
	 *
	 * Return: bool
	 *     true if the field is in a stalemate, false if otherwise.
	 *
	 * Since: 2019-05-30
	 */
	bool checkstalemate(const field_t& field);

}

#endif /* _TIC_TAC_TOE_H */
