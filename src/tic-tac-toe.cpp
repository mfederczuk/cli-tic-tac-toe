// src/tic-tac-toe.cpp
/**
 * tic-tac-toe.hpp implementation.
 * Main source file for the Tic-Tac-Toe game.
 *
 * Since: 2019-05-30
 * LastEdit: 2019-05-30
 */

#include <tic-tac-toe/tic-tac-toe.hpp>
#include <stdexcept>
#include <string>
#include <regex>
#include <tic-tac-toe/utils.hpp>

using std::string;

namespace tic_tac_toe {

	field::field(field::symbol_t fillsym) {
		fill(fillsym);
	}

	field::symbol_t field::get_symbol(field::pos_t pos) const {
		return symbols[_pos_to_int(pos)];
	}

	void field::set_symbol(field::symbol_t symbol, field::pos_t pos) {
		symbols[_pos_to_int(pos)] = symbol;
	}

	void field::fill(field::symbol_t symbol) {
		for(size_t i = 0; i < 9; ++i) {
			symbols[i] = symbol;
		}
	}

	void field::clear() {
		for(size_t i = 0; i < 9; ++i) {
			symbols[i] = symbol::NONE;
		}
	}

	field::symbol_t field::checkwin() const {
		string fstr(9, ' ');
		for(size_t i = 0; i < 9; ++i) {
			fstr[i] = symtochar(symbols[i]);
		}

		// pattern template to match horizontal wins
		const string H_T_PATTERN = "(|...|......)___(|...|......)";
		// pattern template to match vertical wins
		const string V_T_PATTERN = ".?.?_.._.._.?.?";
		// pattern template to match cross1 wins
		const string C1_T_PATTERN = "_..._..._";
		// pattern template to match cross2 wins
		const string C2_T_PATTERN = ".._._._..";

		// combined template pattern
		const string T_PATTERN = string("^(")
		                         + H_T_PATTERN + "|"
		                         + V_T_PATTERN + "|"
		                         + C1_T_PATTERN + "|"
		                         + C2_T_PATTERN + ")$";

		const std::regex X_PATTERN(utils::search_replace(T_PATTERN, '_', 'X'));
		const std::regex O_PATTERN(utils::search_replace(T_PATTERN, '_', 'O'));

		bool xwin = std::regex_match(fstr, X_PATTERN);
		bool owin = std::regex_match(fstr, O_PATTERN);

		if(xwin && owin) {
			throw std::logic_error(
			        "checkwin: Both X and O are in winning positions");
		} else if(xwin && !owin) {
			return symbol::X;
		} else if(!xwin && owin) {
			return symbol::O;
		} else { /* if(!xwin && !owin) */
			return symbol::NONE;
		}
	}

	bool field::checkstalemate() const {
		// if somebody already won it's not a stalemate
		if(checkwin() != symbol::NONE) return false;

		for(size_t i = 0; i < 9; ++i) {
			// just check if there are still empty spots. if yes; not a stalemate
			if(symbols[i] == symbol::NONE) return false;
		}

		return false;
	}

	unsigned short int field::_pos_to_int(field::pos_t p) const {
		// *INDENT-OFF*
		switch(p) {
		case field::pos::UPPER_LEFT:   return 0;
		case field::pos::UPPER_MIDDLE: return 1;
		case field::pos::UPPER_RIGHT:  return 2;

		case field::pos::MIDDLE_LEFT:  return 3;
		case field::pos::MIDDLE:       return 4;
		case field::pos::MIDDLE_RIGHT: return 5;

		case field::pos::LOWER_LEFT:   return 6;
		case field::pos::LOWER_MIDDLE: return 7;
		case field::pos::LOWER_RIGHT:  return 8;

		default: return -1;
		}
		// *INDENT-ON*
	}

	char field::symtochar(field::symbol_t symbol) {
		// *INDENT-OFF*
		switch(symbol) {
		case field::symbol::NONE: return ' ';
		case field::symbol::X:    return 'X';
		case field::symbol::O:    return 'O';
		default: return '\0';
		}
		// *INDENT-ON*
	}

}
