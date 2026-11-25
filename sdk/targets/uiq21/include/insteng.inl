// INSTENG.INL
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//
// Installer engine inline methods
//

inline TBool CInstallEngine::IsRecursive() const { return iParentInstUninstaller!=NULL; }
inline CInstUninstHandler* CInstallEngine::ParentInstUninstaller() { return iParentInstUninstaller; }
inline void CInstallEngine::SetInstallInProgress(TBool aProgress) { iInstallInProgress = aProgress; }

inline const CInstallEngine* CInstallEngine::TopLevelEngine() const
	{
	// Cast to call non-const version
	return CONST_CAST(CInstallEngine*, this)->TopLevelEngine();
	}
