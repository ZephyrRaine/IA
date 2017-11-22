#include "stdafx.h"

#include "Scripts\CharacterController.h"

namespace crea
{
	CharacterController::CharacterController()
	{
		m_pGM = GameManager::getSingleton();
	}

	CharacterController::~CharacterController()
	{
	}
	
	// Move the controller by a vector, only constrained by collisions
	void CharacterController::move(Vector2f _vMotion)
	{
		m_vMotion = _vMotion;
	}

	bool CharacterController::init()
	{
		return true;
	}

	bool CharacterController::update()
	{		
		// TD Movement

		// Get the animation corresponding to the motion and play it

		// Move
		m_pEntity->move(m_vMotion * (float)TimeManager::getSingleton()->getFrameTime().asSeconds());

		return true;
	}

	bool CharacterController::draw()
	{
		return true;
	}

	bool CharacterController::quit()
	{
		return true;
	}
} // namespace crea
