#include "saShearModule.h"

MTypeId saShearModule::id(0x00004);

MObject saShearModule::aAreaBulgeWeight;
MObject saShearModule::aPerimeterBulgeWeight;
MObject saShearModule::aExtraBulge;
MObject saShearModule::aBulgePower;
MObject saShearModule::aBulgeScale;
MObject saShearModule::aAreaMinimumRatio;
MObject saShearModule::aAreaCurrent;
MObject saShearModule::aPerimeterCurrent;
MObject saShearModule::aAreaDefault;
MObject saShearModule::aPerimeterDefault;
MObject saShearModule::aAreaValue;
MObject saShearModule::aPerimeterValue;
MObject saShearModule::aBulgeValue;
MObject saShearModule::aCorrectScale;
MObject saShearModule::aCorrectScaleX;
MObject saShearModule::aCorrectScaleY;
MObject saShearModule::aCorrectScaleZ;
MObject saShearModule::aOutMatrix;
MObject saShearModule::aOutTranslate;
MObject saShearModule::aOutTranslateX;
MObject saShearModule::aOutTranslateY;
MObject saShearModule::aOutTranslateZ;
MObject saShearModule::aOutRotate;
MObject saShearModule::aOutRotateY;
MObject saShearModule::aOutRotateZ;
MObject saShearModule::aOutScale;
MObject saShearModule::aOutScaleX;
MObject saShearModule::aOutScaleY;
MObject saShearModule::aOutScaleZ;
MObject saShearModule::aOutShear;
MObject saShearModule::aOutShearXY;
MObject saShearModule::aOutShearXZ;
MObject saShearModule::aOutShearYZ;
MObject saShearModule::aInMatrixA;
MObject saShearModule::aInMatrixB;
MObject saShearModule::aInMatrixO;
saShearModule::saShearModule() {}
saShearModule::~saShearModule() {}

MStatus saShearModule::compute(const MPlug& plug, MDataBlock& data)

{
	MStatus stat;
	if (plug != aOutMatrix)
		return MS::kFailure;
	
	MMatrix		inMatrixA = data.inputValue(aInMatrixA, &stat).asMatrix();
	MMatrix		inMatrixB = data.inputValue(aInMatrixB, &stat).asMatrix();
	MMatrix		inMatrixO = data.inputValue(aInMatrixO, &stat).asMatrix();
	double perimeterDefaultBase = data.inputValue(aPerimeterDefault, &stat).asDouble();
	double areaMinRatio = data.inputValue(aAreaMinimumRatio, &stat).asDouble();
	double areaDefaultBase = data.inputValue(aAreaDefault, &stat).asDouble();
	double areaBulgeWeight = data.inputValue(aAreaBulgeWeight, &stat).asDouble();
	double perimeterBulgeWeight = data.inputValue(aPerimeterBulgeWeight, &stat).asDouble();
	double extraBulge = data.inputValue(aExtraBulge, &stat).asDouble();
	double bulgePower = data.inputValue(aBulgePower, &stat).asDouble();
	double bulgeScale = data.inputValue(aBulgeScale, &stat).asDouble();
	double correctScaleX = data.inputValue(aCorrectScaleX, &stat).asDouble();
	double correctScaleY = data.inputValue(aCorrectScaleY, &stat).asDouble();
	double correctScaleZ = data.inputValue(aCorrectScaleZ, &stat).asDouble();

	MVector p0(inMatrixO[3][0], inMatrixO[3][1], inMatrixO[3][2]);
	MVector p1(inMatrixA[3][0], inMatrixA[3][1], inMatrixA[3][2]);
	MVector p2(inMatrixB[3][0], inMatrixB[3][1], inMatrixB[3][2]);

	MVector vx(p1 - p0);
	MVector vy(p2 - p0);
	MVector nml(vx^vy);
	double magNml = nml.length();

	// side lengthes of a triangle //
	double a = (p1 - p0).length();
	double b = (p2 - p1).length();
	double c = (p0 - p2).length();

	// perimeter base //
	double perimFactor = (a + b + c) / 3.0;
	double perimValue = perimFactor / perimeterDefaultBase;

	// cross-product(area) base //
	double areaFactor = std::sqrt(magNml);
	double areaValue = areaMinRatio + (1.0 - areaMinRatio) * areaFactor / areaDefaultBase;

	// mixes values //
	double sc = ((1.0 - areaBulgeWeight) + areaValue * areaBulgeWeight)*
		((1.0 - perimeterBulgeWeight) + perimValue * perimeterBulgeWeight);

	MVector vz(nml / magNml*std::pow(sc*extraBulge, bulgePower)*bulgeScale);
	//MVector correct(correctScaleX, correctScaleY, correctScaleZ);
	vx *= correctScaleX;
	vy *= correctScaleY;
	vz *= correctScaleZ;

	MDataHandle outMatrixData = data.outputValue(aOutMatrix);
	MDataHandle outPerimeterCurrentData = data.outputValue(aPerimeterCurrent);
	MDataHandle outPerimeterValueData = data.outputValue(aPerimeterValue);
	MDataHandle outAreaCurrentData = data.outputValue(aAreaCurrent);
	MDataHandle outAreaValueData = data.outputValue(aAreaValue);
	MDataHandle outBulgeValue = data.outputValue(aBulgeValue);

	outPerimeterCurrentData.setDouble(perimFactor);
	outPerimeterValueData.setDouble(perimValue);
	outAreaCurrentData.setDouble(areaFactor);
	outAreaValueData.setDouble(areaValue);
	outBulgeValue.setDouble(sc);
	double resultMatrixArray[4][4] = { { vx.x, vx.y, vx.z, 0.0 }, { vy.x, vy.y, vy.z, 0.0 }, { vz.x, vz.y, vz.z, 0.0 }, { p0.x, p0.y, p0.z, 1.0 } };
	MMatrix resultMatrix(resultMatrixArray);
	outMatrixData.setMMatrix(resultMatrix);

	MTransformationMatrix mtrans(resultMatrix);

	data.setClean(plug);

	return MS::kSuccess;
}

