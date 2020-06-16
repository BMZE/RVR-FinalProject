#ifndef _H_Serializable_H_
#define _H_Serializable_H_

#include <stdlib.h>


class Serializable
{
public:

    Serializable():_size(0), _data(nullptr){};

    virtual ~Serializable();

    /**
     *  Genera la representación binaria de la clase. Debe inicializar
     *  el buffer interno con la función helper alloc_data.
     */
    virtual void to_bin() = 0;

    /**
     *  Esta función recibe un objeto serializado y lo reconstruye.
     *    @param data representación binaria del objeto
     *    @return 0 si éxito -1 en caso contrario
     */
    virtual int from_bin(char * data) = 0;

    /**
     *  Devuelve un puntero al buffer interno con la representación del objeto.
     *  Debe inicializarse previamente via Serializable::to_bin()
     *    @return objeto serializado
     */
    inline char * data() { return _data; }

    /**
     *  @return tamaño del objeto serializado
     */
    inline int32_t size() { return _size; };

protected:

    /**
     *  Reserva memoria para el buffer del objeto serializado
     */
    void alloc_data(int32_t data_size);

    int32_t _size;

    char *  _data;
};
#endif