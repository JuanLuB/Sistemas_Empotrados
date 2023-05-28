#ifndef F_VehicleE_h
#define F_VehicleE_h


//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl.h>

// Data Classes

#include <public/cdlocation.h>

//******************************************************************************
// Required Software Interfaces

#include <vehicle/required_swi.h>
//******************************************************************************
// Component Class   Vehicle

class Vehicle: public CEDROOMComponent {

public:

	//*********************** Component Signal Enum Type ***********************

	 enum EDROOMVehicleSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, SConfigPathPlanner, SMarkObstacle, SNewTargetLocation, SStartPlanning, SConfigOK, SConfigError, SConfigPathTracker, SStopTracking, SStartTracking, SConfigAO, SStart, SObstacleDetected };

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

			//Pools

			public:

			CDLocation	poolCDLocation[10];
			TEDROOMBool	poolMarkCDLocation[10];


			// SetMemory
			void SetMemory(TEDROOMUInt32 numMessages_, CEDROOMMessage * MessagesMem_, TEDROOMBool * MessagesMemMarks_, CEDROOMQueue::CQueueNode * QueueNodesMem_, TEDROOMBool * QueueNodesMemMarks_);

	};


	//*****************************	Component Ports ****************************

	CEDROOMInterface	PathPlannerCtrl;
	CEDROOMInterface	PathTrackerCtrl;
	CEDROOMInterface	AvoidObstaclesSysCtrl;


	// ****************************	Timing SAP *********************************

	CEDROOMTimingSAP	 EDROOMtimingSAP;


	// *****************************	Timing Interfaces **********************

	CEDROOMTimingInterface	Timer;




	// ******************************** Constructor ****************************

	Vehicle(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




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

	#include <vehicle/VehicleC.h>


protected:

	// ********************************  Top State  ****************************

	EDROOMTopState edroomTopState;



};
#endif
