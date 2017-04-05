#ifndef _saClosestIntersectionOnNurbs
#define _saClosestIntersectionOnNurbs

#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MTypeId.h> 

class saClosestIntersectionOnNurbs : public MPxNode
{
public:
	saClosestIntersectionOnNurbs();
	virtual				~saClosestIntersectionOnNurbs();

	virtual MStatus		compute(const MPlug& plug, MDataBlock& data);

	static  void*		creator();
	static  MStatus		initialize();

public:

	static MObject aInNurbsSurface;



	static	MTypeId		id;
};

#endif
