/***************************************************/
/* Nom:	SceneMap.h
/* Description: SceneMap
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __SceneMap_H_
#define __SceneMap_H_

#include "Core\Scene.h"
#include "AITools.h"

using namespace crea;

enum EnumCharacterDirection
{
	kADir_Invalid = -1,
	kADir_Up,
	kADir_UpRight,
	kADir_Right,
	kADir_DownRight,
	kADir_Down,
	kADir_DownLeft,
	kADir_Left,
	kADir_UpLeft,
};

enum EnumAnimCondition
{
	kACond_Invalid = -1,
	kACond_Default = 0,
	kACond_Lumber,
	kACond_Gold,
};

enum EnumAction
{
	kAct_Invalid = -1,
	kAct_Default = 0,
	kAct_Idle,
	kAct_Walk,
	kAct_Die,
	kAct_Chop,
};

class SceneMap : public Scene
{
	GameManager*	m_pGM;

	// Map
	Entity* m_pEntity3;
	Map* m_pMap;
	MapRenderer* m_pMapRenderer;

	// AI Tools
	bool m_bUseAITools;
	AITools* m_pAITools;

	// Animation
	Animator* m_pAnimator;
	ActionTable* m_pActionTable;

public:
	EnumCharacterDirection m_direction;
	EnumAnimCondition m_condition;
	EnumAction m_action;

	SceneMap();
	virtual ~SceneMap();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
