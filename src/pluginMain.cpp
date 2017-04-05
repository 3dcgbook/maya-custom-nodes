#include "saRotToBendTwist.h"
#include "saMultRot.h"
#include "saShearModule.h"
#include "saClosestIntersectionOnMesh.h"
#include "saQuaternionTransform.h"
#include "saIntersectOnSurface.h"
#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )
{ 
	MStatus   status;
	MFnPlugin plugin( obj, "Shuhei Arai", "2015", "Any");

	status = plugin.registerNode("saRotToBendTwist", saRotToBendTwist::id, saRotToBendTwist::creator,saRotToBendTwist::initialize);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.registerNode("saMultRot", saMultRot::id, saMultRot::creator,saMultRot::initialize);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.registerNode("saShearModule", saShearModule::id, saShearModule::creator,saShearModule::initialize);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	
	status = plugin.registerNode("saClosestIntersectionOnMesh", saClosestIntersectionOnMesh::id, saClosestIntersectionOnMesh::creator,saClosestIntersectionOnMesh::initialize);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.registerNode("saQuaternionTransform", saQuaternionTransform::id, saQuaternionTransform::creator,saQuaternionTransform::initialize);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.registerNode("saIntersectOnSurface", saIntersectOnSurface::id, saIntersectOnSurface::creator, saIntersectOnSurface::initialize);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	return status;
}

MStatus uninitializePlugin( MObject obj)
{
	MStatus   status;
	MFnPlugin plugin( obj );

	status = plugin.deregisterNode(saRotToBendTwist::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(saMultRot::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(saShearModule::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	
	status = plugin.deregisterNode(saClosestIntersectionOnMesh::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(saQuaternionTransform::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = plugin.deregisterNode(saIntersectOnSurface::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	return status;
}
