#include <tic-tac-toe/tic-tac-toe.hpp>
#include <ncurses.h>
#include <tic-tac-toe/ascii.hpp>

using std::string;
using namespace tic_tac_toe;

constexpr field::symbol_t INIT_PLAYER = field::symbol::X;

enum class stat {
	RUNNING,
	WINNER_X, WINNER_O,
	STALEMATE,
	GAME_QUIT
};

void mvcurpos_up(field::pos_t& curpos);
void mvcurpos_left(field::pos_t& curpos);
void mvcurpos_right(field::pos_t& curpos);
void mvcurpos_down(field::pos_t& curpos);

void move_to_pos(field::pos_t pos);

int main() {
	field::symbol_t curplayer = field::symbol::NONE; // current player
	field::pos_t curpos = field::pos::UPPER_LEFT; // cursor position
	field_t field;

	stat stat = stat::RUNNING;

	// initializing ncurses
	initscr();
	noecho();
	raw();
	keypad(stdscr, true);

	{
		string drawfield = field.str();
		drawfield = drawfield + "Player: " + field::symtochar(INIT_PLAYER);

		// draw field
		clear();
		mvprintw(0, 0, drawfield.c_str());
	}

	// main game loop
	do {
		// switch player
		switch(curplayer) {
		case field::symbol::NONE: {
			curplayer = INIT_PLAYER;
			break;
		}
		case field::symbol::X: {
			curplayer = field::symbol::O;
			break;
		}
		case field::symbol::O: {
			curplayer = field::symbol::X;
			break;
		}
		}

		{
			string drawfield = field.str();
			drawfield = drawfield + "Player: " + field::symtochar(curplayer);

			// redraw field
			clear();
			mvprintw(0, 0, drawfield.c_str());
		}

		// move cursor back to where it was before we drew the field
		move_to_pos(curpos);

		// set this to false if an action is done that isn't just moving the
		// cursor or doing nothing at all
		bool curmv = true;
		do {
			// *INDENT-OFF*
			switch(getch()) {
			case ASCII::ETX: case ASCII::EOT: case ASCII::CAN:
			case 'q': case 'Q': { // quit game
				stat = stat::GAME_QUIT;
				curmv = false;
				break;
			}
			case ' ': case '\n': { // set symbol
				field::symbol_t tmpsym = field.get_symbol(curpos);
				if(tmpsym == field::symbol::NONE) {
					field.set_symbol(curplayer, curpos);
					curmv = false;
				}
				break;
			}
			case 'x': case 'X': { // set symbol if player is X
				if(curplayer == field::symbol::X) {
					field.set_symbol(field::symbol::X, curpos);
					curmv = false;
				}
				break;
			}
			case 'o': case 'O': { // set symbol if player is O
				if(curplayer == field::symbol::O) {
					field.set_symbol(field::symbol::O, curpos);
					curmv = false;
				}
				break;
			}
			case KEY_UP: case 'w': { // one step up
				mvcurpos_up(curpos);
				break;
			}
			case KEY_PPAGE: case 'W': { // to highest spot
				bool tmpb = true;
				while(tmpb) {
					// *INDENT-OFF*
					switch(curpos) {
					case field::pos::UPPER_LEFT:
					case field::pos::UPPER_MIDDLE:
					case field::pos::UPPER_RIGHT: {
						tmpb = false;
						break;
					}
					default: mvcurpos_up(curpos);
					}
					// *INDENT-ON*
				}
				break;
			}
			case KEY_HOME: case 'A': { // to left hand side
				bool tmpb = true;
				while(tmpb) {
					// *INDENT-OFF*
					switch(curpos) {
					case field::pos::UPPER_LEFT:
					case field::pos::MIDDLE_LEFT:
					case field::pos::LOWER_LEFT: {
						tmpb = false;
						break;
					}
					default: mvcurpos_left(curpos);
					}
					// *INDENT-ON*
				}
				break;
			}
			case KEY_NPAGE: case 'S': { // to lowest spot
				bool tmpb = true;
				while(tmpb) {
					// *INDENT-OFF*
					switch(curpos) {
					case field::pos::LOWER_LEFT:
					case field::pos::LOWER_MIDDLE:
					case field::pos::LOWER_RIGHT: {
						tmpb = false;
						break;
					}
					default: mvcurpos_down(curpos);
					}
					// *INDENT-ON*
				}
				break;
			}
			case KEY_END: case 'D': { // to right hand side
				bool tmpb = true;
				while(tmpb) {
					// *INDENT-OFF*
					switch(curpos) {
					case field::pos::UPPER_RIGHT:
					case field::pos::MIDDLE_RIGHT:
					case field::pos::LOWER_RIGHT: {
						tmpb = false;
						break;
					}
					default: mvcurpos_right(curpos);
					}
					// *INDENT-ON*
				}
				break;
			}
			case KEY_LEFT: case 'a': { // one step left
				mvcurpos_left(curpos);
				break;
			}
			case KEY_DOWN: case 's': { // one step down
				mvcurpos_down(curpos);
				break;
			}
			case KEY_RIGHT: case 'd': { // one step right
				mvcurpos_right(curpos);
				break;
			}
			default: continue;
			}
			// *INDENT-ON*

			// move cursor if move action was done
			if(curmv) move_to_pos(curpos);
		} while(curmv);

		{
			string drawfield = field.str();
			drawfield = drawfield + "Player: " + field::symtochar(curplayer);

			// redraw field
			clear();
			mvprintw(0, 0, drawfield.c_str());
		}

		switch(field.checkwin()) {
		case field::symbol::NONE: {
			if(field.checkstalemate()) stat = stat::STALEMATE;
			break;
		}
		case field::symbol::X: {
			stat = stat::WINNER_X;
			break;
		}
		case field::symbol::O: {
			stat = stat::WINNER_O;
			break;
		}
		}
	} while(stat == stat::RUNNING);

	string endmsg;

	switch(stat) {
	case stat::WINNER_X: {
		endmsg = "X wins!\n";
		break;
	}
	case stat::WINNER_O: {
		endmsg = "O wins!\n";
		break;
	}
	case stat::STALEMATE: {
		endmsg = "Stalemate! Nobody wins!\n";
		break;
	}
	}

	endmsg += "Press any key to quit...";

	curs_set(0); // make cursor invisible
	mvprintw(7, 0, endmsg.c_str());
	refresh();
	getch(); // wait for any user input
	endwin(); // end curses

	return 0;
}

