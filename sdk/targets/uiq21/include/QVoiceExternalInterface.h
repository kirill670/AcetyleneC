// QVoiceExternalInterface.h
// Copyright (C) Symbian Ltd 2000 All rights reserved.
//
// 

#ifndef __QVOICEEXTERNALINTERFACE_H__
#define __QVOICEEXTERNALINTERFACE_H__

/**
* The Voice Note application's UID
*/
const TUid KVoiceUid = { 0x100051FB };

/**
* The Voice Note view's UID
*/
const TUid KVoiceNoteViewUid = {0x1000a8f9};

/**
* This DNL UID will create a new note and start recording.
*/
const TUid KVoiceInteraction={0x10005FD3};


/**
* When KVoiceNoteStartRecord is used as a message, this is the correct 
* class to use.
*/
class TVoiceNoteRecord
{
public:
enum TVoiceCommand
	{
	EStartApp = 1,
	EStartRecording,
	EStopRecording
	};
	TVoiceCommand iCommand;
};

/**
* To be able to send the TVoiceNoteRecord to the ViewActivatedL method, it
* needs to be put into a package buffer. This is the buffer that should be
* used for this purpose.
*/
typedef TPckgBuf<TVoiceNoteRecord> TVoiceNoteRecordBuf;

#endif //__QVOICEEXTERNALINTERFACE_H__

