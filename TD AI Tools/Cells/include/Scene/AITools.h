/***************************************************/
/* Nom:	AITools.h
/* Description: AITools
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __AITools_H_
#define __AITools_H_

#include "Core\Scene.h"
using namespace crea;

class AITools
{
	GameManager*	m_pGM;

	// Selection
	Vector2f m_startSelection;
	Vector2f m_endSelection;
	RectangleShape* m_pSelectionRect;
	ShapeRenderer* m_pRectRenderer;
	TextRenderer* m_pTextRenderer;
	Sprite* m_pSpriteCommands;
	string m_tStringCommands[10];
	Text* m_pDiagText;
	short m_mapWidth;
	short m_mapHeight;
	short m_tileWidth;
	short m_tileHeight;
	
	string m_szLastCommand;
	int measurement;


	int m_iButtonWidth;
	int m_iButtonHeight;
	int m_iNbButtons;
	// Command

	// Diagnostics

public:
	AITools();
	virtual ~AITools();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
