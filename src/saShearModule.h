#ifndef _saShearModule
#define _saShearModule

#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MTypeId.h> 
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MGlobal.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>


class saShearModule : public MPxNode
{
public:
	saShearModule();
	virtual				~saShearModule();
	virtual MStatus		compute(const MPlug& plug, MDataBlock& data);
	static  void*		creator();
	static  MStatus		initialize();

public:
	static  MObject aInMatrixA;
	static  MObject aInMatrixB;
	static  MObject aInMatrixO;
	static	MObject aAreaBulgeWeight;
	static	MObject aPerimeterBulgeWeight;
	static	MObject aExtraBulge;
	static	MObject aBulgePower;
	static	MObject aBulgeScale;
	static	MObject aAreaMinimumRatio;
	static	MObject aAreaCurrent;
	static	MObject aPerimeterCurrent;
	static	MObject aAreaDefault;
	static	MObject aPerimeterDefault;
	static	MObject aAreaValue;
	static	MObject aPerimeterValue;
	static	MObject aBulgeValue;
	static	MObject aCorrectScale;
	static	MObject aCorrectScaleX;
	static	MObject aCorrectScaleY;
	static	MObject aCorrectScaleZ;
	static  MObject aOutMatrix;
	static  MObject aOutTranslate;
	static  MObject aOutTranslateX;
	static  MObject aOutTranslateY;
	static  MObject aOutTranslateZ;
	static  MObject aOutRotate;
	static  MObject aOutRotateX;
	static  MObject aOutRotateY;
	static  MObject aOutRotateZ;
	static  MObject aOutScale;
	static  MObject aOutScaleX;
	static  MObject aOutScaleY;
	static  MObject aOutScaleZ;
	static  MObject aOutShear;
	static  MObject aOutShearXY;
	static  MObject aOutShearXZ;
	static  MObject aOutShearYZ;
	static	MTypeId	id;

};

#endif
