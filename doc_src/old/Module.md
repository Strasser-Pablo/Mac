Module
======

Module

\dot digraph ModuleDependance
{
	GR_JetDEau [ label="Jet D'Eau" URL="\ref GR_JetDEau"];
	GR_Convection [ label="Convection" URL="\ref GR_Convection"];
	GR_Extrapolate [ label="Extrapolate" URL="\ref GR_Extrapolate"];
	GR_Gravity [ label="Gravity" URL="\ref GR_Gravity"];
	GR_Mac_Initialize [ label="Initialize" URL="\ref GR_Mac_Initialize"];
	GR_Move_Particle [ label="Move Particle" URL="\ref GR_Move_Particle"];
	GR_Output [ label="Output" URL="\ref GR_Output"];
	GR_Solve_Pressure [ label="Solve Pressure" URL="\ref GR_Solve_Pressure"];
	GR_Viscosity [ label="Viscosity" URL="\ref GR_Viscosity"];
	GR_World [ label="World" URL="\ref GR_World"];

	GR_GetCellType [ label="Get Cell Type" URL="\ref GR_Get_Cell_Type"];
	GR_GetSpeed [ label="Get Speed" URL="\ref GR_GetSpeed"];

	GR_Cell [ label="Cell" URL="\ref GR_Cell"];
	GR_Particle [ label="Particle" URL="\ref GR_Particle"];
	GR_Container_List [ label="Container List" URL="\ref GR_Container_List"];
	GR_Container_Map [ label="Container Map" URL="\ref GR_Container_Map"];

	GR_Initial_Layer [ label="Initial Layer" URL="\ref GR_Initial_Layer"];
	GR_Update_Fluid [ label="Update Fluid" URL="\ref GR_Update_Fluid"];
	GR_Update_Delete [ label="Update Delete" URL="\ref GR_Update_Delete"];
	GR_Update_Topology [ label="Update Topology" URL="\ref GR_Update_Topology"];

	GR_ODE_Solver [ label="ODE Solver" URL="\ref GR_ODE_Solver"];
	GR_Linear_Solver [ label="Linear Solver" URL="\ref GR_Linear_Solver"];
	GR_Interpolation [ label="Interpolation" URL="\ref GR_Interpolation"];

	GR_JetDEau -> GR_Convection;
	GR_JetDEau -> GR_Extrapolate;
	GR_JetDEau -> GR_Gravity;
	GR_JetDEau -> GR_Mac_Initialize;
	GR_JetDEau -> GR_Move_Particle;
	GR_JetDEau -> GR_Output;
	GR_JetDEau -> GR_Solve_Pressure;
	GR_JetDEau -> GR_Viscosity;
	GR_JetDEau -> GR_World;

	GR_Convection -> GR_GetCellType;
	GR_Convection -> GR_GetSpeed;
	GR_Convection -> GR_World;
	GR_Convection -> GR_ODE_Solver [style=dotted];

	GR_Extrapolate -> GR_World;
	GR_Extrapolate -> GR_GetCellType;

	GR_Gravity -> GR_World;
	GR_Gravity -> GR_GetCellType;

	GR_Mac_Initialize -> GR_World;
	GR_Mac_Initialize -> GR_GetCellType;

	GR_Move_Particle -> GR_World;
	GR_Move_Particle -> GR_GetSpeed;
	GR_Move_Particle -> GR_ODE_Solver;

	GR_Output -> GR_World;

	GR_Viscosity -> GR_World;
	GR_Viscosity -> GR_GetCellType;

	GR_World -> GR_Cell;
	GR_World -> GR_Particle;
	GR_World -> GR_Container_List;
	GR_World -> GR_Container_Map;

	GR_Solve_Pressure -> GR_World;
	GR_Solve_Pressure -> GR_GetCellType;
	GR_Solve_Pressure -> GR_Linear_Solver;

	GR_Mac_Initialize -> GR_Extrapolate;
	GR_Mac_Initialize -> GR_Update_Delete;
	GR_Mac_Initialize -> GR_Update_Topology;
	GR_Mac_Initialize -> GR_Update_Fluid;
	GR_Mac_Initialize -> GR_Initial_Layer;

	GR_GetSpeed -> GR_Interpolation;

}
\enddot
