#pragma once
#include "AnimationEntity.h"
#include "AnimEditInfo.h"

using namespace Anim;

namespace Anim
{
	//enum ACTION_TYPE {ABSOLUTE_ACT=0,RELATIVE_ACT};
	//enum ACTION_WAY {TRANS_ALL=0,TRANS_COORDINATE, TRANS_ROTATION,TRANS_SCALE};

	//class ActionInfo
	//{	 
	//public:
	//	ActionInfo() : _actionType(ABSOLUTE_ACT),_actionWay(TRANS_ALL)
	//	{

	//	}

	//	ActionInfo(ACTION_TYPE actionType,ACTION_WAY actionWay)
	//	{
	//		_actionType = actionType;
	//		_actionWay = actionWay;
	//	}
	//	ACTION_TYPE _actionType;
	//	ACTION_WAY  _actionWay;

	//} ;
	

	//struct PositionInfo
	//{
	//	scale
	//	PositionInfo(C3DPoint positionPoint,C3DPoint extrusion) 
	//	{
	//		_positionPoint = positionPoint;
	//		_extrusion = extrusion;
	//	}
	//	C3DPoint _positionPoint;
	//	C3DPoint _extrusion;
	//	bool operator==(const PositionInfo &otherOne) const
	//	{
	//		return (_positionPoint == otherOne._positionPoint &&
	//			_extrusion == otherOne._extrusion);

	//	}
	//};

	class KeyFrame
	{
	public:
		KeyFrame();
		KeyFrame(AnimationEntity inputEntity,EditPositionInfo _positionActionInfo);		
		bool KeyFrame::operator ==(const KeyFrame  &otherKeyFrame) const;
		AnimationEntity _entity;
		EditPositionInfo _positionActionInfo;
		//ADEX::Transform _positionInfo;
		//ActionInfo _actionInfo;
	private:
		


	};

	
}