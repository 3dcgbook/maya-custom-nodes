#include "saQuaternionTransform.h"

MTypeId     saQuaternionTransform::id(0x00005);
MObject     saQuaternionTransform::aInRotateOrder;
MObject     saQuaternionTransform::aInPositionX;
MObject     saQuaternionTransform::aInPositionY;
MObject     saQuaternionTransform::aInPositionZ;
MObject     saQuaternionTransform::aInPosition;
MObject     saQuaternionTransform::aInRotateX;
MObject     saQuaternionTransform::aInRotateY;
MObject     saQuaternionTransform::aInRotateZ;
MObject     saQuaternionTransform::aInRotate;
MObject     saQuaternionTransform::aOutPositionX;
MObject     saQuaternionTransform::aOutPositionY;
MObject     saQuaternionTransform::aOutPositionZ;
MObject     saQuaternionTransform::aOutPosition;

saQuaternionTransform::saQuaternionTransform() {}
saQuaternionTransform::~saQuaternionTransform() {}

MStatus saQuaternionTransform::compute(const MPlug& plug, MDataBlock& data)
{
	if (!(plug == aOutPosition || plug.parent() == aOutPosition))
		return MS::kFailure;

	short roData = data.inputValue(aInRotateOrder).asShort();
	double3 &inPosData = data.inputValue(aInPosition).asDouble3();
	double3 &inRotData = data.inputValue(aInRotate).asDouble3();
	MVector vec(inPosData[0], inPosData[1], inPosData[2]);
	MEulerRotation rot(inRotData[0], inRotData[1], inRotData[2], MEulerRotation::RotationOrder(roData));
	MQuaternion quat = rot.asQuaternion();
	vec = vec.rotateBy(quat);
	data.outputValue(aOutPosition).set(vec);
	data.setClean(plug);

	return MS::kSuccess;
}

void* saQuaternionTransform::creator(){
	return new saQuaternionTransform();
}

MStatus saQuaternionTransform::initialize()
{
	MStatus				stat;
	MFnNumericAttribute fnNumeric;
	MFnEnumAttribute fnEnum;
	MFnUnitAttribute fnUnit;
	
	aInRotateOrder = fnEnum.create("rotateOrder", "ro",0,&stat);
	fnEnum.addField("xyz", 0);
	fnEnum.addField("yzx", 1);
	fnEnum.addField("zxy", 2);
	fnEnum.addField("xzy", 3);
	fnEnum.addField("yxz", 4);
	fnEnum.addField("zyx", 5);
	addAttribute(aInRotateOrder);

	aInPositionX = fnNumeric.create("inPositionX", "ipx", MFnNumericData::kDouble, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInPositionY = fnNumeric.create("inPositionY", "ipy", MFnNumericData::kDouble, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInPositionZ = fnNumeric.create("inPositionZ", "ipz", MFnNumericData::kDouble, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInPosition = fnNumeric.create("inPosition", "ip", aInPositionX, aInPositionY, aInPositionZ);
	addAttribute(aInPosition);

	aInRotateX = fnUnit.create("inRotateX", "irx", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInRotateY = fnUnit.create("inRotateY", "iry", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInRotateZ = fnUnit.create("inRotateZ", "irz", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInRotate = fnNumeric.create("inRotate", "ir", aInRotateX, aInRotateY, aInRotateZ, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	addAttribute(aInRotate);
	
	aOutPositionX = fnNumeric.create("outPositionX", "opx", MFnNumericData::kDouble, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutPositionY = fnNumeric.create("outPositionY", "opy", MFnNumericData::kDouble, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutPositionZ = fnNumeric.create("outPositionZ", "opz", MFnNumericData::kDouble, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutPosition = fnNumeric.create("outPosition", "op", aOutPositionX, aOutPositionY, aOutPositionZ, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	fnNumeric.setWritable(false);
	fnNumeric.setStorable(false);
	addAttribute(aOutPosition);
	
	attributeAffects(aInRotateOrder, aOutPosition);
	attributeAffects(aInPosition, aOutPosition);
	attributeAffects(aInRotate, aOutPosition);

	return MS::kSuccess;

}

