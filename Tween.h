#pragma once

#include "KeyFrame.h"
#include "Scene.h"

namespace Anim
{
	enum TWEEN_TYPE {LINEAR=0,LINEARROTATE=1,LINEARCOORDINATE,LINEARSCALE};
	class Tween
	{
	public:
		//Tween();
		Tween(int startIndex, KeyFrame startScene,int finishIndex,KeyFrame finishScene);	
		Scene toScene();
		void changeTweenType(TWEEN_TYPE);
		void refresh();
	
	private:		
		
		Scene _tempScene;
		int _startIndex;
		int _finishIndex;
		KeyFrame _startScene;
		KeyFrame _finishScene;	
		TWEEN_TYPE _tweenType;
		Scene doTween();
		Scene tweenLinearCore();
		
		

	};


}
