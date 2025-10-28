#include "LoadAssetThread.h"

LoadAssetThread::LoadAssetThread(int id, IExecutionEvent* callback)
{
	this->id = id;
	this->OnFinished = callback;
}

void LoadAssetThread::SetBatchSize(int size)
{
	this->batchSize = size;
}

void LoadAssetThread::SetMode(bool isBatch)
{
	this->isBatch = isBatch;
}

void LoadAssetThread::OnStartTask()
{
	if (!isBatch) {
		TextureManager::getInstance()->loadSingleStreamAsset(this->id);
		this->OnFinished->OnFinishedExecution();
	}
	else {
		
		for (int i = 0; i < batchSize; i++) {
			if (this->id + i >= 200) break;
			TextureManager::getInstance()->loadSingleStreamAsset(this->id + i);
			this->OnFinished->OnFinishedExecution();
			//this->spawnObject();
		}
	}



}
//
//void LoadAssetThread::run()
//{
//	TextureManager::getInstance()->loadSingleStreamAsset(this->id);
//	this->OnFinished->OnFinishedExecution();
//
//	delete this;
//}
