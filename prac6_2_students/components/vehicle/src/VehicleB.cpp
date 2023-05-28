#include <public/vehicle_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

Vehicle::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(Vehicle &act,
	 CDLocation & EDROOMpVarVTargetLocation,
	 CEDROOMPOOLCDLocation & EDROOMpPoolCDLocation ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	AvoidObstaclesSysCtrl(EDROOMcomponent.AvoidObstaclesSysCtrl),
	PathPlannerCtrl(EDROOMcomponent.PathPlannerCtrl),
	PathTrackerCtrl(EDROOMcomponent.PathTrackerCtrl),
	Timer(EDROOMcomponent.Timer),
	VTargetLocation(EDROOMpVarVTargetLocation),
	EDROOMPoolCDLocation(EDROOMpPoolCDLocation)
{
}

Vehicle::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	AvoidObstaclesSysCtrl(context.AvoidObstaclesSysCtrl),
	PathPlannerCtrl(context.PathPlannerCtrl),
	PathTrackerCtrl(context.PathTrackerCtrl),
	Timer(context.Timer),
	VTargetLocation(context.VTargetLocation),
	EDROOMPoolCDLocation(context.EDROOMPoolCDLocation )
{

}

	// EDROOMSearchContextTrans********************************************

bool Vehicle::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		// Check trigger for signal EDROOMSignalTimeout

		 case (EDROOMSignalTimeout): 

				if (*Msg->GetPInterface() == Timer)
				{

					//Next transition is  ReStart
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

	// User-defined Functions   ****************************

void	Vehicle::EDROOM_CTX_Top_0::FAvObstaclesError()

{

{
 
	io_ctrl_config_avoid_obstacles_error();
 
}

}



void	Vehicle::EDROOM_CTX_Top_0::FInit()

{

io_ctrl_init();

}



void	Vehicle::EDROOM_CTX_Top_0::FInvokeConfigAvObstacles()

{

   //Invoke synchronous communication 
   MsgBack=AvoidObstaclesSysCtrl.invoke(SConfigAO); 
}



void	Vehicle::EDROOM_CTX_Top_0::FInvokeConfigPathPlanner()

{
   //Allocate data from pool
  CDLocation * pSConfigPathPlanner_Data = EDROOMPoolCDLocation.AllocData();
	
		// Complete Data 
	
	*pSConfigPathPlanner_Data=VTargetLocation;
   //Invoke synchronous communication 
   MsgBack=PathPlannerCtrl.invoke(SConfigPathPlanner,
                                                       pSConfigPathPlanner_Data,
                                                        &EDROOMPoolCDLocation); 
}



void	Vehicle::EDROOM_CTX_Top_0::FInvokeConfigPathTracker()

{

   //Invoke synchronous communication 
   MsgBack=PathTrackerCtrl.invoke(SConfigPathTracker); 
}



void	Vehicle::EDROOM_CTX_Top_0::FMarkObstacle()

{
   //Allocate data from pool
  CDLocation * pSMarkObstacle_Data = EDROOMPoolCDLocation.AllocData();
	
		// Complete Data 
	
	*pSMarkObstacle_Data=sensors_get_current_location();
   //Send message 
   PathPlannerCtrl.send(SMarkObstacle,pSMarkObstacle_Data,
                                                        &EDROOMPoolCDLocation); 
}



void	Vehicle::EDROOM_CTX_Top_0::FPathPlannerError()

{

{
 
	io_ctrl_config_path_planner_error();
 
 
}

}



void	Vehicle::EDROOM_CTX_Top_0::FPathTrackerError()

{

{
 
	io_ctrl_path_tracker_error();
 
}

}



void	Vehicle::EDROOM_CTX_Top_0::FProgRecovery()

{
   //Define absolute time
  Pr_Time time;
	
	time.GetTime();
 
	// Timing Service 
	 
	time+=Pr_Time(10,0);  // seconds
	 
	
	io_ctrl_recovery();
   //Program absolute timer 
   Timer.InformAt( time ); 
}



void	Vehicle::EDROOM_CTX_Top_0::FProgTimerConfig()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
   interval = Pr_Time(1,0); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	Vehicle::EDROOM_CTX_Top_0::FStartAvoidObs()

{

   //Send message 
   AvoidObstaclesSysCtrl.send(SStart); 
}



void	Vehicle::EDROOM_CTX_Top_0::FStartPlanning()

{

   //Send message 
   PathPlannerCtrl.send(SStartPlanning); 
}



void	Vehicle::EDROOM_CTX_Top_0::FStartTracking()

{

   //Send message 
   PathTrackerCtrl.send(SStartTracking); 
}



void	Vehicle::EDROOM_CTX_Top_0::FStartUp()

{

{
 
	VTargetLocation=sensors_get_current_location();
 
	if(VTargetLocation.latitude>0) 
		VTargetLocation.latitude-=0.1;
	else
		VTargetLocation.latitude+=0.1;
 
	if(VTargetLocation.longitude>0) 
		VTargetLocation.longitude-=0.1;
	else
		VTargetLocation.longitude+=0.1;	
 
	io_ctrl_startup();
 	  
}

}



void	Vehicle::EDROOM_CTX_Top_0::FStopTracking()

{

   //Send message 
   PathTrackerCtrl.send(SStopTracking); 
}



bool	Vehicle::EDROOM_CTX_Top_0::GConfigError()

{

return(MsgBack->signal==SConfigError);

}



	//********************************** Pools *************************************

	//CEDROOMPOOLCDLocation

Vehicle::EDROOM_CTX_Top_0::CEDROOMPOOLCDLocation::CEDROOMPOOLCDLocation(
			TEDROOMUInt32 elemCount,CDLocation* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(CDLocation))
{
}

CDLocation *	Vehicle::EDROOM_CTX_Top_0::CEDROOMPOOLCDLocation::AllocData()
{
	return(CDLocation*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

Vehicle::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (Vehicle&act
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			VTargetLocation,
			EDROOMPoolCDLocation),
		EDROOMPoolCDLocation(
			10, pEDROOMMemory->poolCDLocation,
			pEDROOMMemory->poolMarkCDLocation)
{

}

	//***************************** EDROOMBehaviour ********************************

void Vehicle::EDROOM_SUB_Top_0::EDROOMBehaviour()
{

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIArrival();

	do
	{

		//Take next transition

		switch(edroomCurrentTrans.localId)
		{

			//Next Transition is Init
			case (Init):
				//Execute Action 
				FInit();
				//Next State is StartUp
				edroomNextState = StartUp;
				break;
			//To Choice Point ConfigAvObstacles
			case (ConfigAvObstacles):

				//Invoke Synchronous Message 
				FInvokeConfigAvObstacles();
				//Evaluate Branch Error
				if( GConfigError() )
				{
					//Execute Action 
					FAvObstaclesError();

					//Branch taken is ConfigAvObstacles_Error
					edroomCurrentTrans.localId =
						ConfigAvObstacles_Error;

					//Next State is SysRecovery
					edroomNextState = SysRecovery;
				 } 
				//Default Branch OK
				else
				{

					//Branch taken is ConfigAvObstacles_OK
					edroomCurrentTrans.localId =
						ConfigAvObstacles_OK;

					//Next State is AvObstaclesConfigured
					edroomNextState = AvObstaclesConfigured;
				 } 
				break;
			//Next Transition is ReStart
			case (ReStart):
				//Next State is StartUp
				edroomNextState = StartUp;
				break;
			//To Choice Point ConfigPathTracker
			case (ConfigPathTracker):

				//Invoke Synchronous Message 
				FInvokeConfigPathTracker();
				//Evaluate Branch Error
				if( GConfigError() )
				{
					//Execute Action 
					FPathTrackerError();

					//Branch taken is ConfigPathTracker_Error
					edroomCurrentTrans.localId =
						ConfigPathTracker_Error;

					//Next State is SysRecovery
					edroomNextState = SysRecovery;
				 } 
				//Default Branch OK
				else
				{

					//Branch taken is ConfigPathTracker_OK
					edroomCurrentTrans.localId =
						ConfigPathTracker_OK;

					//Next State is PathTrackerConfigured
					edroomNextState = PathTrackerConfigured;
				 } 
				break;
			//To Choice Point ConfigPathPlanner
			case (ConfigPathPlanner):

				//Invoke Synchronous Message 
				FInvokeConfigPathPlanner();
				//Evaluate Branch Error
				if( GConfigError() )
				{
					//Execute Action 
					FPathPlannerError();

					//Branch taken is ConfigPathPlanner_Error
					edroomCurrentTrans.localId =
						ConfigPathPlanner_Error;

					//Next State is SysRecovery
					edroomNextState = SysRecovery;
				 } 
				//Default Branch OK
				else
				{
					//Send Asynchronous Messages 
					FStartPlanning();
					FStartTracking();
					FStartAvoidObs();

					//Branch taken is ConfigPathPlanner_OK
					edroomCurrentTrans.localId =
						ConfigPathPlanner_OK;

					//Next State is VehicleReady
					edroomNextState = VehicleReady;
				 } 
				break;
			//Next Transition is ObstacleDetected
			case (ObstacleDetected):
				//Send Asynchronous Messages 
				FStopTracking();
				FMarkObstacle();
				//Next State is VehicleReady
				edroomNextState = VehicleReady;
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState)
		{

				//Go to the state I
			case (I):
				//Arrival to state I
				edroomCurrentTrans=EDROOMIArrival();
				break;

				//Go to the state StartUp
			case (StartUp):
				//Execute Entry Actions 
				FStartUp();
				FProgTimerConfig();
				//Arrival to state StartUp
				edroomCurrentTrans=EDROOMStartUpArrival();
				break;

				//Go to the state VehicleReady
			case (VehicleReady):
				//Arrival to state VehicleReady
				edroomCurrentTrans=EDROOMVehicleReadyArrival();
				break;

				//Go to the state SysRecovery
			case (SysRecovery):
				//Execute Entry Action 
				FProgRecovery();
				//Arrival to state SysRecovery
				edroomCurrentTrans=EDROOMSysRecoveryArrival();
				break;

				//Go to the state AvObstaclesConfigured
			case (AvObstaclesConfigured):
				//Execute Entry Action 
				FProgTimerConfig();
				//Arrival to state AvObstaclesConfigured
				edroomCurrentTrans=EDROOMAvObstaclesConfiguredArrival();
				break;

				//Go to the state PathTrackerConfigured
			case (PathTrackerConfigured):
				//Execute Entry Action 
				FProgTimerConfig();
				//Arrival to state PathTrackerConfigured
				edroomCurrentTrans=EDROOMPathTrackerConfiguredArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void Vehicle::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId Vehicle::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  StartUp

	// ***********************************************************************



TEDROOMTransId Vehicle::EDROOM_SUB_Top_0::EDROOMStartUpArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == Timer)
				{

					//Next transition is  ConfigAvObstacles
					edroomCurrentTrans.localId = ConfigAvObstacles;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  VehicleReady

	// ***********************************************************************



TEDROOMTransId Vehicle::EDROOM_SUB_Top_0::EDROOMVehicleReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SObstacleDetected): 

				 if (*Msg->GetPInterface() == AvoidObstaclesSysCtrl)
				{

					//Next transition is  ObstacleDetected
					edroomCurrentTrans.localId= ObstacleDetected;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  SysRecovery

	// ***********************************************************************



TEDROOMTransId Vehicle::EDROOM_SUB_Top_0::EDROOMSysRecoveryArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  AvObstaclesConfigured

	// ***********************************************************************



TEDROOMTransId Vehicle::EDROOM_SUB_Top_0::EDROOMAvObstaclesConfiguredArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == Timer)
				{

					//Next transition is  ConfigPathTracker
					edroomCurrentTrans.localId = ConfigPathTracker;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  PathTrackerConfigured

	// ***********************************************************************



TEDROOMTransId Vehicle::EDROOM_SUB_Top_0::EDROOMPathTrackerConfiguredArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == Timer)
				{

					//Next transition is  ConfigPathPlanner
					edroomCurrentTrans.localId = ConfigPathPlanner;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



