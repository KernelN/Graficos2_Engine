#pragma once
#include "DLLManager.h"
#include "Entity/Entity2D/Sprite/Tile/Tile.h"
#include <string>

class DLLEXPORT TileMap 
{
public:
	TileMap();
	~TileMap();

	const Tile& tile(unsigned int uiId);
	void setTile(const Tile& rkTile);
	void setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId);

	void setDimensions(float width, float heigth);
	void setTileDimensions(float tileWidth, float tileHeigth);

	void setTexture(std::string path);
	void draw();

	bool importTileMap(std::string filePath);
	void checkCollision(Entity2D* object);

private:
	std::vector<Tile> tiles;
	std::vector<Tile**> _tileMapGrid;

	int bpp;
	
	int _width;
	int _height;

	float _tileWidth;
	float _tileHeight;

	unsigned int textureID;
	unsigned int rendererID;

	float _imageWidth;
	float _imageHeight;

	float convertedPosX;
	float convertedPosY;

	std::string _imagePath;
};