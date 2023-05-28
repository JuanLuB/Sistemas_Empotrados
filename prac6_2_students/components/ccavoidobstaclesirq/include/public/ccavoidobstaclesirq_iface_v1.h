#ifndef CCAVOIDOBSTACLESIRQ_H_
#define CCAVOIDOBSTACLESIRQ_H_

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
 * \class   CCAvoidObstaclesIRQ
 *
 */
class CCAvoidObstaclesIRQ: public CEDROOMComponent {

public:

	/**
	 * \enum TEDROOMCCAvoidObstaclesIRQSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum TEDROOMCCAvoidObstaclesIRQSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							EDROOMIRQsignal, 
							SConfigAO, 
							SStart, 
							SObstacleDetected, 
							SConfigError, 
							SConfigOK };

	/**
	 * \class CCAvoidObstaclesIRQ::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

		public:



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
	// ************************* Component IRQ Handling *******************
	// ********************************************************************

	// ********************************
	// Handling IRQ vector 18

	//! Event for trigger the bottom half associated to the IRQ vector 18
	static Pr_IRQEvent	EDROOMEventIRQ18;
	//! Binary Semaphore for signal the end of the bottom half of the IRQ vector 18
	static Pr_SemaphoreBin	EDROOMSemEndIRQ18;
	//! IRQ Handler for the IRQ vector 18
	static Pr_IRQHandler_RetType	EDROOMIRQ18Handler(void);
	//! Top Half Function for IRQ Handler  18
	static void	EDROOMIRQ18HandlerTopHalfFunction(void);
	//! Idle IRQ Handler for the IRQ vector 18
	static Pr_IRQHandler_RetType	EDROOMIRQ18IdleHandler(void);
	//! Bottom Half Task Function for the IRQ vector 18
	static Pr_TaskRV_t 	EDROOMIRQ18BottomHalfTask(Pr_TaskP_t);
	//! Bottom Half Pr_Task Object for the IRQ vector 18
	Pr_Task 	EDROOMIRQ18BottomHalfT;
	//! Component Port associated to the IRQ vector 18
	static CEDROOMIRQInterface	SensorIRQ;
	//! Global variable required for the botton half of the IRQ vector 18
	static TEDROOMByte	EDROOMVarIRQ18;
	/**
	 * \class CEDROOMPOOLIRQ18TEDROOMByte
	 * \brief Data Pool Class required for the botton half of the IRQ vector 18
	 *
	 */
	class CEDROOMPOOLIRQ18TEDROOMByte:public CEDROOMProtectedMemoryPool {
		//! Data Pool Memory
		TEDROOMByte mem[10+1];
		//! Data Pool Memory Marks
		bool marks[10];
		public:
		//! Constructor
		CEDROOMPOOLIRQ18TEDROOMByte():CEDROOMProtectedMemoryPool(10,mem,marks, sizeof(TEDROOMByte)){}
		//! Function for allocating a data from the pool
		TEDROOMByte	* AllocData(){ return ( TEDROOMByte	* ) CEDROOMProtectedMemoryPool::AllocData();}
	};
	 //!Data Pool required for the botton half of the IRQ vector 18
	static CEDROOMPOOLIRQ18TEDROOMByte	EDROOMPoolIRQ18;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	CCAvoidObstaclesIRQ(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, 
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
	 * \enum TEDROOMCCAvoidObstaclesIRQSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	enum TEDROOMCCAvoidObstaclesIRQSignal { EDROOMSignalTimeout,
		EDROOMSignalDestroy,
		EDROOMIRQsignal,
		SConfigAO,
		SStart,
		SObstacleDetected,
		SConfigError,
		SConfigOK };


		friend class CCAvoidObstaclesIRQ;

		//!component reference
		CCAvoidObstaclesIRQ &EDROOMcomponent;

		//!Current message pointer reference
		CEDROOMMessage * &Msg;

		//!Synchronous message back pointer reference
		CEDROOMMessage * &MsgBack;

		//!Component ports
		CEDROOMInterface & AvoidObstaclesSysCtrl;
		CEDROOMIRQInterface & SensorIRQ;


		//! State Identifiers
		enum TEDROOMStateID{I,
			Idle,
			Ready};

		//!Transition Identifiers
		enum TEDROOMTransitionID{Init,
			Config,
			Start,
			HandleObstacle,
			EDROOMMemoryTrans };



		//!Variables
		TEDROOMByte &VObsDetected;




		//!Constructor
		EDROOM_CTX_Top_0 (CCAvoidObstaclesIRQ &act,
				TEDROOMByte & EDROOMpVarVObsDetected );

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
		void	FConfigOK();

		/**
		 * \brief  
		 */
		void	FHandleIRQ();

		/**
		 * \brief  
		 */
		void	FHandleObstacle();

		/**
		 * \brief  
		 */
		void	FInit();

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
		TEDROOMByte VObsDetected;




	public:

		//! Constructor
		EDROOM_SUB_Top_0 (CCAvoidObstaclesIRQ &act );


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
