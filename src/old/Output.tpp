template <class OutputMethod,int type_dim>
Output<OutputMethod,type_dim>::Output(OutputMethod& outmethod,double t,int &i,streampos &spos,bool with_part):m_out_meth(outmethod),m_t(t),m_i(i),m_spos(spos),b_with_part(with_part)
{

}

template <class OutputMethod,int type_dim>
void Output<OutputMethod,type_dim>::Calculate()
{
	stringstream ss;
	ss<<m_i;
	string str=string("out")+ss.str();
	for(int i=1;i<=type_dim;++i)
	{
		stringstream ss2;
		ss2<<i;
		string str2=str+string("_")+ss2.str()+string(".vtu");
		m_out_meth.Output(str2.c_str(),i);
	}
		stringstream ss3;
		ss3<<type_dim+1;
		string str2=str+string("_")+ss3.str()+string(".vtu");
		m_out_meth.OutputPressure(str2.c_str());
		stringstream ss4;
		ss4<<type_dim+2;
		string str3=str+string("_")+ss4.str()+string(".vtu");
		if(b_with_part)
		{
			m_out_meth.OutputParticle(str3.c_str());
		}
		int mod=0;
		if(b_with_part)
		{
			mod=1;
		}
	for(int i=1;i<=type_dim+1+mod;++i)
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

template <class OutputMethod,int type_dim>
void Output<OutputMethod,type_dim>::SetUp()
{	
	m_out.open("animation.pvd",ios::out);
	m_out<<"<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\">"<<endl;
	m_out<<"<Collection>"<<endl;
}

template <class OutputMethod,int type_dim>
void Output<OutputMethod,type_dim>::Load()
{
	m_out.open("animation.pvd",fstream::out | fstream::in);
	m_out.seekp(m_spos);
}
