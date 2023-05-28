#include <public/capathplanner_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAPathPlanner::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CAPathPlanner &act,
	 CDPath & EDROOMpVarVNextPath,
	 CDLocation & EDROOMpVarVNextStepStartPoing,
	 TEDROOMUInt8 & EDROOMpVarVSimError,
	 CDLocation & EDROOMpVarVTargetLocation,
	 TEDROOMBool & EDROOMpVarVVehicleHalted,
	 CEDROOMPOOLCDPath & EDROOMpPoolCDPath ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	TrackPath(EDROOMcomponent.TrackPath),
	PathPlannerCtrl(EDROOMcomponent.PathPlannerCtrl),
	Timer(EDROOMcomponent.Timer),
	VMaxPathSteps(8),
	VMinPathSteps(3),
	VNextPath(EDROOMpVarVNextPath),
	VNextStepStartPoing(EDROOMpVarVNextStepStartPoing),
	VSimError(EDROOMpVarVSimError),
	VTargetLocation(EDROOMpVarVTargetLocation),
	VVehicleHalted(EDROOMpVarVVehicleHalted),
	EDROOMPoolCDPath(EDROOMpPoolCDPath)
{
}

CAPathPlanner::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	TrackPath(context.TrackPath),
	PathPlannerCtrl(context.PathPlannerCtrl),
	Timer(context.Timer),
	VMaxPathSteps(8),
	VMinPathSteps(3),
	VNextPath(context.VNextPath),
	VNextStepStartPoing(context.VNextStepStartPoing),
	VSimError(context.VSimError),
	VTargetLocation(context.VTargetLocation),
	VVehicleHalted(context.VVehicleHalted),
	EDROOMPoolCDPath(context.EDROOMPoolCDPath )
{

}

	// EDROOMSearchContextTrans********************************************

