#ifndef _saClosestIntersectionOnMesh
#define _saClosestIntersectionOnMesh

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

#include <maya/MFloatPoint.h>
#include <maya/MFloatMatrix.h>
#include <maya/MFloatVector.h>
#include <maya/MFnMesh.h>
#include <maya/MQuaternion.h>
#include <maya/MVector.h>


class saClosestIntersectionOnMesh : public MPxNode
{
public:
	saClosestIntersectionOnMesh();
	virtual				~saClosestIntersectionOnMesh();

	virtual MStatus		compute(const MPlug& plug, MDataBlock& data);

	static  void*		creator();
	static  MStatus		initialize();

public:

	static MObject aInMesh;

	static MObject aInSourcePointX;
	static MObject aInSourcePointY;
	static MObject aInSourcePointZ;
	static MObject aInSourcePoint;

	static MObject aInRayDirectionX;
	static MObject aInRayDirectionY;
	static MObject aInRayDirectionZ;
	static MObject aInRayDirection;

	static MObject aInMaxParam;
	static MObject aInTestBothDirections;
	static MObject aInMatrix;


	static MObject aOutHitPointX;
	static MObject aOutHitPointY;
	static MObject aOutHitPointZ;
	static MObject aOutHitPoint;

	static	MTypeId		id;
};

#endif
