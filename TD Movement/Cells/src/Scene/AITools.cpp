#include "stdafx.h"

#include "Scene\AITools.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneMap.h"
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

	Color* pRed = m_pGM->getColor("Red");
	pRed->setValues(255, 0, 0, 255);
	Color* pBlue = m_pGM->getColor("Blue");
	pBlue->setValues(0, 0, 255, 255);
	Color* pBlack = m_pGM->getColor("Black");
	pBlack->setValues(0, 0, 0, 255);
	Color* pTransparent = m_pGM->getColor("Transparent");
	pTransparent->setValues(0, 0, 0, 0);

	// Selection
	m_bSelection = false;
	m_pSelectionShape = new RectangleShape;
	m_pSelectionShape->setOutlineColor(pBlue);
	m_pSelectionShape->setColor(pTransparent);
	m_pSelectionShape->setOutlineThickness(1.f);

	// Commands
	Texture* pCommandsTexture = m_pGM->getTexture("debug/Commands.png");
	m_pCommandsSprite = m_pGM->getSprite("Commands");
	m_pCommandsSprite->setTexture(pCommandsTexture);

	m_rCommandWindow = FloatRect(896, 640, 256, 256);
	m_pCommandsSprite->setPosition(m_rCommandWindow.m_fX, m_rCommandWindow.m_fY);

	// Diagnostics
	m_pTextFPS = m_pGM->getText("fps");
	m_pTextFPS->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextFPS->setColor(pRed);
	m_pTextFPS->setCharacterSize(14);
	m_pTextFPS->setString("fps:");
	m_pTextFPS->setPosition(900, 0);

	m_pTextCommand = m_pGM->getText("Command");
	m_pTextCommand->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextCommand->setColor(pRed);
	m_pTextCommand->setCharacterSize(14);
	m_pTextCommand->setString("Last command:");
	m_pTextCommand->setPosition(900, 20);

	m_pTextDiagnostics = m_pGM->getText("Diagnostics");
	m_pTextDiagnostics->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextDiagnostics->setColor(pBlue);
	m_pTextDiagnostics->setCharacterSize(14);
	m_pTextDiagnostics->setPosition(-100.f, -100.f);

	m_fCommandDisplayTime = 1.0f;

	// Grid
	m_pMap = m_pGM->getMapRenderer("MapRenderer1")->getMap();
	m_pMap->getSize(m_nWidth, m_nHeight);
	m_pMap->getTileSize(m_nTileWidth, m_nTileHeight);
	m_pMap->getTileIndexLimits(m_iMin, m_iMax, m_jMin, m_jMax);
	m_pNodeShape = new RectangleShape;
	m_pNodeShape->setOutlineColor(pBlack);
	m_pNodeShape->setColor(pTransparent);
	m_pNodeShape->setOutlineThickness(0.5f); 
	m_pNodeShape->setSize(m_nTileWidth, m_nTileHeight);

	return true;
}

bool AITools::isButton(int _i, Vector2f& _vMousePosition)
{
	int i = _i % 5;
	int j = _i / 5;
	FloatRect r(m_rCommandWindow.m_fX + i * 46, m_rCommandWindow.m_fY + j * 38, 46.f, 38.f);
	if (r.contains(_vMousePosition))
	{
		return true;
	}
	return false;
}

