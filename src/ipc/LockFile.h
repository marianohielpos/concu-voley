//
// Created by Mariano Hielpos on 9/19/17.
//

#ifndef CONCU_VOLEY_LOCKFILE_H
#define CONCU_VOLEY_LOCKFILE_H


class LockFile {

private:
    struct flock fl;
    int fd;
    std::string nombre;

public:
    LockFile ( const std::string nombre );
    ~LockFile();

    int tomarLock ();
    int liberarLock ();
    ssize_t escribir ( const void* buffer,const ssize_t buffsize ) const;
};


#endif //CONCU_VOLEY_LOCKFILE_H
