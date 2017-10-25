#include "Scene.h"
#include <ctime>

using namespace Anim;

Scene::Scene(const Scene &obj)
{
	_frameRate = obj._frameRate;
	_sceneFlow = obj._sceneFlow;

}

void Scene::add(int sceneIndex,SceneFrame keyFrame)
{
	_sceneFlow[sceneIndex] = keyFrame;
}

void Scene::clean()
{
	_sceneFlow.clear();

}

void Scene::run()
{	
	SceneFlow::iterator itt = _sceneFlow.end();			
	int frameEnd=(--itt)->first;
	//itt = _sceneFlow.upper_bound(-1000);
	//int frameBegin = itt->first;			
	int frame=0;

	double prevCorrection;
	prevCorrection = 0.0;

	//std::clock_t start;
	for (frame=0; frame<frameEnd+1; frame++)
	{
		std::clock_t start = std::clock();		
		_sceneFlow[frame].action();
		std::clock_t finish = std::clock();

		 if ((finish - start)  < (1000 / _frameRate))
		 {
			Sleep((1000 / _frameRate)-(finish - start));
		 }

	}
}

Scene& Scene::operator<< (   Scene& otherOne)
{
	//Scene result;
	//result._frameRate = _frameRate;	
	//result._sceneFlow = _sceneFlow;	
	SceneFlow::iterator itt;

	for (itt=otherOne._sceneFlow.begin(); itt!=otherOne._sceneFlow.end(); itt++)
	{
		int nebu = itt->first;
		_sceneFlow[nebu] = _sceneFlow[nebu] << itt->second;
	}
	return *this;
}

Scene& Scene::operator+ (   Scene& otherOne)
{
	//Scene result;
	//result._frameRate = _frameRate;	
	//result._sceneFlow = _sceneFlow;	
	SceneFlow::iterator itt, resultt;
	resultt = _sceneFlow.end();
	for (itt=otherOne._sceneFlow.begin(); itt!=otherOne._sceneFlow.end(); itt++)
	{
		
		_sceneFlow[resultt->first + itt->first] =itt->second;
	}
	return *this;
}