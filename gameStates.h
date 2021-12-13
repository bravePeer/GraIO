#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "utilities.h"
#include "gui.h"
#include "mainGame.h"

using namespace sf;
using namespace std;




//Wyjœcie z gry
class CloseMenu : public State
{
public:
	void Render(RenderTarget* target)
	{
		dynamic_cast<RenderWindow*>(target)->close();
	}
private:
};


//MainMenu
class MainMenu : public State
{
public:
	MainMenu()
	{
		buttons = nullptr;
	}
	MainMenu(Font* _font)
		:font(_font)
	{
		buttons = new Button * [NUMBUTTONS];
		buttons[BUTTONSTARTGAME] = new Button({ 200,50 }, { 200,240 }, font, L"Rozpocznij grê", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
		buttons[BUTTONLOADGAME] = new Button({ 200,50 }, { 200,300 }, font, L"Wczytaj grê", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
		buttons[BUTTONSETTINGS] = new Button({ 200,50 }, { 200,360 }, font, L"Ustawienia", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
		buttons[BUTTONEXIT] = new Button({ 200,50 }, { 200,420 }, font, L"Wyjœcie", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
	}
	~MainMenu()
	{
		for (short i = 0; i < NUMBUTTONS; i++)
		{
			delete buttons[i];
		}
		delete[] buttons;
	}

	State* IsStateChanged()
	{
		switch (buttonPressed)
		{
		case BUTTONSTARTGAME:
			return new MainGame(font);
			break;
		case BUTTONLOADGAME:
			return nullptr;
			break;
		case BUTTONSETTINGS:
			return nullptr;
			break;
		case BUTTONEXIT:
			return new CloseMenu;
			break;
		}
		return nullptr;
	}
	void Update(RenderWindow* window, Time* elapsed)
	{
		for (short i = 0; i < NUMBUTTONS; i++)
		{
			buttons[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));

			if (buttons[i]->GetButtonState() == PRESSED)
				buttonPressed = i;
		}
	}
	void Render(RenderTarget* target)
	{
		for (short i = 0; i < NUMBUTTONS; i++)
		{
			buttons[i]->Render(target);
		}
	}
private:
	Button** buttons;
	short buttonPressed = -1;
	Font* font;

	enum BUTTONSID
	{
		BUTTONSTARTGAME, BUTTONLOADGAME, BUTTONSETTINGS, BUTTONEXIT, NUMBUTTONS
	};
};


//Logowanie
class LoginMenu : public State
{
public:
	LoginMenu()
	{
		font = nullptr;
		inputBoxes = nullptr;
		checkButton = nullptr;
	}
	LoginMenu(Font*_font)
		:font(_font)
	{
		inputBoxes = new InputBox*[2];

		inputBoxes[INPUTBOXLOGIN] = new InputBox({ 200,50 }, { 200,50 }, font, L"Login", Color(128, 255, 191), Color(0, 179, 89), Color(0, 153, 77));
		inputBoxes[INPUTBOXPASSWORD] = new InputBox({ 200,50 }, { 200,110 }, font, L"Has³o", Color(128, 255, 191), Color(0, 179, 89), Color(0, 153, 77));
		checkButton = new Button({ 200,50 }, { 200,300 }, font, L"Zaloguj", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
		
	}
	~LoginMenu()
	{
		for (int i = 0; i < ALLINPUTBOXES; i++)
		{
			delete inputBoxes[i];
		}
		delete inputBoxes;
		delete checkButton;
	}
	
	State* IsStateChanged()
	{
		if (checkButton->GetButtonState() == PRESSED)
		{
			//Sprawdzanie czy mozliwe zalogowanie
			cout << "Not working yet" << endl;
			//return new StartMenu(font);
		}
		return nullptr;
	}
	void AddLetter(wchar_t s)
	{
		if (inputBoxes[inputBoxPressed]->GetInputBoxState() == PRESSED)
			inputBoxes[inputBoxPressed]->AddLetter(s);
		else
			inputBoxPressed = -1;
	}
	void Update(RenderWindow* window,Time*elapsed)
	{
		for (int i = 0; i < ALLINPUTBOXES; i++)
		{
			inputBoxes[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));
			
			if (inputBoxes[i]->GetInputBoxState() == PRESSED)
				inputBoxPressed = i;
		}



		checkButton->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));
	}
	void Render(RenderTarget* target)
	{
		for (int i = 0; i < ALLINPUTBOXES; i++)
			inputBoxes[i]->Render(target);

		checkButton->Render(target);
	}
private:
	InputBox** inputBoxes;

	Button* checkButton;

	Font* font;
	short inputBoxPressed = -1;


	enum INPUTBOXESID
	{
		INPUTBOXLOGIN,INPUTBOXPASSWORD,ALLINPUTBOXES
	};
	enum BUTTONSID
	{
		BUTTONLOGIN,BUTTONBACK,ALLBUTTONS
	};
};

//Rejestracja
class RegisterMenu
{

};

class LoadGameMenu
{

};

class NewGameMenu
{

};


//StartMenu
class StartMenu : public State
{
public:
	StartMenu()
	{
	}
	StartMenu(Font* _font)
	{
		font = _font;
		buttons = new Button * [NUMBUTTONS];//new Button({ 200,200 }, { 200,100 }, font, "butt1", Color(255, 0, 0, 255), Color(249, 0, 0, 255), Color(150, 0, 0, 255));
		buttons[BUTTONLOGIN] = new Button({ 200,50 }, { 200,240 }, font, L"Zaloguj", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
		buttons[BUTTONREGISTER] = new Button({ 200,50 }, { 200,300 }, font, L"Zarejestruj", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
		buttons[BUTTONSKIP] = new Button({ 200,50 }, { 200,360 }, font, L"Graj bez logowania", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
		buttons[BUTTONEXIT] = new Button({ 200,50 }, { 200,420 }, font, L"Wyjœcie", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));

	}
	~StartMenu()
	{
		for (short i = 0; i < NUMBUTTONS; i++)
		{
			delete buttons[i];
		}
		delete[] buttons;
	}

	State* IsStateChanged()
	{
		switch (buttonPressed)
		{
		case BUTTONLOGIN:
			return nullptr;// new LoginMenu(font);
			break;
		case BUTTONREGISTER:
			return nullptr;
			break;
		case BUTTONSKIP:
			return new MainMenu(font);
			break;
		case BUTTONEXIT:
			return new CloseMenu;
			break;
		}
		return nullptr;
	}

	void Update(RenderWindow* window, Time* elapsed)
	{
		for (short i = 0; i < NUMBUTTONS; i++)
		{
			buttons[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));

			if (buttons[i]->GetButtonState() == PRESSED)
				buttonPressed = i;
		}
	}
	void Render(RenderTarget* target)
	{
		for (short i = 0; i < NUMBUTTONS; i++)
		{
			buttons[i]->Render(target);
		}
	}

	//Który przycisk wciœniêty
	short GetButtonPressed()
	{
		switch (buttonPressed)
		{
		case BUTTONLOGIN:
			return LOGINMENU;
			break;
		case BUTTONREGISTER:
			return REGISTEMENU;
			break;
		case BUTTONSKIP:
			return MAINMENU;
			break;
		case BUTTONEXIT:
			return EXITGAME;
			break;
		}
		return STARTMENU;
	}


private:
	Button** buttons = nullptr;
	Font* font = nullptr;
	short buttonPressed = -1;


	enum BUTTONSID
	{
		BUTTONLOGIN, BUTTONREGISTER, BUTTONSKIP, BUTTONEXIT, NUMBUTTONS
	};
};