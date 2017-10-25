#pragma once

#include "AnimEditInfo.h"
#include "../api/sds/sds.h"







namespace Anim
{

	//enum ACTION_TYPE {ABSOLUTE_ACT=0,RELATIVE_ACT};
	//enum ACTION_WAY {TRANS_ALL=0,TRANS_COORDINATE, TRANS_ROTATION,TRANS_SCALE};
	////typedef struct _EditPositionInfo  
	////{
	////	ADEX::Transform inputPosition;
	////	ADEX::Transform rotateOffset;
	////	ACTION_TYPE actionType;
	////	ACTION_WAY actionWay;

	////} EditPositionInfo;


	//class EditPositionInfo  
	//{
	//public:
	//	EditPositionInfo():_actionType(ABSOLUTE_ACT),_actionWay(TRANS_ALL)
	//	{

	//	}

	//	EditPositionInfo(ACTION_TYPE actionType,ACTION_WAY actionWay)
	//	{
	//		_actionType = actionType;
	//		_actionWay = actionWay;
	//	}

	//	ADEX::Transform _inputPosition;
	//	ADEX::Transform _rotateOffset;
	//	ACTION_TYPE _actionType;
	//	ACTION_WAY _actionWay;


	//	//inline bool EditPositionInfo::operator==(EditPositionInfo& otherOne) const{
	//	//	
	//	//	if (_actionType==otherOne._actionType &&
	//	//		_actionWay==otherOne._actionWay &&
	//	//		_inputPosition == otherOne._inputPosition &&
	//	//		_rotateOffset == otherOne._rotateOffset 
	//	//		)
	//	//	return true;

	//	//	return false;
	//	//}
	//	bool operator==(const EditPositionInfo& otherOne) const ;

	//} ;


	//class AnmHelper 
	//{
	//public :
	//	AnmHelper();
	//	EditPositionInfo AnmHelper::convertAnimPosToEditPosInfo(const sds_animPosInfo& inputPosInfo);
	//	sds_animPosInfo AnmHelper::convertEditPosInfoToAnimPos (const EditPositionInfo& inputPosInfo);
	//	void AnmHelper::convertToNaNEditPosInfo(EditPositionInfo & nanEditInfo);

	//	//limitTransform is a reference to check if a transform property has to be set or not.
	//	ADEX::Transform _nanTransform;
	//};
	class HelperConverter
	{
	public:
		HelperConverter();
		EditPositionInfo convertAnimPosToEditPosInfo(const sds_animPosInfo& inputPosInfo);
		sds_animPosInfo convertEditPosInfoToAnimPos (const EditPositionInfo& inputPosInfo);
		void convertToNaNTransform(ADEX::Transform & nanTransform);
		void convertToNaNEditPosInfo(EditPositionInfo & nanEditInfo);
		bool isNaNTransform (ADEX::Transform & isNanTransform);
		bool isNaNEditPosInfo (EditPositionInfo & nanEditInfo);
		bool isNaNFloat (float inputVal);
		EditPositionInfo _nanEditPos;
	};

}