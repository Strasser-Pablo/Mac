#ifndef Algorithms_Solve_Pressure_Pyamg_H
#define Algorithms_Solve_Pressure_Pyamg_H

#include <boost/python.hpp>
#include <cmath>
#include <map>
#include <deque>
#include <sys/times.h>
#include <functional>
#include <exception>
#include <numpy/arrayobject.h>
#include <fstream>

namespace with_boost_python
{
using namespace std;
using namespace boost::python;

function<void (npy_intp* row,npy_intp* column,double* data)> global_array_value;
function<int ()> global_array_nnz_size;
function<int ()> global_array_length_size;

function<void (const double* result)> global_array_apply_result;

function<void (double* guess)> global_array_guess_result;

function<void (double* b)> global_array_rhs;

struct array_list_for_matrice
{
	object row;
	object col;
	object data;
};

void Apply_Result(numeric::array res)
{
	cout<<"appl beg"<<endl;
	PyObject* o_res = PyArray_FROM_OTF(res.ptr(), NPY_DOUBLE, NPY_IN_ARRAY);
	object temp(handle<>(o_res));
	const double* result = static_cast<const double*>(PyArray_DATA(o_res));
	global_array_apply_result(result);
	cout<<"appl end"<<endl;
};

object create_rhs()
{
	cout<<"rhs beg"<<endl;
	npy_intp dim_b[1];
  	dim_b[0]=global_array_length_size();

	PyObject* o_b= PyArray_SimpleNew(1,dim_b,NPY_DOUBLE);
	double* b = static_cast<double*>(PyArray_DATA(o_b));
	global_array_rhs(b);
	cout<<"rhs end"<<endl;
	return object(handle<>(o_b));
};


object create_guess()
{
	cout<<"guess beg"<<endl;
	npy_intp dim[1];
  	dim[0]=global_array_length_size();

