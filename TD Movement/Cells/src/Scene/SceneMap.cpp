#include "stdafx.h"

#include "Scene\SceneMap.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"


SceneMap::SceneMap()
{
	// AI Tools
	m_bUseAITools = true;
	m_pAITools = new AITools();
	m_pAITools->setScene(this);
}

SceneMap::~SceneMap()
{
	// AI Tools
	delete m_pAITools;
}
	
bool SceneMap::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Load Map
	m_pEntity3 = m_pGM->getEntity("map0");
	m_pGM->addEntity(m_pEntity3);
	m_pMap = m_pGM->getMap("map0.json"); // CB: TO CHANGE: map id loaded after entity added to display map first (order in tree matters)
	m_pMapRenderer = m_pGM->getMapRenderer("MapRenderer1");
	m_pMapRenderer->setMap(m_pMap);
	m_pEntity3->addComponent(m_pMapRenderer);

	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onInit();
	}

	// Animations
	m_pAnimator = m_pGM->getAnimator("Peon/Peon.animator");
	m_pActionTable = m_pGM->getActionTable("Peon/Peon.act");
	m_direction = kADir_Down;
	m_condition = kACond_Default;
	m_action = kAct_Default;

	return true;
}

bool SceneMap::onUpdate()
{
	if (m_pGM->isKeyPressed(Key::Num1))
	{
		m_pGM->setScene(new SceneMenu());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Num2))
	{
		m_pGM->setScene(new SceneGame());
		return true;
	}

	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onUpdate();
	}
	/*
	// Get direction from keyboard
	if (m_pGM->isKeyPressed(Key::Up))
	{
	if (m_pGM->isKeyPressed(Key::Right))
	{
	m_pAnimator->play(*m_pGM->getAnimation("Peon/Default/Walk/upright.anm"));
	}
	else if (m_pGM->isKeyPressed(Key::Left))
	{
	m_pAnimator->play(*m_pGM->getAnimation("Peon/Default/Walk/upleft.anm"));
	}
	else
	{
	m_pAnimator->play(*m_pGM->getAnimation("Peon/Default/Walk/up.anm"));
	}
	}
	else if (m_pGM->isKeyPressed(Key::Down))
	{
	if (m_pGM->isKeyPressed(Key::Right))
	{
	m_pAnimator->play(*m_pGM->getAnimation("Peon/Default/Walk/downright.anm"));
	}
	else if (m_pGM->isKeyPressed(Key::Left))
	{
	m_pAnimator->play(*m_pGM->getAnimation("Peon/Default/Walk/downleft.anm"));
	}
	else
	{
	m_pAnimator->play(*m_pGM->getAnimation("Peon/Default/Walk/down.anm"));
	}
	}
	else if (m_pGM->isKeyPressed(Key::Right))
	{
	m_pAnimator->play(*m_pGM->getAnimation("Peon/Default/Walk/right.anm"));
	}
	else if (m_pGM->isKeyPressed(Key::Left))
	{
	m_pAnimator->play(*m_pGM->getAnimation("Peon/Default/Walk/left.anm"));
	}
	else
	{
	m_pAnimator->play(*m_pGM->getAnimation("Peon/Default/Idle/down.anm"));
	}
	*/
	
	if (m_pGM->isKeyPressed(Key::Up))
	{
		if (m_pGM->isKeyPressed(Key::Right))
		{
			m_direction = kADir_UpRight;
		}
		else if (m_pGM->isKeyPressed(Key::Left))
		{
			m_direction = kADir_UpLeft;
		}
		else
		{
			m_direction = kADir_Up;
		}
	}
	else if (m_pGM->isKeyPressed(Key::Down))
	{
		if (m_pGM->isKeyPressed(Key::Right))
		{
			m_direction = kADir_DownRight;
		}
		else if (m_pGM->isKeyPressed(Key::Left))
		{
			m_direction = kADir_DownLeft;
		}
		else
		{
			m_direction = kADir_Down;
		}
	}
	else if (m_pGM->isKeyPressed(Key::Right))
	{
		m_direction = kADir_Right;
	}
	else if (m_pGM->isKeyPressed(Key::Left))
	{
		m_direction = kADir_Left;
	}
	string* pAnimationName = m_pActionTable->getAnimation(m_direction, m_condition, m_action);
	Animation* pAnimation = m_pGM->getAnimation(*pAnimationName);
	m_pAnimator->play(*pAnimation);
	
	return true;
}

bool SceneMap::onDraw()
{
	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onDraw();
	}

	return true;
}

bool SceneMap::onQuit()
{
	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onQuit();
	}

	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

