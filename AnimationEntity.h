#pragma once

#include <string>


namespace Anim
{
	//struct dummyADEEntity
	//{

	//};
	class AnimationEntity
	{
	public:
		AnimationEntity();
		AnimationEntity(std::string);	
		bool operator==(const AnimationEntity &otherOne) const;
		std::string _handleName;	

	private:

		

		//template <typename T>
		//T getEntity();

		//dummyADEEntity getADEEntity();
		
		//dummyADEEntity _ADEEntity;

		//sds_ename getSDSEntity();


	};


}
