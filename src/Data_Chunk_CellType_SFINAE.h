#ifndef Data_Chunk_CellType_SFINAE_H
#define Data_Chunk_CellType_SFINAE_H

template <typename Base,typename Variable,typename Dummy=void>
struct Data_Chunk_CellType_void_SFINAE
{
	typedef void type2;
};

template <typename Base,typename Variable>
struct Data_Chunk_CellType_void_SFINAE<Base,Variable,typename Base::type_chunk_cell_type_exist>
{
	typedef void type;
};

template <typename Base,typename Variable,typename Dummy=void>
struct Data_Chunk_CellType_void_Not_SFINAE
{
};

template <typename Base,typename Variable>
struct Data_Chunk_CellType_void_Not_SFINAE<Base,Variable,typename Data_Chunk_CellType_void_SFINAE<Base,Variable>::type2>
{
	typedef void type;
};
#endif
