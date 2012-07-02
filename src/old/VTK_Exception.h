#ifndef VTK_Exception_H
#define VTK_Exception_H
class VTKDimensionError:public std::exception{
	public:
	virtual const char* what() const throw(){
		return "VTK File Format doesn't accept dimension different than 1,2,3.";
	}
};
#endif
