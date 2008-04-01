/*!	\file VectorInterpreter.h
	\brief Takes Tektronix codes as input, and sends the output
	to real graphics devices.
	
	Developed by Aaron Contorer, with bug fixes by Tim Krauskopf.
	TEK 4105 additions by Dave Whittington.
*/
/*###############################################################

	MacTelnet
		� 1998-2008 by Kevin Grant.
		� 2001-2003 by Ian Anderson.
		� 1986-1994 University of Illinois Board of Trustees
		(see About box for full list of U of I contributors).
	
	This program is free software; you can redistribute it or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version
	2 of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be
	useful, but WITHOUT ANY WARRANTY; without even the implied
	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	PURPOSE.  See the GNU General Public License for more
	details.
	
	You should have received a copy of the GNU General Public
	License along with this program; if not, write to:
	
		Free Software Foundation, Inc.
		59 Temple Place, Suite 330
		Boston, MA  02111-1307
		USA

###############################################################*/

#include "UniversalDefines.h"

#ifndef __VECTORINTERPRETER__
#define __VECTORINTERPRETER__

// Mac includes
#include <CoreServices/CoreServices.h>



#pragma mark Constants

typedef SInt16 VectorInterpreter_ID;
enum
{
	kVectorInterpreter_InvalidID				= -1
};

/*!
The command set, which determines how input data streams
are interpreted.
*/
enum VectorInterpreter_Mode
{
	kVectorInterpreter_ModeDisabled		= 'None',	//!< TEK 4014 command set
	kVectorInterpreter_ModeTEK4014		= '4014',	//!< TEK 4014 command set
	kVectorInterpreter_ModeTEK4105		= '4105'	//!< TEK 4105 command set
};

/*!
An interpreter can apply vector graphics to more than one
type of output format.  Currently, it is possible to target
a window or a bitmap.
*/
typedef SInt16 VectorInterpreter_Target;
enum
{
	kVectorInterpreter_TargetScreenPixels		= 0,
	kVectorInterpreter_TargetQuickDrawPicture	= 1
};



#pragma mark Public Methods

//!\name Initialization
//@{

void
	VectorInterpreter_Init				();

//@}

//!\name Creating and Destroying Graphics
//@{

VectorInterpreter_ID
	VectorInterpreter_New				(VectorInterpreter_Target	inTarget,
										 VectorInterpreter_Mode		inCommandSet);

void
	VectorInterpreter_Dispose			(VectorInterpreter_ID*		inoutGraphicIDPtr);

//@}

//!\name Manipulating Graphics
//@{

void
	VectorInterpreter_CopyZoom			(VectorInterpreter_ID		inDestinationGraphicID,
										 VectorInterpreter_ID		inSourceGraphicID);

void
	VectorInterpreter_PageCommand		(VectorInterpreter_ID		inGraphicID);

SInt16
	VectorInterpreter_PiecewiseRedraw	(VectorInterpreter_ID		inGraphicID,
										 VectorInterpreter_ID		inDestinationGraphicID);

size_t
	VectorInterpreter_ProcessData		(VectorInterpreter_ID		inGraphicID,
										 UInt8 const*				inDataPtr,
										 size_t						inDataSize);

void
	VectorInterpreter_Redraw			(VectorInterpreter_ID		inGraphicID,
										 VectorInterpreter_ID		inDestinationGraphicID);

void
	VectorInterpreter_SetPageClears		(VectorInterpreter_ID		inGraphicID,
										 Boolean					inTrueClearsFalseNewWindow);

void
	VectorInterpreter_StopRedraw		(VectorInterpreter_ID		inGraphicID);

void
	VectorInterpreter_Zoom				(VectorInterpreter_ID		inGraphicID,
										 SInt16						inX0,
										 SInt16						inY0,
										 SInt16						inX1,
										 SInt16						inY1);

//@}

void VGgindata(VectorInterpreter_ID vw, unsigned short x, unsigned short y, char c, char *a);

//!\name Miscellaneous
//@{

VectorInterpreter_Mode
	VectorInterpreter_ReturnMode		(VectorInterpreter_ID		inGraphicID);

//@}

#endif

// BELOW IS REQUIRED NEWLINE TO END FILE