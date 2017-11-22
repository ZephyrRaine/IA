/***************************************************/
/* Nom:	CharacterController.h
/* Description: CharacterController
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __CharacterController_H_
#define __CharacterController_H_

#include "Core\Script.h"
#include "Core\Math.h"
#include "Core\GameManager.h"

namespace crea
{
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

	// Predefinitions
	class GameManager;
	class Map;

	class CharacterController : public Script
	{
		GameManager* m_pGM;

		Vector2f m_vMotion;
	
	public:
		CharacterController();
		virtual ~CharacterController();

		void move(Vector2f _vMotion);
		
		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();
	};

} // namespace crea

#endif
