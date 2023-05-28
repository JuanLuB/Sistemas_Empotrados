#ifndef F_CAPathTrackerC_h
#define F_CAPathTrackerC_h

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



class EDROOMTopContext {

protected:

enum EDROOMCAPathTrackerSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, STrackPath, SPathRequest, SConfigPathTracker, SStopTracking, SStartTracking, SConfigError, SConfigOK };


	friend class CAPathTracker;

	CAPathTracker &EDROOMcomponent;

	CEDROOMMessage * &Msg;

	CEDROOMMessage * &MsgBack;

	//Ports

	CEDROOMInterface & TrackPath;
	CEDROOMInterface & PathTrackerCtrl;
	CEDROOMTimingInterface & Timer;

	enum edroomStateId{I, Idle, StandBy, TrackingPath};

	enum IdTrans{Init, NewPath, PathStep, PathStep_LastStep, PathStep_toNextStep, StopTracking, Config, Config_OK, Config_Error, Start,  EDROOMMEMORIA };

	//Constantes



	//Variables

	CDPath &VCurrentPath;
	TEDROOMUInt8 &VCurrentPathStep;
	TEDROOMUInt8 &VSimError;


	//Pool



	// CONSTRUCTORES

	EDROOMTopContext (CAPathTracker &act, CDPath & EDROOMpVarVCurrentPath, TEDROOMUInt8 & EDROOMpVarVCurrentPathStep, TEDROOMUInt8 & EDROOMpVarVSimError );

	EDROOMTopContext ( EDROOMTopContext &contex );

public:

	bool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

	void EDROOMNuevoMens () { EDROOMcomponent.EDROOMNewMsg(); }

	// Funciones Definidas por el usuario

	void	FGoToPathStep();

	void	FNewPath();

	void	FNoError();

	void	FProgTrackStep();

	void	FRequestPath();

	void	FSimError();

	TEDROOMBool	GLastStep();

};

// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



class EDROOMTopState : public EDROOMTopContext {

protected:



	EDROOMTopContext::edroomStateId edroomCurrentState;

	EDROOMTopContext::edroomStateId edroomNextState;

	//Variables

	CDPath VCurrentPath;
	TEDROOMUInt8 VCurrentPathStep;
	TEDROOMUInt8 VSimError;


	//Pools



public:

	// CONSTRUCTOR

	EDROOMTopState (CAPathTracker &act );


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

	// SubEstado Hoja StandBy

	// ***********************************************************************



	TEDROOMTransId EDROOMStandByllegada();

	// ***********************************************************************

	// SubEstado Hoja TrackingPath

	// ***********************************************************************



	TEDROOMTransId EDROOMTrackingPathllegada();

};


#endif