	PyObject* o= PyArray_SimpleNew(1,dim,NPY_DOUBLE);
	double* guess = static_cast<double*>(PyArray_DATA(o));
	global_array_rhs(guess);
	cout<<"guess end"<<endl;
	return object(handle<>(o));
};

array_list_for_matrice f_create_matrice_vector()
{
  cout<<"matrice beg"<<endl;
  npy_intp dim_row[1];
  dim_row[0]=global_array_nnz_size();

  npy_intp dim_col[1];
  dim_col[0]=global_array_nnz_size();

  npy_intp dim_data[1];
  dim_data[0]=global_array_nnz_size();

  array_list_for_matrice s;
  PyObject* o_row= PyArray_SimpleNew(1,dim_row,NPY_INTP);
  npy_intp* res_row = static_cast<npy_intp*>(PyArray_DATA(o_row));

  PyObject* o_col= PyArray_SimpleNew(1,dim_col,NPY_INTP);
  npy_intp* res_col = static_cast<npy_intp*>(PyArray_DATA(o_col));

  PyObject* o_data= PyArray_SimpleNew(1,dim_data,NPY_DOUBLE);
  double* res_data = static_cast<double*>(PyArray_DATA(o_data));

  global_array_value(res_row,res_col,res_data);

  s.row=object(handle<>(o_row));
  s.col=object(handle<>(o_col));
  s.data=object(handle<>(o_data));
  cout<<"matrice end"<<endl;
  return s;
};


BOOST_PYTHON_MODULE(array)
{
  // tell Boost::Python under what name the array is known
  numeric::array::set_module_and_type("numpy", "ndarray");
  def("Apply_Result",Apply_Result);
  def("create_rhs",create_rhs);
  def("create_guess",create_guess);
  def("f_create_matrice_vector",f_create_matrice_vector);
  class_<array_list_for_matrice>("array_list_for_matrice")
	  .def_readwrite("row",&array_list_for_matrice::row)
	  .def_readwrite("col",&array_list_for_matrice::col)
	  .def_readwrite("data",&array_list_for_matrice::data);

  // initialize the Numpy C API
  import_array();
}

template <typename DataType,typename Policy>
class Algorithms_Solve_Pressure_Pyamg: public Policy
{
	using Policy::Get_Divergence;
	using Policy::Get_Gradiant;
	using Policy::Get_Is_Von_Neumann_Boundary;
	using Policy::Get_Pressure_If_Correction;
	typedef typename DataType::type_data_struct type_data;
	typedef typename type_data::type_Data_Grid type_grid;
	typedef typename type_grid::type_data type_data_data;
	typedef typename type_data_data::type_pressure::type_pressure type_pressure;
	typedef typename type_grid::type_offset type_neigh;
	typedef typename type_data_data::type_speed type_speed;
	typedef typename type_speed::type_data_value type_speed_value;
	typedef typename type_speed::type_speed::type_vector type_speed_vector;
	typedef typename type_grid::type_spacing_vector type_spacing_vector;
	typedef typename type_grid::iterator iterator;
	typedef typename type_data::type_Data_Timing type_Data_Timing;
	typedef typename type_Data_Timing::type_Time_Type type_Time_Type;
	static const int type_dim=type_speed::type_dim;
	type_grid& m_grid;
	const type_spacing_vector& m_1_h;
	const type_Time_Type& m_dt;
	bool bpres;
	public:
	Algorithms_Solve_Pressure_Pyamg(DataType data,const Policy& pol) : Policy(pol),m_grid(data.m_data.GetGridData()),m_1_h(data.m_data.GetGridData().m_h.GetRef_Inv()),m_dt(data.m_data.GetTimingData().m_dt),bpres(true)
	{
		Py_Initialize();
		initarray();
		PyRun_SimpleString("from scipy.sparse import *");
		PyRun_SimpleString("from scipy import *");
		PyRun_SimpleString("from scipy.linalg import *");
		PyRun_SimpleString("from pyamg import *");
		PyRun_SimpleString("from numpy import *");

		PyRun_SimpleString("import array");
	}
	void Init_Iteration()
	{
		struct tms t1;
		struct tms t2;
		double conv=double(sysconf(_SC_CLK_TCK));
		long t_deb=times(&t1);

		//First pass give number
		int lay=0;
		int n=0;
		bpres=true;
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().CellType_GetRef().GetIsInDomain())
			{
				if(it.data().Id_Cell_GetRef().GetIsLayerEmpty())
				{
					it.data().Pressure_GetRef().Pressure_Set(type_pressure(0));
					bpres=false;
				}
				it.data().Id_Cell_GetRef().SetLayer(lay);
				++lay;
				++n;
				for(int i=1;i<=type_dim;++i)
				{
					for(int s=-1;s<=1;s+=2)
					{
						type_neigh neigh=it.data().GetNeighbour(i,s);
						//Test if we have a neighbour.
						if(neigh.IsValid())
						{
							if(this->Get_Is_Von_Neumann_Boundary(it.data(),i,s))
							{
							}
							//NeighBour is in domain, assign a number if needed and add the matrice element to calculate the derivatif.
							else if(neigh.CellType_GetRef().GetIsInDomain())
							{
								++n;
							}
						}
					}
				}
			}
			else
			{
				it.data().Id_Cell_GetRef().SetLayerEmpty();
			}
		}

		global_array_nnz_size=[n]()
		{
			return n;
		};

		global_array_length_size=[lay]()
		{
			return lay;
		};


		global_array_value=[this](npy_intp* row,npy_intp* col,double* data)
		{
			int iel=0;
			for(iterator it=this->m_grid.begin();it!=this->m_grid.end();++it)
			{
				if(it.data().CellType_GetRef().GetIsInDomain())
				{
					int row_cur=it.data().Id_Cell_GetRef().GetLayer();
					double temp_diag_value=0;
					for(int i=1;i<=type_dim;++i)
					{
						for(int s=-1;s<=1;s+=2)
						{
							temp_diag_value+=pow(this->m_1_h.Get(i),2);
							int col_cur;
							type_neigh neigh=it.data().GetNeighbour(i,s);
							//Test if we have a neighbour.
							if(neigh.IsValid())
							{
								if(this->Get_Is_Von_Neumann_Boundary(it.data(),i,s))
								{
									temp_diag_value-=pow(this->m_1_h.Get(i),2);
								}
								//NeighBour is in domain, assign a number if needed and add the matrice element to calculate the derivatif.
								else if(neigh.CellType_GetRef().GetIsInDomain())
								{
									col_cur=neigh.Id_Cell_GetRef().GetLayer();
									row[iel]=row_cur;
									col[iel]=col_cur;
									data[iel]=-pow(this->m_1_h.Get(i),2);
									++iel;
								}
							}
						}
					}
					row[iel]=row_cur;
					col[iel]=row_cur;
					data[iel]=temp_diag_value;
					++iel;
				}
			}
		};

