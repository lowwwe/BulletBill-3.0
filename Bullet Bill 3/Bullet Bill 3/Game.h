/// <summary>
/// author Pete Lowe May 2025
/// you need to change the above line or lose marks
/// Also don't have any member properties called Delete...
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.0\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the #endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


const sf::Color ULTRAMARINE{ 5, 55,242,255 }; // const colour

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void processMouseDown(const std::optional<sf::Event>t_event);
	void processMouseMove(const std::optional<sf::Event>t_event);
	void procsesMouseRelease(const std::optional<sf::Event>t_event);
	void checkKeyboardState();
	void update(sf::Time t_deltaTime);
	void render();

	void drawAimLine();
	void moveTarget();
	void moveBall();
	void animateGumba();
	void checkGround();
	bool checkCollisions(sf::CircleShape& t_ball, sf::RectangleShape& t_block, bool t_target);

	void setAimLine();
	void adjustGravity(float t_adjustment);
	void resetCanon();

	void setupTexts();
	void setupSprites();
	void setupCanon();
	void setupTarget();
	void setupGravity();
	


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_jerseyFont;// font used by message
	sf::Text m_missMessage{ m_jerseyFont };
	sf::Text m_hitMessage{ m_jerseyFont };

	int m_misses = 0; // number of misses
	int m_hit = 0; // number of hits


	sf::RectangleShape m_wall; // block for wall
	sf::RectangleShape m_target;// simple target
	sf::RectangleShape m_canon; // simple canon
	sf::Vector2f m_targetLocation; // location of target
	sf::Vector2f m_targetVelocity; // velocity of target
	sf::CircleShape m_ball;// canon ball
	sf::Vector2f m_ballLocation;// ball position
	sf::Vector2f m_ballVelocity;// ball velocity
	sf::Vector2f m_gravity{ 0.0f,0.06f }; // gravity force


	sf::Texture m_barrelTexture;// texture for barrel
	sf::Sprite m_barrelSprite{m_barrelTexture};// barrel sprite
	sf::Texture m_baseTexture;// texture for base
	sf::Sprite m_baseSprite{m_baseTexture};// sprite for base

	sf::Texture m_gumbaTexture;// gumba texture
	sf::Sprite m_targetSprite{ m_gumbaTexture };// gumba sprite
	int m_gumbaFrame{ 0 }; // starting animation frame
	const int GUMBE_FRAMES = 19; // number of frame in the sprite sheet for gumba
	float m_gumbaFrameCount{ 0.0f }; // stating frtame counter varialve float
	float m_gumbaFrameIncrement{0.3f}; // added each game frame to frame counter

	sf::Texture m_bgTexure; // backgraound texture
	sf::Sprite m_bgSprite{ m_bgTexure }; // spreit used to drawe background 
	sf::Texture m_wallTexture; // txture for wall
	sf::Sprite m_wallSprite{ m_wallTexture }; // sprite for wall to be repeated

	sf::Vector2f m_mouseEnd; // location of mouse click or move 
	sf::Vector2f m_canonEnd{ 100.0f,550.0f }; // location of centre of canon wherre the ball is

	sf::VertexArray m_aimLine{ sf::PrimitiveType::Lines }; // line fromcanon to mouse
	bool m_aiming{ false }; // we are aiming
	bool m_firing{ false };// we are firing


	bool m_DELETEexitGame; // control exiting game

	sf::RectangleShape m_gravityBar;// gravity indicator
	sf::Texture m_arrowTexture; // arrow to represent gravity value
	sf::Sprite m_arrowSprite{ m_arrowTexture }; // sprite to draw arrow

	sf::Texture m_bulletTexture;// texture for bullet
	sf::Sprite m_bulletSprite{ m_bulletTexture };// sprite for bullet

	bool m_graphics{ false }; // ture if in graphics mode else shapes
};

#pragma warning( pop ) 
#endif // !GAME_HPP

