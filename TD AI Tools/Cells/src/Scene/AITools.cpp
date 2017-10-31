#include "stdafx.h"

#include "Scene\AITools.h"
#include "Scene\SceneMenu.h"
#include "Core\SceneManager.h"
#include <string>

AITools::AITools()
{

}

AITools::~AITools()
{

}
	
bool AITools::onInit()
{
	m_pGM = GameManager::getSingleton();


	// Selection
	
	m_pSelectionRect = new RectangleShape();
	m_pSelectionRect->setColor(&Color::TRANSPARENT);
	m_pSelectionRect->setOutlineThickness(1.0f);
	m_pSelectionRect->setOutlineColor(&Color::BLUE);
	
	Map* map = m_pGM->getEntity("map0")->getComponent<MapRenderer>()->getMap();
	
	map->getSize(m_mapWidth, m_mapHeight);
	map->getTileSize(m_tileWidth, m_tileHeight);

	m_pRectRenderer = new ShapeRenderer();
	m_pRectRenderer->setShape(m_pSelectionRect);
	
	m_startSelection = m_endSelection = Vector2f(-1.f, -1.f);
	// Commands
	// Diagnostics
	m_pDiagText = new Text();
	m_pDiagText->setFont(m_pGM->getFont("arial.ttf"));
	m_pDiagText->setCharacterSize(12);
	m_pDiagText->setColor(&Color::BLUE);
	m_pDiagText->setPosition(m_pGM->getWindowRect().getWidth(), 0.0f);
	m_pTextRenderer = new TextRenderer();
	m_pTextRenderer->setText(m_pDiagText);
	m_pTextRenderer->init();
	measurement = 0.0f;
	return true;
}

bool AITools::onUpdate()
{
	Vector2f curMousePosition = m_pGM->getMousePosition();
	// Selection
	if (m_pGM->isMouseButtonPressed(Button::MouseLeft))
	{
		if (m_startSelection.getX() == -1.f && m_startSelection.getY() == -1.f)
		{
			m_startSelection = curMousePosition;
		}
		m_pSelectionRect->setPosition(m_startSelection.getX(), m_startSelection.getY());
		m_pSelectionRect->setSize(curMousePosition.getX() - m_startSelection.getX(), curMousePosition.getY() - m_startSelection.getY());

	}
	else if (!m_pGM->isMouseButtonPressed(Button::MouseLeft) && m_startSelection.getX() != -1.f)
	{
		m_endSelection = curMousePosition;
		m_pGM->unselectEntities();
		
		m_pGM->selectEntities(m_startSelection, m_endSelection);
		
	

		//cout << "(" << m_startSelection.getX() << ";" << m_startSelection.getY() << ") - (" << m_endSelection.getX() << ";" << m_endSelection.getY() << ")" << endl;
		m_pSelectionRect->setPosition(-1.f, -1.f);
		m_pSelectionRect->setSize(-1.f, -1.f);
		m_startSelection = Vector2f(-1.f, -1.f);
	}

	float elapsed = TimeManager::getSingleton()->getFrameTime().asSeconds();
	if (elapsed != 0)
	{
		measurement = 1.0f / elapsed;
	}
	// m_pGM->selectEntities( ...);

	// Command
	// m_rCommandWindow.contains(vMousePosition)
	// m_pGM->getSelectedEntities();

	return true;
}

bool AITools::onDraw()
{
	// Selection

	m_pSelectionRect->setOutlineColor(&Color::BLUE);
	m_pRectRenderer->draw();
	// Commands
	m_pTextRenderer->draw();
	// Diagnostics
	ListEntity* list = m_pGM->getSelectedEntities();
	if ((list->size()) > 0)
	{
		m_pDiagText->setCharacterSize(14);
		m_pDiagText->setColor(&Color::BLUE);
		std::list<Entity*>::const_iterator iterator;
		for (iterator = list->begin(); iterator != list->end(); iterator++)
		{
			Entity* e = (*iterator);
			Agent* pAgent = e->getComponent<Agent>();
			string s = e->getName();
			if (pAgent != nullptr)
			{
				s += "\nHea: " + to_string(pAgent->getHealth());
				s += " Str: " + to_string(pAgent->getStrength());
				s += " Int: " + to_string(pAgent->getIntelligence());
				s += " Dex: " + to_string(pAgent->getDexterity());
			}

			m_pDiagText->setString(s);
			Vector2f ePosition = e->getPosition();
			m_pDiagText->setPosition(ePosition.getX(), ePosition.getY());

			m_pTextRenderer->draw();
			//cout << (*iterator)->getName() << endl;
		}
	}

	m_pDiagText->setCharacterSize(16);
	m_pDiagText->setColor(&Color::RED);
	m_pDiagText->setString("FPS: " + to_string(measurement));
	m_pDiagText->setPosition(m_pGM->getWindowRect().getWidth()-150.0f, 0.0f);
	m_pTextRenderer->draw();
	
	m_pSelectionRect->setOutlineColor(&Color::BLACKGENTIL);
	m_pSelectionRect->setSize(m_tileWidth, m_tileHeight);
	for (int y = 0; y < m_mapHeight; y++)
	{
		for (int x = 0; x < m_mapWidth; x++)
		{
			m_pSelectionRect->setPosition(x*m_tileWidth, y*m_tileHeight);
			m_pRectRenderer->draw();
		}
	}

	return true;
}

bool AITools::onQuit()
{

	return true;
}

