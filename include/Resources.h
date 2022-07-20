#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Macros.h"

class Resources
{
public:
	//get to the data 
	static Resources& getInstance();

	//D-tor
	~Resources(){}

	//FUNCTIONS
	sf::Texture& getEnemyTexture();
	sf::Sprite getBackgroud(const int);
	sf::Font& getFont();
	void playSound(const int);

private:
	std::vector <sf::Texture>      m_screens;
	sf::Texture m_enemy;
	sf::Font m_font;
	std::vector <sf::SoundBuffer>  m_soundBuffer;
	sf::Sound m_sound;

	//PRIVATE
	//c-tor, copy-c-tor, operator=
	Resources();
	Resources(const Resources&) = default;
	Resources& operator=(const Resources&) = default;

	//FUNCTIONS
	void setBackground();
	void setFont();
	void setEnemyTexture(); 
	void setSound(); 

};