bool CAPathPlanner::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		// Check trigger for signal SNewTargetLocation

		 case (SNewTargetLocation): 

				if (*Msg->GetPInterface() == PathPlannerCtrl)
				{

					//Next transition is  NewTar
					edroomCurrentTrans.localId= NewTar;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

			 break;

		// Check trigger for signal SPathRequest

		 case (SPathRequest): 

				if (*Msg->GetPInterface() == TrackPath)
				{

					//Next transition is  PatRequest
					edroomCurrentTrans.localId= PatRequest;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

			 break;

		// Check trigger for signal SMarkObstacle

		 case (SMarkObstacle): 

				if (*Msg->GetPInterface() == PathPlannerCtrl)
				{

					//Next transition is  ObsTDetected
					edroomCurrentTrans.localId= ObsTDetected;
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

void	CAPathPlanner::EDROOM_CTX_Top_0::FCalPathStep()

{

{
		io_ctrl_cal_step();
 
 		VNextPath.pathLocations[VNextPath.pathSteps]
					=calNextPathStep(VNextStepStartPoing, VTargetLocation);
 
		VNextPath.pathSteps++;
 
}

}



void	CAPathPlanner::EDROOM_CTX_Top_0::FConfigPlanner()

{

{
 
	VTargetLocation = *(CDLocation *)Msg->data;
 
	
 
}

}



void	CAPathPlanner::EDROOM_CTX_Top_0::FMarkObstacle()

{
   //Handle Msg->data
  CDLocation & varSMarkObstacle = *(CDLocation *)Msg->data;
	
		// Data access
 
  markObstacle(varSMarkObstacle);

}



void	CAPathPlanner::EDROOM_CTX_Top_0::FMaxSteps()

{

{
 
 io_ctrl_max_num_of_step();
 
 
 
}

}



void	CAPathPlanner::EDROOM_CTX_Top_0::FNewTarget()

{
   //Handle Msg->data
  CDLocation & varSNewTargetLocation = *(CDLocation *)Msg->data;
	
		// Data acces
 
	VTargetLocation = varSNewTargetLocation;
 
	VVehicleHalted=true;	
	actuators_halt();
 
	VNextStepStartPoing=sensors_get_current_location();
 
	VNextPath.pathSteps=0;

}



void	CAPathPlanner::EDROOM_CTX_Top_0::FProgNextStep()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
   interval = Pr_Time(0,100000); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAPathPlanner::EDROOM_CTX_Top_0::FReplanning()

{

{
 
   VVehicleHalted=true;
 
   VNextStepStartPoing=sensors_get_current_location();
   VNextPath.pathSteps=0;
 
}

}



void	CAPathPlanner::EDROOM_CTX_Top_0::FReplyConfigOK()

{

  VNextStepStartPoing=sensors_get_current_location();
 
  VVehicleHalted=true;	
		
  VNextPath.pathSteps=0;
   //Reply synchronous communication
   Msg->reply(SConfigOK); 
}



void	CAPathPlanner::EDROOM_CTX_Top_0::FReplySimError()

{

 
 
 VSimError--;
   //Reply synchronous communication
   Msg->reply(SConfigError); 
}



void	CAPathPlanner::EDROOM_CTX_Top_0::FSendNextPath()

{
   //Allocate data from pool
  CDPath * pSTrackPath_Data = EDROOMPoolCDPath.AllocData();
	
		// Complete Data 
	
	*pSTrackPath_Data=VNextPath;
 
	VVehicleHalted=false;	
 
	VNextPath.pathSteps=0;
 
 	io_ctrl_next_path();
   //Send message 
   TrackPath.send(STrackPath,pSTrackPath_Data,&EDROOMPoolCDPath); 
}



bool	CAPathPlanner::EDROOM_CTX_Top_0::GMaxSteps()

{

{
 
 
 return (VNextPath.pathSteps==VMaxPathSteps);
 
 
}

}



bool	CAPathPlanner::EDROOM_CTX_Top_0::GSendMinPath()

{

{
 
 
 	return ((VVehicleHalted)&&(VNextPath.pathSteps>=VMinPathSteps));
 
 
}

}



	//********************************** Pools *************************************

	//CEDROOMPOOLCDPath

CAPathPlanner::EDROOM_CTX_Top_0::CEDROOMPOOLCDPath::CEDROOMPOOLCDPath(
			TEDROOMUInt32 elemCount,CDPath* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(CDPath))
{
}

CDPath *	CAPathPlanner::EDROOM_CTX_Top_0::CEDROOMPOOLCDPath::AllocData()
{
	return(CDPath*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAPathPlanner::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CAPathPlanner&act
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			VNextPath,
			VNextStepStartPoing,
			VSimError,
			VTargetLocation,
			VVehicleHalted,
			EDROOMPoolCDPath),
		VSimError(1),
		VVehicleHalted(true),
		EDROOMPoolCDPath(
			3, pEDROOMMemory->poolCDPath,
			pEDROOMMemory->poolMarkCDPath)
{

}

	//***************************** EDROOMBehaviour ********************************

void CAPathPlanner::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//To Choice Point Config
			case (Config):

				//Execute Action 
				FConfigPlanner();
				//Evaluate Branch Error
				if( VSimError )
				{
					//Invoke Synchronous Message 
					FReplySimError();

					//Branch taken is Config_Error
					edroomCurrentTrans.localId =
						Config_Error;

					//Next State is Idle
					edroomNextState = Idle;
				 } 
				//Default Branch OK
				else
				{
					//Invoke Synchronous Message 
					FReplyConfigOK();

					//Branch taken is Config_OK
					edroomCurrentTrans.localId =
						Config_OK;

					//Next State is Idle
					edroomNextState = Idle;
				 } 
				break;
			//To Choice Point CalStep
			case (CalStep):

				//Execute Action 
				FCalPathStep();
				//Evaluate Branch SendMinPath
				if( GSendMinPath() )
				{
					//Execute Action 
					FProgNextStep();
					//Send Asynchronous Message 
					FSendNextPath();

					//Branch taken is CalStep_SendMinPath
					edroomCurrentTrans.localId =
						CalStep_SendMinPath;

					//Next State is CalculatePath
					edroomNextState = CalculatePath;
				 } 
				//Evaluate Branch MaxStep
				else if( GMaxSteps() )
				{
					//Execute Action 
					FMaxSteps();

					//Branch taken is CalStep_MaxStep
					edroomCurrentTrans.localId =
						CalStep_MaxStep;

					//Next State is CalNextPath
					edroomNextState = CalNextPath;
				 } 
				//Default Branch NextStep
				else
				{
					//Execute Action 
					FProgNextStep();

					//Branch taken is CalStep_NextStep
					edroomCurrentTrans.localId =
						CalStep_NextStep;

					//Next State is CalculatePath
					edroomNextState = CalculatePath;
				 } 
				break;
			//Next Transition is Start
			case (Start):
				//Execute Action 
				FProgNextStep();
				//Next State is CalculatePath
				edroomNextState = CalculatePath;
				break;
			//Next Transition is NewTar
			case (NewTar):
				//Msg->Data Handling 
				FNewTarget();
				//Next State is CalculatePath
				edroomNextState = CalculatePath;
				break;
			//Next Transition is PatRequest
			case (PatRequest):
				//Send Asynchronous Message 
				FSendNextPath();
				//Next State is CalculatePath
				edroomNextState = CalculatePath;
				break;
			//Next Transition is ObsTDetected
			case (ObsTDetected):
				//Msg->Data Handling 
				FMarkObstacle();
				//Execute Action 
				FReplanning();
				//Next State is CalculatePath
				edroomNextState = CalculatePath;
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

				//Go to the state Idle
			case (Idle):
				//Arrival to state Idle
				edroomCurrentTrans=EDROOMIdleArrival();
				break;

				//Go to the state CalculatePath
			case (CalculatePath):
				//Arrival to state CalculatePath
				edroomCurrentTrans=EDROOMCalculatePathArrival();
				break;

				//Go to the state CalNextPath
			case (CalNextPath):
				//Arrival to state CalNextPath
				edroomCurrentTrans=EDROOMCalNextPathArrival();
				//Execute Exit Action 
				FProgNextStep();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CAPathPlanner::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CAPathPlanner::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Idle

	// ***********************************************************************



TEDROOMTransId CAPathPlanner::EDROOM_SUB_Top_0::EDROOMIdleArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SConfigPathPlanner): 

				 if (*Msg->GetPInterface() == PathPlannerCtrl)
				{

					//Next transition is  Config
					edroomCurrentTrans.localId = Config;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

			case (SStartPlanning): 

				 if (*Msg->GetPInterface() == PathPlannerCtrl)
				{

					//Next transition is  Start
					edroomCurrentTrans.localId= Start;
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

	// Leaf SubState  CalculatePath

	// ***********************************************************************



TEDROOMTransId CAPathPlanner::EDROOM_SUB_Top_0::EDROOMCalculatePathArrival()
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

					//Next transition is  CalStep
					edroomCurrentTrans.localId = CalStep;
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

	// Leaf SubState  CalNextPath

	// ***********************************************************************



TEDROOMTransId CAPathPlanner::EDROOM_SUB_Top_0::EDROOMCalNextPathArrival()
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



