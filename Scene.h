#pragma once
#include "SceneFrame.h"
#include <map>

namespace Anim
{
	typedef std::map<int,SceneFrame> SceneFlow;
	class Scene
	{
	public:
		
		Scene() : _frameRate(30)
		{

		}
		
		Scene::Scene(const Scene &obj);

		SceneFlow _sceneFlow;		
		int _frameRate;
		void add(int sceneIndex,SceneFrame sceneFrame);
		void run();
		void clean();

		Scene& operator<< (   Scene& otherOne);
		Scene& operator+  (Scene& otherOne);
		

	private:		
		
		
	};

}