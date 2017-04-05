#include "saClosestIntersectionOnMesh.h"

MTypeId		saClosestIntersectionOnMesh::id(0x00003);
MObject		saClosestIntersectionOnMesh::aInMesh;
MObject		saClosestIntersectionOnMesh::aInSourcePointX;
MObject		saClosestIntersectionOnMesh::aInSourcePointY;
MObject		saClosestIntersectionOnMesh::aInSourcePointZ;
MObject		saClosestIntersectionOnMesh::aInSourcePoint;
MObject		saClosestIntersectionOnMesh::aInRayDirectionX;
MObject		saClosestIntersectionOnMesh::aInRayDirectionY;
MObject		saClosestIntersectionOnMesh::aInRayDirectionZ;
MObject		saClosestIntersectionOnMesh::aInRayDirection;
MObject		saClosestIntersectionOnMesh::aOutHitPointX;
MObject		saClosestIntersectionOnMesh::aOutHitPointY;
MObject		saClosestIntersectionOnMesh::aOutHitPointZ;
MObject		saClosestIntersectionOnMesh::aOutHitPoint;
MObject		saClosestIntersectionOnMesh::aInMaxParam;
MObject		saClosestIntersectionOnMesh::aInTestBothDirections;
MObject		saClosestIntersectionOnMesh::aInMatrix;

saClosestIntersectionOnMesh::saClosestIntersectionOnMesh() {}
saClosestIntersectionOnMesh::~saClosestIntersectionOnMesh() {}

MStatus saClosestIntersectionOnMesh::compute(const MPlug& plug, MDataBlock& data)
{
	if (!(plug == aOutHitPoint || plug == aOutHitPointX || plug == aOutHitPointY || plug == aOutHitPointZ))
		return MS::kFailure;
	
	MStatus stat;
	MDataHandle handle;
	MFnMesh inMeshData = data.inputValue(aInMesh).asMesh();
	double3 &inSourcePtData = data.inputValue(aInSourcePoint).asDouble3();
	double3 &inRayDirData = data.inputValue(aInRayDirection).asDouble3();
	float mpdata = data.inputValue(aInMaxParam).asFloat();
	bool tbddata = data.inputValue(aInTestBothDirections).asBool();
	MFloatMatrix inclusiveM = data.inputValue(aInMatrix).asFloatMatrix();
	
	MFloatPoint  raySource((float)inSourcePtData[0], (float)inSourcePtData[1], (float)inSourcePtData[2], 1.0f);
	MFloatVector rayDirection((float)inRayDirData[0], (float)inRayDirData[1], (float)inRayDirData[2]);
	MFloatPoint hitPoint;
	inMeshData.closestIntersection(raySource, rayDirection, NULL, NULL, false, MSpace::kObject, mpdata, tbddata, NULL, hitPoint, NULL, NULL, NULL, NULL, NULL, 1e-6f, &stat);
	hitPoint *= inclusiveM;
	
	data.outputValue(aOutHitPoint).set(hitPoint.x, hitPoint.y, hitPoint.z);
	data.setClean(plug);

	return MS::kSuccess;
}

void* saClosestIntersectionOnMesh::creator(){
	return new saClosestIntersectionOnMesh();
}

MStatus saClosestIntersectionOnMesh::initialize()
{
	MStatus				stat;
	MFnNumericAttribute fnNumeric;
	MFnUnitAttribute fnUnit;
	MFnTypedAttribute fnType;
	MFnMatrixAttribute fnMatrix;
	
	aInMesh = fnType.create("inMesh", "im", MFnData::kMesh, &stat);
	addAttribute(aInMesh);
	
	aInMaxParam = fnNumeric.create("maxParam", "mp", MFnNumericData::kFloat, 99999.0f, &stat);
	addAttribute(aInMaxParam);
	
	aInTestBothDirections = fnNumeric.create("testBothDirections", "tbd", MFnNumericData::kBoolean, false, &stat);
	addAttribute(aInTestBothDirections);
	
	aInSourcePointX = fnNumeric.create("inSourcePointX", "ispx", MFnNumericData::kDouble, 0.0, &stat);
	aInSourcePointY = fnNumeric.create("inSourcePointY", "ispy", MFnNumericData::kDouble, 0.0, &stat);
	aInSourcePointZ = fnNumeric.create("inSourcePointZ", "ispz", MFnNumericData::kDouble, 0.0, &stat);
	aInSourcePoint  = fnNumeric.create("inSourcePoint", "isp", aInSourcePointX, aInSourcePointY, aInSourcePointZ,&stat);
	addAttribute(aInSourcePoint);
	
	aInRayDirectionX = fnNumeric.create("inRayDirectionX", "irdx", MFnNumericData::kDouble, 1.0, &stat);
	aInRayDirectionY = fnNumeric.create("inRayDirectionY", "irdy", MFnNumericData::kDouble, 0.0, &stat);
	aInRayDirectionZ = fnNumeric.create("inRayDirectionZ", "irdz", MFnNumericData::kDouble, 0.0, &stat);
	aInRayDirection = fnNumeric.create("inRayDirection", "ird", aInRayDirectionX, aInRayDirectionY, aInRayDirectionZ, &stat);
	addAttribute(aInRayDirection);
	
	aInMatrix = fnMatrix.create("inInclusiveMatrix", "iim", MFnMatrixAttribute::kFloat, &stat);
	addAttribute(aInMatrix);
	
	aOutHitPointX = fnNumeric.create("outHitPointX", "ohpx", MFnNumericData::kFloat, 0.0, &stat);
	aOutHitPointY = fnNumeric.create("outHitPointY", "ohpy", MFnNumericData::kFloat, 0.0, &stat);
	aOutHitPointZ = fnNumeric.create("outHitPointZ", "ohpz", MFnNumericData::kFloat, 0.0, &stat);
	aOutHitPoint  = fnNumeric.create("outHitPoint", "ohp", aOutHitPointX,aOutHitPointY,aOutHitPointZ, &stat);
	fnNumeric.setWritable(false);
	fnNumeric.setStorable(false);
	addAttribute(aOutHitPoint);
	
	attributeAffects(aInMesh, aOutHitPoint);
	attributeAffects(aInMaxParam, aOutHitPoint);
	attributeAffects(aInTestBothDirections, aOutHitPoint);
	attributeAffects(aInSourcePoint, aOutHitPoint);
	attributeAffects(aInRayDirection, aOutHitPoint);
	attributeAffects(aInMatrix, aOutHitPoint);
	
	return MS::kSuccess;

}

