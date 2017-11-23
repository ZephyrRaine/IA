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
		Entity* pEntity = getEntity();
		m_pUC = pEntity->getComponent<UserController>();
		m_pUC->setCharacterController(this);
		m_pAnimator = m_pGM->getAnimator("Peon/Peon.animator");
		m_pActionTable = m_pGM->getActionTable("Peon/Peon.act");
		m_vMotion = Vector2f(0.0f, 0.0f);
		return true;
	}

	bool CharacterController::update()
	{
		
		string* pAnimationName = m_pActionTable->getAnimation(m_pUC->m_charDirection, m_pUC->m_condition, m_pUC->m_action);
		Animation* pAnimation = m_pGM->getAnimation(*pAnimationName);
		m_pAnimator->play(*pAnimation);

		// Get the animation corresponding to the motion and play it
		
		m_vMotion.normalize();
		m_pEntity->move(m_vMotion * (float)TimeManager::getSingleton()->getFrameTime().asSeconds() * 100.0f);

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
