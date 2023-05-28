#ifndef VEHICLE_H_
#define VEHICLE_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Data Classes

#include <public/cdlocation_iface_v1.h>


//******************************************************************************
// Required software interfaces

#include <public/sensors_iface_v1.h>
#include <public/io_ctrl_iface_v1.h>


/**
 * \class   Vehicle
 *
 */
class Vehicle: public CEDROOMComponent {

public:

	/**
	 * \enum TEDROOMVehicleSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum TEDROOMVehicleSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SConfigAO, 
							SStart, 
							SObstacleDetected, 
							SConfigError, 
							SConfigOK, 
							SConfigPathPlanner, 
							SMarkObstacle, 
							SNewTargetLocation, 
							SStartPlanning, 
							SConfigPathTracker, 
							SStopTracking, 
							SStartTracking };

	/**
	 * \class Vehicle::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

			//************ Component Timing Service Memory************

			//!Component Timing Service Timer Info Memory
			CEDROOMTimerInfo TimerInf[3];
			//!Component Timing Service Timer Info Marks Memory
			bool TimerInfMarks[3];
			//!Component Timing Service TimeOut Messages Memory
			CEDROOMTimeOutMessage TimeOutMsgs[3];
			//!Component Timing Service TimeOut Messages Marks Memory
			bool TimeOutMsgsMarks[3];

		public: 

			//!Component Timing Service Memory Object
			CEDROOMTimingMemory TimingMemory;

	// ********************************************************************
	// ******************* Component Message Data Pools *******************
	// ********************************************************************

			//! CDLocation Data Pool Memory
			CDLocation	poolCDLocation[10+1];
			//! CDLocation Data Pool Marks Memory
			bool	poolMarkCDLocation[10];


			/** \brief This function is used for setting the Component Memory
			 * 
			 * \param numberOfMsgs number of messages that the component can store
			 * \param msgsMemory memory for the messages that the component can store
			 * \param msgsMemoryMarks memory marks for the messages that the component can store
			 * \param numberOfNodes number of nodes that the component needs
			 * \param queueNodesMemory memory for the component message queues 
			 * \param queueNodesMemoryMarks memory marks for the component message queues 
			 */
			void SetMemory(TEDROOMUInt32 numberOfMsgs
						, CEDROOMMessage * msgsMemory
						, bool * msgsMemoryMarks
						, TEDROOMUInt32 numberOfNodes
						, CEDROOMQueue::CQueueNode * queueNodesMemory
						, bool * queueNodesMemoryMarks);

	};


	// ********************************************************************
	//******************  Component Communication Ports *******************
	// ********************************************************************

	//! AvoidObstaclesSysCtrl Component Port
	CEDROOMInterface	AvoidObstaclesSysCtrl;
	//! PathPlannerCtrl Component Port
	CEDROOMInterface	PathPlannerCtrl;
	//! PathTrackerCtrl Component Port
	CEDROOMInterface	PathTrackerCtrl;


	// ********************************************************************
	// ********************  Timing Service Interface *********************
	// ********************************************************************

	//! Timing Service Access Point. It is common to all timing ports.
	CEDROOMTimingSAP	 EDROOMtimingSAP;


	//! Timer Timing Port
	CEDROOMTimingInterface	Timer;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	Vehicle(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, 
		TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




	//! Component Configuration 
	 int EDROOMConfig();


	//! Component Start 
	 int EDROOMStart();




	#ifdef _EDROOM_SYSTEM_CLOSE

	//! Method that returns true if component is finished 
	bool EDROOMIsComponentFinished();


	#endif

protected:



	//! Component behaviour 
	virtual void EDROOMBehaviour();




public:

	// *****************************	Behaviour  *************************

	// ***********************************************************************

	// class EDROOM_CTX_Top_0

	// ***********************************************************************



	class EDROOM_CTX_Top_0 {

	protected:

	/**
	 * \enum TEDROOMVehicleSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	enum TEDROOMVehicleSignal { EDROOMSignalTimeout,
		EDROOMSignalDestroy,
		SConfigAO,
		SStart,
		SObstacleDetected,
		SConfigError,
		SConfigOK,
		SConfigPathPlanner,
		SMarkObstacle,
		SNewTargetLocation,
		SStartPlanning,
		SConfigPathTracker,
		SStopTracking,
		SStartTracking };


		friend class Vehicle;

		//!component reference
		Vehicle &EDROOMcomponent;

		//!Current message pointer reference
		CEDROOMMessage * &Msg;

		//!Synchronous message back pointer reference
		CEDROOMMessage * &MsgBack;

		//!Component ports
		CEDROOMInterface & AvoidObstaclesSysCtrl;
		CEDROOMInterface & PathPlannerCtrl;
		CEDROOMInterface & PathTrackerCtrl;
		CEDROOMTimingInterface & Timer;


		//! State Identifiers
		enum TEDROOMStateID{I,
			StartUp,
			VehicleReady,
			SysRecovery,
			AvObstaclesConfigured,
			PathTrackerConfigured};

		//!Transition Identifiers
		enum TEDROOMTransitionID{Init,
			ConfigAvObstacles,
			ConfigAvObstacles_Error,
			ConfigAvObstacles_OK,
			ReStart,
			ConfigPathTracker,
			ConfigPathTracker_Error,
			ConfigPathTracker_OK,
			ConfigPathPlanner,
			ConfigPathPlanner_Error,
			ConfigPathPlanner_OK,
			ObstacleDetected,
			EDROOMMemoryTrans };



		//!Variables
		CDLocation &VTargetLocation;


		// Pools *************************************************

		class CEDROOMPOOLCDLocation:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLCDLocation(TEDROOMUInt32 elemCount,CDLocation *pMem, bool *pMarks);
			CDLocation	* AllocData();
		};
		CEDROOMPOOLCDLocation	& EDROOMPoolCDLocation;


		//!Constructor
		EDROOM_CTX_Top_0 (Vehicle &act,
				CDLocation & EDROOMpVarVTargetLocation,
				CEDROOMPOOLCDLocation & EDROOMpPoolCDLocation );

		//!Copy constructor
		EDROOM_CTX_Top_0 (EDROOM_CTX_Top_0 &context);

	public:

		/**
		 * \brief Search Context transition 
		 * \param edroomCurrentTrans returns the context transition 

		 * \return true if context transition is found 

		 */
		bool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

		//! \brief Get new message from the Queue

		void EDROOMNewMessage()
		{ EDROOMcomponent.EDROOMNewMsg(); }

		/**
		 * \brief Get and Clear the Error Flags 
		 * \return the error flags  

		 */
		 TEDROOMUInt32 GetAndClearErrorFlags(){ return EDROOMcomponent.GetAndClearErrorFlags();}

		// User-defined Functions

		void	FAvObstaclesError();

		/**
		 * \brief  
		 */
		void	FInit();

		/**
		 * \brief  
		 */
		void	FInvokeConfigAvObstacles();

		/**
		 * \brief  
		 */
		void	FInvokeConfigPathPlanner();

		/**
		 * \brief  
		 */
		void	FInvokeConfigPathTracker();

		/**
		 * \brief  
		 */
		void	FMarkObstacle();

		void	FPathPlannerError();

		void	FPathTrackerError();

		/**
		 * \brief  
		 */
		void	FProgRecovery();

		/**
		 * \brief  
		 */
		void	FProgTimerConfig();

		/**
		 * \brief  
		 */
		void	FStartAvoidObs();

		/**
		 * \brief  
		 */
		void	FStartPlanning();

		/**
		 * \brief  
		 */
		void	FStartTracking();

		void	FStartUp();

		/**
		 * \brief  
		 */
		void	FStopTracking();

		/**
		 * \brief  
		 */
		bool	GConfigError();

	};

	// ***********************************************************************

	// class EDROOM_SUB_Top_0

	// ***********************************************************************



	class EDROOM_SUB_Top_0 : public EDROOM_CTX_Top_0 {

	protected:



		//!current state identifier
		EDROOM_CTX_Top_0::TEDROOMStateID edroomCurrentState;

		//!next state identifier
		EDROOM_CTX_Top_0::TEDROOMStateID edroomNextState;

		//!Variables
		CDLocation VTargetLocation;


		// Pools**************************************************
		CEDROOMPOOLCDLocation	EDROOMPoolCDLocation;


	public:

		//! Constructor
		EDROOM_SUB_Top_0 (Vehicle &act, CEDROOMMemory *pEDROOMMemory  );


		//! Top Context Behaviour 

		void EDROOMBehaviour();

		//!Top Context Init
		void EDROOMInit();

		//! Initial substate arrival
		TEDROOMTransId EDROOMIArrival();

		// ***********************************************************************

		// Leaf SubState StartUp

		// ***********************************************************************



		TEDROOMTransId EDROOMStartUpArrival();

		// ***********************************************************************

		// Leaf SubState VehicleReady

		// ***********************************************************************



		TEDROOMTransId EDROOMVehicleReadyArrival();

		// ***********************************************************************

		// Leaf SubState SysRecovery

		// ***********************************************************************



		TEDROOMTransId EDROOMSysRecoveryArrival();

		// ***********************************************************************

		// Leaf SubState AvObstaclesConfigured

		// ***********************************************************************



		TEDROOMTransId EDROOMAvObstaclesConfiguredArrival();

		// ***********************************************************************

		// Leaf SubState PathTrackerConfigured

		// ***********************************************************************



		TEDROOMTransId EDROOMPathTrackerConfiguredArrival();

	};

protected:

	//!Top State
	EDROOM_SUB_Top_0 edroomTopState;



};
#endif
