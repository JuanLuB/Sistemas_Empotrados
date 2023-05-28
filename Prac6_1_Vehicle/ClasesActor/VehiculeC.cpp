#include <vehicule/VehiculeE.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORES***********************************************

Vehicule::EDROOMTopContext::EDROOMTopContext (Vehicule &act, TEDROOMBool & EDROOMpVarVErrorInConfig ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,PathPlannerCtrl(EDROOMcomponent.PathPlannerCtrl)
	,PathTrackerCtrl(EDROOMcomponent.PathTrackerCtrl)
	,AvoidObstaclesSysCtrl(EDROOMcomponent.AvoidObstaclesSysCtrl)
	,Timer(EDROOMcomponent.Timer)
	, VErrorInConfig ( EDROOMpVarVErrorInConfig )
 {

}

Vehicule::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,PathPlannerCtrl(contex.PathPlannerCtrl)
	,PathTrackerCtrl(contex.PathTrackerCtrl)
	,AvoidObstaclesSysCtrl(contex.AvoidObstaclesSysCtrl)
	,Timer(contex.Timer)
	, VErrorInConfig ( contex.VErrorInConfig )
 {

}

	// EDROOMSearchContextTrans********************************************

bool Vehicule::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

	bool edroomValidMsg=false; 

	 switch(Msg->signal){

		 case (EDROOMSignalTimeout): 

				if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId= ReStart;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

			 break;

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// Funciones Definidas por el usuario  ****************************

void	Vehicule::EDROOMTopContext::FStartUp()

{
 
 	
 	print_string("basic hw checking\n");

	FProgNextStep();	
 	  
}



void	Vehicule::EDROOMTopContext::FRecovery()

{
 

	print_strig("Power off all subsystems\n");

	print_strig("Restart in 10 seconds);

	// Timing Service 
	 
	time.Add(10);  // seconds
	 
	Timer.InformAt( time, EDROOMprioNormal );
 
 
 
 
}



void	Vehicule::EDROOMTopContext::FAvObstaclesError()

{
 
 	print_string("error in Avoid Obstacles System");

  
 
}



void	Vehicule::EDROOMTopContext::FConfigAvObstacles()

{
 
	
		// invoke 
	
	MsgBack=AvoidObstaclesSysCtrl.invoke(SConfigAO, EDROOMprioVeryHigh);
	
		// Handling MsgBack
	
	VErrorInConfig=(MsgBack->Signal==SConfigError);
	
	
		// End Handling MsgBack
	
	EDROOMFreeMsgBack(MsgBack);
 
 
 
 
}



void	Vehicule::EDROOMTopContext::FConfigPathTracker()

{
 
 
		// invoke 
	
	MsgBack=PathTrackerCtrl.invoke(SConfigPathTracker, EDROOMprioVeryHigh);
	
		// Handling MsgBack
	
	VErrorInConfig=(MsgBack->Signal==SConfigError);
	
	
		// End Handling MsgBack
	
	EDROOMFreeMsgBack(MsgBack);
 
 
 
}



void	Vehicule::EDROOMTopContext::FConfigPathPlanner()

{
 
		// invoke 
	
	MsgBack=PathPlannerCtrl.invoke(SConfigPathPlanner, EDROOMprioVeryHigh);
	
		// Handling MsgBack
	
	
	VErrorInConfig=(MsgBack->Signal==SConfigError);

	
		// End Handling MsgBack
	
	EDROOMFreeMsgBack(MsgBack);
	
 
 
 
}



void	Vehicule::EDROOMTopContext::FProgNextStep()

{
	
	Pr_Time	interval(0); // Declare time var with an initial value in seconds
	 
	Timer.InformIn( interval, EDROOMprioNormal );

 
}



void	Vehicule::EDROOMTopContext::FHandleObstacle()

{

	
 
	CDObstacleLocation * ap_CDObstacleLocation = EDROOMPoolCDObstacleLocation.AllocData();
	
		// Complete Data 

	ap_CDObstacleLocation->latitude=(aux.GetTicks()*5)/360 + 1/aux.Secns();

	ap_CDObstacleLocation->longitude=aux.GetTicks()/360 +1/aux.Secns();
	
		// send new Msg
	
	PathPlannerCtrl.send(SMarkObstacle, EDROOMprioVeryHigh, ap_CDObstacleLocation, &EDROOMPoolCDObstacleLocation);
 
		// send new Msg
	
	PathTrackerCtrl.send(SStopTracking, EDROOMprioVeryHigh);

 
}



	//*****Pools



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

Vehicule::EDROOMTopState::EDROOMTopState (Vehicule &act ):
	  EDROOMTopContext( act , VErrorInConfig )
{

}

	// EDROOMBehaviour**********************************************

void Vehicule::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans = EDROOMIllegada();

	do{

		switch(edroomCurrentTrans.localId){

			case(Init):
				edroomNextState = StartUp;
				break;
			case(ConfigAvObstacles):
				FConfigAvObstacles();
				if( VErrorInConfig ){
					FAvObstaclesError();
					edroomCurrentTrans.localId = ConfigAvObstacles_Error;
					edroomNextState = SysRecovery;
				 } 
				else{
					edroomCurrentTrans.localId = ConfigAvObstacles_OK;
					edroomNextState = AvObstaclesConfigured;
				 } 
				break;
			case(ReStart):
				edroomNextState = StartUp;
				break;
			case(ConfigPathTracker):
				FConfigPathTracker();
				if( VErrorInConfig ){
					edroomCurrentTrans.localId = ConfigPathTracker_Error;
					edroomNextState = SysRecovery;
				 } 
				else{
					edroomCurrentTrans.localId = ConfigPathTracker_OK;
					edroomNextState = PathTrackerConfigured;
				 } 
				break;
			case(ConfigPathPlanner):
				FConfigPathPlanner();
				if( VErrorInConfig ){
					edroomCurrentTrans.localId = ConfigPathPlanner_Error;
					edroomNextState = SysRecovery;
				 } 
				else{
					edroomCurrentTrans.localId = ConfigPathPlanner_OK;
					edroomNextState = VehiculeReady;
				 } 
				break;
			case(ObstacleDetected):
				FHandleObstacle();
				edroomNextState = VehiculeReady;
				break;
		}

		switch(edroomNextState){

			case(I):
				edroomCurrentTrans=EDROOMIllegada();
				break;

			case(StartUp):
				FStartUp();
				edroomCurrentTrans=EDROOMStartUpllegada();
				break;

			case(VehiculeReady):
				edroomCurrentTrans=EDROOMVehiculeReadyllegada();
				break;

			case(SysRecovery):
				FRecovery();
				edroomCurrentTrans=EDROOMSysRecoveryllegada();
				break;

			case(AvObstaclesConfigured):
				FProgNextStep();
				edroomCurrentTrans=EDROOMAvObstaclesConfiguredllegada();
				break;

			case(PathTrackerConfigured):
				FProgNextStep();
				edroomCurrentTrans=EDROOMPathTrackerConfiguredllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void Vehicule::EDROOMTopState::EDROOMInicio(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 llegada SubEstado I

//	 ***********************************************************************



TEDROOMTransId Vehicule::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// llegada SubEstado Hoja StartUp

	// ***********************************************************************



TEDROOMTransId Vehicule::EDROOMTopState::EDROOMStartUpllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNuevoMens ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId = ConfigAvObstacles;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// llegada SubEstado Hoja VehiculeReady

	// ***********************************************************************



TEDROOMTransId Vehicule::EDROOMTopState::EDROOMVehiculeReadyllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNuevoMens ();

		switch(Msg->signal){

			case (SObstacleDetected): 

				 if ( *Msg->GetPInterface() == AvoidObstaclesSysCtrl) {

					edroomCurrentTrans.localId= ObstacleDetected;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// llegada SubEstado Hoja SysRecovery

	// ***********************************************************************



TEDROOMTransId Vehicule::EDROOMTopState::EDROOMSysRecoveryllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNuevoMens ();

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// llegada SubEstado Hoja AvObstaclesConfigured

	// ***********************************************************************



TEDROOMTransId Vehicule::EDROOMTopState::EDROOMAvObstaclesConfiguredllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNuevoMens ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId = ConfigPathTracker;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// llegada SubEstado Hoja PathTrackerConfigured

	// ***********************************************************************



TEDROOMTransId Vehicule::EDROOMTopState::EDROOMPathTrackerConfiguredllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNuevoMens ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId = ConfigPathPlanner;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



