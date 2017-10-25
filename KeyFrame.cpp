#include "KeyFrame.h"
#include "AnimationEntity.h"

using namespace Anim;

KeyFrame::KeyFrame () : _positionActionInfo(EditPositionInfo(ABSOLUTE_ACT))
{

}

KeyFrame::KeyFrame(AnimationEntity inputEntity,EditPositionInfo positionInfo)
{
	_entity = inputEntity;
	_positionActionInfo = positionInfo;
}

bool KeyFrame::operator ==(const KeyFrame &otherKeyFrame) const
{
	return (_entity == otherKeyFrame._entity &&	_positionActionInfo == otherKeyFrame._positionActionInfo);
}