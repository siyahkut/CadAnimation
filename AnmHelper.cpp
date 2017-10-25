#include "AnmHelper.h"

//
//
//
using namespace Anim;
//
//
////AnmHelper::AnmHelper ()
////{
////	//Anim::ADELinker::Converter conv;
////	//conv.convertToNaNEditPosInfo(_nanTransform);
////}
////
////EditPositionInfo AnmHelper::convertAnimPosToEditPosInfo(const sds_animPosInfo& inputPosInfo)
////{
////	EditPositionInfo result;
////	result._inputPosition.scale = ADE::Vector3f(inputPosInfo._scaleXYZ[0], inputPosInfo._scaleXYZ[1], inputPosInfo._scaleXYZ[2]);
////	result._inputPosition.rotation =  ADEX::createRotationX(inputPosInfo._rotateXYZ[0]) * ADEX::createRotationY(inputPosInfo._rotateXYZ[1]) * ADEX::createRotationZ(inputPosInfo._rotateXYZ[2]);
////	result._inputPosition.translation = ADE::Vector3f(inputPosInfo._inputCoordinate[0], inputPosInfo._inputCoordinate[1], inputPosInfo._inputCoordinate[2]);
////
////	result._rotateOffset.translation = ADE::Vector3f(inputPosInfo._rotateOffset[0], inputPosInfo._rotateOffset[1], inputPosInfo._rotateOffset[2]);
////	result._actionType = static_cast<ACTION_TYPE>(inputPosInfo._actType);
////	result._actionWay = static_cast<ACTION_WAY>(inputPosInfo._actWay);
////
////	return result;
////}
////
////sds_animPosInfo AnmHelper::convertEditPosInfoToAnimPos (const EditPositionInfo& inputPosInfo)
////{
////
////	sds_animPosInfo result;
////	sds_point jj = {inputPosInfo._inputPosition.translation.x,inputPosInfo._inputPosition.translation.y,inputPosInfo._inputPosition.translation.z};
////
////	sds_point_set(jj,result._inputCoordinate);
////
////	result._scaleXYZ[0] = inputPosInfo._inputPosition.scale.x;
////	result._scaleXYZ[1] = inputPosInfo._inputPosition.scale.y;
////	result._scaleXYZ[2] = inputPosInfo._inputPosition.scale.z;
////	result._rotateXYZ[0] = ADEX::getAngleX(inputPosInfo._inputPosition.rotation); //std::asin(inputPosInfo.rotation.data[5]);
////	result._rotateXYZ[1] = ADEX::getAngleY(inputPosInfo._inputPosition.rotation); //std::asin(inputPosInfo.rotation.data[6]);
////	result._rotateXYZ[2] = ADEX::getAngleZ(inputPosInfo._inputPosition.rotation); //std::asin(inputPosInfo.rotation.data[1]);
////	result._rotateOffset[0] = inputPosInfo._rotateOffset.translation.x;
////	result._rotateOffset[1] = inputPosInfo._rotateOffset.translation.y;
////	result._rotateOffset[2] = inputPosInfo._rotateOffset.translation.z;
////	result._actType = inputPosInfo._actionType;
////	result._actWay = inputPosInfo._actionWay;
////
////	return result;
////}
////
////
////void AnmHelper::convertToNaNTransform(ADEX::Transform & nanTransform)
////{
////	ADE::Matrix3x3f nan;
////	nan.data[0] = nan.data[1]= nan.data[2]= nan.data[3]= nan.data[4]= nan.data[5]= nan.data[6]= nan.data[7]= nan.data[8]= std::numeric_limits<float>::quiet_NaN();
////	//limitTransform = numeric_limits<float>::quiet_NaN();
////	nanTransform.scale =  ADE::Vector3f(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
////	nanTransform.translation = ADE::Vector3f(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
////	nanTransform.rotation = nan;//ADEX::createRotationX(FLT_MAX) * ADEX::createRotationY(FLT_MAX) * ADEX::createRotationZ(FLT_MAX);
////}
////
////void AnmHelper::convertToNaNEditPosInfo(editPositionInfo & nanEditInfo)
////{
////	convertToNaNTransform(nanEditInfo.inputPosition);
////	convertToNaNTransform(nanEditInfo.rotateOffset);
////}
//
//
HelperConverter::HelperConverter()
{

	convertToNaNEditPosInfo(_nanEditPos);
}


