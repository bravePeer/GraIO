#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "utilities.h"
#include "gui.h"
#include "mainGame.h"
#include "user.h"

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
	MainMenu();
	MainMenu(Font* _font);
	~MainMenu();
	
	State* IsStateChanged();
	void Update(RenderWindow* window, Time* elapsed);
	void Render(RenderTarget* target);
private:
	Button** buttons;
	short buttonPressed;
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
	LoginMenu();
	LoginMenu(Font* _font);
	~LoginMenu();
	
	State* IsStateChanged();
	void AddLetter(wchar_t s);
	void Update(RenderWindow* window, Time* elapsed);
	void Render(RenderTarget* target);
private:
	InputBox** inputBoxes;
	Button** buttons;
	Font* font;
	short inputBoxPressed;
	short buttonPressed;

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
class RegisterMenu : public State
{
public:
	RegisterMenu();
	RegisterMenu(Font* _font);
	~RegisterMenu();

	State* IsStateChanged();
	void AddLetter(wchar_t s);
	void Update(RenderWindow* window, Time* elapsed);
	void Render(RenderTarget* target);
private:
	InputBox** inputBoxes;
	Button** buttons;
	Font* font;
	short inputBoxPressed;
	short buttonPressed;
	enum INPUTBOXESID
	{
		INPUTBOXLOGIN, INPUTBOXPASSWORD, ALLINPUTBOXES
	};
	enum BUTTONSID
	{
		BUTTONREGISTER, BUTTONBACK, ALLBUTTONS
	};
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
	StartMenu();
	StartMenu(Font* _font);
	~StartMenu();

	//Który przycisk wciœniêty
	short GetButtonPressed();
	State* IsStateChanged();

	void Update(RenderWindow* window, Time* elapsed);
	void Render(RenderTarget* target);
private:
	Button** buttons;
	Font* font;
	short buttonPressed;

	enum BUTTONSID
	{
		BUTTONLOGIN, BUTTONREGISTER, BUTTONSKIP, BUTTONEXIT, NUMBUTTONS
	};
};

