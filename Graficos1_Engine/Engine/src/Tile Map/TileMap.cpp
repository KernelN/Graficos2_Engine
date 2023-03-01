#include "TileMap.h"
#include "Utility/XML/tinyxml2.h"
#include "Utility/RendererSingleton.h"
#include "CollisionManager.h"
#include <iostream>

TileMap::TileMap() 
{
	bpp = -1;

	_width = -1;
	_height = -1;

	_tileWidth = -1;
	_tileHeight = -1;

	textureID = 0;
	rendererID = 0;

	_imageWidth = -1;
	_imageHeight = -1;

	convertedPosX = -1;
	convertedPosY = -1;
}

TileMap::~TileMap() {}

const Tile& TileMap::tile(unsigned int uiId) {
	Tile* NoTile = nullptr;

	for (int i = 0; i < tiles.size(); i++) {
		if (uiId == tiles[i].getId()) {
			return tiles[i];
		}
	}

	return *NoTile;
}

void TileMap::setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId) {
	_tileMapGrid[layer][uiCol][uiRow] = tile(uiId);
}

void TileMap::setTile(const Tile& rkTile) {
	tiles.push_back(rkTile);
}

void TileMap::setTileDimensions(float tileWidth, float tileHeight) {
	_tileWidth = tileWidth;
	_tileHeight = tileHeight;
}

void TileMap::setDimensions(float width, float height) {
	_width = width;
	_height = height;

	//creo la grilla bidimensional para guardar la posicion de cada tile igual que en el editor
	Tile** tileMap;
	tileMap = new Tile * [_height];
	for (int i = 0; i < _height; i++) {
		tileMap[i] = new Tile[_width];
	}
	_tileMapGrid.push_back(tileMap);
}

void TileMap::setTexture(std::string path) {
	RendererSingleton::GetRenderer()->GetNewTexture(path, &_imageWidth, &_imageHeight, &bpp, &rendererID);
	textureID = rendererID - 1;
}

void TileMap::draw() {
	RendererSingleton::GetRenderer()->BindTexture(textureID, rendererID);
	RendererSingleton::GetRenderer()->SetTexture(textureID);
	//rkRenderer.setCurrentTexture(textureID);

	float mapWidth = -(_width * _tileWidth) / 2;
	float mapHeight = (_height * _tileHeight) / 2;

	for (int i = 0; i < _tileMapGrid.size(); i++)
	{
		for (int y = 0; y < _height; y++)
		{
			for (int x = 0; x < _width; x++)
			{
				if (_tileMapGrid[i][y][x].getId() == NULL) continue;

				float xTrans = mapWidth + (_tileWidth * x);
				float yTrans = mapHeight - (_tileHeight * y);

				_tileMapGrid[i][y][x].Translate(xTrans, yTrans);
				_tileMapGrid[i][y][x].Draw();
			}
		}
	}
}

