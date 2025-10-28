#include "LoadAssetThread.h"

LoadAssetThread::LoadAssetThread(int id, IExecutionEvent* callback)
{
	this->id = id;
	this->OnFinished = callback;
}

void LoadAssetThread::OnStartTask()
{
	TextureManager::getInstance()->loadSingleStreamAsset(this->id);
	this->OnFinished->OnFinishedExecution();
}
//
//void LoadAssetThread::run()
//{
//	TextureManager::getInstance()->loadSingleStreamAsset(this->id);
//	this->OnFinished->OnFinishedExecution();
//
//	delete this;
//}
