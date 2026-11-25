// $Workfile: MmsUtilsHeaderParameter.inl $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 1 $
// $Date: 18/12/01 12:20 $
//

/** @file 
 * This file contains inline function definitions for the CMmsUtilsHeaderParameter class.
 */


#ifndef __MMSUTILSHEADERPARAMETER_H__
#define __MMSUTILSHEADERPARAMETER_H__


inline TPtrC CMmsUtilsHeaderParameter::Name() const
    {
    return TPtrC(*iName);
    }


inline TMmsParameterValueType CMmsUtilsHeaderParameter::ValueType() const
    {
    return iType;
    }


#endif // __MMSUTILSHEADERPARAMETER_H__
