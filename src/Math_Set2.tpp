template<int DIM,class TypeData>
void Math_Set2<DIM,TypeData>::InsertMax(Physvector<DIM,TypeData> & key)
{
	m_data[key.Get(1)].InsertMax(key,2);
}

template<int DIM,class TypeData>
void Math_Set2<DIM,TypeData>::InsertMin(Physvector<DIM,TypeData> & key)
{
	m_data[key.Get(1)].InsertMax(key,2);
}

template<int DIM,class TypeData>
template<int DIM2>
void Math_Set2<DIM,TypeData>::InsertMax(Physvector<DIM2,TypeData> & key,int i)
{
	m_data[key.Get(i)].InsertMax(key,i+1);
}

template<int DIM,class TypeData>
template<int DIM2>
void Math_Set2<DIM,TypeData>::InsertMin(Physvector<DIM2,TypeData> & key,int i)
{
	m_data[key.Get(i)].InsertMin(key,i+1);
}

template<int DIM,class TypeData>
Rel_Ensemble Math_Set2<DIM,TypeData>::IsIn(Math_Set2<DIM,TypeData> & B)
{
	cout<<"DIM "<<DIM<<endl;
	
	if(m_data.empty()&&B.m_data.empty())
	{
		return Rel_Ensemble::Both_Empty;
	}
	if(m_data.empty())
	{
		return Rel_Ensemble::A_Empty;
	}
	
	if(B.m_data.empty())
	{
		return Rel_Ensemble::B_Empty;
	}
	bool b_A_empty=false;
	bool b_B_empty=false;
	for(typename map<TypeData,Math_Set2<DIM-1,TypeData> >::iterator it=m_data.begin();it!=m_data.end();++it)
	{
		Rel_Ensemble res=it->second.IsIn(B.m_data[it->first]);
		switch(res)
		{
			case Rel_Ensemble::A_In_B:
				if(b_B_empty)
				{
					throw logic_error("Is surface closed?");
				}
				return Rel_Ensemble::A_In_B;
			break;
			case Rel_Ensemble::B_In_A:
				if(b_A_empty)
				{
					throw logic_error("Is surface closed?");
				}
				return Rel_Ensemble::B_In_A;
			break;
			case Rel_Ensemble::A_Empty:
				b_A_empty=true;
			break;
			case Rel_Ensemble::B_Empty:
				b_B_empty=true;
			break;
			case Rel_Ensemble::Both_Empty:
				b_A_empty=true;
				b_B_empty=true;
			break;
			case Rel_Ensemble::NONE:
				return Rel_Ensemble::NONE;
			break;
		}
	}
	//Return none because if it is in a set, one of the 1d set
	//will have return the 1d set.
	//if empty will have returned.
	//A none can be there if the projection whith the thirth component,
	//doesn't intersect. Only element of set A will be iterated.
	//And B will always be empty (in the element iterated.
	return Rel_Ensemble::NONE;
}

template<class TypeData>
Math_Set2<1,TypeData>::Math_Set2()
{
}

template<class TypeData>
void Math_Set2<1,TypeData>::InsertMin(Physvector<1,TypeData> & key)
{
	InsertMin(key,1);
}

template<class TypeData>
void Math_Set2<1,TypeData>::InsertMax(Physvector<1,TypeData> & key)
{
	InsertMax(key,1);
}

template<class TypeData>
template<int DIM2>
void Math_Set2<1,TypeData>::InsertMin(Physvector<DIM2,TypeData> & key,int i)
{
	m_inter_min.insert(key.Get(i));
}

template<class TypeData>
template<int DIM2>
void Math_Set2<1,TypeData>::InsertMax(Physvector<DIM2,TypeData> & key,int i)
{
	m_inter_max.insert(key.Get(i));
}

