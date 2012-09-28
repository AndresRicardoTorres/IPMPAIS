#ifndef CALIFICACION_H
#define CALIFICACION_H


class Calificacion
{
    public:
        Calificacion();
        virtual ~Calificacion();
        unsigned int getAnno() { return anno; }
        void setAnno(unsigned int val) { anno = val; }
        const char* getCodigoEstudiante() { return codigoEstudiante; }
        void setCodigoEstudiante(const char* val) { codigoEstudiante = val; }
        const char* getCodigoOriginalAsignatura() { return codigoOriginalAsignatura; }
        void setCodigoOriginalAsignatura(const char* val) { codigoOriginalAsignatura = val; }
        const char* getCodigoAsignatura() { return codigoAsignatura; }
        void setCodigoAsignatura(const char* val) { codigoAsignatura = val; }
        const char* getTipoCursado() { return tipoCursado; }
        void setTipoCursado(const char* val) { tipoCursado = val; }
        int getTipoNumericoCursado() { return tipoNumericoCursado; }
        void setTipoNumericoCursado(int val) { tipoNumericoCursado = val; }
        unsigned int getCreditos() { return creditos; }
        void setCreditos(unsigned int val) { creditos = val; }
        const char* getCalificacion() { return calificacion; }
        void setCalificacion(const char* val) { calificacion = val; }
        const char* getPeriodo() { return periodo; }
        void setPeriodo(const char* val) { periodo = val; }
        const char* getNombreAsignatura() { return nombreAsignatura; }
        void setNombreAsignatura(const char* val) { nombreAsignatura = val; }
        double getCalificacionReal() { return calificacionReal; }
        void setCalificacionReal(double val) { calificacionReal = val; }
    protected:
    private:
        unsigned int anno;
        const char* codigoEstudiante;
        const char* codigoOriginalAsignatura;
        const char* codigoAsignatura;
        const char* nombreAsignatura;
        const char* tipoCursado;
        int tipoNumericoCursado;
        unsigned int creditos;
        const char* calificacion;
        const char* periodo;
        double calificacionReal;
};

#endif // CALIFICACION_H
