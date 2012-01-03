/*!	\file MemoryBlockReferenceLocker.template.h
	\brief A refinement of MemoryBlockLocker that simply retains
	reference lock counts without doing anything special
	(compare this to, say, a Memory Block Handle Locker, which
	also makes additional Memory Manager calls).
*/
/*###############################################################

	Data Access Library 2.6
	© 1998-2012 by Kevin Grant
	
	This library is free software; you can redistribute it or
	modify it under the terms of the GNU Lesser Public License
	as published by the Free Software Foundation; either version
	2.1 of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be
	useful, but WITHOUT ANY WARRANTY; without even the implied
	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	PURPOSE.  See the GNU Lesser Public License for details.
	
	You should have received a copy of the GNU Lesser Public
	License along with this library; if not, write to:
	
		Free Software Foundation, Inc.
		59 Temple Place, Suite 330
		Boston, MA  02111-1307
		USA

###############################################################*/

#include <UniversalDefines.h>

#ifndef __MEMORYBLOCKREFERENCELOCKER__
#define __MEMORYBLOCKREFERENCELOCKER__

// Mac includes
#include <CoreServices/CoreServices.h>

// library includes
#include <MemoryBlockLocker.template.h>



#pragma mark Types

/*!
This class can be used to count locks on references.  You might
use this to provide a “secure delete” facility, where you don’t
delete some underlying data unless this class claims that no
reference locks exist - and, you provide users with a way to
acquire and release locks on your references, deferring most of
the implementation details to this template code.
*/
template < typename structure_reference_type, typename structure_type >
class MemoryBlockReferenceLocker:
public MemoryBlockLocker< structure_reference_type, structure_type >
{
public:
	//! increments the lock count by one; always returns nullptr because pointer return value has no meaning
	structure_type*
	acquireLock	(structure_reference_type	inReference);
	
	//! decrements the lock count by one
	void
	releaseLock	(structure_reference_type	inReference);

protected:
	//! decrements the lock count by one; unused 2nd parameter
	void
	releaseLock	(structure_reference_type	inReference,
				 structure_type**			inDummyPtr);

private:
};



#pragma mark Public Methods

template < typename structure_reference_type, typename structure_type >
structure_type*
MemoryBlockReferenceLocker< structure_reference_type, structure_type >::
acquireLock	(structure_reference_type	inReference)
{
	UInt16				newLockCount = 0;
#ifndef NDEBUG
	UInt16				oldLockCount = this->returnLockCount(inReference);
#endif
	
	
	newLockCount = this->incrementLockCount(inReference);
	assert(newLockCount > oldLockCount);
	return nullptr; // the return value has no meaning
}// acquireLock


template < typename structure_reference_type, typename structure_type >
void
MemoryBlockReferenceLocker< structure_reference_type, structure_type >::
releaseLock	(structure_reference_type	inReference)
{
	structure_type*		dummyPtr = nullptr;
	
	
	// use the dummy-parameter version as a “worker function”
	releaseLock(inReference, &dummyPtr);
}// releaseLock


template < typename structure_reference_type, typename structure_type >
void
MemoryBlockReferenceLocker< structure_reference_type, structure_type >::
releaseLock	(structure_reference_type	inReference,
			 structure_type**			UNUSED_ARGUMENT(inNull))
{
	UInt16	newLockCount = 0;
#ifndef NDEBUG
	UInt16	oldLockCount = this->returnLockCount(inReference);
#endif
	
	
	assert(oldLockCount > 0);
	newLockCount = this->decrementLockCount(inReference);
	assert(newLockCount < oldLockCount);
}// releaseLock

#endif

// BELOW IS REQUIRED NEWLINE TO END FILE
