#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using std::string;

class GameClock
{
	public:
		//Singleton getInstance
		static GameClock& getInstance();
		//Restart the game clock
		float restart();
		//Get the elapsed time
		float getElapsedTime();
		//Returns if the time passed from last time
		bool isTimePassed(float last, float time);
	private:
		GameClock();
		sf::Clock clock;
};