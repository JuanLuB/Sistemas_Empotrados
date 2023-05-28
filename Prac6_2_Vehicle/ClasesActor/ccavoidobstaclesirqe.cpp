

#include <public/ccavoidobstaclesirq_iface_v1.h>



	// ******************* HANDLING IRQ 18********************

Pr_IRQEvent	CCAvoidObstaclesIRQ::EDROOMEventIRQ18(18);
Pr_SemaphoreBin	CCAvoidObstaclesIRQ::EDROOMSemEndIRQ18(0);


		// ******************* DATA ***************

TEDROOMByte	CCAvoidObstaclesIRQ::	EDROOMVarIRQ18;


		// ******************* DATA POOL *******

CCAvoidObstaclesIRQ::CEDROOMPOOLIRQ18TEDROOMByte	CCAvoidObstaclesIRQ::EDROOMPoolIRQ18;


		// ******************* Aux IRQ Handler **************

void 	CCAvoidObstaclesIRQ::EDROOMIRQ18HandlerTopHalfFunction(void){

	bool EDROOMIRQ18BottomHalfSignal=true;
	EDROOMVarIRQ18='X';

	if (EDROOMIRQ18BottomHalfSignal)
		EDROOMEventIRQ18.Signal();

}



		// ******************* IRQ Handler **************

Pr_IRQHandler_RetType	CCAvoidObstaclesIRQ::EDROOMIRQ18Handler(void){

	EDROOMIRQ18HandlerTopHalfFunction();

}



		// ******************* IRQ Idle Handler **************

Pr_IRQHandler_RetType	CCAvoidObstaclesIRQ::EDROOMIRQ18IdleHandler(void){

}



		// ******************* Bottom Half Task **************

Pr_TaskRV_t 	CCAvoidObstaclesIRQ::EDROOMIRQ18BottomHalfTask(Pr_TaskP_t){

	bool endTask=false;

	do
	{

		EDROOMEventIRQ18.Wait();

		bool EDROOMIRQ18SendMsgToCmp=true;

		if(!EDROOMSemEndIRQ18.WaitCond()){

			actuators_halt();

			if(EDROOMIRQ18SendMsgToCmp){
				TEDROOMByte	*pEDROOMVarIRQ;

				pEDROOMVarIRQ=EDROOMPoolIRQ18.AllocData();

				*pEDROOMVarIRQ=EDROOMVarIRQ18;

				SensorIRQ.NewIRQMsg(EDROOMIRQsignal, pEDROOMVarIRQ, &EDROOMPoolIRQ18);

			}
			Pr_IRQManager::EnableIRQ(18);

		}else endTask=1;

	}while(!endTask);

}



		// ******************* IRQPort **************

CEDROOMIRQInterface CCAvoidObstaclesIRQ::SensorIRQ( 
		CCAvoidObstaclesIRQ::EDROOMIRQ18Handler 
		,CCAvoidObstaclesIRQ::EDROOMIRQ18IdleHandler 
		,CCAvoidObstaclesIRQ::EDROOMEventIRQ18
		,CCAvoidObstaclesIRQ::EDROOMSemEndIRQ18
		,18 );




// ******************************* CONSTRUCTOR ************************************



CCAvoidObstaclesIRQ::CCAvoidObstaclesIRQ(TEDROOMComponentID id,
		TEDROOMUInt32 roomNumMaxMens,
		TEDROOMPriority roomtaskPrio,
		TEDROOMStackSizeType roomStack,
		CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,
				roomtaskPrio,roomStack, pActorMemory ),

		// ***************   BOTTOM HALF IRQ TASKS  ********************

		EDROOMIRQ18BottomHalfT( EDROOMIRQ18BottomHalfTask,EDROOMprioURGENT,256),

		// ***************	Top State  *****************

		edroomTopState(*this)


{


}


//**************************************************************************
//**************************   PUBLIC METHODS  *****************************



//************************** EDROOMConfig **********************************


int CCAvoidObstaclesIRQ::EDROOMConfig()
{


 return 0; 
}



//************************** EDROOMStart **********************************

int CCAvoidObstaclesIRQ::EDROOMStart()
{


	//***************** CEDROOMComponent::EDROOMStart*********

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

	return 0;
}


//**************************************************************************
//***************************    PROTECTED METHODS *************************



//*****************************  EDROOMBehaviour ***************************



void CCAvoidObstaclesIRQ::EDROOMBehaviour()
{

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();


		// *************** PUERTOS IRQ ********************

	SensorIRQ.EndIRQHandlerTask();
}




//********************* ComponentIsFinished **********************************


#ifdef _EDROOM_SYSTEM_CLOSE

bool CCAvoidObstaclesIRQ::EDROOMIsComponentFinished()
{


	return ( CEDROOMComponent::EDROOMIsComponentFinished());

}

#endif


//****************** EDROOMMemory::SetMemory *******************************

void CCAvoidObstaclesIRQ::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ ,
		CEDROOMMessage * MessagesMem_,
		bool * MessagesMemMarks_,
		TEDROOMUInt32 numberOfNodes_,
		CEDROOMQueue::CQueueNode * QueueNodesMem_,
		bool * QueueNodesMemMarks_)
{

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_,
			numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);


}

