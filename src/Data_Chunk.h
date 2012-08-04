#ifndef Data_Chunk_H
#define Data_Chunk_H

template <class ... Chunk>
class Data_Chunk : public Chunk...
{
};
#endif
