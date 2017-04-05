#include "saIntersectOnSurface.h"

MTypeId		saIntersectOnSurface::id(0x00006);
MObject		saIntersectOnSurface::aInSrf;
MObject		saIntersectOnSurface::aInSourcePointX;
MObject		saIntersectOnSurface::aInSourcePointY;
MObject		saIntersectOnSurface::aInSourcePointZ;
MObject		saIntersectOnSurface::aInSourcePoint;
MObject		saIntersectOnSurface::aInRayDirectionX;
MObject		saIntersectOnSurface::aInRayDirectionY;
MObject		saIntersectOnSurface::aInRayDirectionZ;
MObject		saIntersectOnSurface::aInRayDirection;
MObject		saIntersectOnSurface::aOutHitPointX;
MObject		saIntersectOnSurface::aOutHitPointY;
MObject		saIntersectOnSurface::aOutHitPointZ;
MObject		saIntersectOnSurface::aOutHitPoint;
MObject		saIntersectOnSurface::aInMatrix;

saIntersectOnSurface::saIntersectOnSurface() {}
saIntersectOnSurface::~saIntersectOnSurface() {}

MStatus saIntersectOnSurface::compute(const MPlug& plug, MDataBlock& data)
{
	if (!(plug == aOutHitPoint || plug == aOutHitPointX || plug == aOutHitPointY || plug == aOutHitPointZ))
		return MS::kFailure;

	MFnNurbsSurface inSrfData = data.inputValue(aInSrf).asNurbsSurface();
	double3 &inSourcePtData = data.inputValue(aInSourcePoint).asDouble3();
	double3 &inRayDirData = data.inputValue(aInRayDirection).asDouble3();
	MMatrix inclusiveM = data.inputValue(aInMatrix).asMatrix();

	MPoint  raySource(inSourcePtData[0], inSourcePtData[1], inSourcePtData[2], 1.0);
	MVector rayDirection(inRayDirData[0], inRayDirData[1], inRayDirData[2]);
	MPoint hitPoint;
	
	double u, v;

	inSrfData.intersect(raySource,rayDirection,u,v,hitPoint,1.0e-3,MSpace::kObject,false,NULL,false,NULL,NULL);
	hitPoint *= inclusiveM;

	data.outputValue(aOutHitPoint).set(hitPoint.x, hitPoint.y, hitPoint.z);

	return MS::kSuccess;
}

void* saIntersectOnSurface::creator(){
	return new saIntersectOnSurface();
}

MStatus saIntersectOnSurface::initialize()
{
	MStatus				stat;
	MFnNumericAttribute fnNumeric;
	MFnUnitAttribute fnUnit;
	MFnTypedAttribute fnType;
	MFnMatrixAttribute fnMatrix;

	aInSrf = fnType.create("create", "cr", MFnData::kNurbsSurface, &stat);
	addAttribute(aInSrf);


	aInSourcePointX = fnNumeric.create("inSourcePointX", "ispx", MFnNumericData::kDouble, 0.0, &stat);
	aInSourcePointY = fnNumeric.create("inSourcePointY", "ispy", MFnNumericData::kDouble, 0.0, &stat);
	aInSourcePointZ = fnNumeric.create("inSourcePointZ", "ispz", MFnNumericData::kDouble, 0.0, &stat);
	aInSourcePoint = fnNumeric.create("inSourcePoint", "isp", aInSourcePointX, aInSourcePointY, aInSourcePointZ, &stat);
	addAttribute(aInSourcePoint);

	aInRayDirectionX = fnNumeric.create("inRayDirectionX", "irdx", MFnNumericData::kDouble, 1.0, &stat);
	aInRayDirectionY = fnNumeric.create("inRayDirectionY", "irdy", MFnNumericData::kDouble, 0.0, &stat);
	aInRayDirectionZ = fnNumeric.create("inRayDirectionZ", "irdz", MFnNumericData::kDouble, 0.0, &stat);
	aInRayDirection = fnNumeric.create("inRayDirection", "ird", aInRayDirectionX, aInRayDirectionY, aInRayDirectionZ, &stat);
	addAttribute(aInRayDirection);

	aInMatrix = fnMatrix.create("inInclusiveMatrix", "iim", MFnMatrixAttribute::kDouble, &stat);
	addAttribute(aInMatrix);

	aOutHitPointX = fnNumeric.create("outHitPointX", "ohpx", MFnNumericData::kDouble, 0.0, &stat);
	aOutHitPointY = fnNumeric.create("outHitPointY", "ohpy", MFnNumericData::kDouble, 0.0, &stat);
	aOutHitPointZ = fnNumeric.create("outHitPointZ", "ohpz", MFnNumericData::kDouble, 0.0, &stat);
	aOutHitPoint = fnNumeric.create("outHitPoint", "ohp", aOutHitPointX, aOutHitPointY, aOutHitPointZ, &stat);
	fnNumeric.setWritable(false);
	fnNumeric.setStorable(false);
	addAttribute(aOutHitPoint);

	attributeAffects(aInSrf, aOutHitPoint);
	attributeAffects(aInSourcePoint, aOutHitPoint);
	attributeAffects(aInRayDirection, aOutHitPoint);
	attributeAffects(aInMatrix, aOutHitPoint);

	return MS::kSuccess;

}

