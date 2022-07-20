#include "Resources.h"


/*SINGLETONE CLASS = the third case (static object in function get INstance) */
/* all the function are set to the members the other are (const) get functions */


//-----------------------------------------------------------------------------
Resources::Resources()
{
	setEnemyTexture();
	setBackground();
	setFont();
	setSound(); 
}


//-----------------------------------------------------------------------------
Resources& Resources::getInstance()
{
	static Resources instane;
	return instane;
}


//-----------------------------------------------------------------------------
void Resources::setBackground()
{
	sf::Texture texture; 
	for (const auto& name : BACKGROUNDS)
	{
		texture.loadFromFile(name);
		texture.setSmooth(true);
		m_screens.emplace_back(texture);
	}
}


//-----------------------------------------------------------------------------
sf::Sprite Resources::getBackgroud(const int screen) 
{
	sf::Sprite temp(m_screens[screen]);
	temp.setTexture(m_screens[screen]);
	temp.setPosition({ 200, 200 });
	return temp;
}


//-----------------------------------------------------------------------------
void Resources::setFont()
{
	m_font.loadFromFile("font.ttf");
}


//-----------------------------------------------------------------------------
sf::Font& Resources::getFont() 
{
	return m_font;
}


//-----------------------------------------------------------------------------
void Resources::setEnemyTexture()
{
	m_enemy.loadFromFile("cat.png");
	m_enemy.setSmooth(true);
}


//-----------------------------------------------------------------------------
sf::Texture& Resources::getEnemyTexture()
{
	return m_enemy;
}


//-----------------------------------------------------------------------------
void Resources::playSound(const int enumSound) 
{
	m_sound.setBuffer(m_soundBuffer[enumSound]);
	m_sound.play();
}


//-----------------------------------------------------------------------------
void Resources::setSound()
{
	sf::SoundBuffer soundBf;

	for (const auto& name : SOUNDS)
	{
		soundBf.loadFromFile(name);
		m_soundBuffer.push_back(soundBf);
	}
}