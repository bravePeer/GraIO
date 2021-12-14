#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

using namespace sf;

/* --- U¿ytkownik --- */
class User
{

public:
	/*Logowanie*/
	static bool Login(String _login, String _password)
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
				
				cout << L"Zalogowano pomyœlnie" << endl;
				login = _login;
				logged = true;
				return true;
			}
			else if(s[0]== 'F')
			{
				cout << L"Nie zalogowano" << endl;
				return false;
			}
			else
			{
				cout << L"B³¹d" << endl;
			}
		}
		else
		{
			cout << status << endl;
			//throw "B³¹d podczas ³¹czenia z serwerem";
		}

		return false;
	}
	/*Rejestracja*/
	static bool Register(String _login, String _password)
	{
		String loginPage = "graioregiste.php";
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

				cout << L"Pomyœlnie utworzono konto" << endl;
				login = _login;
				logged = true;
				return true;
			}
			else if (s[0] == 'F')
			{
				cout << L"Nie utworzono konta" << endl;
				return false;
			}
			else
			{
				cout << L"B³¹d" << endl;
			}
		}
		else
		{
			cout << status << endl;
			//throw "B³¹d podczas ³¹czenia z serwerem";
		}

		return false;

	}
	static String GetLogin();

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