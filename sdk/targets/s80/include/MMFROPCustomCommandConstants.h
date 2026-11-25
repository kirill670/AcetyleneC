#ifndef __MMFROPCUSTOMCOMMANDCONSTANTS_H
#define __MMFROPCUSTOMCOMMANDCONSTANTS_H


/**
 * @publishedAll
 *
 * Interface UID and messages for the ROP Controller API.
 */
const TUid KUidInterfaceMMFROPController = {0x101F855D};
/**
 *  Function constants
 */
enum TMMFROPControllerMessage
{
    EMMFROPControllerGetApplicationConfig,
    EMMFROPControllerSetApplicationConfig
};

/**
 *  Constants describing the config version to query
 */
enum TMMFROPControllerConfigVersion
{
    KMMFAudioVideoConfigDefault,   // Configuration created on installation
    KMMFAudioVideoConfigOperator,  // Configuration created on operator setup
    KMMFAudioVideoConfigUser       // Last Configuration saved by the application
};
    

#endif __MMFROPCUSTOMCOMMANDCONSTANTS_H
