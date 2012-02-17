template <class TypeWorld,class TypeGetStagSpeedPos>
Output<TypeWorld,TypeGetStagSpeedPos>::Output(TypeWorld &world,TypeGetStagSpeedPos & stag,const Physvector<type_dim,type_data>& h,double & t,type_cell fluid):m_out_speed(world,stag,h,fluid),m_i(0),m_t(t)
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
		string str2=str+string("_4.vtu");
		//fstream p(str2.c_str(),fstream::out);
		m_out_speed.OutputPressure(str2.c_str());
		string str3=str+string("_5.vtu");
		//fstream p2(str3.c_str(),fstream::out);
		m_out_speed.OutputParticle(str3.c_str());
		static fstream out("animation.pvd",fstream::out) ;
		if(m_i==0)
		{
			out<<"<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
			out<<"<Collection>"<<endl;
		}
		
	out<<" <DataSet timestep=\""<<m_t<<"\" group=\"\" part=\"1\" file=\""<<str<<"_1.vtu\" />"<<endl;
	out<<" <DataSet timestep=\""<<m_t<<"\" group=\"\" part=\"2\" file=\""<<str<<"_2.vtu\" />"<<endl;
	out<<" <DataSet timestep=\""<<m_t<<"\" group=\"\" part=\"3\" file=\""<<str<<"_3.vtu\" />"<<endl;
	out<<" <DataSet timestep=\""<<m_t<<"\" group=\"\" part=\"4\" file=\""<<str<<"_4.vtu\" />"<<endl;
	out<<" <DataSet timestep=\""<<m_t<<"\" group=\"\" part=\"5\" file=\""<<str<<"_5.vtu\" />"<<endl;
	streampos pos;
	pos=out.tellp();
	out<<"</Collection>"<<endl;
	out<<"</VTKFile>"<<endl;
	out.seekp(pos);
	cout<<"output "<<m_i<<endl;
	++m_i;
}