void mvcurpos_up(field::pos_t& curpos) {
	// *INDENT-OFF*
	switch(curpos) {
		case field::pos::UPPER_LEFT:   curpos = field::pos::LOWER_LEFT; break;
		case field::pos::UPPER_MIDDLE: curpos = field::pos::LOWER_MIDDLE; break;
		case field::pos::UPPER_RIGHT:  curpos = field::pos::LOWER_RIGHT; break;

		case field::pos::MIDDLE_LEFT:  curpos = field::pos::UPPER_LEFT; break;
		case field::pos::MIDDLE:       curpos = field::pos::UPPER_MIDDLE; break;
		case field::pos::MIDDLE_RIGHT: curpos = field::pos::UPPER_RIGHT; break;

		case field::pos::LOWER_LEFT:   curpos = field::pos::MIDDLE_LEFT; break;
		case field::pos::LOWER_MIDDLE: curpos = field::pos::MIDDLE; break;
		case field::pos::LOWER_RIGHT:  curpos = field::pos::MIDDLE_RIGHT; break;
	}
	// *INDENT-ON*
}

void mvcurpos_left(field::pos_t& curpos) {
	// *INDENT-OFF*
	switch(curpos) {
		case field::pos::UPPER_LEFT:   curpos = field::pos::UPPER_RIGHT; break;
		case field::pos::UPPER_MIDDLE: curpos = field::pos::UPPER_LEFT; break;
		case field::pos::UPPER_RIGHT:  curpos = field::pos::UPPER_MIDDLE; break;

		case field::pos::MIDDLE_LEFT:  curpos = field::pos::MIDDLE_RIGHT; break;
		case field::pos::MIDDLE:       curpos = field::pos::MIDDLE_LEFT; break;
		case field::pos::MIDDLE_RIGHT: curpos = field::pos::MIDDLE; break;

		case field::pos::LOWER_LEFT:   curpos = field::pos::LOWER_RIGHT; break;
		case field::pos::LOWER_MIDDLE: curpos = field::pos::LOWER_LEFT; break;
		case field::pos::LOWER_RIGHT:  curpos = field::pos::LOWER_MIDDLE; break;
	}
	// *INDENT-ON*
}

