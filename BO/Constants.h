#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <functional>
#include <memory>

//Uncomment in server
//#define SERVER

class IBaseGun;

enum Direction {
	Up = 1,
	Down = 1 << 1,
	Left = 1 << 2,
	Right = 1 << 3,
	UpLeft = 1 << 4,
	UpRight = 1 << 5,
	DownLeft = 1 << 6,
	DownRight = 1 << 7,
	Current = 1 << 8
};

#define PI 3.14159265358979323846


const int WINDOW_SIZE_X = 500;
const int WINDOW_SIZE_Y = 500;
const std::string TITLE = "Counter Strike 2D";
const std::string PLAYER_TEXTURE = "Resources/Players.png";
const std::string TILES_TEXTURE = "Resources/tileset.png";
const std::string BULLETS_TEXTURE = "Resources/Bullets.png";
const std::string WEAPONS_TEXTURE = "Resources/Weapons.png";
const std::string INTRO_BR_TEXTURE = "Resources/introbr.jpg";
const std::string MENU_FONT = "Resources/cs_regular.ttf";

const std::string ON_MOUSE_DOWN = "onMouseDown";
const std::string ON_MOUSE_UP = "onMouseUp";
const std::string ON_MOUSE_MOVE = "onMouseMove";
const std::string ON_KEY_PRESSED = "onKeyPressed";

const std::string ON_MOVE = "onMove";
const std::string ON_GAME_START = "onGameStart";
const std::string ON_GAME_EXIT = "onGameExit";
const std::string ON_GAME_RESUME = "onGameResume";

const std::string GAME_SCREEN = "GameScreen";
const std::string MENU_SCREEN = "MenuScreen";
const std::string SHOP_SCREEN = "ShopScreen";
const std::string HUD_SCREEN = "HudScreen";

const sf::Vector2f TILE_SIZE = sf::Vector2f(40, 40);
const sf::IntRect PLAYER_TEXTURE_RECT = sf::IntRect(0, 0, 40, 40);
const sf::IntRect GLOCK_BULLET_TEXTURE_RECT = sf::IntRect(0, 40, 5, 10);
const sf::IntRect USP_BULLET_TEXTURE_RECT = sf::IntRect(0, 40, 5, 10);
const sf::IntRect AK_BULLET_TEXTURE_RECT = sf::IntRect(0, 40, 5, 10);
const sf::IntRect M4_BULLET_TEXTURE_RECT = sf::IntRect(0, 40, 5, 10);


const char SEPARATOR = ',';
const char SEPARATOR2 = ';';

//const sf::IpAddress SERVER_IP = sf::IpAddress::LocalHost;
const sf::IpAddress SERVER_IP = "40.118.3.201";
const unsigned short SERVER_PORT = 5642;

const sf::IntRect GLOCK_TEXTURE_RECT = sf::IntRect(0, 0, 50, 50);
const int GLOCK_BULLETS_COUNT = 100;
const sf::IntRect USP_TEXTURE_RECT = sf::IntRect(150, 0, 50, 50);
const int USP_BULLETS_COUNT = 90;
const sf::IntRect AK_TEXTURE_RECT = sf::IntRect(50, 0, 50, 50);
const int AK_BULLETS_COUNT = 180;
const sf::IntRect M4_TEXTURE_RECT = sf::IntRect(100, 0, 50, 50);
const int M4_BULLETS_COUNT = 200;


//Bullets per sec
const float GLOCK_SPEED = 3;
const float USP_SPEED = 5;
const float AK_SPEED = 10;
const float M4_SPEED = 12;

//Coordinates per sec
const float GLOCK_BULLET_SPEED = 1000;
const float USP_BULLET_SPEED = 1200;
const float AK_BULLET_SPEED = 1500;
const float M4_BULLET_SPEED = 1800;
const float PLAYER_SPEED = 300;

//Coordinates to move
const float GLOCK_BULLET_DURATION = 350;
const float USP_BULLET_DURATION = 400;
const float AK_BULLET_DURATION = 500;
const float M4_BULLET_DURATION = 600;

const std::string GLOCK_NAME = "GLOCK18-";
const std::string USP_NAME = "USP-";
const std::string AK_NAME = "AK47-";
const std::string M4_NAME = "M4A1-";

const int GLOCK_PRICE = 300;
const int USP_PRICE = 400;
const int M4_PRICE = 700;
const int AK_PRICE = 600;

inline std::istream& operator>>(std::istream& is, sf::Vector2f& v2f) {
	is >> v2f.x;
	is >> v2f.y;
	return is;
}

inline std::istream& operator>>(std::istream& is, sf::IntRect& intRect) {
	is >> intRect.left;
	is >> intRect.top;
	is >> intRect.width;
	is >> intRect.height;
	return is;
}

struct WeaponWithPrice {
	int price;
	std::function<std::shared_ptr<IBaseGun>(sf::Vector2f)> buyFunc;
};