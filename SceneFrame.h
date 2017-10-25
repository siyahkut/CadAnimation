#pragma once


#include "KeyFrame.h"
#include <vector>



namespace Anim
{
	
	typedef std::vector<KeyFrame> KeyFrames;

class SceneFrame
{
private:	 
	 KeyFrames _sceneChange;
	 //sds_animPosInfo convertTransformToAnimPos (const ADEX::Transform& inputPosInfo);
	 //ADEX::Transform convertAnimPosToTransform (const sds_animPosInfo& inputPosInfo);
	 //void actionKeyFrame(char const * inputHandle, sds_animPosInfo inputPos);

public:
	SceneFrame();
	SceneFrame(KeyFrame keyFrame);
	SceneFrame(const SceneFrame &obj);
	void SceneFrame::add(KeyFrame keyFrame);
	void SceneFrame::remove(KeyFrame keyFrame);
	SceneFrame& operator<< (const SceneFrame &otherOne);
	void action();
	//SceneFrame operator+ (const SceneFrame &otherOne) ;

	

};

}