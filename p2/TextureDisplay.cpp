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
	this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();
//	std::cout << "hahaha" << std::endl;
	
	//<code here for spawning icon object periodically>	
	//std::cout << "a: " << deltaTime.asMilliseconds() << std::endl;

	//this->ticks += deltaTime.asMilliseconds();

	// spawn new icon every 5 seconds
	if (this->ticks >= STREAMING_LOAD_DELAY) {

		int texCount = TextureManager::getInstance()->getNumLoadedStreamTextures();
		//
		////int streamIndex = this->iconList.size(); // use how many we spawned so far
		////TextureManager::getInstance()->loadSingleStreamAsset(streamIndex);

		//if (texCount < 200) {
		//	TextureManager::getInstance()->loadSingleStreamAsset(texCount);
		//	this->spawnObject();
		//}

		//switch (this->streamingType) {
		//	case SINGLE_STREAM: {
		//		if (texCount < 200) {
		//			/*TextureManager::getInstance()->loadSingleStreamAsset(texCount);
		//			this->spawnObject();*/
		//			LoadAssetThread* asset = new LoadAssetThread(texCount, this);
		//			//asset->start();
		//			this->threadPool.ScheduleTasks(asset);
		//		}
		//		break;
		//	}

		//	case BATCH_LOAD: {
		//		int batchSize = 5;
		//		for (int i = 0; i < batchSize; i++) {
		//			if (texCount + i >= 200) break;
		//			TextureManager::getInstance()->loadSingleStreamAsset(texCount + i);
		//			//this->spawnObject();
		//		}
		//		break;
		//	}
		//}

		if (texCount < 200) {
			LoadAssetThread* asset = new LoadAssetThread(texCount, this);

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
