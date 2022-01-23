#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

/* --- U�ytkownik --- */
class User
{
public:
	/*Logowanie*/
	static void Login(String _login, String _password)
	{
		String loginPage = "graiologin.php";
		Http http;
		http.setHost("graio.refy.pl");

		Http::Request request(loginPage,Http::Request::Method::Post);
		request.setBody("l=" + _login + "&p=" + _password);

		Http::Response response = http.sendRequest(request);
		Http::Response::Status status =  response.getStatus();
		if (status == Http::Response::Ok)
		{
			string s = response.getBody();
			cout << s << endl;

			if (s[0] == 'T')
			{
				
				cout << L"Zalogowano pomy�lnie" << endl;
				login = _login;
				logged = true;
			}
			else if(s[0]== 'F')
			{
				cout << L"Nie zalogowano" << endl;
			}
			else
			{
				cout << L"B��d" << endl;
			}
		}
		else
		{
			cout << status << endl;
			//throw "B��d podczas ��czenia z serwerem";
		}

	}
	/*Rejestracja*/
	static void Register(String _login, String _password)
	{
		if (_login.getSize() < 5)
			throw "Za kr�tki login";
		if (_password.getSize() < 8)
			throw "Za kr�tkie haslo";


		String loginPage = "graioregister.php";
		Http http;
		http.setHost("graio.refy.pl");

		Http::Request request(loginPage, Http::Request::Method::Post);
		request.setBody("l=" + _login + "&p=" + _password);

		Http::Response response = http.sendRequest(request);
		Http::Response::Status status = response.getStatus();
		if (status == Http::Response::Ok)
		{
			string s = response.getBody();
			cout << s << endl;

			if (s[0] == 'T')
			{

				cout << L"Pomy�lnie utworzono konto" << endl;
				login = _login;
				logged = true;
			}
			else if (s[0] == 'F')
			{
				cout << L"Nie utworzono konta" << endl;
			}
			else
			{
				cout << L"B��d" << endl;
			}
		}
		else
		{
			throw "B��d podczas ��czenia z serwerem!\nKod b��du: ";//+status;
		}


	}
	static String GetLogin();
	static bool IsLogged()
	{
		return logged;
	}

private:
	static String login;
	static bool logged;
};

String User::login = "";
bool User::logged = false;

String User::GetLogin()
{
	return User::login;
}