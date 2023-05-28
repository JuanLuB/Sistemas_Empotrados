#include <public/capathtracker_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAPathTracker::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CAPathTracker &act,
	 CDPath & EDROOMpVarVCurrentPath,
	 TEDROOMUInt8 & EDROOMpVarVCurrentPathStep,
	 TEDROOMUInt8 & EDROOMpVarVSimError ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	TrackPath(EDROOMcomponent.TrackPath),
	PathTrackerCtrl(EDROOMcomponent.PathTrackerCtrl),
	Timer(EDROOMcomponent.Timer),
	VCurrentPath(EDROOMpVarVCurrentPath),
	VCurrentPathStep(EDROOMpVarVCurrentPathStep),
	VSimError(EDROOMpVarVSimError)
{
}

CAPathTracker::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	TrackPath(context.TrackPath),
	PathTrackerCtrl(context.PathTrackerCtrl),
	Timer(context.Timer),
	VCurrentPath(context.VCurrentPath),
	VCurrentPathStep(context.VCurrentPathStep),
	VSimError(context.VSimError)
{

}

	// EDROOMSearchContextTrans********************************************

bool CAPathTracker::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User-defined Functions   ****************************

void	CAPathTracker::EDROOM_CTX_Top_0::FGetNewPatch()

{
   //Handle Msg->data
  CDPath & varSTrackPath = *(CDPath *)Msg->data;
	
		// Data access
 
	VCurrentPath = varSTrackPath;
 
 	VCurrentPathStep=0;

}



void	CAPathTracker::EDROOM_CTX_Top_0::FGoToPathStep()

{

{
 io_ctrl_go_to_path_step(VCurrentPathStep);
 
 actuators_go_to_location(VCurrentPath.pathLocations[VCurrentPathStep]);
 
 VCurrentPathStep++;
 
}

}



void	CAPathTracker::EDROOM_CTX_Top_0::FProgFirstTrackStep()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
 interval = Pr_Time(0,10000); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAPathTracker::EDROOM_CTX_Top_0::FProgNextTrackStep()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
  interval = Pr_Time(0,400000); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAPathTracker::EDROOM_CTX_Top_0::FReplyOK()

{

actuators_start();
   //Reply synchronous communication
   Msg->reply(SConfigOK); 
}



void	CAPathTracker::EDROOM_CTX_Top_0::FReplySimError()

{

 
 
  VSimError--;
   //Reply synchronous communication
   Msg->reply(SConfigError); 
}



void	CAPathTracker::EDROOM_CTX_Top_0::FSendPathRequest()

{

   //Send message 
   TrackPath.send(SPathRequest); 
}



bool	CAPathTracker::EDROOM_CTX_Top_0::GLastStep()

{

{
 
	return (VCurrentPathStep>=VCurrentPath.pathSteps);
 
 
 
 
}

}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAPathTracker::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CAPathTracker&act):
		EDROOM_CTX_Top_0(act,
			VCurrentPath,
			VCurrentPathStep,
			VSimError),
		VCurrentPathStep(0),
		VSimError(2)
{

}

	//***************************** EDROOMBehaviour ********************************

void CAPathTracker::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
			//Next Transition is NewPath
			case (NewPath):
				//Msg->Data Handling 
				FGetNewPatch();
				//Execute Action 
				FProgFirstTrackStep();
				//Next State is TrackingPath
				edroomNextState = TrackingPath;
				break;
			//To Choice Point PathStep
			case (PathStep):

				//Execute Action 
				FGoToPathStep();
				//Evaluate Branch LastStep
				if( GLastStep() )
				{
					//Send Asynchronous Message 
					FSendPathRequest();

					//Branch taken is PathStep_LastStep
					edroomCurrentTrans.localId =
						PathStep_LastStep;

					//Next State is StandBy
					edroomNextState = StandBy;
				 } 
				//Default Branch toNextStep
				else
				{
					//Execute Action 
					FProgNextTrackStep();

					//Branch taken is PathStep_toNextStep
					edroomCurrentTrans.localId =
						PathStep_toNextStep;

					//Next State is TrackingPath
					edroomNextState = TrackingPath;
				 } 
				break;
			//To Choice Point Config
			case (Config):

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
					FReplyOK();

					//Branch taken is Config_OK
					edroomCurrentTrans.localId =
						Config_OK;

					//Next State is Idle
					edroomNextState = Idle;
				 } 
				break;
			//Next Transition is Start
			case (Start):
				//Next State is StandBy
				edroomNextState = StandBy;
				break;
			//Next Transition is StopTrack
			case (StopTrack):
				//Next State is Pause
				edroomNextState = Pause;
				break;
			//Next Transition is ResumePath
			case (ResumePath):
				//Msg->Data Handling 
				FGetNewPatch();
				//Next State is TrackingPath
				edroomNextState = TrackingPath;
				break;
			//Next Transition is ToStandBy
			case (ToStandBy):
				//Next State is StandBy
				edroomNextState = StandBy;
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

				//Go to the state StandBy
			case (StandBy):
				//Arrival to state StandBy
				edroomCurrentTrans=EDROOMStandByArrival();
				break;

				//Go to the state TrackingPath
			case (TrackingPath):
				//Arrival to state TrackingPath
				edroomCurrentTrans=EDROOMTrackingPathArrival();
				break;

				//Go to the state Pause
			case (Pause):
				//Arrival to state Pause
				edroomCurrentTrans=EDROOMPauseArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CAPathTracker::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CAPathTracker::EDROOM_SUB_Top_0::EDROOMIArrival()
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



TEDROOMTransId CAPathTracker::EDROOM_SUB_Top_0::EDROOMIdleArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SConfigPathTracker): 

				 if (*Msg->GetPInterface() == PathTrackerCtrl)
				{

					//Next transition is  Config
					edroomCurrentTrans.localId = Config;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

			case (SStartTracking): 

				 if (*Msg->GetPInterface() == PathTrackerCtrl)
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

	// Leaf SubState  StandBy

	// ***********************************************************************



TEDROOMTransId CAPathTracker::EDROOM_SUB_Top_0::EDROOMStandByArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (STrackPath): 

				 if (*Msg->GetPInterface() == TrackPath)
				{

					//Next transition is  NewPath
					edroomCurrentTrans.localId= NewPath;
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

	// Leaf SubState  TrackingPath

	// ***********************************************************************



TEDROOMTransId CAPathTracker::EDROOM_SUB_Top_0::EDROOMTrackingPathArrival()
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

					//Next transition is  PathStep
					edroomCurrentTrans.localId = PathStep;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

			case (SStopTracking): 

				 if (*Msg->GetPInterface() == PathTrackerCtrl)
				{

					//Next transition is  StopTrack
					edroomCurrentTrans.localId= StopTrack;
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

	// Leaf SubState  Pause

	// ***********************************************************************



TEDROOMTransId CAPathTracker::EDROOM_SUB_Top_0::EDROOMPauseArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (STrackPath): 

				 if (*Msg->GetPInterface() == TrackPath)
				{

					//Next transition is  ResumePath
					edroomCurrentTrans.localId= ResumePath;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == Timer)
				{

					//Next transition is  ToStandBy
					edroomCurrentTrans.localId= ToStandBy;
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



