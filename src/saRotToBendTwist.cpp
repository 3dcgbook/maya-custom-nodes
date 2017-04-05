#include "saRotToBendTwist.h"



MTypeId     saRotToBendTwist::id(0x00001);
MObject     saRotToBendTwist::aMethod;
MObject     saRotToBendTwist::aReverse;
MObject     saRotToBendTwist::aInRotateX;
MObject     saRotToBendTwist::aInRotateY;
MObject     saRotToBendTwist::aInRotateZ;
MObject     saRotToBendTwist::aInRotate;
MObject     saRotToBendTwist::aOutSwingX;
MObject     saRotToBendTwist::aOutSwingY;
MObject     saRotToBendTwist::aOutSwingZ;
MObject     saRotToBendTwist::aOutSwing;
MObject     saRotToBendTwist::aOutRollX;
MObject     saRotToBendTwist::aOutRollY;
MObject     saRotToBendTwist::aOutRollZ;
MObject     saRotToBendTwist::aOutRoll;

saRotToBendTwist::saRotToBendTwist() {}
saRotToBendTwist::~saRotToBendTwist() {}

MStatus saRotToBendTwist::compute(const MPlug& plug, MDataBlock& data)
{
	if (!(plug == aOutRoll  || plug == aOutRollX  || plug == aOutRollY  || plug == aOutRollZ ||
		  plug == aOutSwing || plug == aOutSwingX || plug == aOutSwingY || plug == aOutSwingZ))
			return MS::kFailure;
	
	MDataHandle handle = data.inputValue(aInRotate);
	double3 &a = handle.asDouble3();

	handle = data.inputValue(aReverse);
	bool reverse = handle.asBool();

	MEulerRotation rot(a[0], a[1], a[2]);
	MQuaternion quat = rot.asQuaternion();
	if (reverse)
		quat = quat.inverse();
	MVector _X_VEC = MVector::xAxis;
	MVector vec = _X_VEC.rotateBy(quat);
	MQuaternion swingQ = MQuaternion(_X_VEC, vec);
	MQuaternion rollQ = quat * swingQ.inverse();
	if (reverse){
		swingQ = swingQ.inverse();
		rollQ = rollQ.inverse();
	}

	MEulerRotation swingE = swingQ.asEulerRotation();
	MEulerRotation rollE  = rollQ.asEulerRotation();

	handle = data.outputValue(aOutRoll);
	handle.set(rollE.x,rollE.y,rollE.z);

	handle = data.outputValue(aOutSwing);
	handle.set(swingE.x, swingE.y, swingE.z);

	data.setClean(plug);

	return MS::kSuccess;
}

void* saRotToBendTwist::creator(){
	return new saRotToBendTwist();
}

MStatus saRotToBendTwist::initialize()
{
	MStatus				stat;
	MFnNumericAttribute fnNumeric;
	MFnUnitAttribute fnUnit;

	aReverse = fnNumeric.create("reverseOrder", "ror", MFnNumericData::kBoolean, false, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	addAttribute(aReverse);

	aInRotateX = fnUnit.create("inRotateX", "irx",MFnUnitAttribute::kAngle, 0.0,&stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInRotateY = fnUnit.create("inRotateY", "iry", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInRotateZ = fnUnit.create("inRotateZ", "irz", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aInRotate  = fnNumeric.create("inRotate","ir",aInRotateX,aInRotateY,aInRotateZ,&stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	addAttribute(aInRotate);

	aOutSwingX = fnUnit.create("outSwingX", "osx", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutSwingY = fnUnit.create("outSwingY", "osy", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutSwingZ = fnUnit.create("outSwingZ", "osz", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutSwing = fnNumeric.create("outSwing", "os", aOutSwingX, aOutSwingY, aOutSwingZ, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	fnNumeric.setWritable(false);
	fnNumeric.setStorable(false);
	addAttribute(aOutSwing);
	
	aOutRollX = fnUnit.create("outRollX", "orx", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutRollY = fnUnit.create("outRollY", "ory", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutRollZ = fnUnit.create("outRollZ", "orz", MFnUnitAttribute::kAngle, 0.0, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	aOutRoll = fnNumeric.create("outRoll", "or", aOutRollX, aOutRollY, aOutRollZ, &stat);
	CHECK_MSTATUS_AND_RETURN_IT(stat);
	fnNumeric.setWritable(false);
	fnNumeric.setStorable(false);
	addAttribute(aOutRoll);

	attributeAffects(aReverse,aOutSwing);
	attributeAffects(aReverse, aOutRoll);
	attributeAffects(aInRotate, aOutSwing);
	attributeAffects(aInRotate, aOutRoll);

	return MS::kSuccess;

}

