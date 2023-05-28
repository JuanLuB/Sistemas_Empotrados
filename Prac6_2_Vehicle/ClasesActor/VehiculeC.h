#ifndef F_VehiculeC_h
#define F_VehiculeC_h

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



class EDROOMTopContext {

protected:

enum EDROOMVehiculeSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, SConfigPathPlanner, SMarkObstacle, SConfigOK, SConfigError, SConfigPathTracker, SStopTracking, SConfigAO, SObstacleDetected };


	friend class Vehicule;

	Vehicule &EDROOMcomponent;

	CEDROOMMessage * &Msg;

	CEDROOMMessage * &MsgBack;

	//Ports

	CEDROOMInterface & PathPlannerCtrl;
	CEDROOMInterface & PathTrackerCtrl;
	CEDROOMInterface & AvoidObstaclesSysCtrl;
	CEDROOMTimingInterface & Timer;

	enum edroomStateId{I, StartUp, VehiculeReady, SysRecovery, AvObstaclesConfigured, PathTrackerConfigured};

	enum IdTrans{Init, ConfigAvObstacles, ConfigAvObstacles_OK, ConfigAvObstacles_Error, ReStart, ConfigPathTracker, ConfigPathTracker_OK, ConfigPathTracker_Error, ConfigPathPlanner, ConfigPathPlanner_OK, ConfigPathPlanner_Error, ObstacleDetected,  EDROOMMEMORIA };

	//Constantes



	//Variables

	TEDROOMBool &VErrorInConfig;


	//Pool



	// CONSTRUCTORES

	EDROOMTopContext (Vehicule &act, TEDROOMBool & EDROOMpVarVErrorInConfig );

	EDROOMTopContext ( EDROOMTopContext &contex );

public:

	bool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

	void EDROOMNuevoMens () { EDROOMcomponent.EDROOMNewMsg(); }

	// Funciones Definidas por el usuario

	void	FStartUp();

	void	FRecovery();

	void	FAvObstaclesError();

	void	FConfigAvObstacles();

	void	FConfigPathTracker();

	void	FConfigPathPlanner();

	void	FProgNextStep();

	void	FHandleObstacle();

};

// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



class EDROOMTopState : public EDROOMTopContext {

protected:



	EDROOMTopContext::edroomStateId edroomCurrentState;

	EDROOMTopContext::edroomStateId edroomNextState;

	//Variables

	TEDROOMBool VErrorInConfig;


	//Pools



public:

	// CONSTRUCTOR

	EDROOMTopState (Vehicule &act );


	// EDROOMBehaviour**********************************************

	void EDROOMBehaviour();

	// Inicio**********************************************

	void EDROOMInicio();

	// ***********************************************************************

	// SubEstado Inicial 

	// ***********************************************************************



	TEDROOMTransId EDROOMIllegada();

	// ***********************************************************************

	// SubEstado Hoja StartUp

	// ***********************************************************************



	TEDROOMTransId EDROOMStartUpllegada();

	// ***********************************************************************

	// SubEstado Hoja VehiculeReady

	// ***********************************************************************



	TEDROOMTransId EDROOMVehiculeReadyllegada();

	// ***********************************************************************

	// SubEstado Hoja SysRecovery

	// ***********************************************************************



	TEDROOMTransId EDROOMSysRecoveryllegada();

	// ***********************************************************************

	// SubEstado Hoja AvObstaclesConfigured

	// ***********************************************************************



	TEDROOMTransId EDROOMAvObstaclesConfiguredllegada();

	// ***********************************************************************

	// SubEstado Hoja PathTrackerConfigured

	// ***********************************************************************



	TEDROOMTransId EDROOMPathTrackerConfiguredllegada();

};


#endif
