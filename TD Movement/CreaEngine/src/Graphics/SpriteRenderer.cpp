#include "stdafx.h"

#include "Graphics\SpriteRenderer.h"
#include "Core\GameManager.h"
#include <SFML/Graphics.hpp>

namespace crea
{
	SpriteRenderer::SpriteRenderer()
	{
		m_pSprite = nullptr;
	}

	SpriteRenderer::~SpriteRenderer()
	{

	}

	bool SpriteRenderer::init()
	{
		return true;
	}
	
	bool SpriteRenderer::update()
	{
		return true;
	}
	
	bool SpriteRenderer::draw()
	{
		if (m_pSprite)
		{
			// Set sprite position
			Vector2f vPos = getEntity()->getPosition();
			m_pSprite->setPosition(vPos.getX(), vPos.getY());
			if (m_pTextureRect)
			{
				m_pSprite->setTextureRect(m_pTextureRect->getLeft(), m_pTextureRect->getTop(),
					m_pTextureRect->getWidth(), m_pTextureRect->getHeight());
			}

			// Draw
			crea::GameManager::getSingleton()->getWindow()->draw(*m_pSprite->m_pSprite);
		}

		return true;
	}
	
	bool SpriteRenderer::quit()
	{
		return true;
	}

} // namespace crea