bool TileMap::importTileMap(std::string filePath) {
	tinyxml2::XMLDocument tileset; //guarda el documento
	tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones

	errorHandler = tileset.LoadFile(filePath.c_str()); //carga el archivo XML
	if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) return false;

	// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
	tinyxml2::XMLElement* mapNode = tileset.FirstChildElement("map");
	if (mapNode == nullptr)
		return false;
	setDimensions(mapNode->FloatAttribute("width"), mapNode->FloatAttribute("height"));				// Get width and heigth for
	setTileDimensions(mapNode->FloatAttribute("tilewidth"), mapNode->FloatAttribute("tileheight")); // the map and the tiles


	int columns = _width;  // Columns of Tiles in the Tileset
	int rows = _height;

	// Loading Tileset element
	tinyxml2::XMLDocument tilesheet; //guarda el documento

	std::string tilesetPath = "res/tilemap/";
	tilesetPath += mapNode->FirstChildElement("tileset")->Attribute("source");

	errorHandler = tilesheet.LoadFile(tilesetPath.c_str()); //carga el archivo XML
	if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) return false;

	tinyxml2::XMLElement* pTilesheet = tilesheet.FirstChildElement("tileset");
	if (pTilesheet == NULL)
		return false;

	_imagePath = "res/tilemap/";
	_imagePath += pTilesheet->FirstChildElement("image")->Attribute("source");			// Loading Textures
	setTexture(_imagePath); //

	// Save the Tiles in the TileMap
	float tileX = 0.0f, tileY = 0.0f;
	int _id = 1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Tile* newTile = new Tile();;

			int imgSize[2] = { _imageWidth, _imageHeight };
			float sprtSize[2] = { _tileWidth / _imageWidth, _tileHeight / _imageHeight };
			float uv[2] = { tileX / _imageWidth, tileY / _imageHeight };

			newTile->setId(_id);
			newTile->SetSprite(textureID, imgSize, sprtSize, uv);
			newTile->Scale(_tileWidth, _tileHeight);

			//newTile.setTextureCoordinates(tileX / _imageWidth, tileY / _imageHeight,
			//	(tileX + _tileWidth) / _imageWidth, tileY / _imageHeight,
			//	tileX / _imageWidth, (tileY + _tileHeight) / _imageHeight,
			//	(tileX + _tileWidth) / _imageWidth, (tileY + _tileHeight) / _imageHeight);

			tileX += _tileWidth;
			setTile(*newTile);
			_id++;
		}
		tileX = 0;
		tileY += _tileHeight;
	}


	// Loading Layer element
	tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer == NULL)
		return false;

	// Loading Tileset element
	tinyxml2::XMLElement* pTilesetData = pLayer->FirstChildElement("data");
	if (pTilesetData == NULL)
		return false;

	tinyxml2::XMLElement* pTile = pTilesetData->FirstChildElement("tile");
	tinyxml2::XMLElement* pTileData;
	
	unsigned int tileID = 0;
	while (pTile) 
	{
		pTileData = pTilesheet->FirstChildElement("tile");
		unsigned int gid = pTile->IntAttribute("gid") - 1;

		unsigned int i = 0;
		while (pTileData && i <= gid)
		{
			i = pTileData->IntAttribute("id");
			if (i == gid)
			{
				tinyxml2::XMLElement* pProperty = pTileData->FirstChildElement("properties")->FirstChildElement("property");
				std::string propertyName = pProperty->Attribute("value");

				if (propertyName == "false")
					tiles[tileID].walkability(false);
				else
					tiles[tileID].walkability(true);

				break;
			}
			else
			{
				pTileData = pTileData->NextSiblingElement("tile");
				continue;
			}
		}

		pTile = pTile->NextSiblingElement("tile");
		tileID++;
	}

	int layerCount = 0;
	while (pLayer) {
		// Loading Data element
		pTilesetData = pLayer->FirstChildElement("data");
		if (pTilesetData == NULL)
			return false;

		if (layerCount > 0) {
			Tile** tileMap;
			tileMap = new Tile * [_height];
			for (int i = 0; i < _height; i++) {
				tileMap[i] = new Tile[_width];
			}
			_tileMapGrid.push_back(tileMap);
		}

		while (pTilesetData)
		{
			std::vector<int> tileGids;

			pTile = pTilesetData->FirstChildElement("tile");
			while (pTile)
			{
				unsigned int gid = std::atoi(pTile->Attribute("gid")); // tile's id is saved
				tileGids.push_back(gid);
				pTile = pTile->NextSiblingElement("tile");
			}

			int gid = 0;
			for (int y = 0; y < _height; y++) {
				for (int x = 0; x < _width; x++) {
					if (tileGids[gid] != 0)
						setMapTileId(layerCount, y, x, tileGids[gid]);
					gid++;
				}
			}

			pTilesetData = pTilesetData->NextSiblingElement("data");
		}

		layerCount++;
		pLayer = pLayer->NextSiblingElement("layer");
	}

	return true;
}

void TileMap::checkCollision(Entity2D* object) {

	convertedPosX = object->GetTranslation().x + (_width / 2) * _tileWidth;
	convertedPosY = object->GetTranslation().y - (_height / 2) * _tileHeight;

	int left_tile = convertedPosX / _tileWidth;
	int right_tile = (convertedPosX + object->GetScale().x) / _tileWidth;

	int top_tile = (convertedPosY / _tileHeight) * -1;
	int bottom_tile = ((convertedPosY - object->GetScale().y) / _tileHeight) * -1; // Se resta porque el eje Y crece hacia arriba

	if (left_tile < 0)
		left_tile = 0;

	if (right_tile >= _width)
		right_tile = _width - 1;

	if (top_tile < 0)
		top_tile = 0;

	if (bottom_tile >= _height)
		bottom_tile = _height - 1;

	/*
	cout << "converted X: " << convertedPosX << endl;
	cout << "converted Y: " << convertedPosY << endl;

	cout << "left: " <<left_tile << endl;
	cout << "right: "<<right_tile << endl;
	cout << "top: " << top_tile << endl;
	cout << "bottom: "<<bottom_tile << endl;
	*/

	bool tileColliding;
	Tile* tile;

	for (int i = left_tile; i <= right_tile; i++) {

		for (int j = top_tile; j <= bottom_tile; j++) {

			for (int k = 0; k < _tileMapGrid.size(); k++) {
				//cout << "caminable " << "[" << k << "]" << "[" << j << "]" << "[" << i << "] : "<< _tileMapGrid[k][j][i].isWalkable() << endl; // true == 1  ; false == 0
				//cout << true << endl;
				tile = &_tileMapGrid[k][j][i];
				
				if (tile->isWalkable()) continue;

				tileColliding = CollisionManager::CheckCollision(tile, object);
				
				if (!tileColliding) continue;

				object->UndoTranslation();
			}
		}
	}
}