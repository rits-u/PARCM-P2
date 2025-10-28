#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "IconObject.h"


TextureDisplay::TextureDisplay(): AGameObject("TextureDisplay")
{
	
}

void TextureDisplay::initialize()
{
	this->threadPool.StartScheduling();
}

void TextureDisplay::processInput(sf::Event event)
{
	
}

void TextureDisplay::update(sf::Time deltaTime)
{
	int numAsset = 205;
	this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();

	if (this->ticks >= STREAMING_LOAD_DELAY) {

		int texCount = TextureManager::getInstance()->getNumLoadedStreamTextures();

		if (texCount < numAsset) {
			LoadAssetThread* asset = new LoadAssetThread(texCount, this);
			asset->SetNumAsset(numAsset);

			switch (this->streamingType) {
				case SINGLE_STREAM:
					asset->SetMode(false);
					break;
				case BATCH_LOAD:
					asset->SetMode(true);
					asset->SetBatchSize(5);
					break;
			}

			this->threadPool.ScheduleTasks(asset);
		}

		this->ticks = 0;
		
	}
}

void TextureDisplay::OnFinishedExecution()
{
	this->spawnObject();
}

void TextureDisplay::spawnObject()
{
	guard.lock();
	String objectName = "Icon_" + to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	iconObj->setPosition(x, y);
	guard.unlock();

	//std::cout << "Set position: " << x << " " << y << std::endl;
	//std::cout << "Spawned " << objectName << " at " << x << "," << y << std::endl;

	this->columnGrid++;
	if(this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}
	GameObjectManager::getInstance()->addObject(iconObj);
}
