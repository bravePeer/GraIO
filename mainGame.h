#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "unit.h"
#include "building.h"
#include "ai.h"
#include "world.h"
#include "gui.h"
#include "user.h"

using namespace sf;

class Player
{
public:
	Player()
	{
		//units = nullptr;
		world = nullptr;
		//units = new Unit({ 2, 2 });
	}
	Player(World* _world, bool _isAI)
	:world(_world),isAI(_isAI)
	{
		gameRes.food = 100;
		gameRes.gold = 100;
		gameRes.wood = 100;
		gameRes.iron = 100;
	}
	~Player()
	{
		//delete units;
	}

	InGameResources GetPlayerRes()
	{
		return gameRes;
	}

	void NextRound()
	{
		for (unsigned short i = 0; i < buildings.size(); i++)
		{
			buildings[i]->NextRound(&gameRes);
		}
	}
	
	bool CanBuildBuilding(Building* newBuilding)
	{
		if (*newBuilding->GetCost() <= gameRes)
		{
			return true;
		}
		else
			throw L"Za ma³o surowców";
		return false;
	}
	bool CanProduceUnit(Unit* unit)
	{
		if (*unit->GetCost() <= gameRes)
			return true;
		else
			throw L"Za ma³o surowców";
		return false;
	}


	
	void BuildBuilding(Building* newBuilding)
	{
		gameRes = gameRes - *newBuilding->GetCost();
		buildings.push_back(newBuilding);
		cout << "Budynek dodany" << endl;
	}
	void ProduceUnit(Unit* unit, bool free=false)
	{
		if(!free)
			gameRes = gameRes - *unit->GetCost();
		units.push_back(unit);
		cout << "jednostka dodana" << endl;
	}

	bool IsAI()
	{
		return isAI;
	}

	bool HasUnit(Vector2i pos)
	{
		//if (units[0]->isAlive()==true)
		{
			isUnit = true;
		}
		//else
		{
			isUnit = false;
			return isUnit;
		}
		
	}

	int GetAmountOfBuilding(unsigned short type)
	{
		int amount = 0;
		for (int i = 0; i < buildings.size(); i++)
		{
			if (buildings[i]->GetType() == type)
				amount++;
		}
		return amount;
	}

	Vector2i GetPosOfBuilding(unsigned short type, int number)
	{
		int n = 0;
		//for (int i = 0; i < buildings.size(); i++)
		//{
		//	if()
		//}
	}

	void Render(RenderTarget* target)
	{
	//	units->Render(target);
	}
private:
	//Unit* units;
	World* world;

	vector<Building*> buildings;
	vector<Unit*> units;

	InGameResources gameRes;

	bool isAI;
	bool isUnit;
};

/*G³ówna gra*/
class MainGame : public State
{
public:
	MainGame()
	{
		font = nullptr;

		world = nullptr;
		view = nullptr;
		//unit = nullptr;

		textBox = nullptr;
		resInfoTextBox = nullptr;
		tileInfo = nullptr;

		canDrawMouseOnMap = false;

		buttons = nullptr;
		canCreateUnits = false;

		buttonPressed = -1;
		player = nullptr;
		isPlayerRound = false;
		isNextRound = true;

		isMouseClicked = false;
		buildingGraphic = nullptr;
	}
	MainGame(Font* _font)
		:font(_font)
	{

		view = new View({ 800,450 }, { 1600, 900 });
		origin = view->getCenter();
		//textBox = new TextBox( { view->getSize().x, (view->getSize().y * 0.2f) }, { 0,static_cast<float>(view->getSize().y * 0.8) }, font, L"coœ tam pisz", Color(255, 0, 0, 255), Color(255, 0, 0, 255), Color(255, 0, 0, 255));


		/* Text box'y */
		worldArea.setSize({ static_cast<float>(view->getSize().x),static_cast<float>(view->getSize().y * 0.76) });
												//685
		textBox = new TextBox({ 1600,215 }, { 0,worldArea.getSize().y }, font, L"coœ tam pisz", Color(255, 0, 0, 255), Color(255, 0, 0, 255), Color(255, 0, 0, 255));
		resInfoTextBox = new TextBox({ 240,205 }, { 1100,690 }, font, L"Surowce:", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));

		//worldArea.setPosition(0, 0);

		mouseOnTileTexture.loadFromFile("Resources\\Textures\\ramka.png");
		mouseOnTile.setTexture(mouseOnTileTexture);

