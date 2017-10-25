#include "AnimationEntity.h"

using namespace Anim;

AnimationEntity::AnimationEntity()
{

}

AnimationEntity::AnimationEntity(std::string inputHandleName)
{
	_handleName = inputHandleName;
}

bool AnimationEntity::operator==(const AnimationEntity &otherOne) const
{
	return (_handleName == otherOne._handleName);
}

