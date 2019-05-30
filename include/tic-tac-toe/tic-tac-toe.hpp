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
		constexpr symbol_t O    = 2;

		inline bool _valid_symbol(symbol_t symbol) {
			return (symbol == symbol::NONE
			        || symbol == symbol::X || symbol == symbol::O);
		}
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

		inline bool _valid_pos(pos_t pos) {
			return (pos >= pos::MIN && pos <= pos::MAX);
		}
	}

	typedef std::array<symbol_t, 9> field_t;
	inline namespace field {
		inline bool _valid_field(const field_t& field) {
			for(size_t i = 0, s = field.size(); i < s; ++i) {
				if(!_valid_symbol(field[i])) return false;
			}
			return true;
		}
	}

	/**
	 * Returns the symbol of the FIELD at POS.
	 *
	 * Param const field_t& field:
	 *     The field to get a symbol from.
	 *
	 * Param pos_t pos:
	 *     The position to get the symbol from.
	 *
	 * Return: symbol_t
	 *     The symbol of FIELD at POS.
	 *
	 * Since: 2019-05-30
	 */
	symbol_t get_symbol(const field_t& field, pos_t pos);
	/**
	 * Sets SYMBOL to FIELD at POS.
	 *
	 * Param tic_tac_toe::symbol_t symbol:
	 *     The symbol to set.
	 *
	 * Param tic_tac_toe::field_t& field:
	 *     Reference to a field to set the symbol in.
	 *
	 * Param tic_tac_toe::pos_t pos:
	 *     The position to set the symbol to.
	 *
	 * Since: 2019-05-30
	 */
	void set_symbol(symbol_t symbol, field_t& field, pos_t pos);
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
