

#include <public/ccavoidobstacles_iface_v1.h>



	// ******************* HANDLING IRQ 18********************

Pr_IRQEvent	CCAvoidObstacles::EDROOMEventIRQ18(18);
Pr_SemaphoreBin	CCAvoidObstacles::EDROOMSemEndIRQ18(0);


		// ******************* DATA ***************

TEDROOMByte	CCAvoidObstacles::	EDROOMVarIRQ18;


		// ******************* DATA POOL *******

CCAvoidObstacles::CEDROOMPOOLIRQ18TEDROOMByte	CCAvoidObstacles::EDROOMPoolIRQ18;


		// ******************* Aux IRQ Handler **************

void 	CCAvoidObstacles::EDROOMIRQ18HandlerTopHalfFunction(void){

	bool EDROOMIRQ18BottomHalfSignal=true;
	EDROOMVarIRQ18=io_ctrl_get_obstacle_info();

	if (EDROOMIRQ18BottomHalfSignal)
		EDROOMEventIRQ18.Signal();

}



		// ******************* IRQ Handler **************

Pr_IRQHandler_RetType	CCAvoidObstacles::EDROOMIRQ18Handler(void){

	EDROOMIRQ18HandlerTopHalfFunction();

}



		// ******************* IRQ Idle Handler **************

Pr_IRQHandler_RetType	CCAvoidObstacles::EDROOMIRQ18IdleHandler(void){

}



		// ******************* Bottom Half Task **************

Pr_TaskRV_t 	CCAvoidObstacles::EDROOMIRQ18BottomHalfTask(Pr_TaskP_t){

	bool endTask=false;

	do
	{

		EDROOMEventIRQ18.Wait();

		bool EDROOMIRQ18SendMsgToCmp=true;

		if(!EDROOMSemEndIRQ18.WaitCond()){

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

CEDROOMIRQInterface CCAvoidObstacles::SensorIRQ( 
		CCAvoidObstacles::EDROOMIRQ18Handler 
		,CCAvoidObstacles::EDROOMIRQ18IdleHandler 
		,CCAvoidObstacles::EDROOMEventIRQ18
		,CCAvoidObstacles::EDROOMSemEndIRQ18
		,18 );




// ******************************* CONSTRUCTOR ************************************



CCAvoidObstacles::CCAvoidObstacles(TEDROOMComponentID id,
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


int CCAvoidObstacles::EDROOMConfig()
{


 return 0; 
}



//************************** EDROOMStart **********************************

int CCAvoidObstacles::EDROOMStart()
{


	//***************** CEDROOMComponent::EDROOMStart*********

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

	return 0;
}


//**************************************************************************
//***************************    PROTECTED METHODS *************************



//*****************************  EDROOMBehaviour ***************************



void CCAvoidObstacles::EDROOMBehaviour()
{

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();


		// *************** PUERTOS IRQ ********************

	SensorIRQ.EndIRQHandlerTask();
}




//********************* ComponentIsFinished **********************************


#ifdef _EDROOM_SYSTEM_CLOSE

bool CCAvoidObstacles::EDROOMIsComponentFinished()
{


	return ( CEDROOMComponent::EDROOMIsComponentFinished());

}

#endif


//****************** EDROOMMemory::SetMemory *******************************

void CCAvoidObstacles::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ ,
		CEDROOMMessage * MessagesMem_,
		bool * MessagesMemMarks_,
		TEDROOMUInt32 numberOfNodes_,
		CEDROOMQueue::CQueueNode * QueueNodesMem_,
		bool * QueueNodesMemMarks_)
{

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_,
			numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);


}

