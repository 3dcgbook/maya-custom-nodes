#include "saMultRot.h"

MTypeId     saMultRot::id(0x00002);
MObject     saMultRot::aMethod;
MObject     saMultRot::aReverse;
MObject     saMultRot::aInRotateX;
MObject     saMultRot::aInRotateY;
MObject     saMultRot::aInRotateZ;
MObject     saMultRot::aInRotate;
MObject     saMultRot::aOutRotateX;
MObject     saMultRot::aOutRotateY;
MObject     saMultRot::aOutRotateZ;
MObject     saMultRot::aOutRotate;

saMultRot::saMultRot() {}
saMultRot::~saMultRot() {}

MStatus saMultRot::compute(const MPlug& plug, MDataBlock& data)
{
	if (!(plug == aOutRotate || plug == aOutRotateX || plug == aOutRotateY || plug == aOutRotateZ))
		return MS::kFailure;
	
	MArrayDataHandle arrayHandle = data.inputArrayValue(aInRotate);
	MDataHandle handle;
	MQuaternion quat;
	MEulerRotation rot;
	unsigned count = arrayHandle.elementCount();
	for (unsigned num = 0; num < count; num++){
		arrayHandle.jumpToArrayElement(num);
		handle = arrayHandle.inputValue().child(aInRotate);
		double3 &a = handle.asDouble3();
		rot.setValue(a[0], a[1], a[2]);
		quat *= rot.asQuaternion();
	}
	rot = quat.asEulerRotation();
	
	handle = data.outputValue(aOutRotate);
	handle.set(rot.x, rot.y, rot.z);
	
	data.setClean(plug);

	return MS::kSuccess;
}

void* saMultRot::creator(){
	return new saMultRot();
}

MStatus saMultRot::initialize()
{
	MStatus				stat;
	MFnNumericAttribute fnNumeric;
	MFnUnitAttribute fnUnit;

	aReverse = fnNumeric.create("reverseOrder", "ror", MFnNumericData::kBoolean, false, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	addAttribute(aReverse);

	aInRotateX = fnUnit.create("inRotateX", "irx", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInRotateY = fnUnit.create("inRotateY", "iry", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInRotateZ = fnUnit.create("inRotateZ", "irz", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInRotate = fnNumeric.create("inRotate", "ir", aInRotateX, aInRotateY, aInRotateZ, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	fnNumeric.setArray(true);
	fnNumeric.setHidden(true);
	addAttribute(aInRotate);

	aOutRotateX = fnUnit.create("outRotateX", "orx", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutRotateY = fnUnit.create("outRotateY", "ory", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutRotateZ = fnUnit.create("outRotateZ", "orz", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutRotate = fnNumeric.create("outRotate", "or", aOutRotateX, aOutRotateY, aOutRotateZ, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	fnNumeric.setWritable(false);
	fnNumeric.setStorable(false);
	addAttribute(aOutRotate);

	attributeAffects(aInRotate, aOutRotate);

	return MS::kSuccess;

}

