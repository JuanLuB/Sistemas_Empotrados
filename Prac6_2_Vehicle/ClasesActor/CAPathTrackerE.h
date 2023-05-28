#ifndef F_CAPathTrackerE_h
#define F_CAPathTrackerE_h


//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl.h>

// Data Classes

#include <public/cdpath.h>

//******************************************************************************
// Required Software Interfaces

#include <capathtracker/required_swi.h>
//******************************************************************************
// Component Class   CAPathTracker

class CAPathTracker: public CEDROOMComponent {

public:

	//*********************** Component Signal Enum Type ***********************

	 enum EDROOMCAPathTrackerSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, STrackPath, SPathRequest, SConfigPathTracker, SStopTracking, SStartTracking, SConfigError, SConfigOK };

	//***************************** Component Memory ***************************

	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//CQueueHead

			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

			//TimingMemory

			CEDROOMTimerInfo TimerInf[3];
			TEDROOMBool TimerInfMarks[3];
			CEDROOMTimeOutMessage TimeOutMess[3];
			TEDROOMBool TimeOutMessMarks[3];

		public: 

			CEDROOMTimingMemory TimingMemory;

			public:



			// SetMemory
			void SetMemory(TEDROOMUInt32 numMessages_, CEDROOMMessage * MessagesMem_, TEDROOMBool * MessagesMemMarks_, CEDROOMQueue::CQueueNode * QueueNodesMem_, TEDROOMBool * QueueNodesMemMarks_);

	};


	//*****************************	Component Ports ****************************

	CEDROOMInterface	TrackPath;
	CEDROOMInterface	PathTrackerCtrl;


	// ****************************	Timing SAP *********************************

	CEDROOMTimingSAP	 EDROOMtimingSAP;


	// *****************************	Timing Interfaces **********************

	CEDROOMTimingInterface	Timer;




	// ******************************** Constructor ****************************

	CAPathTracker(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




	// *************************************************************************

	// **************************** Public Methods	****************************

	// *************************************************************************



	// **************************** Configuration ******************************

	 int EDROOMConfig();


	// ************************************* Start *****************************

	 int EDROOMStart();




	#ifdef _EDROOM_SYSTEM_CLOSE

	// ***************************** IsComponentFinished ***********************

	TEDROOMBool EDROOMIsComponentFinished();


	#endif

	// *************************************************************************

	// **************************** Protected Methods	************************

	// *************************************************************************

protected:



	// *********************************** Behaviour ***************************

	virtual void EDROOMBehaviour();




public:

	// *****************************	Behaviour File *************************

	#include <capathtracker/CAPathTrackerC.h>


protected:

	// ********************************  Top State  ****************************

	EDROOMTopState edroomTopState;



};
#endif
