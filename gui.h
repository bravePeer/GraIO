#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "utilities.h"

using namespace std;
using namespace sf;


//Przycisk xd
class Button
{
public:
	Button()
	{
		font = nullptr;
	}
	Button(Vector2f _size, Vector2f _pos, Font* _font, String _text, Color _idle, Color _hover, Color _active)
		:font(_font), idleColor(_idle), hoverColor(_hover), activeColor(_active)
	{
		shape.setSize(_size);
		shape.setPosition(_pos);
		shape.setFillColor(idleColor);
		
		text.setFont(*font);
		text.setCharacterSize(20);
		text.setString(_text);
		text.setFillColor(Color::White);
		text.setPosition(
			shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f);
	}
	~Button()
	{}

	short GetButtonState()
	{
		return buttonState;
	}
	void Update(const Vector2f mousePos)
	{
		buttonState = IDLE;

		if (shape.getGlobalBounds().contains(mousePos))
		{
			buttonState = HOVER;

			if (Mouse::isButtonPressed(Mouse::Left))
				buttonState = PRESSED;
		}

		switch (buttonState)
		{
		case IDLE:
			shape.setFillColor(idleColor);
			break;
		case HOVER:
			shape.setFillColor(hoverColor);
			break;
		case PRESSED:
			shape.setFillColor(activeColor);
			break;
		}

	}
	void Render(RenderTarget* target)
	{
		target->draw(shape);
		target->draw(text);
	}
private:
	RectangleShape shape;

	Font* font;
	Text text;

	Color idleColor, hoverColor, activeColor;

	unsigned short buttonState = IDLE;
};

class InputBox
{
public:
	InputBox()
	{
		font = nullptr;
	}
	InputBox(Vector2f _size, Vector2f _pos, Font* _font, String _text, Color _idle, Color _hover, Color _active)
		:font(_font), idleColor(_idle), hoverColor(_hover), activeColor(_active)
	{
		shape.setSize(_size);
		shape.setPosition(_pos);
		shape.setFillColor(idleColor);

		text.setFont(*font);
		text.setCharacterSize(20);
		text.setString(_text);
		text.setFillColor(Color::White);
		text.setPosition(
			shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f);
	}
	~InputBox()
	{}

	String GetTypedString()
	{

	}
	void AddLetter(wchar_t s)
	{
		if(inputBoxState == PRESSED)
		if (s == 8)
		{
			if (typed.getSize())
			{
				typed.erase(typed.getSize() - 1);
			}
		}
		else
		{
			typed += s;
		}
		text.setString(typed);
		text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f, text.getPosition().y);

	}
	void Update(const Vector2f mousePos, const Event*events)
	{

		if (shape.getGlobalBounds().contains(mousePos))
		{
			if(inputBoxState == IDLE)
				inputBoxState = HOVER;

			if (Mouse::isButtonPressed(Mouse::Left))
				inputBoxState = PRESSED;
		}
		else
		{
			if (Mouse::isButtonPressed(Mouse::Left))
				inputBoxState = IDLE;
		}

		switch (inputBoxState)
		{
		case IDLE:
			shape.setFillColor(idleColor);
			break;
		case HOVER:
			shape.setFillColor(hoverColor);
			break;
		case PRESSED:
			shape.setFillColor(activeColor);
			//if (events->type == Event::KeyPressed)
			//{
			//	
			//}
			break;
		}

	}
	void Render(RenderTarget* target)
	{
		target->draw(shape);
		target->draw(text);
	}
private:
	RectangleShape shape;

	Font* font;
	Text text;
	String typed;

	Color idleColor, hoverColor, activeColor;

	unsigned short inputBoxState = IDLE;
};

//MainMenu
class MainMenu
{
public:
	MainMenu()
	{
		buttons = nullptr;
	}
	MainMenu(Font*font)
	{
		buttons = new Button * [NUMBUTTONS];//new Button({ 200,200 }, { 200,100 }, font, "butt1", Color(255, 0, 0, 255), Color(249, 0, 0, 255), Color(150, 0, 0, 255));
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

	short GetButtonPressed()
	{
		switch (buttonPressed)
		{
		case BUTTONSTARTGAME:
			return LOGINMENU;
			break;
		case BUTTONLOADGAME:
			return REGISTEMENU;
			break;
		case BUTTONSETTINGS:
			return MAINMENU;
			break;
		case BUTTONEXIT:
			return EXITGAME;
			break;
		}
		return STARTMENU;
	}

	void Update(Vector2f mousePos)
	{
		for (short i = 0; i < NUMBUTTONS; i++)
		{
			buttons[i]->Update(mousePos);

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

	enum BUTTONSID
	{
		BUTTONSTARTGAME, BUTTONLOADGAME, BUTTONSETTINGS, BUTTONEXIT, NUMBUTTONS
	};
};

//StartMenu
class StartMenu
{
public:
	StartMenu()
	{
		buttons = nullptr;
	}
	StartMenu(Font*font)
	{
		buttons = new Button*[NUMBUTTONS];//new Button({ 200,200 }, { 200,100 }, font, "butt1", Color(255, 0, 0, 255), Color(249, 0, 0, 255), Color(150, 0, 0, 255));
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

	void Update(Vector2f mousePos)
	{
		for (short i = 0; i < NUMBUTTONS; i++)
		{
			buttons[i]->Update(mousePos);

			if (buttons[i]->GetButtonState() == PRESSED)
				buttonPressed = i;
		}
	}
	void Render(RenderTarget*target)
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
	Button** buttons;
	short buttonPressed = -1;

	enum BUTTONSID
	{
		BUTTONLOGIN,BUTTONREGISTER,BUTTONSKIP,BUTTONEXIT,NUMBUTTONS
	};
};

//Logowanie
class LoginMenu
{
public:
	LoginMenu()
	{
		//inputBoxLogin = new InputBox()
	}
	~LoginMenu()
	{
		delete inputBoxLogin;
		delete inputBoxPassword;
		delete checkButton;
	}
private:
	InputBox* inputBoxLogin, *inputBoxPassword;

	Button* checkButton;
};

//Rejestracja
class RegisterMenu
{

};