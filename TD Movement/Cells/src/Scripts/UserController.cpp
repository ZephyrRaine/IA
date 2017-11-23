#include "stdafx.h"

#include "Scripts/UserController.h"
#include "Scripts/CharacterController.h"

namespace crea
{
	// UserController
	UserController::UserController()
	{
		m_pCharacterController = nullptr;
		m_pGM = GameManager::getSingleton();
	}

	UserController::~UserController()
	{
	}

	Vector2f UserController::GetAngleFromCharDirection(EnumCharacterDirection _charDir)
	{
		if (m_action != kAct_Walk)
			return Vector2f(0.0f, 0.0f);
		double angle = 0.0;
		switch (_charDir)
		{
		case crea::kADir_Up:
			angle = (3.0*PI)/2.0;
			break;
		case crea::kADir_UpRight:
			angle = (7.0*PI)/ 4.0;
			break;
		case crea::kADir_Right:
			angle = 0.0;
			break;
		case crea::kADir_DownRight:
			angle = PI/4.0;
			break;
		case crea::kADir_Down:
			angle = PI/2.0;
			break;
		case crea::kADir_DownLeft:
			angle = (3.0*PI) / 4.0;
			break;
		case crea::kADir_Left:
			angle = PI;
			break;
		case crea::kADir_UpLeft:
			angle = (5.0*PI) / 4.0;
			break;
		default:
			return Vector2f(0.0f, 0.0f);
			break;
		}
		return Vector2f(cos(angle), sin(angle));
	}

	void UserController::setCharacterController(CharacterController* _pCharacterController)
	{ 
		m_pCharacterController = _pCharacterController; 
	}

	bool UserController::init()
	{
		// TD Movement
		m_charDirection = kADir_Down;
		m_condition = kACond_Default;
		m_action = kAct_Default;
		//setCharacterController(getEntity()->getComponent<CharacterController>());
		m_Direction = Vector2f(0.f, 0.f);

		return true;
	}

	bool UserController::update()
	{
		// TD Movement
		m_charDirection = kADir_Invalid;
		m_condition = kACond_Default;
		m_action = kAct_Walk;

		// TD Movement
		if (m_pGM->isKeyPressed(Key::Up))
		{

			if (m_pGM->isKeyPressed(Key::Right))
			{
				m_charDirection = kADir_UpRight;
			}
			else if (m_pGM->isKeyPressed(Key::Left))
			{
				m_charDirection = kADir_UpLeft;
			}
			else
			{
				m_charDirection = kADir_Up;
			}
		}
		else if (m_pGM->isKeyPressed(Key::Down))
		{
			if (m_pGM->isKeyPressed(Key::Right))
			{
				m_charDirection = kADir_DownRight;
			}
			else if (m_pGM->isKeyPressed(Key::Left))
			{
				m_charDirection = kADir_DownLeft;
			}
			else
			{
				m_charDirection = kADir_Down;
			}
		}
		else if (m_pGM->isKeyPressed(Key::Right))
		{
			m_charDirection = kADir_Right;
		}
		else if (m_pGM->isKeyPressed(Key::Left))
		{
			m_charDirection = kADir_Left;
		}
		else if (m_pGM->isKeyPressed(Key::D))
		{
			m_condition = kACond_Default;
		}
		else if (m_pGM->isKeyPressed(Key::G))
		{
			m_condition = kACond_Gold;
		}
		else if (m_pGM->isKeyPressed(Key::L))
		{
			m_condition = kACond_Lumber;
		}
		else if (m_pGM->isKeyPressed(Key::C))
		{
			m_action = kAct_Chop;
		}
		else if (m_pGM->isKeyPressed(Key::K))
		{
			m_action = kAct_Die;
		}
		else
		{
			m_action = kAct_Idle;
		}
		
		// Keyboard control		
		// Move CharacterController in the direction given by the keys
		if (m_pGM->isMouseButtonPressed(Button::MouseRight))
		{
			Vector2f mousePos = m_pGM->getMousePosition();
			mousePos -= getEntity()->getPosition();
			m_action = kAct_Walk;
			double atan2 = atan2f(mousePos.getY(), mousePos.getX());
			cout << atan2 << endl;
			m_Direction = Vector2f(cos(atan2), sin(atan2));
			if (m_Direction.getX() < -0.5f)
			{
				if (m_Direction.getY() < -0.5f)
				{
					m_charDirection = kADir_UpLeft;
				}
				else if (m_Direction.getY() > 0.5f)
				{
					m_charDirection = kADir_DownLeft;
				}
				else
					m_charDirection = kADir_Left;
			}
			else if(m_Direction.getX() > 0.5f)
			{
				if (m_Direction.getY() < -0.5f)
				{
					m_charDirection = kADir_UpRight;
				}
				else if (m_Direction.getY() > 0.5f)
				{
					m_charDirection = kADir_DownRight;
				}
				else
				{
					m_charDirection = kADir_Right;
				}
			}
			else if (m_Direction.getY() < -0.5f)
			{
				m_charDirection = kADir_Up;
			}
			else
			{
				m_charDirection = kADir_Down;
			}
		}
		else
		{	
			m_Direction = GetAngleFromCharDirection(m_charDirection);
		}
		
		m_pCharacterController->move(m_Direction);	
		
		// Add Direction, Action and Condition from keys

		// Mouse control
		// Add Direction from mouse


		return true;
	}

	bool UserController::draw()
	{
		return true;
	}

	bool UserController::quit()
	{
		return true;
	}
} // namespace crea
