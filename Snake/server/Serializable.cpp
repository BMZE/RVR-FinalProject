#include "Serializable.h"


// Serializable::Serializable()
// {
    
// }

void Serializable::alloc_data(int32_t data_size)
{
    if ( _data != 0 )
    {
        free(_data);
    }

    _data = (char *) malloc(data_size);
    _size = data_size;
}

Serializable::~Serializable()
{
    if ( _data != 0 )
    {
        free(_data);
    }
}