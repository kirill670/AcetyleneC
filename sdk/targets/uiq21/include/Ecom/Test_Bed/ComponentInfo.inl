// ComponentInfo.inl
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

//##ModelId=3A70658B030B
inline const TEntry& CComponentInfo::Entry() const
	{
	return *iComponentEntry;
	}

//##ModelId=3A70658B030A
inline const RPointerArray<CUnitTestInfo>& CComponentInfo::UnitTestsInfo() const
	{
	return *iUnitTestsInfo;
	}
