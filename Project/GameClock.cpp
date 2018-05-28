#include "GameClock.h"

GameClock& GameClock::getInstance() {
	static GameClock instance;
	return instance;
}

float GameClock::restart() {
	return clock.restart().asSeconds();
}

float GameClock::getElapsedTime() {
	return clock.getElapsedTime().asSeconds();
}

bool GameClock::isTimePassed(float last, float time) {
	return getElapsedTime() - last >= time /*|| last == 0*/;
}

GameClock::GameClock() {}