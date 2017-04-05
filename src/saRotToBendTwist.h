#ifndef _saRotToBendTwist
#define _saRotToBendTwist

#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MEulerRotation.h>
#include <maya/MQuaternion.h>
#include <maya/MVector.h>
 
class saRotToBendTwist : public MPxNode
{
public:
						saRotToBendTwist();
	virtual				~saRotToBendTwist();

	virtual MStatus		compute( const MPlug& plug, MDataBlock& data );

	static  void*		creator();
	static  MStatus		initialize();

public:

	static MObject aMethod;
	static MObject aReverse;

	static MObject aInRotateX;
	static MObject aInRotateY;
	static MObject aInRotateZ;
	static MObject aInRotate;

	static MObject aOutSwingX;
	static MObject aOutSwingY;
	static MObject aOutSwingZ;
	static MObject aOutSwing;

	static MObject aOutRollX;
	static MObject aOutRollY;
	static MObject aOutRollZ;
	static MObject aOutRoll;

	static	MTypeId		id;
};

#endif
