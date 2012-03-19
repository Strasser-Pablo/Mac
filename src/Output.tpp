template <class TypeWorld,class TypeGetStagSpeedPos>
Output<TypeWorld,TypeGetStagSpeedPos>::Output(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,double & t,type_cell fluid,int &i,streampos &spos):m_out_speed(world,stag,h,fluid),m_t(t),m_i(i),m_spos(spos)
{

}

template <class TypeWorld,class TypeGetStagSpeedPos>
void Output<TypeWorld,TypeGetStagSpeedPos>::Calculate()
{
	stringstream ss;
	ss<<m_i;
	string str=string("out")+ss.str();
	for(int i=1;i<=type_dim;++i)
	{
		stringstream ss2;
		ss2<<i;
		string str2=str+string("_")+ss2.str()+string(".vtu");
		//fstream p(str2.c_str(),fstream::out);
		m_out_speed.Output(str2.c_str(),i);
	}
		stringstream ss3;
		ss3<<type_dim+1;
		string str2=str+string("_")+ss3.str()+string(".vtu");
		//fstream p(str2.c_str(),fstream::out);
		m_out_speed.OutputPressure(str2.c_str());
		stringstream ss4;
		ss4<<type_dim+2;
		string str3=str+string("_")+ss4.str()+string(".vtu");
		//fstream p2(str3.c_str(),fstream::out);
		m_out_speed.OutputParticle(str3.c_str());
	for(int i=1;i<=type_dim+2;++i)
	{
		m_out<<" <DataSet timestep=\""<<m_t<<"\" group=\"\" part=\""<<i<<"\" file=\""<<str<<"_"<<i<<".vtu\" />"<<endl;
	}
	m_spos=m_out.tellp();
	m_out<<"</Collection>"<<endl;
	m_out<<"</VTKFile>"<<endl;
	m_out.seekp(m_spos);
	cout<<"mspos "<<m_spos<<endl;
	cout<<"output "<<m_i<<endl;
	++m_i;
}

template <class TypeWorld,class TypeGetStagSpeedPos>
void Output<TypeWorld,TypeGetStagSpeedPos>::SetUp()
{	
	m_out.open("animation.pvd",ios::out);
	m_out<<"<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
	m_out<<"<Collection>"<<endl;
}

template <class TypeWorld,class TypeGetStagSpeedPos>
void Output<TypeWorld,TypeGetStagSpeedPos>::Load()
{
	m_out.open("animation.pvd",fstream::out | fstream::in);
	m_out.seekp(m_spos);
}
