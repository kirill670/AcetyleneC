#ifndef CPLUGINADAPTERUTIL_H
#define CPLUGINADAPTERUTIL_H
#include "PluginAdapterInterface.h"

typedef MPluginAdapter *MPluginAdapterPTR;
typedef CCoeControl *CCoeControlPTR;


class CPluginAdapterUtil {
public:
IMPORT_C static void ExtractParentControlAndApiL(const NPWindow* window, //IN
			   					       MPluginAdapterPTR &aPluginAdapter, //out
									   CCoeControlPTR &aCoeControl //out
								  );
};

/////////////////////////////
//use use use use use use use

//NPError NPP_SetWindow(NPP instance, NPWindow* window) {
//	CPluginAdapterUtil::ExtractParentControlAndApiL(window,iAdaptor,iParentControl);
//	etc...
//
#endif
