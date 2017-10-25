#include "Tween.h"
#include "KeyFrame.h"

#include <3DPoint.h>



using namespace Anim;

Tween::Tween(int startIndex, KeyFrame startScene,int finishIndex,KeyFrame finishScene) : _tweenType(LINEAR)
{
	 _startIndex   = startIndex;
	 _finishIndex  = finishIndex;
	 _startScene   = startScene;
	 _finishScene  = finishScene;
	 _tempScene    = doTween();
}

Scene Tween::doTween()
{
	switch (_tweenType)
	{
		case LINEAR:
			return tweenLinearCore();
		break;
	}
}

Scene Tween::tweenLinearCore ()
{
	Scene result;
	int counter = 1;
	int startCounter = _startIndex;
	int totalFrames = (_finishIndex - _startIndex) +1;
	ADEX::Transform step;

	step.translation = (_finishScene._positionActionInfo._inputPosition.translation - _startScene._positionActionInfo._inputPosition.translation) / totalFrames ;	
	float stepXAng = (ADEX::getAngleX(_finishScene._positionActionInfo._inputPosition.rotation) - ADEX::getAngleX(_startScene._positionActionInfo._inputPosition.rotation)) / totalFrames;  
	float stepYAng = (ADEX::getAngleY(_finishScene._positionActionInfo._inputPosition.rotation) - ADEX::getAngleY(_startScene._positionActionInfo._inputPosition.rotation)) / totalFrames;  
	float stepZAng = (ADEX::getAngleZ(_finishScene._positionActionInfo._inputPosition.rotation) - ADEX::getAngleZ(_startScene._positionActionInfo._inputPosition.rotation)) / totalFrames;  
	step.scale = (_finishScene._positionActionInfo._inputPosition.scale - _startScene._positionActionInfo._inputPosition.scale) / totalFrames;

	while (startCounter <= _finishIndex)
	{
		//ADEX::Transform posInfo;
		EditPositionInfo positionInfo;

		switch (_startScene._positionActionInfo._actionType )
		{
			case ABSOLUTE_ACT:
					positionInfo._inputPosition.translation = _startScene._positionActionInfo._inputPosition.translation + ( step.translation * static_cast<sds_real>(counter) );
					positionInfo._inputPosition.rotation = ADEX::createRotationX(stepXAng * counter) * ADEX::createRotationY(stepYAng * counter ) * ADEX::createRotationZ(stepZAng * counter);
					positionInfo._inputPosition.scale = _startScene._positionActionInfo._inputPosition.scale + ( step.scale * counter );
					positionInfo._rotateOffset.translation = _startScene._positionActionInfo._rotateOffset.translation;
				break;
			case RELATIVE_ACT:						
					positionInfo._inputPosition.translation = step.translation; 
					positionInfo._inputPosition.rotation = ADEX::createRotationX(stepXAng) * ADEX::createRotationY(stepYAng) * ADEX::createRotationZ(stepZAng);
					positionInfo._inputPosition.scale = step.scale;
					positionInfo._rotateOffset.translation = (_startScene._positionActionInfo._rotateOffset.translation + _finishScene._positionActionInfo._rotateOffset.translation) * 0.5;


					positionInfo._actionType = _startScene._positionActionInfo._actionType;

			break;
		}

		KeyFrame tweenFrame(_startScene._entity,positionInfo);
		result.add(startCounter,SceneFrame(tweenFrame));
		++counter;
		++startCounter;
	}

	return result;
}

//Scene Tween::tweenRotateLinear ()
//{
//	Scene result;
//	int counter = 1;
//	int startCounter = _startIndex;
//	int totalFrames = (_finishIndex - _startIndex) +1;
//	ADEX::Transform step;
//
//	step.translation = (_finishScene._positionInfo.translation - _startScene._positionInfo.translation) / totalFrames ;	
//	//double stepXAng = (asin(_finishScene._positionInfo.rotation.data[5]) - asin(_startScene._positionInfo.rotation.data[5])) / totalFrames;
//	//double stepYAng = (asin(_finishScene._positionInfo.rotation.data[6]) - asin(_startScene._positionInfo.rotation.data[6])) / totalFrames ;
//	//double stepZAng = (asin(_finishScene._positionInfo.rotation.data[1]) - asin(_startScene._positionInfo.rotation.data[1])) / totalFrames;
//	float stepXAng = (ADEX::getAngleX(_finishScene._positionInfo.rotation) - ADEX::getAngleX(_startScene._positionInfo.rotation)) / totalFrames;  //(asin(_finishScene._positionInfo.rotation.data[5]) - asin(_startScene._positionInfo.rotation.data[5])) / totalFrames;
//	float stepYAng = (ADEX::getAngleY(_finishScene._positionInfo.rotation) - ADEX::getAngleY(_startScene._positionInfo.rotation)) / totalFrames;   //(asin(_finishScene._positionInfo.rotation.data[6]) - asin(_startScene._positionInfo.rotation.data[6])) / totalFrames ;
//	float stepZAng = (ADEX::getAngleZ(_finishScene._positionInfo.rotation) - ADEX::getAngleZ(_startScene._positionInfo.rotation)) / totalFrames;   //(asin(_finishScene._positionInfo.rotation.data[1]) - asin(_startScene._positionInfo.rotation.data[1])) / totalFrames;
//	step.scale = (_finishScene._positionInfo.scale - _startScene._positionInfo.scale) / totalFrames;
//
//	//tweenAbsoluteLinear(startCounter,)
//	while (startCounter <= _finishIndex)
//	{
//		ADEX::Transform posInfo;
//
//		switch (_startScene._actionType )
//		{
//		case ABSOLUTE_ACT:
//			posInfo.translation = _startScene._positionInfo.translation + ( step.translation * static_cast<sds_real>(counter) );
//			posInfo.rotation = ADEX::createRotationX(stepXAng * counter) * ADEX::createRotationY(stepYAng * counter ) * ADEX::createRotationZ(stepZAng * counter);
//			posInfo.scale = _startScene._positionInfo.scale + ( step.scale * counter );
//			break;
//		case RELATIVE_ACT:
//
//
//			posInfo.translation = _finishScene._positionInfo.translation;
//			
//			posInfo.rotation = ADEX::createRotationX(stepXAng) * ADEX::createRotationY(stepYAng) * ADEX::createRotationZ(stepZAng);
//			posInfo.scale = _startScene._positionInfo.scale ;
//			break;
//		}
//
//		KeyFrame tweenFrame(_startScene._entity,posInfo,_startScene._actionType);
//		result.add(startCounter,SceneFrame(tweenFrame));
//		++counter;
//		++startCounter;
//
//	}
//	return result;
//}


void Tween::changeTweenType(TWEEN_TYPE newType)
{
	_tweenType = newType;
}

void Tween::refresh()
{
	_tempScene.clean();
	_tempScene = doTween();
}

Scene Tween::toScene()
{
	return _tempScene;
}