/* --- MainMenu --- */
MainMenu::MainMenu()
{
	buttons = nullptr;
	font = nullptr;
	buttonPressed = -1;
}
MainMenu::MainMenu(Font* _font)
	:font(_font)
{
	buttons = new Button * [NUMBUTTONS];
	buttons[BUTTONSTARTGAME] = new Button({ 200,50 }, { 200,240 }, font, L"Rozpocznij grê", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
	buttons[BUTTONLOADGAME] = new Button({ 200,50 }, { 200,300 }, font, L"Wczytaj grê", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
	buttons[BUTTONSETTINGS] = new Button({ 200,50 }, { 200,360 }, font, L"Ustawienia", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
	buttons[BUTTONEXIT] = new Button({ 200,50 }, { 200,420 }, font, L"Wyjœcie", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
	buttonPressed = -1;
}
MainMenu::~MainMenu()
{
	for (short i = 0; i < NUMBUTTONS; i++)
	{
		delete buttons[i];
	}
	delete[] buttons;
}

State* MainMenu::IsStateChanged()
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
void MainMenu::Update(RenderWindow* window, Time* elapsed)
{
	for (short i = 0; i < NUMBUTTONS; i++)
	{
		buttons[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));

		if (buttons[i]->GetButtonState() == PRESSED)
			buttonPressed = i;
	}
}
void MainMenu::Render(RenderTarget* target)
{
	for (short i = 0; i < NUMBUTTONS; i++)
	{
		buttons[i]->Render(target);
	}
}


/* --- LoginMenu --- */
LoginMenu::LoginMenu()
{
	font = nullptr;
	inputBoxes = nullptr;
	buttons = nullptr;
	inputBoxPressed = -1;
	buttonPressed = -1;
}
LoginMenu::LoginMenu(Font* _font)
	:font(_font)
{
	inputBoxes = new InputBox * [2];
	inputBoxes[INPUTBOXLOGIN] = new InputBox({ 200,50 }, { 200,50 }, font, L"Login", Color(128, 255, 191), Color(0, 179, 89), Color(0, 153, 77));
	inputBoxes[INPUTBOXPASSWORD] = new InputBox({ 200,50 }, { 200,110 }, font, L"Has³o", Color(128, 255, 191), Color(0, 179, 89), Color(0, 153, 77));

	buttons = new Button * [2];
	buttons[BUTTONLOGIN] = new Button({ 200,50 }, { 200,300 }, font, L"Zaloguj", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
	buttons[BUTTONBACK] = new Button({ 200,50 }, { 200,360 }, font, L"Powrót", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
	inputBoxPressed = -1;
	buttonPressed = -1;
}
LoginMenu::~LoginMenu()
{
	for (int i = 0; i < ALLINPUTBOXES; i++)
	{
		delete inputBoxes[i];
	}
	delete inputBoxes;
	for (int i = 0; i < ALLBUTTONS; i++)
	{
		delete buttons[i];
	}
	delete buttons;
}

State* LoginMenu::IsStateChanged()
{
	if (buttonPressed == 0)
	{
		//Sprawdzanie czy mozliwe zalogowanie
		try
		{
			User::Login(inputBoxes[INPUTBOXLOGIN]->GetTypedString(), inputBoxes[INPUTBOXPASSWORD]->GetTypedString());
		}
		catch (const String&s)
		{
			cout << &s << endl;
		}
		cout <<(string) User::GetLogin() << endl;
		cout << "Not working yet" << endl;
		return new StartMenu(font);
	}
	else if (buttonPressed == 1)
		return new StartMenu(font);
	
	return nullptr;
}
void LoginMenu::AddLetter(wchar_t s)
{
	if (inputBoxes[inputBoxPressed]->GetInputBoxState() == PRESSED)
		inputBoxes[inputBoxPressed]->AddLetter(s);
	else
		inputBoxPressed = -1;
}
void LoginMenu::Update(RenderWindow* window, Time* elapsed)
{
	for (int i = 0; i < ALLINPUTBOXES; i++)
	{
		inputBoxes[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));

		if (inputBoxes[i]->GetInputBoxState() == PRESSED)
			inputBoxPressed = i;
	}

	for (int i = 0; i < ALLBUTTONS; i++)
	{
		buttons[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));

		if (buttons[i]->GetButtonState() == PRESSED)
			buttonPressed = i;
	}
}
void LoginMenu::Render(RenderTarget* target)
{
	for (int i = 0; i < ALLINPUTBOXES; i++)
		inputBoxes[i]->Render(target);
	
	for (int i = 0; i < ALLBUTTONS; i++)
		buttons[i]->Render(target);
}



/* --- RegisterMenu --- */
RegisterMenu::RegisterMenu()
{
	font = nullptr;
	inputBoxes = nullptr;
	buttons = nullptr;
	inputBoxPressed = -1;
	buttonPressed = -1;
}
RegisterMenu::RegisterMenu(Font* _font)
	:font(_font)
{
	inputBoxes = new InputBox * [2];
	inputBoxes[INPUTBOXLOGIN] = new InputBox({ 200,50 }, { 200,50 }, font, L"Login", Color(128, 255, 191), Color(0, 179, 89), Color(0, 153, 77));
	inputBoxes[INPUTBOXPASSWORD] = new InputBoxPassword({ 200,50 }, { 200,110 }, font, L"Has³o", Color(128, 255, 191), Color(0, 179, 89), Color(0, 153, 77));
	
	buttons = new Button * [2];
	buttons[BUTTONREGISTER] = new Button({ 200,50 }, { 200,300 }, font, L"Zarejestruj", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
	buttons[BUTTONBACK] = new Button({ 200,50 }, { 200,360 }, font, L"Powrót", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
	
	inputBoxPressed = -1;
	buttonPressed = -1;
}
RegisterMenu::~RegisterMenu()
{
	for (int i = 0; i < ALLINPUTBOXES; i++)
	{
		delete inputBoxes[i];
	}
	delete inputBoxes;
	for (int i = 0; i < ALLBUTTONS; i++)
	{
		delete buttons[i];
	}
	delete buttons;
}

State* RegisterMenu::IsStateChanged()
{
	if (buttonPressed == 0)
	{
		//Sprawdzanie czy mozliwa rejestracja
		try
		{
			User::Register(inputBoxes[INPUTBOXLOGIN]->GetTypedString(), inputBoxes[INPUTBOXPASSWORD]->GetTypedString());
			cout << (string)User::GetLogin() << endl;
			return new StartMenu(font);
		}
		catch (const char* s)
		{
			cout << s << endl;
			buttonPressed = -1;
		}
		
	}
	else if (buttonPressed == 1)
		return new StartMenu(font);

	return nullptr;
}
void RegisterMenu::AddLetter(wchar_t s)
{
	if (inputBoxes[inputBoxPressed]->GetInputBoxState() == PRESSED)
		inputBoxes[inputBoxPressed]->AddLetter(s);
	else
		inputBoxPressed = -1;
}
void RegisterMenu::Update(RenderWindow* window, Time* elapsed)
{
	//cout << "awd" << endl;
	for (int i = 0; i < ALLINPUTBOXES; i++)
	{
		inputBoxes[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));

		if (inputBoxes[i]->GetInputBoxState() == PRESSED)
			inputBoxPressed = i;
	}

	for (int i = 0; i < ALLBUTTONS; i++)
	{
		buttons[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));

		if (buttons[i]->GetButtonState() == PRESSED)
			buttonPressed = i;
	}
}
void RegisterMenu::Render(RenderTarget* target)
{
	for (int i = 0; i < ALLINPUTBOXES; i++)
		inputBoxes[i]->Render(target);

	for (int i = 0; i < ALLBUTTONS; i++)
		buttons[i]->Render(target);
}





/* --- StartMenu --- */
StartMenu::StartMenu()
{
	buttons = nullptr;
	font = nullptr;
	buttonPressed = -1;
}
StartMenu::StartMenu(Font* _font)
{
	font = _font;
	buttons = new Button * [NUMBUTTONS];//new Button({ 200,200 }, { 200,100 }, font, "butt1", Color(255, 0, 0, 255), Color(249, 0, 0, 255), Color(150, 0, 0, 255));
	buttons[BUTTONLOGIN] = new Button({ 200,50 }, { 200,240 }, font, L"Zaloguj", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
	buttons[BUTTONREGISTER] = new Button({ 200,50 }, { 200,300 }, font, L"Zarejestruj", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
	buttons[BUTTONSKIP] = new Button({ 200,50 }, { 200,360 }, font, L"Graj bez logowania", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
	buttons[BUTTONEXIT] = new Button({ 200,50 }, { 200,420 }, font, L"Wyjœcie", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
	buttonPressed = -1;
}
StartMenu::~StartMenu()
{
	for (short i = 0; i < NUMBUTTONS; i++)
	{
		delete buttons[i];
	}
	delete[] buttons;
}

State* StartMenu::IsStateChanged()
{
	switch (buttonPressed)
	{
	case BUTTONLOGIN:
		return new LoginMenu(font);
		break;
	case BUTTONREGISTER:
		return new RegisterMenu(font);
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
short StartMenu::GetButtonPressed()
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
void StartMenu::Update(RenderWindow* window, Time* elapsed)
{
	for (short i = 0; i < NUMBUTTONS; i++)
	{
		buttons[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));

		if (buttons[i]->GetButtonState() == PRESSED)
			buttonPressed = i;
	}
}
void StartMenu::Render(RenderTarget* target)
{
	for (short i = 0; i < NUMBUTTONS; i++)
	{
		buttons[i]->Render(target);
	}
}

