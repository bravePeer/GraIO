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



//Wyj�cie z gry
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

class SaveGameMenu
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
	StartMenu();
	StartMenu(Font* _font);
	~StartMenu();

	//Kt�ry przycisk wci�ni�ty
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

//czy to ma sens? xd
class NothingState : public State
{
public:
	NothingState() { }
	~NothingState() { }
};

class PauseMenu : public State
{
public:
	PauseMenu()
	{
		buttons = nullptr;
		font = nullptr;
		buttonPressed = -1;
	}
	PauseMenu(Font* _font)
		:font(_font)
	{
		buttons = new Button * [NUMBUTTONS];
		buttons[BUTTONRESUME] = new Button({ 200,50 }, { 200,240 }, font, L"Wzn�w gre", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
		buttons[BUTTONSAVE] = new Button({ 200,50 }, { 200,300 }, font, L"Zapisz gre", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
		buttons[BUTTONLOAD] = new Button({ 200,50 }, { 200,360 }, font, L"Wczytaj gr�", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
		buttons[BUTTONMAINMENU] = new Button({ 200,50 }, { 200,420 }, font, L"Wr�� do menu", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
		buttons[BUTTONEXIT] = new Button({ 200,50 }, { 200,480 }, font, L"Wyj�cie z gry", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
		buttonPressed = -1;
	}
	~PauseMenu()
	{
		for (short i = 0; i < NUMBUTTONS; i++)
		{
			delete buttons[i];
		}
		delete[] buttons;
	}

	//Kt�ry przycisk wci�ni�ty
	//short GetButtonPressed()
	
	void SetIsGamePaused(bool *set)
	{
		isGamePaused = set;
	}
	//bool GetIsGamePaused()
	//{
	//	return isGamePaused;
	//}

	State* IsStateChanged()
	{
		switch (buttonPressed)
		{
		case BUTTONRESUME:
			buttonPressed = -1;
			*isGamePaused = false;
			changed = true;
			return nullptr;
			break;
		case BUTTONSAVE:
			return new LoginMenu(font);// tymczasowo
			break;
		case BUTTONMAINMENU:
			return new MainMenu(font);
			break;
		case BUTTONEXIT:
			return new CloseMenu;
			break;
		}
		return nullptr;
	}

	void ChangeButtonPos(Vector2f pos)
	{
		if (changed)
		{
			for (int i = 0; i < NUMBUTTONS; i++)
			{
				buttons[i]->Move(pos);
			}
			changed = false;
		}
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
	Font* font;
	short buttonPressed;
	//State* selfState;
	//State* mainGameState;
	bool *isGamePaused;
	bool changed;

	enum BUTTONSID
	{
		BUTTONRESUME, BUTTONSAVE, BUTTONLOAD, BUTTONMAINMENU, BUTTONEXIT, NUMBUTTONS
	};
};



class MainGameState : public State
{ 
public:
	MainGameState()
	{
		font = nullptr;
		isGamePaused = false;
		mainGame = nullptr;
		pauseMenu = nullptr;
	}
	MainGameState(Font* _font, bool loadGame = false)
		:font(_font)
	{
		mainGame = new MainGame(font);
		pauseMenu = new PauseMenu(font);
		mainGame->SetIsGamePaused(&isGamePaused);
		pauseMenu->SetIsGamePaused(&isGamePaused);
		isGamePaused = false;

		if (loadGame)
			mainGame->LoadGame("testSave");
	//	changed = false;
	}
	~MainGameState()
	{
		delete pauseMenu;
		delete mainGame;
	}

	State* IsStateChanged()
	{
		State * s = pauseMenu->IsStateChanged();
		if (dynamic_cast<LoginMenu*>(s))
		{
			mainGame->SaveGame("testSave");
		}

		return s;
	}

	void Update(RenderWindow* window, Time* elapsed)
	{
		if (!isGamePaused)
			mainGame->Update(window, elapsed);
		else
		{
			//pauseMenu->ChangeButtonPos(mainGame->GetOrigin());
			pauseMenu->Update(window, elapsed);
		}
	}
	void Render(RenderTarget* target)
	{
		mainGame->Render(target);
		if (isGamePaused)
			pauseMenu->Render(target);
	}
private:
	MainGame* mainGame;
	PauseMenu* pauseMenu;

	bool isGamePaused;
	//bool changed;

	Font* font;
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
	buttons[BUTTONSTARTGAME] = new Button({ 200,50 }, { 200,240 }, font, L"Rozpocznij gr�", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
	buttons[BUTTONLOADGAME] = new Button({ 200,50 }, { 200,300 }, font, L"Wczytaj gr�", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
	buttons[BUTTONSETTINGS] = new Button({ 200,50 }, { 200,360 }, font, L"Ustawienia", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
	buttons[BUTTONEXIT] = new Button({ 200,50 }, { 200,420 }, font, L"Wyj�cie", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
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
	State* maingame = nullptr;
	switch (buttonPressed)
	{
	case BUTTONSTARTGAME:
		maingame = new MainGameState(font);
		//dynamic_cast<MainGame*>(maingame)->SetSelfState(maingame);
		//return maingame;
		//return new MainGame(font);
		return maingame;
		break;
	case BUTTONLOADGAME:
		maingame = new MainGameState(font, true);
		//dynamic_cast<MainGameState*>(maingame);
		return maingame;
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
	inputBoxes[INPUTBOXPASSWORD] = new InputBox({ 200,50 }, { 200,110 }, font, L"Has�o", Color(128, 255, 191), Color(0, 179, 89), Color(0, 153, 77));

	buttons = new Button * [2];
	buttons[BUTTONLOGIN] = new Button({ 200,50 }, { 200,300 }, font, L"Zaloguj", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
	buttons[BUTTONBACK] = new Button({ 200,50 }, { 200,360 }, font, L"Powr�t", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
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
	for (int i = 0; i < ALLINPUTBOXES; i++)
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
	inputBoxes[INPUTBOXPASSWORD] = new InputBoxPassword({ 200,50 }, { 200,110 }, font, L"Has�o", Color(128, 255, 191), Color(0, 179, 89), Color(0, 153, 77));
	
	buttons = new Button * [2];
	buttons[BUTTONREGISTER] = new Button({ 200,50 }, { 200,300 }, font, L"Zarejestruj", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
	buttons[BUTTONBACK] = new Button({ 200,50 }, { 200,360 }, font, L"Powr�t", Color(255, 0, 0, 255), Color(249, 110, 0, 255), Color(150, 0, 0, 255));
	
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
	buttons[BUTTONEXIT] = new Button({ 200,50 }, { 200,420 }, font, L"Wyj�cie", Color(255, 0, 0, 255), Color(249, 0, 110, 255), Color(150, 0, 0, 255));
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


/*To poprawi�*/
State* MainGame::IsStateChanged()
{
	if (buttonPressed%10 == BUTTONMENU)
	{
		buttonPressed = -1;
		return new NothingState;// MainMenu(font);
	}

	return nullptr;
}
