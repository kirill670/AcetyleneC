// CBNFNODE.H
// Copyright (C) Symbian LTD, 1999
//
// BNF node header
//

#ifndef __CBNFNODE_H__
#define __CBNFNODE_H__

#include <e32base.h>
#include "CNode.h" 


typedef const TDesC* CBNFNodeAttributeType;

#define _SHAREDSTRING(X) IMPORT_C static CBNFNodeAttributeType K##X();
#define _SHAREDSTRINGBODY(X) EXPORT_C CBNFNodeAttributeType CBNFNode::K##X() \
    { \
    _LIT(K##X, #X); \
    return &(K##X); \
    }

// CBNFNode
//
//##ModelId=3B666BC70111
class CBNFNode : public CTypedNode<TInt, const TDesC*> 
{
public:
	//##ModelId=3B666BC70146
	IMPORT_C ~CBNFNode();

	//##ModelId=3B666BC70144
	IMPORT_C static CBNFNode* NewL(TInt aType);

    _SHAREDSTRING(PreRuleCallback)
    _SHAREDSTRING(PostRuleCallback)
    _SHAREDSTRING(Reference)
    _SHAREDSTRING(RangeStart)
    _SHAREDSTRING(RangeEnd)
    _SHAREDSTRING(NMoreCount)
    _SHAREDSTRING(NMoreMinimum)
    _SHAREDSTRING(NMoreMaximum)

protected:
    IMPORT_C CBNFNode(TInt aType);
};

#endif // __CBNFNODE_H__