void* saShearModule::creator()

{
	return new saShearModule();
}

MStatus saShearModule::initialize()
{
	MStatus status;
	MFnNumericAttribute numFn;
	MFnUnitAttribute	uAttr;
	MFnMatrixAttribute mAttr;

	aInMatrixA = mAttr.create("inMatrix1", "im1", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(false);
	mAttr.setStorable(true);
	mAttr.setHidden(true);

	aInMatrixB = mAttr.create("inMatrix2", "im2", MFnMatrixAttribute::kDouble,&status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(false);
	mAttr.setStorable(true);
	mAttr.setHidden(true);
	aInMatrixO = mAttr.create("inMatrix", "im", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(false);
	mAttr.setStorable(true);
	mAttr.setHidden(true);
	aOutMatrix = mAttr.create("outMatrix", "om", MFnMatrixAttribute::kDouble, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	mAttr.setKeyable(false);
	mAttr.setStorable(true);
	mAttr.setHidden(true);
	aAreaBulgeWeight = numFn.create("areaBulgeWeight", "abw", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(true);
	numFn.setStorable(true);
	aPerimeterBulgeWeight = numFn.create("perimeterBulgeWeight", "pbw", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(true);
	numFn.setStorable(true);

	aExtraBulge = numFn.create("extraBulge", "eb", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(true);
	numFn.setStorable(true);
	aBulgePower = numFn.create("bulgePower", "bp", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(true);
	numFn.setStorable(true);

	aBulgeScale = numFn.create("bulgeScale", "bs", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(true);
	numFn.setStorable(true);

	aAreaMinimumRatio = numFn.create("areaMinimumRatio", "amr", MFnNumericData::kDouble, 0.25, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(true);
	numFn.setStorable(true);

	aAreaCurrent = numFn.create("areaCurrent", "ac", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(false);
	numFn.setChannelBox(true);
	numFn.setStorable(true);

	aPerimeterCurrent = numFn.create("perimeterCurrent", "pc", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(false);
	numFn.setChannelBox(true);
	numFn.setStorable(true);

	aAreaDefault = numFn.create("areaDefault", "ad", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(false);
	numFn.setChannelBox(true);
	numFn.setStorable(true);

	aPerimeterDefault = numFn.create("perimeterDefault", "pd", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(false);
	numFn.setChannelBox(true);
	numFn.setStorable(true);

	aAreaValue = numFn.create("areaValue", "av", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(false);
	numFn.setChannelBox(true);
	numFn.setStorable(true);

	aPerimeterValue = numFn.create("perimeterValue", "pv", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(false);
	numFn.setChannelBox(true);
	numFn.setStorable(true);

	aBulgeValue = numFn.create("bulgeValue", "bv", MFnNumericData::kDouble, 1.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(false);
	numFn.setChannelBox(true);
	numFn.setStorable(true);

	aCorrectScaleX = numFn.create("correctScaleX", "csx", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(false);
	numFn.setChannelBox(true);
	numFn.setStorable(true);

	aCorrectScaleY = numFn.create("correctScaleY", "csy", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(false);
	numFn.setChannelBox(true);
	numFn.setStorable(true);

	aCorrectScaleZ = numFn.create("correctScaleZ", "csz", MFnNumericData::kDouble, 0.0, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	numFn.setKeyable(false);
	numFn.setChannelBox(true);
	numFn.setStorable(true);
	aCorrectScale = numFn.create("correctScale", "cs", aCorrectScaleX, aCorrectScaleY, aCorrectScaleZ, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	addAttribute(aInMatrixA);
	addAttribute(aInMatrixB);
	addAttribute(aInMatrixO);

	addAttribute(aAreaBulgeWeight);
	addAttribute(aPerimeterBulgeWeight);
	addAttribute(aExtraBulge);
	addAttribute(aBulgePower);
	addAttribute(aBulgeScale);
	addAttribute(aAreaMinimumRatio);
	addAttribute(aAreaCurrent);
	addAttribute(aPerimeterCurrent);
	addAttribute(aAreaDefault);
	addAttribute(aPerimeterDefault);
	addAttribute(aAreaValue);
	addAttribute(aPerimeterValue);
	addAttribute(aBulgeValue);
	addAttribute(aCorrectScale);
	addAttribute(aOutMatrix);

	attributeAffects(aInMatrixA, aOutMatrix);
	attributeAffects(aInMatrixB, aOutMatrix);
	attributeAffects(aInMatrixO, aOutMatrix);
	attributeAffects(aAreaDefault, aOutMatrix);
	attributeAffects(aPerimeterDefault, aOutMatrix);
	attributeAffects(aAreaBulgeWeight, aOutMatrix);
	attributeAffects(aPerimeterBulgeWeight, aOutMatrix);
	attributeAffects(aExtraBulge, aOutMatrix);
	attributeAffects(aBulgePower, aOutMatrix);
	attributeAffects(aBulgeScale, aOutMatrix);
	attributeAffects(aAreaMinimumRatio, aOutMatrix);
	attributeAffects(aCorrectScaleX, aOutMatrix);
	attributeAffects(aCorrectScaleY, aOutMatrix);
	attributeAffects(aCorrectScaleZ, aOutMatrix);

	return MS::kSuccess;
}