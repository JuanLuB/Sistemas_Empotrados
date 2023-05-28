#ifndef CAPATHPLANNER_H_
#define CAPATHPLANNER_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Data Classes

#include <public/cdlocation_iface_v1.h>
#include <public/cdpath_iface_v1.h>


//******************************************************************************
// Required software interfaces

#include <public/sensors_iface_v1.h>
#include <public/actuators_iface_v1.h>
#include <public/planner_iface_v1.h>
#include <public/io_ctrl_iface_v1.h>


/**
 * \class   CAPathPlanner
 *
 */
class CAPathPlanner: public CEDROOMComponent {

public:

	/**
	 * \enum TEDROOMCAPathPlannerSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum TEDROOMCAPathPlannerSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							STrackPath, 
							SPathRequest, 
							SConfigPathPlanner, 
							SMarkObstacle, 
							SNewTargetLocation, 
							SStartPlanning, 
							SConfigError, 
							SConfigOK };

	/**
	 * \class CAPathPlanner::CEDROOMMemory
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

			//! CDPath Data Pool Memory
			CDPath	poolCDPath[3+1];
			//! CDPath Data Pool Marks Memory
			bool	poolMarkCDPath[3];


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

	//! TrackPath Component Port
	CEDROOMInterface	TrackPath;
	//! PathPlannerCtrl Component Port
	CEDROOMInterface	PathPlannerCtrl;


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
	CAPathPlanner(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, 
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
	 * \enum TEDROOMCAPathPlannerSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	enum TEDROOMCAPathPlannerSignal { EDROOMSignalTimeout,
		EDROOMSignalDestroy,
		STrackPath,
		SPathRequest,
		SConfigPathPlanner,
		SMarkObstacle,
		SNewTargetLocation,
		SStartPlanning,
		SConfigError,
		SConfigOK };


		friend class CAPathPlanner;

		//!component reference
		CAPathPlanner &EDROOMcomponent;

		//!Current message pointer reference
		CEDROOMMessage * &Msg;

		//!Synchronous message back pointer reference
		CEDROOMMessage * &MsgBack;

		//!Component ports
		CEDROOMInterface & TrackPath;
		CEDROOMInterface & PathPlannerCtrl;
		CEDROOMTimingInterface & Timer;


		//! State Identifiers
		enum TEDROOMStateID{I,
			Idle,
			CalculatePath,
			CalNextPath};

		//!Transition Identifiers
		enum TEDROOMTransitionID{Init,
			Config,
			Config_Error,
			Config_OK,
			CalStep,
			CalStep_SendMinPath,
			CalStep_MaxStep,
			CalStep_NextStep,
			Start,
			NewTar,
			PatRequest,
			ObsTDetected,
			EDROOMMemoryTrans };

		//!Constants
		const TEDROOMUInt8 VMaxPathSteps;
		const TEDROOMUInt8 VMinPathSteps;


		//!Variables
		CDPath &VNextPath;
		CDLocation &VNextStepStartPoing;
		TEDROOMUInt8 &VSimError;
		CDLocation &VTargetLocation;
		TEDROOMBool &VVehicleHalted;


		// Pools *************************************************

		class CEDROOMPOOLCDPath:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLCDPath(TEDROOMUInt32 elemCount,CDPath *pMem, bool *pMarks);
			CDPath	* AllocData();
		};
		CEDROOMPOOLCDPath	& EDROOMPoolCDPath;


		//!Constructor
		EDROOM_CTX_Top_0 (CAPathPlanner &act,
				CDPath & EDROOMpVarVNextPath,
				CDLocation & EDROOMpVarVNextStepStartPoing,
				TEDROOMUInt8 & EDROOMpVarVSimError,
				CDLocation & EDROOMpVarVTargetLocation,
				TEDROOMBool & EDROOMpVarVVehicleHalted,
				CEDROOMPOOLCDPath & EDROOMpPoolCDPath );

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

		void	FCalPathStep();

		void	FConfigPlanner();

		/**
		 * \brief  
		 */
		void	FMarkObstacle();

		void	FMaxSteps();

		/**
		 * \brief  
		 */
		void	FNewTarget();

		/**
		 * \brief  
		 */
		void	FProgNextStep();

		void	FReplanning();

		/**
		 * \brief  
		 */
		void	FReplyConfigOK();

		/**
		 * \brief  
		 */
		void	FReplySimError();

		/**
		 * \brief  
		 */
		void	FSendNextPath();

		bool	GMaxSteps();

		bool	GSendMinPath();

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
		CDPath VNextPath;
		CDLocation VNextStepStartPoing;
		TEDROOMUInt8 VSimError;
		CDLocation VTargetLocation;
		TEDROOMBool VVehicleHalted;


		// Pools**************************************************
		CEDROOMPOOLCDPath	EDROOMPoolCDPath;


	public:

		//! Constructor
		EDROOM_SUB_Top_0 (CAPathPlanner &act, CEDROOMMemory *pEDROOMMemory  );


		//! Top Context Behaviour 

		void EDROOMBehaviour();

		//!Top Context Init
		void EDROOMInit();

		//! Initial substate arrival
		TEDROOMTransId EDROOMIArrival();

		// ***********************************************************************

		// Leaf SubState Idle

		// ***********************************************************************



		TEDROOMTransId EDROOMIdleArrival();

		// ***********************************************************************

		// Leaf SubState CalculatePath

		// ***********************************************************************



		TEDROOMTransId EDROOMCalculatePathArrival();

		// ***********************************************************************

		// Leaf SubState CalNextPath

		// ***********************************************************************



		TEDROOMTransId EDROOMCalNextPathArrival();

	};

protected:

	//!Top State
	EDROOM_SUB_Top_0 edroomTopState;



};
#endif
