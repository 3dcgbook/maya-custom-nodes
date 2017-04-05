//
// Copyright (C) Shuhei Arai
// 
// File: saNodesNode.cpp
//
// Dependency Graph Node: saNodes
//
// Author: Maya Plug-in Wizard 2.0
//

#include "saClosestIntersectionOnNurbs.h"

#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MArrayDataHandle.h>

#include <maya/MGlobal.h>
#include <maya/MEulerRotation.h>
#include <maya/MQuaternion.h>
#include <maya/MVector.h>
#include <iostream>

MTypeId     saClosestIntersectionOnNurbs::id(0x00012);

saClosestIntersectionOnNurbs::saClosestIntersectionOnNurbs() {}
saClosestIntersectionOnNurbs::~saClosestIntersectionOnNurbs() {}

MStatus saClosestIntersectionOnNurbs::compute(const MPlug& plug, MDataBlock& data)
{
	

	data.setClean(plug);

	return MS::kSuccess;
}

void* saClosestIntersectionOnNurbs::creator(){
	return new saClosestIntersectionOnNurbs();
}

MStatus saClosestIntersectionOnNurbs::initialize()
{
	MStatus				stat;
	MFnNumericAttribute fnNumeric;
	MFnEnumAttribute fnEnum;
	MFnUnitAttribute fnUnit;
	MFnTypedAttribute fnType;


	return MS::kSuccess;

}

