/*
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 * Copyright (c) 2019 Michael Federczuk
 */
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
#include <string>

namespace tic_tac_toe {

	/**
	 * Class for a Tic-Tac-Toe field.
	 *
	 * Since: 2019-05-30
	 * LastEdit: 2019-05-30
	 */
	class field {

		public:
			/**
			 * The three symbols that can be placed on the Tic-Tac-Toe field:
			 * NONE, X and O and INVALID, which is rarely used.
			 *
			 * Since: 2019-05-30
			 * LastEdit: 2019-05-30
			 */
			enum class symbol : unsigned short int {
				NONE,
				X, O,
				INVALID
			};
			typedef symbol symbol_t;

			/**
			 * Available positions on the field.
			 *
			 * Since: 2019-05-30
			 * LastEdit: 2019-05-30
			 */
			enum class pos : unsigned short int {
				UPPER_LEFT,  UPPER_MIDDLE, UPPER_RIGHT,
				MIDDLE_LEFT, MIDDLE,       MIDDLE_RIGHT,
				LOWER_LEFT,  LOWER_MIDDLE, LOWER_RIGHT,
				INVALID
			};
			typedef pos pos_t;

		private:
			symbol_t symbols[9];

		public:
			/**
			 * Constructs a new field object.
			 *
			 * Param tic_tac_toe::field::symbol_t fillsym = tic_tac_toe::field::symbol::NONE:
			 *     The symbol to initially fill the field with.
			 *
			 * Since: 2019-05-30
			 */
			field(symbol_t fillsym = symbol::NONE);

			/**
			 * Returns the symbol at position POS.
			 *
			 * Param tic_tac_toe::field::pos_t pos:
			 *     The position to get the symbol from.
			 *
			 * Return: tic_tac_toe::field::symbol_t
			 *     The symbol at position POS.
			 *
			 * Since: 2019-05-30
			 */
			symbol_t get_symbol(pos_t pos) const;
			/**
			 * Overrides the symbol at position POS with SYMBOL.
			 *
			 * Param tic_tac_toe::field::symbol_t symbol:
			 *     The new value of the symbol.
			 *
			 * Param tic_tac_toe::field::pos_t pos:
			 *     The position to set the new symbol at.
			 *
			 * Since: 2019-05-30
			 */
			void set_symbol(symbol_t symbol, pos_t pos);
			/**
			 * Sets the symbol at every position to SYMBOL.
			 *
			 * Param tic_tac_toe::field::symbol_t symbol:
			 *     The symbol to fill the field with.
			 *
			 * Since: 2019-05-30
			 */
			void fill(symbol_t symbol);
			/**
			 * Fills the field with symbol symbol::NONE.
			 *
			 * Since: 2019-05-30
			 */
			void clear();

			/**
			 * Checks with symbol is in a winning position, returns either
			 * symbol::X, symbol::O or symbol::NONE.
			 *
			 * Return: tic_tac_toe::field::symbol_t
			 *     Which symbol is in a winning position, or symbol::NONE if
			 *     none has won yet.
			 *
			 * Since: 2019-05-30
			 */
			symbol_t checkwin() const;
			/**
			 * Checks if the field is in a stalemate.
			 *
			 * Return: bool
			 *     true if the field is in a stalemate, false if otherwise.
			 *
			 * Since: 2019-05-30
			 */
			bool checkstalemate() const;

			/**
			 * Returns a two-dimensional std::array with all symbols of the
			 * field.
			 *
			 * Return: std::array<std::array<tic_tac_toe::field::symbol_t, 3>, 3>
			 *     A two-dimensional std::array with all symbols.
			 *
			 * Since: 2019-05-30
			 */
			std::array<std::array<symbol_t, 3>, 3> data() const;
			/**
			 * Returns a two-dimensional std::array with all symbols of the
			 * field, converted to chars using the symtochar(symbol_t) function.
			 *
			 * Return: std::array<std::array<char, 3>, 3>
			 *     A two-dimensional std::array with all symbols as chars.
			 *
			 * Since: 2019-05-30
			 */
			std::array<std::array<char, 3>, 3> char_data() const;

			/**
			 * Returns a string representation of this field.
			 *
			 * Return: std::string
			 *     A pretty string, showing all symbols.
			 *
			 * Since: 2019-05-30
			 */
			std::string str() const;

		public:
			/**
			 * Turns the entered symbol SYMBOL into a char and returns it.
			 *
			 * Param tic_tac_toe::field::symbol_t symbol:
			 *     The symbol to convert to a char.
			 *
			 * Return: char
			 *     The converted symbol.
			 *
			 * Since: 2019-05-30
			 */
			static char symtochar(symbol_t symbol);
			/**
			 * Turns the entered char CH into a symbol and returns it.
			 *
			 * If the char can't be converted, then symbol::INVALID will be
			 * returned.
			 *
			 * Param char ch:
			 *     The char to convert to a symbol.
			 *
			 * Return: tic_tac_toe::field::symbol_t
			 *     The converted char.
			 *
			 * Since: 2019-05-30
			 */
			static symbol_t chartosym(char ch);

			/**
			 * Turns the entered position POS into an unsigned short int and
			 * returns it.
			 *
			 * Param tic_tac_toe::field::pos_t pos:
			 *     The position to convert to a int.
			 *
			 * Return: unsigned short int
			 *     The converted position.
			 *
			 * Since: 2019-05-30
			 */
			static unsigned short int postoint(pos_t pos);
			/**
			 * Turns the entered unsigned short int I into a position and
			 * returns it.
			 *
			 * If the int can't be converted, then pos::INVALID will be returned.
			 *
			 * Param unsigned short int i:
			 *     The int to convert to a position.
			 *
			 * Return: tic_tac_toe::field::pos_t
			 *     The converted int.
			 *
			 * Since: 2019-05-30
			 */
			static pos_t intopos(unsigned short int i);

	};
	typedef field field_t;

}

#endif /* _TIC_TAC_TOE_H */
