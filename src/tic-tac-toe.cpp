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
#include <regex>
#include <tic-tac-toe/utils.hpp>

using std::string;

namespace tic_tac_toe {

	field::field(field::symbol_t fillsym) {
		if(fillsym == field::symbol::INVALID)
			throw new std::invalid_argument("field: field::symbol::INVALID is not allowed");

		fill(fillsym);
	}

	/* ====================================================================== */
	/* public */

	field::symbol_t field::get_symbol(field::pos_t pos) const {
		return symbols[_pos_to_int(pos)];
	}

	void field::set_symbol(field::symbol_t symbol, field::pos_t pos) {
		if(symbol == field::symbol::INVALID)
			throw new std::invalid_argument("set_symbol: field::symbol::INVALID is not allowed");

		symbols[_pos_to_int(pos)] = symbol;
	}

	void field::fill(field::symbol_t symbol) {
		if(symbol == field::symbol::INVALID)
			throw new std::invalid_argument("fill: field::symbol::INVALID is not allowed");

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

	std::array<std::array<field::symbol_t, 3>, 3> field::data() const {
		std::array<std::array<field::symbol_t, 3>, 3> d;

		d[0][0] = symbols[0];
		d[1][0] = symbols[1];
		d[2][0] = symbols[2];

		d[0][1] = symbols[3];
		d[1][1] = symbols[4];
		d[2][1] = symbols[5];

		d[0][2] = symbols[6];
		d[1][2] = symbols[7];
		d[2][2] = symbols[8];

		return d;
	}

	std::array<std::array<char, 3>, 3> field::char_data() const {
		std::array<std::array<char, 3>, 3> d;

		d[0][0] = symtochar(symbols[0]);
		d[1][0] = symtochar(symbols[1]);
		d[2][0] = symtochar(symbols[2]);

		d[0][1] = symtochar(symbols[3]);
		d[1][1] = symtochar(symbols[4]);
		d[2][1] = symtochar(symbols[5]);

		d[0][2] = symtochar(symbols[6]);
		d[1][2] = symtochar(symbols[7]);
		d[2][2] = symtochar(symbols[8]);

		return d;
	}

	string field::str() const {
		std::array<std::array<char, 3>, 3> cd = char_data();

		string str;
		str = str + cd[0][0] + " | " + cd[1][0] + " | " + cd[2][0] + '\n';
		str += "--+---+--\n";
		str = str + cd[0][1] + " | " + cd[1][1] + " | " + cd[2][1] + '\n';
		str += "--+---+--\n";
		str = str + cd[0][2] + " | " + cd[1][2] + " | " + cd[2][2] + '\n';
		return str;
	}

	/* ====================================================================== */
	/* private */

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

	/* ====================================================================== */
	/* static */

	char field::symtochar(field::symbol_t symbol) {
		// *INDENT-OFF*
		switch(symbol) {
		case field::symbol::NONE: return ' ';
		case field::symbol::X:    return 'X';
		case field::symbol::O:    return 'O';
		case field::symbol::INVALID:
		default: return '\0';
		}
		// *INDENT-ON*
	}

	field::symbol_t field::chartosym(char ch) {
		// *INDENT-OFF*
		switch(std::tolower(ch)) {
		case ' ': return field::symbol::NONE;
		case 'x': return field::symbol::X;
		case 'o': return field::symbol::O;
		default:  return field::symbol::INVALID;
		}
		// *INDENT-ON*
	}

}
