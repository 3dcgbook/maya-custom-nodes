#ifndef _saQuaternionTransform
#define _saQuaternionTransform

#include <maya/MPxNode.h>
#include <maya/MTypeId.h> 
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MEulerRotation.h>
#include <maya/MQuaternion.h>
#include <maya/MVector.h>

class saQuaternionTransform : public MPxNode
{
public:
	saQuaternionTransform();
	virtual				~saQuaternionTransform();
	virtual MStatus		compute(const MPlug& plug, MDataBlock& data);
	static  void*		creator();
	static  MStatus		initialize();


public:

	static MObject aInRotateOrder;

	static MObject aInPositionX;
	static MObject aInPositionY;
	static MObject aInPositionZ;
	static MObject aInPosition;

	static MObject aInRotateX;
	static MObject aInRotateY;
	static MObject aInRotateZ;
	static MObject aInRotate;

	static MObject aOutPositionX;
	static MObject aOutPositionY;
	static MObject aOutPositionZ;
	static MObject aOutPosition;

	static	MTypeId		id;
};

#endif
