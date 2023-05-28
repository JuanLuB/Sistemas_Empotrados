#ifndef CCAVOIDOBSTACLES_H_
#define CCAVOIDOBSTACLES_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Required software interfaces

#include <public/sensors_iface_v1.h>
#include <public/io_ctrl_iface_v1.h>
#include <public/actuators_iface_v1.h>


/**
 * \class   CCAvoidObstacles
 *
 */
class CCAvoidObstacles: public CEDROOMComponent {

public:

	/**
	 * \enum TEDROOMCCAvoidObstaclesSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum TEDROOMCCAvoidObstaclesSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SConfigAO, 
							SStart, 
							SObstacleDetected, 
							SConfigError, 
							SConfigOK };

	/**
	 * \class CCAvoidObstacles::CEDROOMMemory
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
	CCAvoidObstacles(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, 
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
	 * \enum TEDROOMCCAvoidObstaclesSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	enum TEDROOMCCAvoidObstaclesSignal { EDROOMSignalTimeout,
		EDROOMSignalDestroy,
		SConfigAO,
		SStart,
		SObstacleDetected,
		SConfigError,
		SConfigOK };


		friend class CCAvoidObstacles;

		//!component reference
		CCAvoidObstacles &EDROOMcomponent;

		//!Current message pointer reference
		CEDROOMMessage * &Msg;

		//!Synchronous message back pointer reference
		CEDROOMMessage * &MsgBack;

		//!Component ports
		CEDROOMInterface & AvoidObstaclesSysCtrl;
		CEDROOMTimingInterface & Timer;


		//! State Identifiers
		enum TEDROOMStateID{I,
			Idle,
			Ready};

		//!Transition Identifiers
		enum TEDROOMTransitionID{Init,
			Config,
			Start,
			CheckObstacles,
			CheckObstacles_ObstDetected,
			CheckObstacles_NoObstacle,
			EDROOMMemoryTrans };



		//!Variables
		TEDROOMBool &VObsDetected;




		//!Constructor
		EDROOM_CTX_Top_0 (CCAvoidObstacles &act,
				TEDROOMBool & EDROOMpVarVObsDetected );

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

		/**
		 * \brief  
		 */
		void	FCheckObstacles();

		/**
		 * \brief  
		 */
		void	FConfigOK();

		/**
		 * \brief  
		 */
		void	FHandleObstacle();

		/**
		 * \brief  
		 */
		void	FProgNExtDetection();

		/**
		 * \brief  
		 */
		bool	GObsDetected();

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
		TEDROOMBool VObsDetected;




	public:

		//! Constructor
		EDROOM_SUB_Top_0 (CCAvoidObstacles &act );


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

		// Leaf SubState Ready

		// ***********************************************************************



		TEDROOMTransId EDROOMReadyArrival();

	};

protected:

	//!Top State
	EDROOM_SUB_Top_0 edroomTopState;



};
#endif
