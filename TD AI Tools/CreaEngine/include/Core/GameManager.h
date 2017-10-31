/***************************************************/
/* Nom:	GameManager.h
/* Description: GameManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __GameManager_H_
#define __GameManager_H_

#include "SceneManager.h"
#include "EntityManager.h"
#include "Data\DataManager.h"
#include "Input\InputManager.h"
#include "Core\Math.h"
#include "AI\Agent.h"

namespace sf
{
	class RenderWindow;
}

namespace crea
{

	class CREAENGINE_API GameManager
	{
		GameManager();

		// window
		sf::RenderWindow* m_pWindow;
		IntRect m_rWindowRect;

	public:
		~GameManager();

		static GameManager* getSingleton();

		inline sf::RenderWindow* getWindow() { return m_pWindow; }

		IntRect getWindowRect() { return m_rWindowRect; }

		void setWindowRect(IntRect _rect) {m_rWindowRect = _rect; }

		inline void setScene(Scene* s) { SceneManager::getSingleton()->setScene(s); }

		// Input
		inline bool isKeyPressed(Key _key) { return InputManager::getSingleton()->isKeyPressed(_key); }

		inline bool isMouseButtonPressed(Button _button) { return InputManager::getSingleton()->isMouseButtonPressed(_button); }

		inline Vector2f getMousePosition() { return InputManager::getSingleton()->getMousePosition(); }

		// Data
		inline Font* getFont(string _szName) { return DataManager::getSingleton()->getFont(_szName); }

		inline Texture* getTexture(string _szName) { return DataManager::getSingleton()->getTexture(_szName); }

		inline Color* getColor(string _szName) { return DataManager::getSingleton()->getColor(_szName); }

		inline Text* getText(string _szName) { return DataManager::getSingleton()->getText(_szName); }

		inline Sprite* getSprite(string _szName) { return DataManager::getSingleton()->getSprite(_szName); }

		inline Map* getMap(string _szName) { return DataManager::getSingleton()->getMap(_szName); }

		inline Agent* getAgent(string _szName) { return DataManager::getSingleton()->getAgent(_szName); }

		inline MapRenderer* getMapRenderer(string _szName) { return EntityManager::getSingleton()->getMapRenderer(_szName); }

		inline TextRenderer* getTextRenderer(string _szName) { return EntityManager::getSingleton()->getTextRenderer(_szName); }

		inline SpriteRenderer* getSpriteRenderer(string _szName) { return EntityManager::getSingleton()->getSpriteRenderer(_szName); }

		inline Entity* getEntity(string _szName) { return EntityManager::getSingleton()->getEntity(_szName); }

		inline void addEntity(Entity* _pEntity, Entity* _pParent = nullptr)  { EntityManager::getSingleton()->addEntity(_pEntity, _pParent); }

		inline void clearAllData() { DataManager::getSingleton()->clear(); }

		inline void clearAllEntities()  { EntityManager::getSingleton()->clear(); }

		// Selection
		inline void selectEntities(Vector2f _vStart, Vector2f _vEnd) { EntityManager::getSingleton()->selectEntities(_vStart, _vEnd); }

		inline void unselectEntities() { EntityManager::getSingleton()->unselectEntities(); }

		inline ListEntity* getSelectedEntities() { return EntityManager::getSingleton()->getSelectedEntities(); }

		void init();

		void update();

		void quit();
	};

} // namespace crea

#endif