void mvcurpos_right(field::pos_t& curpos) {
	// *INDENT-OFF*
	switch(curpos) {
		case field::pos::UPPER_LEFT:   curpos = field::pos::UPPER_MIDDLE; break;
		case field::pos::UPPER_MIDDLE: curpos = field::pos::UPPER_RIGHT; break;
		case field::pos::UPPER_RIGHT:  curpos = field::pos::UPPER_LEFT; break;

		case field::pos::MIDDLE_LEFT:  curpos = field::pos::MIDDLE; break;
		case field::pos::MIDDLE:       curpos = field::pos::MIDDLE_RIGHT; break;
		case field::pos::MIDDLE_RIGHT: curpos = field::pos::MIDDLE_LEFT; break;

		case field::pos::LOWER_LEFT:   curpos = field::pos::LOWER_MIDDLE; break;
		case field::pos::LOWER_MIDDLE: curpos = field::pos::LOWER_RIGHT; break;
		case field::pos::LOWER_RIGHT:  curpos = field::pos::LOWER_LEFT; break;
	}
	// *INDENT-ON*
}

void mvcurpos_down(field::pos_t& curpos) {
	// *INDENT-OFF*
	switch(curpos) {
		case field::pos::UPPER_LEFT:   curpos = field::pos::MIDDLE_LEFT; break;
		case field::pos::UPPER_MIDDLE: curpos = field::pos::MIDDLE; break;
		case field::pos::UPPER_RIGHT:  curpos = field::pos::MIDDLE_RIGHT; break;

		case field::pos::MIDDLE_LEFT:  curpos = field::pos::LOWER_LEFT; break;
		case field::pos::MIDDLE:       curpos = field::pos::LOWER_MIDDLE; break;
		case field::pos::MIDDLE_RIGHT: curpos = field::pos::LOWER_RIGHT; break;

		case field::pos::LOWER_LEFT:   curpos = field::pos::UPPER_LEFT; break;
		case field::pos::LOWER_MIDDLE: curpos = field::pos::UPPER_MIDDLE; break;
		case field::pos::LOWER_RIGHT:  curpos = field::pos::UPPER_RIGHT; break;
	}
	// *INDENT-ON*
}

void move_to_pos(field::pos_t pos) {
	// *INDENT-OFF*
	switch(pos) {
	case field::pos::UPPER_LEFT: move(0, 0); break;
	case field::pos::UPPER_MIDDLE: move(0, 4); break;
	case field::pos::UPPER_RIGHT: move(0, 8); break;

	case field::pos::MIDDLE_LEFT: move(2, 0); break;
	case field::pos::MIDDLE: move(2, 4); break;
	case field::pos::MIDDLE_RIGHT: move(2, 8); break;

	case field::pos::LOWER_LEFT: move(4, 0); break;
	case field::pos::LOWER_MIDDLE: move(4, 4); break;
	case field::pos::LOWER_RIGHT: move(4, 8); break;
	}
	// *INDENT-ON*
}