EditPositionInfo HelperConverter::convertAnimPosToEditPosInfo(const sds_animPosInfo& inputPosInfo)
{
	EditPositionInfo result;
	result._inputPosition.scale = ADE::Vector3f(inputPosInfo._scaleXYZ[0], inputPosInfo._scaleXYZ[1], inputPosInfo._scaleXYZ[2]);
	result._inputPosition.rotation =  ADEX::createRotationX(inputPosInfo._rotateXYZ[0]) * ADEX::createRotationY(inputPosInfo._rotateXYZ[1]) * ADEX::createRotationZ(inputPosInfo._rotateXYZ[2]);
	result._inputPosition.translation = ADE::Vector3f(inputPosInfo._inputCoordinate[0], inputPosInfo._inputCoordinate[1], inputPosInfo._inputCoordinate[2]);

	result._rotateOffset.translation = ADE::Vector3f(inputPosInfo._rotateOffset[0], inputPosInfo._rotateOffset[1], inputPosInfo._rotateOffset[2]);
	result._actionType = static_cast<ACTION_TYPE>(inputPosInfo._actType);

	return result;
}

sds_animPosInfo HelperConverter::convertEditPosInfoToAnimPos (const EditPositionInfo& inputPosInfo)
{

	sds_animPosInfo result;
	sds_point jj = {inputPosInfo._inputPosition.translation.x,inputPosInfo._inputPosition.translation.y,inputPosInfo._inputPosition.translation.z};

	sds_point_set(jj,result._inputCoordinate);

	result._scaleXYZ[0] = inputPosInfo._inputPosition.scale.x;
	result._scaleXYZ[1] = inputPosInfo._inputPosition.scale.y;
	result._scaleXYZ[2] = inputPosInfo._inputPosition.scale.z;
	result._rotateXYZ[0] = ADEX::getAngleX(inputPosInfo._inputPosition.rotation); //std::asin(inputPosInfo.rotation.data[5]);
	result._rotateXYZ[1] = ADEX::getAngleY(inputPosInfo._inputPosition.rotation); //std::asin(inputPosInfo.rotation.data[6]);
	result._rotateXYZ[2] = ADEX::getAngleZ(inputPosInfo._inputPosition.rotation); //std::asin(inputPosInfo.rotation.data[1]);
	result._rotateOffset[0] = inputPosInfo._rotateOffset.translation.x;
	result._rotateOffset[1] = inputPosInfo._rotateOffset.translation.y;
	result._rotateOffset[2] = inputPosInfo._rotateOffset.translation.z;
	result._actType = static_cast<int>(inputPosInfo._actionType);

	return result;
}


bool HelperConverter::isNaNTransform (ADEX::Transform & isNanTransform)
{
	return !(isNanTransform.rotation.data[0] == isNanTransform.rotation.data[0] && isNanTransform.translation.x == isNanTransform.translation.x && isNanTransform.scale.x == isNanTransform.scale.x);
}

bool HelperConverter::isNaNEditPosInfo (EditPositionInfo & nanEditInfo)
{
	return isNaNTransform(nanEditInfo._inputPosition);
}


bool HelperConverter::isNaNFloat (float inputVal)
{
	return !(inputVal == inputVal);
}

void HelperConverter::convertToNaNTransform(ADEX::Transform & nanTransform)
{
	ADE::Matrix3x3f nan;
	nan.data[0] = nan.data[1]= nan.data[2]= nan.data[3]= nan.data[4]= nan.data[5]= nan.data[6]= nan.data[7]= nan.data[8]= std::numeric_limits<float>::quiet_NaN();
	nanTransform.scale =  ADE::Vector3f(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
	nanTransform.translation = ADE::Vector3f(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
	nanTransform.rotation = nan;
}

void HelperConverter::convertToNaNEditPosInfo(EditPositionInfo & nanEditInfo)
{
	convertToNaNTransform(nanEditInfo._inputPosition);
	//convertToNaNTransform(nanEditInfo._rotateOffset);
}
