/// <summary>
/// author Pete Lowe May 2025
/// you need to change the above line or lose marks
/// </summary>


#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the texts
/// load and setup the images
/// load and setup the sounds
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{800U, 600U}, 32U }, "Bullet Bill" },
	m_DELETEexitGame{false} //when true game will exit
{
	setupTexts(); // load font 
	setupSprites(); // load texture
	setupAudio(); // load sounds
	m_targetVelocity = sf::Vector2f{ -0.6f,0.0f };
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_DELETEexitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_DELETEexitGame = true; 
	}
}

/// <summary>
/// Check if any keys are currently pressed
/// </summary>
void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_DELETEexitGame = true; 
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	checkKeyboardState();
	if (m_DELETEexitGame)
	{
		m_window.close();
	}
	moveTarget();
	animateGumba();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_wall);
	m_window.draw(m_target);
	m_window.draw(m_targetSprite);
	m_window.draw(m_DELETEwelcomeMessage);
	
	m_window.display();
}

void Game::moveTarget()
{
	const float SPEED = 0.6f;
	const float LEFT_EDGE = 432.0f;
	const float RIGHT_EDGE = 745.0f;

	if (m_targetLocation.x < LEFT_EDGE)
	{
		m_targetVelocity.x = SPEED ;
		m_targetSprite.setScale(sf::Vector2f{ -1.0f,1.0f });
		m_targetSprite.setOrigin(sf::Vector2f{ 52.0f,0.0f });
	}
	if (m_targetLocation.x > RIGHT_EDGE)
	{
		m_targetVelocity.x = -SPEED;
		m_targetSprite.setScale(sf::Vector2f{ 1.0f,1.0f });
		m_targetSprite.setOrigin(sf::Vector2f{ 0.0f,0.0f });
	}

	m_targetLocation += m_targetVelocity;
	m_target.setPosition(m_targetLocation);
	m_targetSprite.setPosition(m_targetLocation);
}

void Game::animateGumba()
{
	int frame = 0;
	const int FRAME_WIDTH = 52;
	const int FRAME_HEIGHT = 54;

	m_gumbaFrameCount += m_gumbaFrameIncrement;
	frame = static_cast<int>(m_gumbaFrameCount);
	if (frame > GUMBE_FRAMES)
	{
		frame = 0;
		m_gumbaFrameCount -= 20.0f;
	}
	if (frame != m_gumbaFrame)
	{
		m_gumbaFrame = frame;
		m_targetSprite.setTextureRect(sf::IntRect{sf::Vector2i{FRAME_WIDTH*frame,0}, sf::Vector2i{FRAME_WIDTH,FRAME_HEIGHT}});
	}

}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupTexts()
{
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_DELETEwelcomeMessage.setFont(m_jerseyFont);
	m_DELETEwelcomeMessage.setString("SFML Game");
	m_DELETEwelcomeMessage.setPosition(sf::Vector2f{ 205.0f, 240.0f });
	m_DELETEwelcomeMessage.setCharacterSize(96U);
	m_DELETEwelcomeMessage.setOutlineColor(sf::Color::Black);
	m_DELETEwelcomeMessage.setFillColor(sf::Color::Red);
	m_DELETEwelcomeMessage.setOutlineThickness(2.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprites()
{
	m_wall.setFillColor(sf::Color::Black);
	m_wall.setSize(sf::Vector2f{ 32.0f,100.0f });
	m_wall.setPosition(sf::Vector2f{ 400.0f, 500.0f });

	m_target.setFillColor(sf::Color::Green);
	m_target.setSize(sf::Vector2f{ 55.0f,55.0f });
	m_targetLocation = sf::Vector2f{ 432.0f,545.0f };
	m_target.setPosition(m_targetLocation);

	if (!m_gumbaTexture.loadFromFile("assets/images/gumba.png"))
	{
		std::cout << "problem with gumba" << std::endl;
	}

	m_targetSprite.setTexture(m_gumbaTexture,true);
	m_targetSprite.setTextureRect(sf::IntRect{ sf::Vector2i{0,0}, sf::Vector2i{52,54} });

}

/// <summary>
/// load sound file and assign buffers
/// </summary>
void Game::setupAudio()
{
	if (!m_DELETEsoundBuffer.loadFromFile("ASSETS\\AUDIO\\beep.wav"))
	{
		std::cout << "Error loading beep sound" << std::endl;
	}
	
}
