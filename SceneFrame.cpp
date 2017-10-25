#include "SceneFrame.h"
#include "AnmHelper.h"

using namespace Anim;



SceneFrame::SceneFrame()
{

}

SceneFrame::SceneFrame(const SceneFrame &obj)
{
	_sceneChange = obj._sceneChange;
	
}

SceneFrame::SceneFrame(KeyFrame keyFrame)
{
	SceneFrame::add(keyFrame);
}


void SceneFrame::add(KeyFrame keyFrame)
{
	_sceneChange.push_back(keyFrame);
}

void SceneFrame::remove(KeyFrame keyFrame)
{	
	KeyFrames::iterator keyFramesIt;
	for (keyFramesIt = _sceneChange.begin();keyFramesIt != _sceneChange.end();keyFramesIt++ )
	{
		if (*keyFramesIt == keyFrame)
		{
			_sceneChange.erase(keyFramesIt);
		}
	}
}

SceneFrame& SceneFrame::operator<< (const SceneFrame &otherOne)
{
	//SceneFrame result;	
	//._sceneChange = otherOne._sceneChange;
	_sceneChange.insert(_sceneChange.end(), otherOne._sceneChange.begin(), otherOne._sceneChange.end() );
	return *this;
}

void SceneFrame::action()
{
	HelperConverter helper;
	KeyFrames::iterator keyFramesIt;

	for (keyFramesIt = _sceneChange.begin();keyFramesIt != _sceneChange.end();keyFramesIt++ )
	{
		KeyFrame curKeyFrame = *keyFramesIt;

		//sds_anim_setpos(curKeyFrame._entity._handleName.c_str(),convertTransformToAnimPos(curKeyFrame._positionInfo));
		//actionKeyFrame(curKeyFrame._entity._handleName.c_str(),convertTransformToAnimPos(curKeyFrame._positionInfo));
		sds_anim_multipos(curKeyFrame._entity._handleName.c_str(),helper.convertEditPosInfoToAnimPos(curKeyFrame._positionActionInfo));
	}
}



//void SceneFrame::action()
//{
//	KeyFrames::iterator keyFramesIt;
//	for (keyFramesIt = _sceneChange.begin();keyFramesIt != _sceneChange.end();keyFramesIt++ )
//	{
//		KeyFrame curKeyFrame = *keyFramesIt;
//		sds_anim_multipos(curKeyFrame._entity._handleName.c_str(),convertTransformToAnimPos(curKeyFrame._positionInfo),1);
//		
//	}
//}

//void SceneFrame::actionKeyFrame(char const * inputHandle, sds_animPosInfo inputPos)
//{
//	switch (_actionType)
//	{
//	case ABSOLUTE_ACT:
//		sds_anim_setpos(inputHandle,inputPos);
//		break;
//	case RELATIVE_ACT:
//		sds_anim_multipos(inputHandle,inputPos,1);
//		break;
//	}
//}
//
//ADEX::Transform SceneFrame::convertAnimPosToTransform (const sds_animPosInfo& inputPosInfo)
//{
//	ADEX::Transform result;
//	result.scale = ADE::Vector3f(inputPosInfo._scaleX, inputPosInfo._scaleY, inputPosInfo._scaleZ);
//	result.rotation =  ADEX::createRotationX(inputPosInfo._rotateX) * ADEX::createRotationY(inputPosInfo._rotateY) * ADEX::createRotationZ(inputPosInfo._rotateZ);
//	result.translation = ADE::Vector3f(inputPosInfo._inputCoordinate[0], inputPosInfo._inputCoordinate[1], inputPosInfo._inputCoordinate[2]);
//	return result;
//}
//
//sds_animPosInfo SceneFrame::convertTransformToAnimPos (const ADEX::Transform& inputPosInfo)
//{
//	//ADEX::Transform result;
//	//result.scale = ADE::Vector3f(inputPosInfo._scaleX, inputPosInfo._scaleY, inputPosInfo._scaleZ);
//	//result.rotation =  ADEX::createRotationX(inputPosInfo._rotateX) * ADEX::createRotationY(inputPosInfo._rotateY) * ADEX::createRotationZ(inputPosInfo._rotateZ);
//	//result.translation = ADE::Vector3f(inputPosInfo._inputCoordinate[0], inputPosInfo._inputCoordinate[1], inputPosInfo._inputCoordinate[2]);
//	//return result;
//
//	sds_animPosInfo result;
//	sds_point jj = {inputPosInfo.translation.x,inputPosInfo.translation.y,inputPosInfo.translation.z};
//
//	sds_point_set(jj,result._inputCoordinate);
//
//	result._scaleX = inputPosInfo.scale.x;
//	result._scaleY = inputPosInfo.scale.y;
//	result._scaleZ = inputPosInfo.scale.z;
//	result._rotateX = std::asin(inputPosInfo.rotation.data[5]);
//	result._rotateY = std::asin(inputPosInfo.rotation.data[6]);
//	result._rotateZ = std::asin(inputPosInfo.rotation.data[1]);
//	return result;
//}

//SceneFrame SceneFrame::operator+ (const SceneFrame &otherOne)
//{
//	SceneFrame result;
//	result._sceneIndex = _sceneIndex;
//	result._sceneChange = _sceneChange;
//	if (result._sceneIndex == otherOne._sceneIndex)
//	{
//		result << otherOne;
//	}
//	return result;
//}