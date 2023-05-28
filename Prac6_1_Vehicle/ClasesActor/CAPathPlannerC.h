#ifndef F_CAPathPlannerC_h
#define F_CAPathPlannerC_h

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



class EDROOMTopContext {

protected:

enum EDROOMCAPathPlannerSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, STrackPath, SPathRequest, SConfigPathPlanner, SMarkObstacle, SNewTargetLocation, SStartPlanning, SConfigOK, SConfigError };


	friend class CAPathPlanner;

	CAPathPlanner &EDROOMcomponent;

	CEDROOMMessage * &Msg;

	CEDROOMMessage * &MsgBack;

	//Ports

	CEDROOMInterface & TrackPath;
	CEDROOMInterface & PathPlannerCtrl;
	CEDROOMTimingInterface & Timer;

	enum edroomStateId{I, Idle, CalculatePath, CalNextPath};

	enum IdTrans{Init, Config, Config_Error, Config_OK, CalStep, CalStep_SendMinPath, CalStep_NextStep, CalStep_MaxStep, ObstacleDetected, NewTarget, PathReq, Start,  EDROOMMEMORIA };

	//Constantes

	const TEDROOMUInt8 VMaxPathSteps;
	const TEDROOMUInt8 VMinPathSteps;


	//Variables

	CDPath &VNextPath;
	CDLocation &VNextStepStartPoing;
	TEDROOMUInt8 &VSimError;
	CDLocation &VTargetLocation;
	TEDROOMBool &VVehicleHalted;


	//Pool

	class CEDROOMPOOLCDPath:public CEDROOMProtectedMemoryPool {
		public:
		CEDROOMPOOLCDPath(TEDROOMUInt32 elemCount,CDPath *pMem, TEDROOMBool *pMarks);
		CDPath	* AllocData();
	};
	CEDROOMPOOLCDPath	& EDROOMPoolCDPath;


	// CONSTRUCTORES

	EDROOMTopContext (CAPathPlanner &act, CDPath & EDROOMpVarVNextPath, CDLocation & EDROOMpVarVNextStepStartPoing, TEDROOMUInt8 & EDROOMpVarVSimError, CDLocation & EDROOMpVarVTargetLocation, TEDROOMBool & EDROOMpVarVVehicleHalted, CEDROOMPOOLCDPath & EDROOMpPoolCDPath );

	EDROOMTopContext ( EDROOMTopContext &contex );

public:

	bool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

	void EDROOMNuevoMens () { EDROOMcomponent.EDROOMNewMsg(); }

	// Funciones Definidas por el usuario

	void	FCalPathStep();

	void	FConfigOK();

	void	FConfigPlanner();

	void	FMarkObstacleAndReplanning();

	void	FMaxSteps();

	void	FProgStepPlanning();

	void	FSendMinPath();

	void	FSendPath();

	void	FSetNewTarget();

	void	FSimError();

	TEDROOMBool	GMaxSteps();

	TEDROOMBool	GSendMinPath();

};

// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



class EDROOMTopState : public EDROOMTopContext {

protected:



	EDROOMTopContext::edroomStateId edroomCurrentState;

	EDROOMTopContext::edroomStateId edroomNextState;

	//Variables

	CDPath VNextPath;
	CDLocation VNextStepStartPoing;
	TEDROOMUInt8 VSimError;
	CDLocation VTargetLocation;
	TEDROOMBool VVehicleHalted;


	//Pools

	CEDROOMPOOLCDPath	EDROOMPoolCDPath;


public:

	// CONSTRUCTOR

	EDROOMTopState (CAPathPlanner &act, CEDROOMMemory *pEDROOMMemory  );


	// EDROOMBehaviour**********************************************

	void EDROOMBehaviour();

	// Inicio**********************************************

	void EDROOMInicio();

	// ***********************************************************************

	// SubEstado Inicial 

	// ***********************************************************************



	TEDROOMTransId EDROOMIllegada();

	// ***********************************************************************

	// SubEstado Hoja Idle

	// ***********************************************************************



	TEDROOMTransId EDROOMIdlellegada();

	// ***********************************************************************

	// SubEstado Hoja CalculatePath

	// ***********************************************************************



	TEDROOMTransId EDROOMCalculatePathllegada();

	// ***********************************************************************

	// SubEstado Hoja CalNextPath

	// ***********************************************************************



	TEDROOMTransId EDROOMCalNextPathllegada();

};


#endif
