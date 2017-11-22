/***************************************************/
/* Nom:	AITools.h
/* Description: AITools
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __AITools_H_
#define __AITools_H_

#include "Core\Scene.h"
using namespace crea;

enum EnumCommandType
{
	Command_Invalid = -1,
	Command_Reset = 0,
	Command_Kill,
	Command_Stop,
	Command_GoToHQ,
	Command_GoTo,
	Command_Build,
	Command_Mine,
	Command_Harvest,
	Command_Suicide,
	Command_Boost,
	Command_GoToHQWithLumber
}; 

class AITools
{
	GameManager*	m_pGM;

	// Selection
	bool m_bSelection;
	Vector2f m_vStartSelection;
	Vector2f m_vEndSelection;
	RectangleShape* m_pSelectionShape;

	// Command
	FloatRect m_rCommandWindow;
	bool m_bCommand;
	EnumCommandType m_eCommandType;
	Sprite* m_pCommandsSprite;

	// Diagnostic
	Text* m_pTextFPS;
	Text* m_pTextCommand;
	Text* m_pTextDiagnostics;
	Clock m_CommandDisplayClock;
	float m_fCommandDisplayTime;

	// Grid
	Map* m_pMap;
	short m_nWidth;
	short m_nHeight;
	short m_nTileWidth;
	short m_nTileHeight;
	RectangleShape* m_pNodeShape;

	// Tile index limits
	int m_iMin;
	int m_iMax;
	int m_jMin;
	int m_jMax;

	bool isButton(int _i, Vector2f& _vMousePosition);

	Scene* m_pScene;

public:
	AITools();
	virtual ~AITools();

	void setScene(Scene* _pScene) { m_pScene = _pScene; }

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
