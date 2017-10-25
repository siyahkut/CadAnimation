#pragma once

#include "../ADE3/Include/adex/ADEXTransform.h"

enum ACTION_TYPE
{
	ABSOLUTE_ACT=0,
	RELATIVE_ACT
};

struct EditPositionInfo  
{
	ADEX::Transform _inputPosition;
	ADEX::Transform _rotateOffset;
	ACTION_TYPE _actionType;

	EditPositionInfo()
		: _actionType(ABSOLUTE_ACT)
	{}
	EditPositionInfo(ACTION_TYPE actionType)
		: _actionType(actionType)
	{}
	inline bool operator==(const EditPositionInfo& otherOne) const
	{
		return (_actionType == otherOne._actionType)
			&& (_inputPosition == otherOne._inputPosition)
			&& (_rotateOffset == otherOne._rotateOffset);
	}
};