#pragma once
/*Ten plik zawiera podstawowe enum'y i moze jakie� statyczne funkcje globalne*/

enum GAMESTATE
{
	STARTMENU, LOGINMENU, REGISTEMENU, MAINMENU, GAME, NEWGAME, LOADGAME, EXITGAME
};

enum ButtonStates {
	IDLE, HOVER, PRESSED
};