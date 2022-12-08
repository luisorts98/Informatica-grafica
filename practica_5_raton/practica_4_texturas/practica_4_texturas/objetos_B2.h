//**************************************************************************
// Práctica 2
//**************************************************************************

#include <vector>
#include <OpenGL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "CImg.h"
using namespace cimg_library;


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS, SOLID_FLAT, SOLID_SMOOTH, TEXTURE,SELECT} _modo; //SOLID FLAT Y SOLID SMOOTH DE LA PRÁCTICA 4

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
    _puntos3D();
void     draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
vector<_vertex3f> colores_vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:
    
    _triangulos3D();
    void     draw_aristas(float r, float g, float b, int grosor);
    void    draw_solido(float r, float g, float b);
    void     draw_solido_colores();
    void     draw(_modo modo, float r, float g, float b, float grosor);
    /* asignación de colores */
    void    colors_random();
    void     colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);
    void colors_Lambert_caras(float l_x, float l_y, float l_z, float r, float g, float b);
    
    void calcular_normales_caras(); //practica4
    void calcular_normales_vertices();//practica4
    void draw_solido_plano();//practica4
    void draw_solido_suave();//practica4
    vector<_vertex3i> caras;
    vector<_vertex3f> colores_caras;
    //practica 5
    void draw_seleccion(int r, int g, int b);
    //practica 4
    vector<_vertex3f> normales_caras;
    vector<_vertex3f> normales_vertices;
    

    //material;
_vertex4f ambiente;
_vertex4f difuso;
_vertex4f especular;   
float brillo;


};



//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

    _cubo(float tam=0.5);
    
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

    _piramide(float tam=0.5, float al=1.0);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

void  parametros(char *archivo);
};



//************************************************************************
// objeto por revolución
//************************************************************************
// tipo indica si es una figura por revolución normal o bien un cono o una esfera
// tipo=0 normal, tipo=1 cono, tipo=2 esfera
// tapa_in=0 sin tapa, tapa_in=1 con tapa
// tapa_su=0 sin tapa, tapa_su=1 con tapa

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
       
    void  parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su);
    };

 
class _cilindro: public _rotacion
{
public:

    _cilindro(float radio=1.0, float altura=2.0, int num=12);
};

class _cono: public _rotacion
{
public:

    _cono(float radio=8, float altura=0.5, int num=1);
};

class _esfera: public _rotacion
{
public:

    _esfera(float radio=1.0, int num1=16, int num2=16);
};



//************************************************************************
// rotacion archivo PLY
//************************************************************************

class _rotacion_PLY: public _rotacion
{
public:
       _rotacion_PLY();
void  parametros_PLY(char *archivo, int num);
};



//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion: public _triangulos3D
{
public:
       _extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};

//************************************************************************
// práctica 3, objeto jerárquico articulado excavadora
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// visor
//************************************************************************

class _visor: public _triangulos3D
{
public:
      _visor(float radio=1.0, float ancho=2.0, int num=8);
};

//************************************************************************
// objetivo1 antiguamente brazo
//************************************************************************

class _objetivo1: public _triangulos3D
{
public:
      _objetivo1();
    
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cilindro rueda;
};
//************************************************************************
// objetivo2 antiguamente brazo
//************************************************************************

class _objetivo2: public _triangulos3D
{
public:
      _objetivo2();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cilindro rueda;
_esfera circulo;
};

//************************************************************************
// detalles
//************************************************************************

class _detalles: public _triangulos3D
{
public:
      _detalles();
    
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cilindro rueda;
_esfera circulo;
};

//************************************************************************
// detalles2
//************************************************************************

class _detalles2: public _triangulos3D
{
public:
      _detalles2();
    
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cilindro rueda;
_esfera circulo;
_cubo base;
};

//************************************************************************
// circulo //antes cabina
//************************************************************************

class _basecirculo: public _triangulos3D
{
public:
       _basecirculo();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_esfera circulo;
_cubo base;
};

//************************************************************************
// BaseCamarasustentación
//************************************************************************

class _baseCamara: public _triangulos3D
{
public:
      _baseCamara();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
_cubo base;
_esfera circulo;
_visor visor;
   
};
//************************************************************************
// pantalla
//************************************************************************

class _pantalla: public _triangulos3D
{
public:
      _pantalla();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
_cubo base;
_esfera circulo;
_piramide piramide;
};

//************************************************************************
// ruedin1
//************************************************************************

class _ruedin1: public _triangulos3D
{
public:
      _ruedin1();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
_cubo base;
_esfera circulo;
};


//************************************************************************
// ruedin2
//************************************************************************

class _ruedin2: public _triangulos3D
{
public:
      _ruedin2();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
_cubo base;
_esfera circulo;
};

//************************************************************************
// ruedin3
//************************************************************************

class _ruedin3: public _triangulos3D
{
public:
      _ruedin3();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
_cubo base;
_esfera circulo;
};


//************************************************************************
// BaseCamaratripode
//************************************************************************

class _baseCamaratripode: public _triangulos3D
{
public:
      _baseCamaratripode();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
_cubo base;
_esfera circulo;
_piramide piramide;
};

//************************************************************************
// camara (montaje del objeto final)
//************************************************************************

class _camara: public _triangulos3D
{
public:
       _camara();
       
void  draw(_modo modo, float r, float g, float b, float grosor);
//practica 5
void seleccion();
float giro_camara; //antiguo giro_cabina
float zoom; //giro_primer_brazo
float movimientovertical; //giro_segundo_brazo
float giro_monitor; //giro_pala
float giro_ruedin;
float giro_ruedin2;
float giro_ruedin3;
float zoom_max; //giro_primer_brazo_max
float zoom_min;
float movimientovertical_max;
float movimientovertical_min;
float giro_monitor_max; //giro_pala_max
float giro_monitor_min;
//practica 5 para seleccionar partes del objeto
_vertex3f color_pick;//que color usamos cuando seleccionamos un objeto
vector<_vertex3i> color_select;
vector<int> activo;
int piezas;
int grosor_select; ///grosor de la linea de seleccion


protected:
_visor visor;
_objetivo1 objetivo1;
_objetivo2 objetivo2;
_basecirculo basecirculo;
_baseCamara basecamara;
_baseCamaratripode baseCamaratripode;
_pantalla pantalla;
_baseCamara pala2;
_detalles detalles;
_detalles2 detalles2;
_ruedin1 ruedin1;
_ruedin2 ruedin2;
_ruedin3 ruedin3;
};
