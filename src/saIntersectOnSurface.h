#ifndef _saIntersectOnSurface
#define _saIntersectOnSurface

#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>

#include <maya/MPoint.h>
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MVector.h>
#include <maya/MFnNurbsSurface.h>


class saIntersectOnSurface : public MPxNode
{
public:
	saIntersectOnSurface();
	virtual				~saIntersectOnSurface();

	virtual MStatus		compute(const MPlug& plug, MDataBlock& data);

	static  void*		creator();
	static  MStatus		initialize();

public:

	static MObject aInSrf;

	static MObject aInSourcePointX;
	static MObject aInSourcePointY;
	static MObject aInSourcePointZ;
	static MObject aInSourcePoint;

	static MObject aInRayDirectionX;
	static MObject aInRayDirectionY;
	static MObject aInRayDirectionZ;
	static MObject aInRayDirection;

	static MObject aInMatrix;


	static MObject aOutHitPointX;
	static MObject aOutHitPointY;
	static MObject aOutHitPointZ;
	static MObject aOutHitPoint;

	static	MTypeId		id;
};

#endif
