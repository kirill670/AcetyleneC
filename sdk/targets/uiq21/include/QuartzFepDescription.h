// QuartzFepDescription.h
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __QUARTZFEPDESCRIPTION_H__
#define __QUARTZFEPDESCRIPTION_H__

// global includes
#include <E32STD.H>

// some constants
const TInt KQuartzFepNameMaxLength = 30;

/**
 * This class gives a more detailed description about a Fep, with a more
 * userfriendly Name (that's better then the FileName), and a description
 * what kind of Fep it is.
 *
 * @short This class gives a more detailed description about a Fep.
 * 
 * @since Quartz 6.0
 */
class TQuartzFepDescription
	{
public:
	enum TFepType
		{
		EFepTypeUnspecified		= 0,
		EFepTypeWriteAnywhere	= 1,
		EFepTypeFloatingInABox	= 2
		};

public:
	TQuartzFepDescription() : iFepName(KNullDesC), iFepType(EFepTypeUnspecified) {};

public:
	TBuf<KQuartzFepNameMaxLength> iFepName;
	TInt iFepType;
	};

// Definition of a pointer to a function
typedef void (*TQuartzFepDescriptionFunctionL)(TQuartzFepDescription& aQuartzFepDescription);

#endif	// __QUARTZFEPDESCRIPTION_H__