template<class TypeData>
Rel_Ensemble Math_Set2<1,TypeData>::IsIn(Math_Set2<1,TypeData> & B)
{
	//Test of empty case.
	if(m_inter_max.empty()&&m_inter_min.empty()&&B.m_inter_max.empty()&&B.m_inter_min.empty())
	{
		return Rel_Ensemble::Both_Empty;
	}
	if(m_inter_max.empty()&&m_inter_min.empty())
	{
		return Rel_Ensemble::A_Empty;
	}
	if(B.m_inter_max.empty()&&B.m_inter_min.empty())
	{
		return Rel_Ensemble::B_Empty;
	}
	//We use the function lower_bound to find greater or egual element in the other ensemble.
	iterator it_min=B.m_inter_min.begin();
	iterator it_max=B.m_inter_max.begin();
	iterator it_min_lb=m_inter_min.lower_bound(*it_min);
	iterator it_max_lb=m_inter_min.lower_bound(*it_max);
	//If it_min_lb and it_max_lb are not the same, it say that a element of the min table is between min and max
	//The shematic is:
	//		A		B
	//				it_min(min)
	//		it_min_lb(min)
	//
	//		(a max element is there because we canot traverse the boundary.)
	//				it_max(max)
	//
	//		it_max_lb(min)
	if(it_min_lb!=it_max_lb)
	{
		return Rel_Ensemble::A_In_B;
	}

	//Here only the case B_In_A and NONE need to be treated.
	//And it_min_lb==it_max_lb
	iterator it_min_up=m_inter_max.lower_bound(*it_min);

	//If it_min_up==m_inter_max.end(), it say that no max term is below to enclose the surface.
	//
	//The shematic is:
	//
	//		A			B
	//						
	//					it_min(min)		  _ 
	//								|
	//					it_max(max)		|  No max element in A in this region.
	//								|  So B_In_A impossible.
	//		it_min_lb(min)=it_max_lb		        | 
	//		                                                |
	//                                                              |
	//		it_min_up(max)==m_inter_max.end()              \ /
	//
	if(it_min_up==m_inter_max.end())
	{
		return Rel_Ensemble::NONE;
	}
	//If it_max_lb==m_inter_min.end() This say that because we know that we have a maximal below max in B.
	//That B_In_A.
	//The  shematic is:
	//
	//		A			B
	//
	//		(A min element muss be there because min and max are supposed paired)
	//              |
	//		| 			it_min(min)
	//              |  We enclose everything
	//              |
	//		|			it_max(max)
	//              |
	//		it_min_up(max)!=m_inter_max_end  Because we have not yet returned.
	//
	//		it_max_lb(min)==m_inter_min.end
	if(it_max_lb==m_inter_min.end())
	{
		return Rel_Ensemble::B_In_A;
	}
	//A this point we are sure that it_max_lb and it_min_up can be dereferenced.
	//We can test if *it_min_up is below or above.
	//
	// A Shematic is:
	//
	// 		A			B
	//		
	//		(A min is there to pair with the max below)
	//
	// 					it_min(min)
	//
	//
	//
	// 					it_max(max)
	//
	//
	//		it_min_up(max)
	//
	//		it_max_lb(min)
	if(*it_min_up<=*it_max_lb)
	{
		return Rel_Ensemble::B_In_A;
	}
	// This variable is needed to Solve a subtil case.
  	// We take the lower bound in B of a element in B.
  	iterator it2=B.m_inter_min.lower_bound(*it_max);
  	// If it2==m_inter_min.end() then we are in a case of séparation of the interacting zone.
  	//
  	// A shematic is:
  	//
  	// 		A			B
  	//
  	// 		  |      		it_min(min)
  	//                |	No min and max is there
  	//                |      So A is not in B An B is not in A.
  	// 		  |      		it_max(max)
  	//		it_max_lb(min)	
  	//
  	//
  	//		it_min_up(max)
  	//
  	// 					it2(min)==B.m_inter_min.end()
  	if(it2==B.m_inter_min.end())
  	{
  		return Rel_Ensemble::NONE;
  	}
  	// Now it2 can be dereferenced without problem.
  	//
  	// A shematic is:
  	//
  	// 		A			B
  	//
  	// 					it_min(min)
  	//
  	//
  	// 					it_max(max)
  	//
  	// 	   				it2(min)!=B.m_inter_min.end()
  	// 	   	it_max_lb(min)        	|
  	//                                      |
  	// 	   	it_min_up(max)          |
  	//                                      |
  	//                                      (a max should be there to pair)
  	if(*it2<=*it_max_lb)
  	{
  		return Rel_Ensemble::A_In_B;
  	}
  	// The remaining case.
  	// A shematic is:
  	//
  	// 		A			B
  	//
  	// 					it_min(min)
  	//
  	//
  	// 					it_max(max)
  	//
  	// 	   	it_max_lb(min)        	
  	//                                      Hier we are not in the interval. We are separated.
  	// 	   	it_min_up(max)          
  	//                                      
  	// 	   				it2(min)!=B.m_inter_min.end()
  	return Rel_Ensemble::NONE;
}
