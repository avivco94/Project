#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
//Uncomment in server
//#define SERVER

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


const sf::IntRect PLAYER_TEXTURE_RECT = sf::IntRect(0, 0, 40, 40);
const sf::IntRect GLOCK_BULLET_TEXTURE_RECT = sf::IntRect(0, 40, 5, 10);

const char SEPARATOR = ',';
const char SEPARATOR2 = ';';

const sf::IpAddress SERVER_IP = sf::IpAddress::LocalHost;
const unsigned short SERVER_PORT = 5642;

const sf::IntRect GLOCK_TEXTURE_RECT = sf::IntRect(0, 0, 40, 40);
const int GLOCK_BULLETS_COUNT = 100;

//Bullets per sec
const float GLOCK_SPEED = 5;

//Coordinates per sec
const float GLOCK_BULLET_SPEED = 1000;
const float PLAYER_SPEED = 300;

//Coordinates to move
const float GLOCK_BULLET_DURATION = 350;


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