		//tile info
		tileInfo = new TextBox({ 100,50 }, { 0,0 }, font, L"Inormacje dotycz¹ce pola", Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0), 12);
		canDrawMouseOnMap = false;
		isMouseClicked = false;


		//Przyciski
		//buttons = new Button({ view->getSize().x * 0.2f, (view->getSize().y * 0.18f) }, { 10,static_cast<float>(view->getSize().y * 0.81) }, font, L"AWd", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));

		buttons = new Button * [ALLBUTTONS];
		buttons[BUTTONBARRACKS] = new Button({ 240,100 }, { 5,690 }, font, L"Koszary", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttons[BUTTONMINE] = new Button({ 240,100 }, { 250,690 }, font, L"Kopalnia", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttons[BUTTONWINDMILL] = new Button({ 240,100 }, { 5,795 }, font, L"M³yn", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttons[BUTTONSAWMILL] = new Button({ 240,100 }, { 250,795 }, font, L"Tartak", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttons[BUTTONNEXTROUND] = new Button({ 240,150 }, { 1355,690 }, font, L"Nastêpna tura", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttons[BUTTONMENU] = new Button({ 240,50 }, { 1355,845 }, font, L"Menu", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttonPressed = -1;

		otherButtonFunction = 0;
		canCreateUnits = false;
		player = new Player(world,false);
		isPlayerRound = true;
		isNextRound = true;

		playerPC = new Player(world, true);
		lastButtonPressed = -1;


		//Grafiki moze to po³¹czyæ w jedn¹ klase?
		buildingGraphic = new BuildingGraphic();
		buildingGraphic->LoadBuildingGraphic();
		unitGraphic = new UnitGraphic();
		unitGraphic->LoadUnitGraphic();
		graphic = new Graphic();
		graphic->LoadGroundGraphic(3);

		
		/* Tworzenie œwiata */
		LoadWorldFromPreset();
		
		//wczytanie presetu
		//world = new World({ 10,10 },graphic->GetAllSpritesGround());



		


		//Testowy przeciwnik
		
		Unit* enemy = new Unit(KNIGHT, unitGraphic->GetSpriteBuilding());
		playerPC->ProduceUnit(enemy,true);
		world->SetUnit({ 9,9 }, enemy);

	}
	~MainGame()
	{
		delete textBox;
		delete tileInfo;
		delete view;
		delete world;
		//delete buttons;

		for (short i = 0; i < ALLBUTTONS; i++)
		{
			delete buttons[i];
		}
		delete[] buttons;

		delete resInfoTextBox;
		delete buildingGraphic;
		delete unitGraphic;
		delete graphic;
	}

	State* IsStateChanged();

	void LoadGame()
	{

	}

	void Update(RenderWindow* window, Time* elapsed)
	{
		//Obsluga klawiszy (ruch mapy)
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			offset.y = 0;

			offset.x = 1 * elapsed->asMilliseconds();
			origin.x -= offset.x;
			view->setCenter(origin);
			window->setView(*view);


			//Ustawianie pozycji
			offset.x *= -1;
			ChangeGuiPosition();
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			offset.y = 0;

			offset.x = 1 * elapsed->asMilliseconds();
			origin.x += offset.x;
			view->setCenter(origin);
			window->setView(*view);

			//Ustawianie pozycji
			//textBox->SetPostition({ textBox->GetPosition().x + offset.x ,textBox->GetPosition().y });
			ChangeGuiPosition();
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			offset.x = 0;

			offset.y = 1 * elapsed->asMilliseconds();
			origin.y -= offset.y;
			view->setCenter(origin);
			window->setView(*view);

			//Ustawianie pozycji
			offset.y *= -1;
			ChangeGuiPosition();
			//textBox->SetPostition({ textBox->GetPosition().x, textBox->GetPosition().y - offset.y  });
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			offset.x = 0;
			offset.y = 1 * elapsed->asMilliseconds();
			origin.y += offset.y;
			view->setCenter(origin);
			window->setView(*view);

			//Ustawianie pozycji
			//textBox->SetPostition({ textBox->GetPosition().x, textBox->GetPosition().y + offset.y  });
			ChangeGuiPosition();
		}

		//Os³uga myszki
		MouseOnWorld(window);

		UpdateTileInfo(window);

		//Robi dodatkowe rzeczy TYLKO podczas rozpoczêcia nowej tury
		if (isNextRound)
		{
			if (isPlayerRound)	//Pocz¹tek tury gracza
			{
				//Sprawdzanie warunków zwyciêstwa
				cout << "---Tura Gracza---" << endl;
				
				player->NextRound();
				ChangeResInfoTextBox();
			}
			else //Pocz¹tek tury ai
			{
				playerPC->NextRound();
				cout << "---Tura PC---" << endl;
			}
			isNextRound = false;
		}

		/* Tura gracza */
		if (isPlayerRound)
		{
			//Obs³uga przycisków gui
			UpdateButtons(window);
		}
		else /* Tura AI */
		{
			AIRound();
		}
	}
	void Render(RenderTarget* target)
	{
		/*Œwiat*/

		world->Render(target);

		//unit->Render(target);
		//unit->Render(target);

		/*Klikniête elementy*/
		RenderMouse(target);


		/*Pzyciski i faktyczne gui xd*/
		RenderTileInfo(target);

		textBox->Render(target);
		resInfoTextBox->Render(target);
		RenderButtons(target);

		player->Render(target);

	}
private:
	Font* font;

	World* world;
	//Unit* unit;
	View* view;
	Vector2f offset;
	Vector2f origin;


	TextBox* textBox;	//taki informacyjny
	TextBox* resInfoTextBox;

	Player* player;
	Player* playerPC;
	bool isPlayerRound;
	bool isNextRound;
	AI ai;


	/* do myszki */
	RectangleShape worldArea;
	bool canDrawMouseOnMap;
	Texture mouseOnTileTexture;
	Sprite mouseOnTile;
	Vector2i mousePosOnMap;
	bool isMouseClicked;

	/* informacje o tile */
	TextBox* tileInfo;


	/*Some*/
	Vector2i secectedWorldPos;

	
	/* Przyciski w gui */
	Button** buttons;
	//Button* buttons;
	short buttonPressed;
	short lastButtonPressed;
	short otherButtonFunction;
	bool canCreateUnits;
	//bool canMoveUnit; //Ruch jendostki
	//Button** createUnitButtons;
	//Button** commandUnitButtons;

	//Dodaæ dodatkowe pod gui? 
	/*Tworzenie jednostek:
	* -> musi istnieæ budynek by stworzyæ jednostkê
	* -> po wybraniu budynku wyswietlana jest lista jednostek do wyprodukowania
	* -> jezeli na budynku stoi jednostka to nie mozna wejsc w interakcje z budynkiem

	*/

	/*Tworzenie jednostek*/

	/*Ruch jednostek*/
	Vector2i selectedUnitPos;

	/* Grafiki */
	BuildingGraphic* buildingGraphic;
	UnitGraphic* unitGraphic;
	Graphic* graphic;

	//UnitGraphic* unitGraphic;
	enum BUTTONSID
	{
		BUTTONBARRACKS, BUTTONMINE, BUTTONWINDMILL, BUTTONSAWMILL, BUTTONNEXTROUND, BUTTONMENU, ALLBUTTONS,
		BUTTONUNIT1 = 10, BUTTONUNIT2 = 11, BUTTONUNIT3 = 12, BUTTONUNIT4 = 13,
		BUTTONMOVE = 20, BUTTONATACK = 21, BUTTONHEAL = 22, BUTTONDELETE = 23
	};

	/*Generowanie œwiata*/
	void GenerateWorld()
	{

	}
	/*Wczytanie gotowego œwiata*/
	void LoadWorldFromPreset()
	{
		fstream preset;
		preset.open("Resources\\Presets\\mapPresets.txt", ios::in);

		Vector2i tempPos;//tutaj wielkosc mapy
		preset >> tempPos.x >> tempPos.y;

		if (tempPos.x == 0 || tempPos.y == 0)
		{
			cout << "Blad podczas ladowania presetu swiata" << endl;
		}

		world = new World(tempPos, &preset,graphic->GetAllSpritesGround());

		//tutaj tempPos pozycja zamku
		//Ustawianie budynków podstawowych
		preset >> tempPos.x >> tempPos.y;
		BuildBuilding(tempPos, CASTLE,player);
		preset >> tempPos.x >> tempPos.y;
		BuildBuilding(tempPos, CASTLE,playerPC);
		ai.SetStartingPos(tempPos);


		preset.close();
	}

	void AIRound()
	{
		switch (ai.CalculateAction())
		{
		case 0://budowanie jednostek
			cout << "Budowanie budynku";
			BuildBuilding(ai.RandomPos(ai.GetStartingPos()), BARRACKS, playerPC);
			break;
		case 1:
			cout << "Budowanie jednostki";
			//playerPC.
			break;
		case 2:
			cout << "ruch jednostki";
			break;
		default:

			break;
		}



		cout << "Tura gracza" << endl;
		buttonPressed = -1;
		isPlayerRound = true;
		isNextRound = true;
	}

	void BuildBuilding(Vector2i _worldPos, short _type, Player*_player)
	{
		//Jezeli mozna wybudowaæ
		Building* newBuilding = nullptr;

		//1.
		switch (_type)
		{
		case MINE:
			newBuilding = new Mine(_type, buildingGraphic->GetSpriteBuilding(_type),!_player->IsAI());
			break;
		case SAWMILL:
			newBuilding = new Sawmill(_type, buildingGraphic->GetSpriteBuilding(_type), !_player->IsAI());
			break;
		case WINDMILL:
			newBuilding = new Windmill(_type, buildingGraphic->GetSpriteBuilding(_type), !_player->IsAI());
			break;
		case BARRACKS:
			newBuilding = new Barracks(_type, buildingGraphic->GetSpriteBuilding(_type), !_player->IsAI());
			break;
		default:
			newBuilding = new TestBuilding(_type, buildingGraphic->GetSpriteBuilding(_type), !_player->IsAI());
			break;
		}


		try
		{
			if (_player->CanBuildBuilding(newBuilding) && world->CanSetBuilding(_worldPos, newBuilding))
			{
				_player->BuildBuilding(newBuilding);
				world->SetBuilding(_worldPos, newBuilding);
				if (!_player->IsAI())
				{
					ChangeResInfoTextBox();
				}
			}

			//	world->SetBuilding(_worldPos, _type, buildingGraphic->GetSpriteBuilding(_type));

		}
		catch (const char* str)
		{
			cout << str << endl;
			delete newBuilding;
		}
		catch (const wchar_t* str)
		{
			if (!_player->IsAI())
				textBox->SetString(str);
			delete newBuilding;
		}

		Delay(100);
	}
	bool CreateUnit(Vector2i _worldPos, Unit* _unit, Player*_player)
	{
		try
		{
			if (_player->CanProduceUnit(_unit) && world->CanSetUnit(_worldPos, _unit))
			{
				_player->ProduceUnit(_unit);
				world->SetUnit(_worldPos, _unit);
				if(!_player->IsAI())
					ChangeResInfoTextBox();
			}
		}
		catch (const char* str)
		{
			cout << str << endl;
			return false;

		}
		catch (const wchar_t* str)
		{
			if (!_player->IsAI())
				textBox->SetString(str);
			return false;
		}

		Delay(100);
		return true;
	}
	void ActionOfUnit(Vector2i _worldPos, int action, Player* _player)
	{
		try
		{
			String info;

			switch (action)
			{
			case 1://Ruch
				world->MoveUnit(selectedUnitPos, _worldPos, &info);
				break;
			case 2://Atak
				world->MoveUnit(selectedUnitPos, _worldPos, &info, true);
				break;
			case 3://Leczenie
				world->HealUnit(selectedUnitPos);
				break;
			case 4://Usuwanie
				cout << "Usuwanie";
				world->DeleteUnit(selectedUnitPos);
				break;
			}
			if(!_player->IsAI())
			textBox->SetString(info);
		}
		catch (const char* str)
		{
			cout << str << endl;
		}
		catch (const wchar_t* str)
		{
			if (!_player->IsAI())
				textBox->SetString(str);
		}

		
		Delay(150);
	}

	void ChangeGuiPosition()
	{
		textBox->Move(offset);
		resInfoTextBox->Move(offset);
		for (short i = 0; i < ALLBUTTONS; i++)
		{
			buttons[i]->Move(offset);
		}
	}
	void ChangeResInfoTextBox()
	{
		String s;
		s = L"Surowce:\nZ³oto: " + to_wstring(player->GetPlayerRes().gold);
		s += L"\nDrewno: " + to_wstring(player->GetPlayerRes().wood);
		s += L"\n¯elazo: " + to_wstring(player->GetPlayerRes().iron);
		s += L"\n¯ywnoœæ: " + to_wstring(player->GetPlayerRes().food);

		resInfoTextBox->SetString(s);
	}

	void UpdateButtons(RenderWindow* window)
	{
		for (int i = 0; i < ALLBUTTONS; i++)
		{
			buttons[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));

			if (buttons[i]->GetButtonState() == PRESSED)
			{
				buttonPressed = i + otherButtonFunction;
			}
		}

		if (buttonPressed % 10 == BUTTONNEXTROUND)
		{
			cout << "Tura komputera" << endl;
			isPlayerRound = false;
			isNextRound = true;
		}
		else if (buttonPressed >= BUTTONBARRACKS && buttonPressed <= BUTTONSAWMILL)
		{
			Building* temp = nullptr;

			switch (buttonPressed)
			{
			case BUTTONMINE:
				temp = new Mine(MINE, nullptr);
				break;
			case BUTTONBARRACKS:
				temp = new Barracks(BARRACKS, nullptr);
				break;
			case BUTTONSAWMILL:
				temp = new Sawmill(SAWMILL, nullptr);
				break;
			case BUTTONWINDMILL:
				temp = new Windmill(WINDMILL, nullptr);
				break;
			}

			String s = L"";
			s += temp->GetName();
			s += L"\n" + temp->GetDesc();
			s += L"\n---Koszt---";
			s += L"\nZ³oto: " + to_wstring(temp->GetCost()->gold);
			s += L"\tDrewno: " + to_wstring(temp->GetCost()->wood);
			s += L"\n¯elazo: " + to_wstring(temp->GetCost()->iron);
			s += L"\t¯ywnoœæ: " + to_wstring(temp->GetCost()->food);
			s += L"\nWymagane pole: " + temp->GetNameNeededGround();
			textBox->SetString(s);

			delete temp;
		}
		else if (buttonPressed >= BUTTONUNIT1 && buttonPressed <= BUTTONUNIT4)
		{
			Unit* unit = nullptr;
			bool keepUnit = false;

			switch (buttonPressed)
			{
			case BUTTONUNIT1:
				unit = new Unit(KNIGHT, unitGraphic->GetSpriteBuilding(KNIGHT), true);
				break;
			case BUTTONUNIT2:
				unit = new Unit(HUSSAR, unitGraphic->GetSpriteBuilding(HUSSAR), true);
				//if (lastButtonPressed == -1)
				//{
				//	lastButtonPressed = buttonPressed;
				//	buttonPressed = -1;
				//}
				//if (lastButtonPressed == buttonPressed)
				//{
				//	cout << "Tworzymy jednostke" << endl;
				//	buttonPressed = -1;
				//	lastButtonPressed = -1;
				//}
				break;
			case BUTTONUNIT3:
				unit = new Unit(ARCHER, unitGraphic->GetSpriteBuilding(ARCHER), true);
				//if (lastButtonPressed == -1)
				//{
				//	lastButtonPressed = buttonPressed;
				//	buttonPressed = -1;
				//}
				//if (lastButtonPressed == buttonPressed)
				//{
				//	cout << "Tworzymy jednostke" << endl;
				//	buttonPressed = -1;
				//	lastButtonPressed = -1;
				//}
				break;
			case BUTTONUNIT4:
				unit = new Unit(CROSSBOWMAN, unitGraphic->GetSpriteBuilding(CROSSBOWMAN), true);
				//if (lastButtonPressed == -1)
				//{
				//	lastButtonPressed = buttonPressed;
				//	buttonPressed = -1;
				//}
				//if (lastButtonPressed == buttonPressed)
				//{
				//	cout << "Tworzymy jednostke" << endl;
				//	buttonPressed = -1;
				//	lastButtonPressed = -1;
				//}
				break;
			}

			String s = L"";
			s += unit->GetName();
			s += L"\n" + unit->GetDesc();
			s += L"\n---Koszt---";
			s += L"\nZ³oto: " + to_wstring(unit->GetCost()->gold);
			s += L"\tDrewno: " + to_wstring(unit->GetCost()->wood);
			s += L"\n¯elazo: " + to_wstring(unit->GetCost()->iron);
			s += L"\t¯ywnoœæ: " + to_wstring(unit->GetCost()->food);
			s += L"\nWciœnij jeszcze raz aby stworzyæ";
			textBox->SetString(s);

			if (lastButtonPressed == -1)
			{
				lastButtonPressed = buttonPressed;
				buttonPressed = -1;
			}
			if (lastButtonPressed == buttonPressed)
			{
				cout << "Tworzymy jednostke" << endl;
				buttonPressed = -1;
				lastButtonPressed = -1;
				cout << secectedWorldPos.x << endl;
				keepUnit = CreateUnit(secectedWorldPos, unit, player);
			}

			if (!keepUnit)
				delete unit;
		}
		else if (buttonPressed >= BUTTONMOVE && buttonPressed <= BUTTONDELETE)
		{
			String s = L"";

			switch (buttonPressed)
			{
			case BUTTONMOVE:
				s = L"Wybierz pole na które jednostka ma siê przemieœciæ";
				break;
			case BUTTONATACK:
				s = L"Wybierz pole które jednostka ma zaatakowaæ";
				break;
			case BUTTONHEAL:
				s = L"Wciœnij jeszcze raz aby jednostka zaczê³a siê leczyæ";
				break;
			case BUTTONDELETE:
				s = L"Wciœnije jeszcze raz aby usun¹æ jednostkê";
				break;
			}
			
			
			if (lastButtonPressed == -1 && (buttonPressed == BUTTONHEAL|| buttonPressed == BUTTONDELETE))
			{
				lastButtonPressed = buttonPressed;
				buttonPressed = -1;
			}
			if (lastButtonPressed == buttonPressed && (buttonPressed == BUTTONHEAL || buttonPressed == BUTTONDELETE))
			{
				if (buttonPressed == BUTTONHEAL)
				{
					//cout << "Leczenie jednostki" << endl;
					ActionOfUnit(selectedUnitPos, 3,player);
				}
				if (buttonPressed == BUTTONDELETE)
				{
					//cout << "Usuwanie jednostki" << endl;
					ActionOfUnit(selectedUnitPos, 4, player);
				}
				buttonPressed = -1;
				lastButtonPressed = -1;
			}

			textBox->SetString(s);
		}
	}
	void RenderButtons(RenderTarget* target)
	{
		//buttons->Render(target);
		for (short i = 0; i < ALLBUTTONS; i++)
		{
			buttons[i]->Render(target);
		}
	}

	/*Co robic gdy myszka zosta³a klikniêta w obszarze mapy*/
	void MouseOnClick()
	{
		if (!(mousePosOnMap < world->GetSize()))
			return;

		secectedWorldPos = mousePosOnMap;
		if (buttonPressed >= 0)
		{
			switch (buttonPressed)
			{
			case BUTTONBARRACKS:
				textBox->SetString(L"Wybudowano Koszary");
				BuildBuilding(mousePosOnMap, BARRACKS,player);

				break;
			case BUTTONMINE:
				textBox->SetString(L"Wybudowano Kopalnie");
				BuildBuilding(mousePosOnMap, MINE, player);

				break;
			case BUTTONWINDMILL:
				textBox->SetString(L"Wybudowano M³yn");
				BuildBuilding(mousePosOnMap, WINDMILL, player);
				break;
			case BUTTONSAWMILL:
				textBox->SetString(L"Wybudowano Tartak");
				BuildBuilding(mousePosOnMap, SAWMILL, player);
				break;
			case BUTTONMOVE:
				//textBox->SetString(L"Wybierz pole na które ma siê ruszyæ jednostka");
				ActionOfUnit(mousePosOnMap,1, player);
				break;
			case BUTTONATACK:
				//textBox->SetString(L"Wybierz pole które ma zaatakowaæ jednostka");
				ActionOfUnit(mousePosOnMap,2, player);
				break;
			}
			//	isMouseClicked = false;
			buttonPressed = -1;

			return;
		}

		if (canCreateUnits)
		{
			canCreateUnits = false;
			otherButtonFunction = 0;
			buttons[BUTTONBARRACKS]->SetString(L"Koszary");
			buttons[BUTTONMINE]->SetString(L"Kopalnia");
			buttons[BUTTONWINDMILL]->SetString(L"M³yn");
			buttons[BUTTONSAWMILL]->SetString(L"Tartak");
		}

		

		if (world->GetTile(mousePosOnMap)->unit)
		{
			/*
			* 1 -> Ruch
			* 2 -> Atak
			* 3 -> Leczenie
			* 4 -> Likwidacja jednostki
			*/
			if (world->GetTile(mousePosOnMap)->unit->IsPlayerUnit())
			{
				textBox->SetString(L"Tu znajduje sie jednostka");//Tu implementacja ruchu

				otherButtonFunction = 20;
				canCreateUnits = true; // albo ruszyc

				buttons[BUTTONBARRACKS]->SetString(L"Przemieœæ");
				buttons[BUTTONMINE]->SetString(L"Atak");
				buttons[BUTTONWINDMILL]->SetString(L"Ulecz");
				buttons[BUTTONSAWMILL]->SetString(L"Usun");

				selectedUnitPos = secectedWorldPos;
			}
			else
			{
				textBox->SetString(L"Tu znajduje sie przciwnik");
			}

		}
		else if (world->GetTile(mousePosOnMap)->building)
		{
			if (world->GetTile(mousePosOnMap)->building->IsPlayerBuilding())
			{
				textBox->SetString(world->GetTile(mousePosOnMap)->building->GetName());

				if (world->GetTile(mousePosOnMap)->building->GetType() == BARRACKS)
				{
					/* Zmiana przyciski na tworzenie jednostek */
					textBox->SetString(L"Wybierz jednostke do stworzenia");
					otherButtonFunction = 10;
					canCreateUnits = true;

					buttons[BUTTONBARRACKS]->SetString(L"Rycerz");
					buttons[BUTTONMINE]->SetString(L"Husarz");
					buttons[BUTTONWINDMILL]->SetString(L"£ucznik");
					buttons[BUTTONSAWMILL]->SetString(L"Kusznik");
				}
			}
			else
			{
				textBox->SetString(L"Budynek przeciwnika");//Tu implementacja ruchu
			}
		}
		else
		{
			textBox->SetString(L"Wybrane pole:\nx:" + to_wstring(mousePosOnMap.x) + " y:" + to_wstring(mousePosOnMap.y));
		}

	}
	void MouseOnWorld(RenderWindow* window)
	{
		Vector2i mousePos = Mouse::getPosition(*window);
		canDrawMouseOnMap = false;

		if (worldArea.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
		{//Trzeba poprawiæ
			Vector2i pos = Vector2i(mousePos.x % window->getSize().x, mousePos.y % window->getSize().y) - Vector2i(window->getSize().x / 2, window->getSize().y / 2);
			mousePosOnMap = Screen2Map(static_cast<Vector2i>(Vector2f(pos.x, pos.y-30)) + static_cast<Vector2i>(window->getView().getCenter()) - static_cast<Vector2i>(offset), { TILEW,TILEH });


			canDrawMouseOnMap = true;
			mouseOnTile.setPosition(ScreenPos(mousePosOnMap, { TILEW,TILEH }));

			/*To powinno byc w innej medodzie*/

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				//isMouseClicked = true; // czy wcisnieta na mapie
				MouseOnClick();
			}
		}
	}
	void RenderMouse(RenderTarget* target)
	{
		if (canDrawMouseOnMap)
			target->draw(mouseOnTile);
	}

	void UpdateTileInfo(RenderWindow* window)
	{
		tileInfo->SetPostition({
			static_cast<float>(Mouse::getPosition(*window).x) + origin.x - window->getSize().x / 2 + 50,
			static_cast<float>(Mouse::getPosition(*window).y + origin.y - window->getSize().y / 2) });

		String tileInfoText = L"Zawartoœæ pola:\n";
		Tile tile = *world->GetTile(mousePosOnMap);

		switch (tile.groundType)
		{
		case GRASS:
			tileInfoText += L"Trawa";
			break;
		case IRON:
			tileInfoText += L"Z³o¿e ¿elaza";
			break;
		case STONE:
			tileInfoText += L"Z³o¿e kamienia";
			break;
		case WOOD:
			tileInfoText += L"Las";
			break;
		default:
			tileInfoText += L"-";
			break;
		}


		//	tileInfoText += L"\nZasoby:\nFood:" + to_wstring(player->GetPlayerRes().food)
		//		+ L"\nIron:" + to_wstring(player->GetPlayerRes().iron)
		//		+ L"\nWood:" + to_wstring(player->GetPlayerRes().wood)
		//		+ L"\nGold:" + to_wstring(player->GetPlayerRes().gold);

		tileInfo->SetString(tileInfoText);
	}
	void RenderTileInfo(RenderTarget* target)
	{
		if (canDrawMouseOnMap)
			tileInfo->Render(target);
	}
};