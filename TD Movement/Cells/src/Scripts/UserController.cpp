#include "stdafx.h"

#include "Scripts/UserController.h"
#include "Scripts/CharacterController.h"

namespace crea
{
	// UserController
	UserController::UserController()
	{
		m_pCharacterController = nullptr;
		m_pGM = GameManager::getSingleton();
	}

	UserController::~UserController()
	{
	}

	void UserController::setCharacterController(CharacterController* _pCharacterController)
	{ 
		m_pCharacterController = _pCharacterController; 
	}

	bool UserController::init()
	{
		m_Direction = Vector2f(0.f, 0.f);

		return true;
	}

	bool UserController::update()
	{
		// TD Movement

		// Keyboard control		
		// Move CharacterController in the direction given by the keys
		m_pCharacterController->move(m_Direction);

		// Add Direction, Action and Condition from keys

		// Mouse control
		// Add Direction from mouse


		return true;
	}

	bool UserController::draw()
	{
		return true;
	}

	bool UserController::quit()
	{
		return true;
	}
} // namespace crea
