#ifndef _saMultRot
#define _saMultRot

#include <maya/MPxNode.h>
#include <maya/MTypeId.h> 
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MEulerRotation.h>
#include <maya/MQuaternion.h>
#include <maya/MVector.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MArrayDataHandle.h>

class saMultRot : public MPxNode
{
public:
	saMultRot();
	virtual				~saMultRot();

	virtual MStatus		compute(const MPlug& plug, MDataBlock& data);

	static  void*		creator();
	static  MStatus		initialize();

public:

	static MObject aMethod;
	static MObject aReverse;

	static MObject aInRotateX;
	static MObject aInRotateY;
	static MObject aInRotateZ;
	static MObject aInRotate;

	static MObject aOutRotateX;
	static MObject aOutRotateY;
	static MObject aOutRotateZ;
	static MObject aOutRotate;

	static	MTypeId		id;
};

#endif
