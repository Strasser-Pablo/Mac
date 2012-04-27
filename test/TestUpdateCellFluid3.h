#include <cxxtest/TestSuite.h>
#include "../src/UpdateCellFluid3.h"
#include "../src/PhysvectorKeyOrder.h"
#include "../src/TableContainerList.h"
#include "../src/KeyTableMap.h"
#include "../src/MacWorld2.h"
#include "../src/MacCell.h"
#include "../src/Particle.h"
#include "../src/MacGetStagPos.h"
#include "../src/GetCellType.h"
#include <functional>
#define eps 1e-10
class Test_UpdateCellFluid : public CxxTest::TestSuite
{
	public:
	void testupdate()
	{
		typedef MacWorld2<KeyTableMap<Physvector<2,int>,MacCell<2,double,int>,PhysvectorKeyOrder<2,int > >, TableContainerList<Particle<Physvector<2,double> > >,2 > type_world;
		typedef MacGetStagPos<type_world>  type_stag;
		typedef GetCellType<type_world> type_getcelltype;
		typedef std::function<bool(Physvector<2,int>)> type_part_cond;
		PhysvectorKeyOrder<2,int> korder;
		
		KeyTableMap<Physvector<2,int>,MacCell<2,double,int>,PhysvectorKeyOrder<2,int > > grid(korder);
		TableContainerList<Particle<Physvector<2,double> > > list_part;
		
		Physvector<2,double> v;
		v.Set(USEELLIPSE,0.1,0.1);
		Particle<Physvector<2,double> > part(v);
		Particle<Physvector<2,double> >* ppart;
		list_part.push_back(part);
		ppart=&list_part.back();	
		
		v.Set(USEELLIPSE,2.1,0.1);
		Particle<Physvector<2,double> > part2(v);
		Particle<Physvector<2,double> >* ppart2;
		list_part.push_back(part2);
		ppart2=&list_part.back();	

		v.Set(USEELLIPSE,2.1,2.1);
		Particle<Physvector<2,double> > part3(v);
		Particle<Physvector<2,double> >* ppart3;
		list_part.push_back(part3);
		ppart3=&list_part.back();	

		v.Set(USEELLIPSE,0.1,2.1);
		Particle<Physvector<2,double> > part4(v);
		Particle<Physvector<2,double> >* ppart4;
		list_part.push_back(part4);
		ppart4=&list_part.back();	

		
		
		list<Particle<Physvector<2,double> >*> m_part_list_surf;
		m_part_list_surf.push_back(ppart);
		m_part_list_surf.push_back(ppart2);
		m_part_list_surf.push_back(ppart3);
		m_part_list_surf.push_back(ppart4);
		type_world world(grid,list_part);
		int i=world.GetNextId();
		world.m_list_surface[i].m_dir=type_world::dir_exterior::LEFT;
		world.m_list_surface[i].m_list=m_part_list_surf;
;
		Physvector<2,double> v_h;
		v_h.SetAll(1.0);
		type_stag m_stag(v_h);
		int m_air=0;
		int m_fluid=1;
		int m_boundary_air=2;
		int m_boundary_fluid=3;
		double m_rho_fluid=1000;
		double m_rho_air=1;
		double m_1_rho_fluid=0.001;
		double m_1_rho_air=1;
		double m_rho_inter=1000;
		double m_rho_inter_bound=1000;
		double m_1_rho_inter=0.001;
		double m_1_rho_inter_bound=0.001;
		type_getcelltype m_GetCellType(world,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		type_part_cond m_part_cond=[](Physvector<2,int> key){return false;};
		UpdateCellFluid3<type_world,type_stag ,type_getcelltype,type_part_cond> U(world,v_h,v_h,m_GetCellType,m_stag,m_part_cond);
		U.Update();
		Physvector<2,int> key;
		key.Set(1,1);
		key.Set(2,1);
		TS_ASSERT(m_GetCellType.GetIsFluidOnly(key));
		key.Set(1,0);
		key.Set(2,0);
		TS_ASSERT(m_GetCellType.GetIsBoundaryFluid(key));
		key.Set(1,0);
		key.Set(2,1);
		TS_ASSERT(m_GetCellType.GetIsBoundaryFluid(key));
	}
	
	void testConst()
	{	
		typedef KeyTableMap<Physvector<2,int>,MacCell<2,double,int>,PhysvectorKeyOrder<2,int > > type_table; 
		typedef TableContainerList<Particle<Physvector<2,double> > > type_list;
		typedef MacWorld2<type_table, type_list,2 > type_world;
		typedef MacGetStagPos<type_world>  type_stag;
		typedef GetCellType<type_world> type_getcelltype;
		typedef std::function<bool(Physvector<2,int>)> type_part_cond;
		PhysvectorKeyOrder<2,int> korder;
		
		type_table grid(korder);
		type_list list_part;
		type_world world(grid,list_part);
;
		Physvector<2,int> key;
		Physvector<2,double> speed;
		speed.Set(1,0);
		speed.Set(2,4);
		int fluid=0;

		for(int i=-3;i<=3;++i)
		{
			key.Set(1,i);
			key.Set(2,0);
			MacCell<2,double,int> m(speed,0,fluid,-1);
			m.SetConstSpeed(2,true);
			world.m_mac_grid[key]=m;
		}
		Physvector<2,double> v_h;
		v_h.SetAll(1.0);
		type_stag m_stag(v_h);
		int m_air=0;
		int m_fluid=1;
		int m_boundary_air=2;
		int m_boundary_fluid=3;
		double m_rho_fluid=1000;
		double m_rho_air=1;
		double m_1_rho_fluid=0.001;
		double m_1_rho_air=1;
		double m_rho_inter=1000;
		double m_rho_inter_bound=1000;
		double m_1_rho_inter=0.001;
		double m_1_rho_inter_bound=0.001;
		type_getcelltype m_GetCellType(world,m_fluid,m_boundary_fluid,m_air,m_boundary_air,m_rho_fluid,m_rho_air,m_1_rho_fluid,m_1_rho_air,m_rho_inter,m_1_rho_inter,m_rho_inter_bound,m_1_rho_inter_bound);
		type_part_cond m_part_cond=[](Physvector<2,int> key){return false;};
		UpdateCellFluid3<type_world,type_stag ,type_getcelltype,type_part_cond> U(world,v_h,v_h,m_GetCellType,m_stag,m_part_cond);
		U.PrepareConst();
		for(typename type_list::iterator it=world.m_particle_list.begin();it!=world.m_particle_list.end();++it)
		{
			Physvector<2,double> pos;
			(*it).GetPos(pos);
		}
	}
};