bool AITools::onUpdate()
{
	// FPS
	Time frameTime = TimeManager::getSingleton()->getFrameTime();
	m_pTextFPS->setString(to_string((int)(1 / frameTime.asSeconds())) + " fps");

	// Selection
	if (m_pGM->isMouseButtonPressed(Button::MouseLeft))
	{
		if (!m_bSelection) // just pressed
		{
			m_vStartSelection = m_pGM->getMousePosition();
		}
		m_bSelection = true;
	}
	else
	{
		if (m_bSelection) // just released
		{
			m_vEndSelection = m_pGM->getMousePosition();
			m_pGM->unselectEntities();
			m_pGM->selectEntities(m_vStartSelection, m_vEndSelection);
		}
		m_bSelection = false;
	}

	// Command
	if (m_pGM->isMouseButtonPressed(Button::MouseRight))
	{
		if (!m_bCommand) // just pressed
		{
			m_eCommandType = Command_Invalid;
			Vector2f vMousePosition = m_pGM->getMousePosition();
			if (m_rCommandWindow.contains(vMousePosition))
			{
				if (isButton(0, vMousePosition))
				{
					m_eCommandType = Command_Reset;
				}
				else if (isButton(1, vMousePosition))
				{
					m_eCommandType = Command_Kill;
				}
				else if (isButton(2, vMousePosition))
				{
					m_eCommandType = Command_Stop;
				}
				else if (isButton(3, vMousePosition))
				{
					m_eCommandType = Command_GoToHQ;
				}
				else if (isButton(4, vMousePosition))
				{
					m_eCommandType = Command_GoTo;
				}
				else if (isButton(5, vMousePosition))
				{
					m_eCommandType = Command_Build;
				}
				else if (isButton(6, vMousePosition))
				{
					m_eCommandType = Command_Mine;
				}
				else if (isButton(7, vMousePosition))
				{
					m_eCommandType = Command_Harvest;
				}
				else if (isButton(8, vMousePosition))
				{
					m_eCommandType = Command_Suicide;
				}
				else if (isButton(9, vMousePosition))
				{
					m_eCommandType = Command_Boost;
				}
				else if (isButton(10, vMousePosition))
				{
					m_eCommandType = Command_GoToHQWithLumber;
				}
			}
		}
		m_bCommand = true;
	}
	else
	{
		if (m_bCommand) // just released
		{
			// Restart the command display timer
			m_CommandDisplayClock.restart();

			// Do the command
			ListEntity* pSelectedEntities = m_pGM->getSelectedEntities();
			for (ListEntity::iterator i = pSelectedEntities->begin(); i != pSelectedEntities->end(); ++i)
			{
				Entity* pEntity = (Entity*)*i;

				if (m_eCommandType == Command_Reset)
				{
					m_pTextCommand->setString("Reset");
					((SceneMap*)m_pScene)->m_action = kAct_Default;
					((SceneMap*)m_pScene)->m_condition = kACond_Default;
				}
				else if (m_eCommandType == Command_Kill)
				{
					m_pTextCommand->setString("Kill");
					((SceneMap*)m_pScene)->m_action = kAct_Chop;
					((SceneMap*)m_pScene)->m_condition = kACond_Default;
				}
				else if (m_eCommandType == Command_Stop)
				{
					m_pTextCommand->setString("Stop");
					((SceneMap*)m_pScene)->m_action = kAct_Idle;
					//((SceneMap*)m_pScene)->m_condition = kACond_Default;
				}
				else if (m_eCommandType == Command_GoToHQ)
				{
					m_pTextCommand->setString("GoToWithGold");
					((SceneMap*)m_pScene)->m_action = kAct_Walk;
					((SceneMap*)m_pScene)->m_condition = kACond_Gold;
				}
				else if (m_eCommandType == Command_GoTo)
				{
					m_pTextCommand->setString("GoTo");
					((SceneMap*)m_pScene)->m_action = kAct_Walk;
					((SceneMap*)m_pScene)->m_condition = kACond_Default;
				}
				else if (m_eCommandType == Command_Build)
				{
					m_pTextCommand->setString("Build");
					((SceneMap*)m_pScene)->m_action = kAct_Chop;
					((SceneMap*)m_pScene)->m_condition = kACond_Default;
				}
				else if (m_eCommandType == Command_Mine)
				{
					m_pTextCommand->setString("Mine");
					((SceneMap*)m_pScene)->m_action = kAct_Chop;
					((SceneMap*)m_pScene)->m_condition = kACond_Default;
				}
				else if (m_eCommandType == Command_Harvest)
				{
					m_pTextCommand->setString("Harvest");
					((SceneMap*)m_pScene)->m_action = kAct_Chop;
					((SceneMap*)m_pScene)->m_condition = kACond_Default;
				}
				else if (m_eCommandType == Command_Suicide)
				{
					m_pTextCommand->setString("Suicide");
					((SceneMap*)m_pScene)->m_action = kAct_Die;
					((SceneMap*)m_pScene)->m_condition = kACond_Default;
				}
				else if (m_eCommandType == Command_Boost)
				{
					m_pTextCommand->setString("Boost");
					((SceneMap*)m_pScene)->m_action = kAct_Idle;
				}
				else if (m_eCommandType == Command_GoToHQWithLumber)
				{
					m_pTextCommand->setString("GoToWithLumber");
					((SceneMap*)m_pScene)->m_action = kAct_Walk;
					((SceneMap*)m_pScene)->m_condition = kACond_Lumber;
				}
				else
				{
					m_pTextCommand->setString("?");
				}
			}

			m_eCommandType = Command_Invalid; 
		}
		m_bCommand = false;
	}

	return true;
}

bool AITools::onDraw()
{
	// Selection
	if (m_pGM->isMouseButtonPressed(Button::MouseLeft))
	{
		Vector2f vMousePosition = m_pGM->getMousePosition();
		m_pSelectionShape->setPosition(m_vStartSelection.getX(), m_vStartSelection.getY());
		m_pSelectionShape->setSize(vMousePosition.getX() - m_vStartSelection.getX(), vMousePosition.getY() - m_vStartSelection.getY());
		m_pSelectionShape->draw();
	}

	// Diagnostics
	ListEntity* pSelectedEntities = m_pGM->getSelectedEntities();
	for (ListEntity::iterator i = pSelectedEntities->begin(); i != pSelectedEntities->end(); ++i)
	{
		Entity* pEntity = (Entity*)*i;
		Vector2f position = pEntity->getPosition();
		m_pTextDiagnostics->setPosition(position.getX(), position.getY() - 50);
		string szDiagnostics;
		szDiagnostics += pEntity->getName();
		Agent* pAgent = pEntity->getComponent<Agent>();
		if (pAgent)
		{
			// Stats
			szDiagnostics += "\nHea: ";
			szDiagnostics += to_string(pAgent->getHealth());
			szDiagnostics += " Str: ";
			szDiagnostics += to_string(pAgent->getStrength());
			szDiagnostics += " Int: ";
			szDiagnostics += to_string(pAgent->getIntelligence());
			szDiagnostics += " Dex: ";
			szDiagnostics += to_string(pAgent->getDexterity());

		}
		m_pTextDiagnostics->setString(szDiagnostics);
		m_pTextDiagnostics->draw();
	}

	// Commands
	if (!pSelectedEntities->empty())
	{
		m_pCommandsSprite->draw();
	}

	// FPS
	m_pTextFPS->draw();

	if (m_CommandDisplayClock.getElapsedTime().asSeconds()<m_fCommandDisplayTime)
	{
		m_pTextCommand->draw();
	}

	// Grid
	for (short i = m_iMin; i <= m_iMax; i++)
	{
		for (short j = m_jMin; j <= m_jMax; j++)
		{
			m_pNodeShape->setPosition((float)i*m_nTileWidth, (float)j*m_nTileHeight);
			m_pNodeShape->draw();			
		}
	}

	return true;
}

bool AITools::onQuit()
{
	delete m_pSelectionShape;
	delete m_pNodeShape;

	return true;
}

