#ifndef F_VehicleC_h
#define F_VehicleC_h

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



class EDROOMTopContext {

protected:

enum EDROOMVehicleSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, SConfigPathPlanner, SMarkObstacle, SNewTargetLocation, SStartPlanning, SConfigOK, SConfigError, SConfigPathTracker, SStopTracking, SStartTracking, SConfigAO, SStart, SObstacleDetected };


	friend class Vehicle;

	Vehicle &EDROOMcomponent;

	CEDROOMMessage * &Msg;

	CEDROOMMessage * &MsgBack;

	//Ports

	CEDROOMInterface & PathPlannerCtrl;
	CEDROOMInterface & PathTrackerCtrl;
	CEDROOMInterface & AvoidObstaclesSysCtrl;
	CEDROOMTimingInterface & Timer;

	enum edroomStateId{I, StartUp, VehicleReady, SysRecovery, AvObstaclesConfigured, PathTrackerConfigured};

	enum IdTrans{Init, ConfigAvObstacles, ConfigAvObstacles_OK, ConfigAvObstacles_Error, ReStart, ConfigPathTracker, ConfigPathTracker_OK, ConfigPathTracker_Error, ConfigPathPlanner, ConfigPathPlanner_OK, ConfigPathPlanner_Error, ObstacleDetected,  EDROOMMEMORIA };

	//Constantes



	//Variables

	TEDROOMBool &VErrorInConfig;
	CDLocation &VTargetLocation;


	//Pool

	class CEDROOMPOOLCDLocation:public CEDROOMProtectedMemoryPool {
		public:
		CEDROOMPOOLCDLocation(TEDROOMUInt32 elemCount,CDLocation *pMem, TEDROOMBool *pMarks);
		CDLocation	* AllocData();
	};
	CEDROOMPOOLCDLocation	& EDROOMPoolCDLocation;


	// CONSTRUCTORES

	EDROOMTopContext (Vehicle &act, TEDROOMBool & EDROOMpVarVErrorInConfig, CDLocation & EDROOMpVarVTargetLocation, CEDROOMPOOLCDLocation & EDROOMpPoolCDLocation );

	EDROOMTopContext ( EDROOMTopContext &contex );

public:

	bool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

	void EDROOMNuevoMens () { EDROOMcomponent.EDROOMNewMsg(); }

	// Funciones Definidas por el usuario

	void	FAvObstaclesError();

	void	FConfigAvObstacles();

	void	FConfigPathPlanner();

	void	FConfigPathTracker();

	void	FHandleObstacle();

	void	FPathPlannerError();

	void	FPathTrackerError();

	void	FProgNextConfig();

	void	FRecovery();

	void	FStart();

	void	FStartUp();

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
	CDLocation VTargetLocation;


	//Pools

	CEDROOMPOOLCDLocation	EDROOMPoolCDLocation;


public:

	// CONSTRUCTOR

	EDROOMTopState (Vehicle &act, CEDROOMMemory *pEDROOMMemory  );


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

	// SubEstado Hoja VehicleReady

	// ***********************************************************************



	TEDROOMTransId EDROOMVehicleReadyllegada();

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
