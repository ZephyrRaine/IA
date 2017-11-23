/***************************************************/
/* Nom:	UserController.h
/* Description: UserController
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __UserController_H_
#define __UserController_H_

#include "Core\Script.h"
#include "Core\Math.h"
#include "Scripts\CharacterController.h"

namespace crea
{
	class CharacterController;
	enum EnumCharacterDirection;
	enum EnumAnimCondition;
	enum EnumAction;

	class UserController : public Script
	{
		GameManager* m_pGM;
		CharacterController* m_pCharacterController;

		Vector2f m_Direction;

	public:
		EnumCharacterDirection m_charDirection;
		EnumAnimCondition m_condition;
		EnumAction m_action;

		UserController();
		virtual ~UserController();

		Vector2f GetAngleFromCharDirection(EnumCharacterDirection _charDir);
		void setCharacterController(CharacterController* _pCharacterController);

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();
	};

} // namespace crea

#endif
