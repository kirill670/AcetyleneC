// DevASRCommon.h
//
// Copyright © 2002 Nokia Corporation. All rights reserved
//

#ifndef __DEVASRCOMMON_H__
#define __DEVASRCOMMON_H__

// TYPEDEFS
typedef TInt TDevASRError;

// CONSTANTS

// Pre-defined Engine Parameter Identifiers starts from index 0x01
// User-define Engine Parameter Identifiers starts from index 0x10000 and end at index KMaxTInt.

const TInt KRejectionThreshold=0x01;

// DATA TYPES

/**
 * @publishedAll
 * DevASR Event codes
 */

enum TDevASREvent
	{
	/** End of utterance event **/
	EDevASREouDetected = 1,
	/** Front end intialisation complete */
	EDevASRInitFrontend,
	/** Back end intialisation complete */
	EDevASRInitRecognitionBackend,
	/** Training back end intialisation complete */
	EDevASRInitTrainBackend,
	/** Load grammar complete */
	EDevASRLoadGrammar,
	/** Load lexicon complete */
	EDevASRLoadLexicon,
	/** Load models complete */
	EDevASRLoadModels,
	/** Rule unloaded from grammar */
	EDevASRUnloadRule,
	/** Playback complete event */
	EDevASRPlay,
	/** Playback started event */
	EDevASRPlayStarted,
	/** Recognition complete event */
	EDevASRRecognize,
	/** Record complete event */
	EDevASRRecord,
	/** Record started event */
	EDevASRRecordStarted,
	/** Training completed event */
	EDevASRTrain
	};


/**
 * @publishedAll
 * Mode used to initialize the recognizer
 */

enum TRecognizerMode
	{
	/** Speaker independent recognition mode */
	ESiRecognition,
	/** Speaker dependent recognition mode */
	ESdRecognition,
	/** Speaker dependent training mode */
	ESdTraining,
	/** Speaker independent recognition test mode */
	ESiRecognitionTest,
	/** Speaker dependent recognition test mode */
	ESdRecognitionTest,
	/** Speaker dependent training test mode */
	ESdTrainingTest,
	/** Speaker independent adaptation mode */
	ESiAdaptation
	};

#endif // __DEVASRCOMMON_H__