		PyRun_SimpleString("s=array.f_create_matrice_vector()");
		PyRun_SimpleString("A=csr_matrix((s.data,(s.row,s.col)))");

		PyRun_SimpleString("ml = smoothed_aggregation_solver(A,strength=('symmetric', {'theta': 0.0}),\n"
				"smooth=\"jacobi\",Bimprove=[None],aggregate=\"standard\",\n"
				"presmoother=('block_gauss_seidel', {'sweep': 'symmetric', 'iterations': 1}),\n"
				"postsmoother=('block_gauss_seidel', {'sweep': 'symmetric', 'iterations': 1}),\n"
				"max_coarse=100,\n"
				"coarse_solver=\"pinv\")");

		cout<<"aft "<<endl;
		long t_end=times(&t2);
	/*	cout<<"real Pressure_Prepare+Factorize "<<(t_end-t_deb)/conv<<endl;
		cout<<"real Pressure_Prepare+Factorize "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
		cout<<"nnz "<<global_array_nnz_size()<<endl;
		cout<<"n "<<global_array_length_size()<<endl;
		
		PyRun_SimpleString("from pyamg.gallery import *");
		PyRun_SimpleString("A2 = poisson((500,500), format='csr')");
		cout<<"bef "<<endl;
		PyRun_SimpleString("ml2 = smoothed_aggregation_solver(A2,strength=('symmetric', {'theta': 0.0}),\n"
				"smooth=\"jacobi\",Bimprove=[None],aggregate=\"standard\",\n"
				"presmoother=('block_gauss_seidel', {'sweep': 'symmetric', 'iterations': 1}),\n"
				"postsmoother=('block_gauss_seidel', {'sweep': 'symmetric', 'iterations': 1}),\n"
				"coarse_solver=\"pinv\")");
		cout<<"bef solve "<<endl;*/
		
	}
	void End_Iteration()
	{
	}
	void Divergence_Projection()
	{
		cout<<"bef "<<endl;

		double conv=double(sysconf(_SC_CLK_TCK));

/*
		struct tms tb1;
		struct tms tb2;
		long t_debb=times(&tb1);
		PyRun_SimpleString("x2 = ml2.solve(b2, tol=1e-12)");
		long t_endb=times(&tb2);
		cout<<"real solveonly b"<<(t_endb-t_debb)/conv<<endl;
		cout<<"user solveonly b"<<(tb2.tms_utime-tb1.tms_utime)/conv<<endl;


		struct tms tc1;
		struct tms tc2;
		long t_debc=times(&tc1);
		PyRun_SimpleString("x3 = ml2.solve(b2, tol=1e-12)");
		long t_endc=times(&tc2);
		cout<<"real solveonly c"<<(t_endc-t_debc)/conv<<endl;
		cout<<"user solveonly c"<<(tc2.tms_utime-tc1.tms_utime)/conv<<endl;
*/

		struct tms t1;
		struct tms t2;
		long t_deb=times(&t1);

		global_array_rhs=[this](double* b)
		{
			double m_1_dt=1/m_dt;
			for(iterator it=this->m_grid.begin();it!=this->m_grid.end();++it)
			{
				int lay_cur;
				if(it.data().CellType_GetRef().GetIsInDomain())
				{
					lay_cur=it.data().Id_Cell_GetRef().GetLayer();
					b[lay_cur]=-this->Get_Divergence(it.data()).Get()*m_1_dt;
				}
			}
		};

		global_array_guess_result=[this](double* guess)
		{
			// Set the pressure of cell from the result.
			for(iterator it=this->m_grid.begin();it!=this->m_grid.end();++it)
			{
				int lay_cur;
				if(it.data().CellType_GetRef().GetIsInDomain())
				{
					lay_cur=it.data().Id_Cell_GetRef().GetLayer();
					guess[lay_cur]=it.data().Pressure_GetRef().Pressure_Get().Get();
				}
			}
		};

		global_array_apply_result=[this](const double* result)
		{
			// Set the pressure of cell from the result.
			for(iterator it=this->m_grid.begin();it!=this->m_grid.end();++it)
			{
				int lay_cur;
				if(it.data().CellType_GetRef().GetIsInDomain())
				{
					lay_cur=it.data().Id_Cell_GetRef().GetLayer();
					it.data().Pressure_GetRef().Pressure_Set(type_pressure(result[lay_cur]));
				}
				else
				{
					it.data().Pressure_GetRef().Pressure_Set(type_pressure(0));
				}
			}
		};

		PyRun_SimpleString("b=array.create_rhs()");
		PyRun_SimpleString("x0=array.create_guess()");
		cout<<"bef solve "<<endl;
		struct tms ta1;
		struct tms ta2;
		long t_deba=times(&ta1);
		PyRun_SimpleString("x = ml.solve(b, tol=1e-12)");
		long t_enda=times(&ta2);
		cout<<"real solveonly "<<(t_enda-t_deba)/conv<<endl;
		cout<<"user solveonly "<<(ta2.tms_utime-ta1.tms_utime)/conv<<endl;
		cout<<"aft solve "<<endl;
	//	PyRun_SimpleString("print max(abs(x-x0))");
		/*
		struct tms tb1;
		struct tms tb2;
		long t_debb=times(&tb1);
		PyRun_SimpleString("b2 = rand(A.shape[0])");
		PyRun_SimpleString("x2 = ml.solve(b2, tol=1e-12)");
		long t_endb=times(&tb2);
		cout<<"real solveonly b"<<(t_endb-t_debb)/conv<<endl;
		cout<<"user solveonly b"<<(tb2.tms_utime-tb1.tms_utime)/conv<<endl;

		PyRun_SimpleString("print max(abs(A*x2-b2))");

		struct tms tc1;
		struct tms tc2;
		long t_debc=times(&tc1);
		PyRun_SimpleString("b3 = rand(A.shape[0])");
		PyRun_SimpleString("x3 = ml.solve(b3, tol=1e-12)");
		long t_endc=times(&tc2);
		cout<<"real solveonly c"<<(t_endc-t_debc)/conv<<endl;
		cout<<"user solveonly c"<<(tc2.tms_utime-tc1.tms_utime)/conv<<endl;

		PyRun_SimpleString("print max(abs(A*x3-b3))");
		*/
		PyRun_SimpleString("array.Apply_Result(x)");
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			for(int i=1;i<=type_dim;++i)
			{
				if(Get_Pressure_If_Correction(it.data(),i))
				{
					it.data().Speed_GetRef().Set(i,it.data().Speed_GetRef().Get(i)-Get_Gradiant(it.data(),i)*m_dt);
				}
			}
		}
		for(iterator it=m_grid.begin();it!=m_grid.end();++it)
		{
			if(it.data().CellType_GetRef().GetIsInDomain())
			{
				type_speed_value div=Get_Divergence(it.data()).Get();
				if(abs(div)>0.00000001)
				{
					cout<<"key "<<it.key()<<endl;
					cout<<"div "<<Get_Divergence(it.data()).Get()<<endl;
				}
			}
		}
		long t_end=times(&t2);
		cout<<"real Pressure_Solve "<<(t_end-t_deb)/conv<<endl;
		cout<<"real Pressure_Solve "<<(t2.tms_utime-t1.tms_utime)/conv<<endl;
		cout<<"nnz "<<global_array_nnz_size()<<endl;
		cout<<"n "<<global_array_length_size()<<endl;
		static fstream m_out("stat_pres_tim.txt",fstream::out);
		if(bpres)
		{
			m_out<<"no pres"<<endl;
		}
		else
		{
			m_out<<"pres"<<endl;
		}
		m_out<<((t2.tms_utime-t1.tms_utime)/conv)<<" "<<global_array_nnz_size()<<" "<<global_array_length_size()<<endl;



	}
};
}
using with_boost_python::Algorithms_Solve_Pressure_Pyamg;

#endif
