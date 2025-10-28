#include "LoadAssetThread.h"

std::counting_semaphore<4> assetSemaphore(2);

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

void LoadAssetThread::SetNumAsset(int num)
{
	this->numAssets = num;
}

void LoadAssetThread::OnStartTask()
{
	if (!isBatch) {
		TextureManager::getInstance()->loadSingleStreamAsset(this->id);
		this->OnFinished->OnFinishedExecution();
	}
	else {
		for (int i = 0; i < batchSize; i++) {
			if (this->id + i >= this->numAssets) break;
			TextureManager::getInstance()->loadSingleStreamAsset(this->id + i);
			this->OnFinished->OnFinishedExecution();
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
