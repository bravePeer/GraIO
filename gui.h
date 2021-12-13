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
//Pole do wprowadzania tekstu
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
		return typed;
	}
	short GetInputBoxState()
	{
		return inputBoxState;
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
	void Update(const Vector2f mousePos/*, const Event*events*/)
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
			if (Mouse::isButtonPressed(Mouse::Left) || inputBoxState == HOVER)
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
//Pole do wypisywania tekstu na ekranie
class TextBox
{
public:
	TextBox()
	{
		font = nullptr;
	}
	TextBox(Vector2f _size, Vector2f _pos, Font* _font, String _text, Color _idle, Color _hover, Color _active)
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
	~TextBox()
	{}

	Vector2f GetPosition()
	{
		return shape.getPosition();
	}
	short GetInputBoxState()
	{
		return inputBoxState;
	}
	void SetString(String _string)
	{
		string = _string;
	}
	void SetPostition(Vector2f drawPos)
	{
		shape.setPosition(drawPos);
		text.setPosition(
			shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f);
	}
	void Update()
	{
		

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
	String string;

	Color idleColor, hoverColor, activeColor;

	unsigned short inputBoxState = IDLE;
};

//Bazowy stan gry w gui.h póki co
class State
{
public:
	State() {}
	~State() {}

	virtual State* IsStateChanged()
	{
		return nullptr;
	}
	virtual void Update(RenderWindow*window, Time* elapsed)
	{}
	virtual void Render(RenderTarget* target)
	{}
private:

};
