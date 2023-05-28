

#include <vehicule/VehiculeE.h>





	// ******************* CONSTRUCTOR ************************************



Vehicule::Vehicule(TEDROOMComponentID id,unsigned int roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory *pActorMemory ) : 
		CEDROOMComponent(id,EDROOMprioMINIMUM+1,4,roomNumMaxMens,roomtaskPrio,roomStack, pActorMemory )


		// ***************	TIMERS ********************

		,EDROOMtimingSAP(this, 3,&pActorMemory->TimingMemory)


		// ***************	TIMERS ********************

		,Timer(&EDROOMtimingSAP, 2 )




		// ***************	Estado Top *****************

		,edroomTopState(*this)


{


}


	//***************	METODOS PUBLICOS  ********************************



		//**********           CONFIGURACION               ************


int Vehicule::EDROOMConfig() {




 return 0; }



		//**********           START               ************


int Vehicule::EDROOMStart() {



		//****************** INICIO DE LA TAREA TIMERS**********************

	EDROOMtimingSAP.Start();

		//****************** INICIO DEL PROPIO ACTOR **********************

	CEDROOMComponent::EDROOMStart(); 	// Llamada a la funcion Start de la clase Actor

return 0;}


	// ***************	METODOS PROTEGIDOS *******************************



		//**********        COMPORTAMIENTO           ************



void Vehicule::EDROOMBehaviour() {

	edroomTopState.EDROOMBehaviour();

}




		//**********        ACTORTERMINADO           ************


	#ifdef _EDROOM_SYSTEM_CLOSE

TEDROOMBool Vehicule::EDROOMIsComponentFinished() {


	return ( AvoidObstacles.EDROOMIsComponentFinished() && PathPlanner.EDROOMIsComponentFinished() && PathTracker.EDROOMIsComponentFinished() && CEDROOMComponent::EDROOMIsComponentFinished());

}


	#endif

	// ***************	EDROOM Memory ******************************

void Vehicule::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_, CEDROOMMessage * MessagesMem_, TEDROOMBool * MessagesMemMarks_, CEDROOMQueue::CQueueNode * QueueNodesMem_, TEDROOMBool * QueueNodesMemMarks_){
		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_, QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);

		TimingMemory.SetMemory(3,TimerInf,&TimerInfMarks[0],TimeOutMess,&TimeOutMessMarks[0]);


}

