#include "stdafx.h"

#include "Data\TileSet.h"
#include "json\json.h"

namespace crea
{
	TileSet::TileSet()
	{
	}

	bool TileSet::ParseJson(Json::Value _jsonTileset)
	{

		m_nColumns = (short)(_jsonTileset.get("columns", 0).asInt());
		m_nFirstgid = (short)(_jsonTileset.get("firstgid", 0).asInt());
		m_nImageheight = (short)(_jsonTileset.get("imageheight", 0).asInt());
		m_nImagewidth = (short)(_jsonTileset.get("imagewidth", 0).asInt());
		m_nMargin = (short)(_jsonTileset.get("margin", 0).asInt());
		m_szName = _jsonTileset.get("name", 0).asString();
		m_nSpacing = (short)(_jsonTileset.get("spacing", 0).asInt());
		m_nTilecount = (short)(_jsonTileset.get("tilecount", 0).asInt());
		m_nTileheight = (short)(_jsonTileset.get("tileheight", 0).asInt());
		m_nTilewidth = (short)(_jsonTileset.get("tilewidth", 0).asInt());

		return true;
	}


	TileSet::~TileSet()
	{
		VectorTerrain::iterator it = m_Terrains.begin();
		while (it != m_Terrains.end()) {
			delete (*it);
			it = m_Terrains.erase(it);
		}
	}
	
}