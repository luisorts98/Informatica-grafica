//**************************************************************************
// Práctica 3
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"
#include <time.h>
#include "CImg.h"
//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
    glVertex3fv((GLfloat *) &vertices[i]);
    }
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
  ///se pone para poner un valor por defecto para la practica 4
ambiente=_vertex4f(1.0,1.0,0.2,1.0); //coeficiente ambiente y difuso
difuso=_vertex4f(1.0,1.0,0.2,1.0);
especular=_vertex4f(0.5,0.5,0.5,1.0); //coegfiuente especular
brillo=10;  //exponente del brillo 

}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
    int i;
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glColor3f(r,g,b);
        glBegin(GL_TRIANGLES);
        for (i=0;i<caras.size();i++){
            glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
            glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
            glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
            }
        glEnd();



}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores()
{/*
        int i;
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBegin(GL_TRIANGLES);
        for (i=0;i<caras.size();i++){
            switch (i) {
                case 0:
                    glColor3f(0.5, 1.0, 1.0);
                    break;
                case 1:
                    glColor3f(1.0, 1.0, 1.0);
                    break;
                case 2:
                    glColor3f(0.0, 0.0, 1.0);
                    break;
                case 3:
                    glColor3f(1.0, 0.0, 1.0);
                    break;
                case 4:
                    glColor3f(1.0, 0.5, 0.0);
                    break;
                case 5:
                    glColor3f(0.5, 0.5, 0.5);
                    break;
                case 6:
                    glColor3f(0.1, 0.1, 0.1);
                    break;
                case 7:
                    glColor3f(0.1, 0.0, 0.1);
                    break;
                case 8:
                    glColor3f(0.1, 0.1, 0.0);
                    break;
                case 9:
                    glColor3f(0.0, 0.1, 0.0);
                    break;
                case 10:
                    glColor3f(0.1, 0.0, 0.0);
                    break;
                default:
                    glColor3f(1.0, 0.5, 0.0);
            }
            glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
            glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
            glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
           
        }
        glEnd();*/
    int i;
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    for (i=0;i<caras.size();i++){
        glColor3f(colores_caras[i].r,colores_caras[i].g,colores_caras[i].b);
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
        }
    glEnd();
    
    }



//*************************************************************************
// dibujar en modo sólido plano PRACTICA 4
//*************************************************************************

void _triangulos3D::draw_solido_plano()
{
    int i;
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_FLAT);
    glEnable(GL_NORMALIZE);
    glEnable (GL_LIGHTING); //se activa la iluminación
   
    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *)  &ambiente); //se define la reflexión ambiente
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *)  &difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR,(GLfloat *) &especular);
    glMaterialfv(GL_FRONT, GL_SHININESS,(GLfloat *) &brillo);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    for (i=0;i<caras.size();i++){
        glNormal3f(normales_caras[i].x,normales_caras[i].y,normales_caras[i].z); 
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
        }
    glEnd();
     glDisable (GL_LIGHTING); //se desactiva la iluminación

    }

    //*************************************************************************
// dibujar en modo sólido smooth PRACTICA 4
//*************************************************************************

void _triangulos3D::draw_solido_suave()
{//
int i;
glEnable (GL_LIGHTING);
glEnable(GL_SMOOTH);
glEnable(GL_NORMALIZE);
glEnable (GL_LIGHTING);


glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)  &ambiente); //se define la reflexión ambiente
glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)  &difuso);
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,(GLfloat *) &especular);
glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,(GLfloat *) &brillo);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
    glNormal3f(normales_vertices[caras[i]._0].x,normales_vertices[caras[i]._0].y,normales_vertices[caras[i]._0].z);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glNormal3f(normales_vertices[caras[i]._1].x,normales_vertices[caras[i]._1].y,normales_vertices[caras[i]._1].z);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glNormal3f(normales_vertices[caras[i]._2].x,normales_vertices[caras[i]._2].y,normales_vertices[caras[i]._2].z);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
glEnd();
glDisable (GL_LIGHTING);

}
//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
   
switch (modo){
    case POINTS:draw_puntos(r, g, b, grosor);break;
    case EDGES:draw_aristas(r, g, b, grosor);break;
    case SOLID:draw_solido(r, g, b);break;
    case SOLID_COLORS:draw_solido_colores();break;
    case SOLID_FLAT:draw_solido_plano();break;
    case SOLID_SMOOTH:draw_solido_suave();break;
    }
}
//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random()
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
srand (time(NULL));
for (i=0;i<n_c;i++)
  {colores_caras[i].r=rand()%1000/1000.0;
   colores_caras[i].g=rand()%1000/1000.0;
   colores_caras[i].b=rand()%1000/1000.0;
  }
}
//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
for (i=0;i<n_c;i++)
  {if (i%2==0)
     {colores_caras[i].r=r1;
      colores_caras[i].g=g1;
      colores_caras[i].b=b1;
     }
   else
     {colores_caras[i].r=r2;
      colores_caras[i].g=g2;
      colores_caras[i].b=b2;
     }
  }
}

//*************************************************************************
// Generacion de colores lambert
//*************************************************************************

void _triangulos3D::colors_Lambert_caras(float l_x, float l_y, float l_z, float r, float g, float b){
    int i, n_c;
    n_c=caras.size();
    colores_caras.resize(n_c);
    _vertex3f luz,aux_luz;
    float modulo, producto_escalar;
    aux_luz.x=l_x;
    aux_luz.y=l_y;
    aux_luz.z=l_z;
    
    for (i=0;i<n_c; i++){
        luz=aux_luz-vertices[caras[i]._0];
        modulo= sqrt(luz.x*luz.x+luz.y*luz.y+luz.z*luz.z);
        luz.x=luz.x/modulo;
        luz.y=luz.y/modulo;
        luz.z=luz.z/modulo;
        producto_escalar=luz.x*normales_caras[i].x+luz.y*normales_caras[i].y+luz.z*normales_caras[i].z;
        if(producto_escalar<=0){ producto_escalar=0.0;}
       
        colores_caras[i].r=r*0.2+r*producto_escalar; //r*producto_escalar como queramos en teoria es mas real el puesto
        colores_caras[i].g=g*0.2+g*producto_escalar;
        colores_caras[i].b=b*0.2+b*producto_escalar+0.01; //lo de 0.01 es para lo de la luz blanca se quede exactamente real 
    }
}

//*************************************************************************
// calcular normales   A = P1 - P0 y ~B = P2 −P0 //ES UN MENOSSSSS en el guión está mal
//*************************************************************************

void _triangulos3D::calcular_normales_caras(){
    
    int i, n_c;
    n_c=caras.size();
    colores_caras.resize(n_c);
    normales_caras.resize(n_c);
    _vertex3f vector_a, vector_b, aux;
    float modulo;
    
    for(i=0;i<n_c;i++){
        vector_a=vertices[caras[i]._1]-vertices[caras[i]._0];
        vector_b=vertices[caras[i]._2]-vertices[caras[i]._0];
        //normales_caras[i].x=vector_a.y*vector_b.z-vector_a.z*vector_b.y;
        aux.x=vector_a.y*vector_b.z-vector_a.z*vector_b.y;
        aux.y=vector_a.z*vector_b.x-vector_a.x*vector_b.z;
        aux.z=vector_a.x*vector_b.y-vector_a.y*vector_b.x;
        modulo = sqrt(aux.x*aux.x+aux.y*aux.y+aux.z*aux.z);
        
        normales_caras[i].x=aux.x/modulo;
        normales_caras[i].y=aux.y/modulo;
        normales_caras[i].z=aux.z/modulo;
    }
}

void _triangulos3D::calcular_normales_vertices(){
    
    int i, n_v;
    n_v=vertices.size();
    normales_vertices.resize(n_v);
    for(i=0;i<n_v;i++){
        normales_vertices[i].x=0;
        normales_vertices[i].y=0;
        normales_vertices[i].z=0;
    }
    for(i=0;i<caras.size();i++){
        normales_vertices[caras[i]._0]+=normales_caras[i];
        normales_vertices[caras[i]._1]+=normales_caras[i];
        normales_vertices[caras[i]._2]+=normales_caras[i];

    }
    for(i=0;i<n_v;i++){
       float norma=sqrt(normales_vertices[i].x*normales_vertices[i].x+normales_vertices[i].y*normales_vertices[i].y+normales_vertices[i].z*normales_vertices[i].z);
        normales_vertices[i].x/=norma;
        normales_vertices[i].y/=norma;
        normales_vertices[i].z/=norma;
    }
  // for( i=0; i<caras.size(); i++){
    //normales_vertices[caras[i]._0] += normales_caras[i];
   // normales_vertices[caras[i]._1] += normales_caras[i];
   // normales_vertices[caras[i]._2] += normales_caras[i];
 // }
  //  for(i=0; i<normales_vertices.size(); i++){
   //     normales_vertices[i].normalize();
   // }*/

}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
/*
// vertices
    vertices.resize(8);

    vertices[0].x = -tam; vertices[0].y = 0; vertices[0].z = tam;
    vertices[1].x = tam; vertices[1].y = 0; vertices[1].z = tam;
    vertices[2].x = tam; vertices[2].y = 0; vertices[2].z = -tam;
    vertices[3].x = -tam; vertices[3].y = 0; vertices[3].z = -tam;
    vertices[4].x = -tam; vertices[4].y = 2*tam; vertices[4].z = tam;
    vertices[5].x = tam; vertices[5].y = 2*tam; vertices[5].z = tam;
    vertices[6].x = tam; vertices[6].y = 2*tam; vertices[6].z = -tam;
    vertices[7].x = -tam; vertices[7].y = 2*tam; vertices[7].z = -tam;
    
// triangulos
    caras.resize(12);

    caras[0]._0=0; caras[0]._1=1; caras[0]._2=5;
    caras[1]._0=0; caras[1]._1=4; caras[1]._2=5;
    caras[2]._0=1; caras[2]._1=2; caras[2]._2=6;
    caras[3]._0=1; caras[3]._1=5; caras[3]._2=6;
    caras[4]._0=2; caras[4]._1=3; caras[4]._2=7;
    caras[5]._0=2; caras[5]._1=6; caras[5]._2=7;
    caras[6]._0=3; caras[6]._1=0; caras[6]._2=4;
    caras[7]._0=3; caras[7]._1=4; caras[7]._2=7;
    caras[8]._0=0; caras[8]._1=1; caras[8]._2=3;
    caras[9]._0=1; caras[9]._1=2; caras[9]._2=3;
    caras[10]._0=4; caras[10]._1=5; caras[10]._2=6;
    caras[11]._0=4; caras[11]._1=6; caras[11]._2=7;
 */
    //vertices
    vertices.resize(8);
    vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
    vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
    vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
    vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
    vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
    vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
    vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
    vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

    // triangulos
    caras.resize(12);
    caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
    caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
    caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
    caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
    caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
    caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
    caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
    caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
    caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
    caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
    caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
    caras[11]._0=1;caras[11]._1=5;caras[11]._2=4; 
    //colores de las caras
    colors_random();
    //practica 4 normales a caras
    ambiente = _vertex4f(0.329412, 0.223529, 0.027451,1.0);
    difuso = _vertex4f(0.780392, 0.568627, 0.113725,1.0);
    especular = _vertex4f(0.992157, 0.941176, 0.807843,1.0);
    brillo = 27.8974;
    calcular_normales_caras();
    calcular_normales_vertices();
    
    }


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices
vertices.resize(5);
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
    //colores de las caras
    colors_random();
    //practica 4 normales a caras
     ambiente = _vertex4f( 0.135, 0.2225, 0.1575, 0.95);
    difuso = _vertex4f(0.54, 0.89, 0.63, 0.95);
    especular = _vertex4f(0.316228, 0.316228, 0.316228, 0.95);
    brillo = 12.8;
    calcular_normales_caras();
     calcular_normales_vertices();
}
//*************************************************************************
// clase objeto ply
//*************************************************************************
_cilindro::_cilindro(float radio, float altura, int num)
{
vector<_vertex3f> perfil;
_vertex3f aux;

aux.x=radio; aux.y=-altura/2.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=radio; aux.y=altura/2.0; aux.z=0.0;
perfil.push_back(aux);
parametros(perfil,num,0,1,1);
}

//*************************************************************************
// clase cono
//*************************************************************************

_cono::_cono(float radio, float altura, int num)
{
vector<_vertex3f> perfil;
_vertex3f aux;

aux.x=radio; aux.y=0; aux.z=0.0;
perfil.push_back(aux);
aux.x=0.0; aux.y=altura; aux.z=0.0;
perfil.push_back(aux);
parametros(perfil,num,1,1,1);
}
//*************************************************************************
// clase esfera
//*************************************************************************

_esfera::_esfera(float radio, int num1, int num2){
    vector<_vertex3f> perfil;
    _vertex3f aux;
    int i;
    for (i=1;i<num1;i++)
      {aux.x=radio*cos(M_PI*i/(num1*1.0)-M_PI/2.0);
       aux.y=radio*sin(M_PI*i/(num1*1.0)-M_PI/2.0);
       aux.z=0.0;
       perfil.push_back(aux);
      }
    parametros(perfil,num2,2,1,1);
    //practica 4 normales a caras
    ambiente = _vertex4f(0.2295, 0.08825, 0.0275, 1.0);
    difuso = _vertex4f(0.5508, 0.2118, 0.066, 1.0);
    especular = _vertex4f(0.580594, 0.223257, 0.0695701, 1.0);
    brillo = 51.2;
    calcular_normales_caras();
     calcular_normales_vertices();
}
//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply()
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}




void _objeto_ply::parametros(char *archivo)
{
    int n_ver,n_car;
    int i;
    
    vector<float> ver_ply ; //vector para ver. una va por casilla. por tanto, se almacena xyz de forma consecutiva. antes lo haciamos que cada casilla tenia .x, .y y .z
    vector<int>   car_ply ;
    
    _file_ply::read(archivo, ver_ply, car_ply );  //se usara como argv[1]. guarda ver y caras.
    
    n_ver=ver_ply.size()/3;
    n_car=car_ply.size()/3;
    
    printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);
    
    vertices.resize(n_ver);
    caras.resize(n_car);
    
    //vertices
    
    for(int i=0;i<n_ver;i++){
        vertices[i].x=ver_ply[3*i];//es el triple porque es una matriz de una sola dimension
        vertices[i].y=ver_ply[3*i+1]; //para avanzar los elementos de la matriz
        vertices[i].z=ver_ply[3*i+2];
        
    }
    //Caras
    
    for(int i=0;i<n_car;i++){
        caras[i].x=car_ply[3*i];//es el triple porque es una matriz de una sola dimension
        caras[i].y=car_ply[3*i+1]; //para avanzar los elementos de la matriz
        caras[i].z=car_ply[3*i+2];
        
    }
    ambiente = _vertex4f(0.329412, 0.223529, 0.027451,1.0);
    difuso = _vertex4f(0.780392, 0.568627, 0.113725,1.0);
    especular = _vertex4f(0.992157, 0.941176, 0.807843,1.0);
    brillo = 27.8974;
    calcular_normales_caras();
    calcular_normales_vertices();
    //asignacion de colores
    colors_Lambert_caras(-0,10, 40, 1.0,0.8,0.0);
    /*colores_caras.resize(n_car);
    srand(10);
    // colores
    float sum;
    int n;
    colores_caras.resize(caras.size());
    for (i=0;i<caras.size();i++)
    {if (vertices[caras[i]._0].y>=0)
    {colores_caras[i].r=rand()%1000/1000.0;
        colores_caras[i].b=0.0;
        colores_caras[i].g=0.8;
    }
    else
    {n=rand()%10;
        sum=rand()%100/500.0;
        if (n<5) colores_caras[i].r=0.251+sum;
        else colores_caras[i].r=0.251-sum;
        if (n>5) colores_caras[i].b=0.805+sum;
        else colores_caras[i].b=0.805-sum;
        if (n>5) colores_caras[i].g=0.816+sum;
        else colores_caras[i].g=0.816-sum;
    }
    }*/
}



//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;
float radio;

// tratamiento de los vértice
radio=sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);

num_aux=perfil.size();
if (tipo==1) num_aux=num_aux-1;
vertices.resize(num_aux*num+2);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

caras.resize(2*(num_aux-1)*num+2*num);
int c=0;
for (j=0;j<num;j++)
 {
  for (i=0;i<num_aux-1;i++)
    {caras[c]._0=i+j*num_aux;
     caras[c]._1=((j+1)%num)*num_aux+i;
     caras[c]._2=1+i+j*num_aux;
     c+=1;
     caras[c]._0=((j+1)%num)*num_aux+i;
     caras[c]._1=((j+1)%num)*num_aux+1+i;
     caras[c]._2=1+i+j*num_aux;
     c+=1;
   }
 }
 
 //tapa inferior
 int total=num_aux*num;
 vertices[total].x=0.0;
 if (tipo==2) vertices[total].y=-radio;
 else vertices[total].y=perfil[0].y;
 vertices[total].z=0.0;

for (j=0;j<num;j++)
 {
     caras[c]._0=j*num_aux;
     caras[c]._1=((j+1)%num)*num_aux;
     caras[c]._2=total;
     c+=1;
 }
 
//tapa superior
 vertices[total+1].x=0.0;
 if (tipo==1) vertices[total+1].y=perfil[1].y;
 if (tipo==0) vertices[total+1].y=perfil[num_aux-1].y;
 if (tipo==2) vertices[total+1].y=radio;
 vertices[total+1].z=0.0;
 
 for (j=0;j<num;j++)
 {
     caras[c]._0=total+1;
     caras[c]._1=((j+1)%num)*num_aux+num_aux-1;
     caras[c]._2=num_aux-1+j*num_aux;
     c+=1;
 }

    //normales a caras
    calcular_normales_caras();
/// PARA LA NORMAL DE CARAS DE LA ESFERAAA
    if(tipo==2){
        float norma;
        int n_v;
        n_v=vertices.size();
        normales_vertices.resize(n_v);
        for(int i=0;i<n_v;i++){
            norma=sqrt(vertices[i].x*vertices[i].x+vertices[i].y*vertices[i].y+vertices[i].z*vertices[i].z);
            normales_vertices[i].x=vertices[i].x/norma;
            normales_vertices[i].y=vertices[i].y/norma;
            normales_vertices[i].z=vertices[i].z/norma;
        }

    }else calcular_normales_vertices();
    //colores
    colors_Lambert_caras(0,20,20,1.0,0.4,0.7);
//colores de las caras
//colors_random();
}

//************************************************************************
// rotacion archivo PLY (caso especial de rotacion)
//************************************************************************

_rotacion_PLY::_rotacion_PLY()
{

}

void _rotacion_PLY::parametros_PLY(char *archivo, int num)
{

}

//************************************************************************
// objeto por extrusión
//************************************************************************


_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
int i;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=poligono.size();
vertices.resize(num_aux*2);
for (i=0;i<num_aux;i++)
    {
      vertices[2*i]=poligono[i];
      vertices[2*i+1].x=poligono[i].x+x;
      vertices[2*i+1].y=poligono[i].y+y;
      vertices[2*i+1].z=poligono[i].z+z;
    }
    
// tratamiento de las caras

caras.resize(num_aux*2);
int c=0;
for (i=0;i<num_aux;i++)
  {
   caras[c]._0=i*2;
   caras[c]._1=(i*2+2)%(num_aux*2);
   caras[c]._2=i*2+1;
   c=c+1;
   caras[c]._0=(i*2+2)%(num_aux*2);
   caras[c]._1=(i*2+2)%(num_aux*2)+1;
   caras[c]._2=i*2+1;
   c=c+1;
      
   }
    //colores de las caras
    colors_random();
    //practica 4 normales a caras
    
    calcular_normales_caras();
    calcular_normales_vertices();
}

//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************


//************************************************************************
// visor
//***********************************************************************

_visor::_visor(float radio, float ancho, int num) //antigua pala
{
vector<_vertex3f> perfil;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int i, j;

vertice_aux.x=radio; vertice_aux.y=0; vertice_aux.z=-ancho/2.0;
perfil.push_back(vertice_aux);
vertice_aux.z=ancho/2.0;
perfil.push_back(vertice_aux);

// tratamiento de los vértices

for (j=0;j<=num;j++)
  {for (i=0;i<2;i++)
     {
      vertice_aux.x=perfil[i].x*cos(M_PI*j/(1.0*num))-
                    perfil[i].y*sin(M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].x*sin(M_PI*j/(1.0*num))+
                    perfil[i].y*cos(M_PI*j/(1.0*num));
      vertice_aux.z=perfil[i].z;
      vertices.push_back(vertice_aux);
     }
  }
  
// tratamiento de las caras

for (j=0;j<num;j++)
   {cara_aux._0=j*2;
    cara_aux._1=(j+1)*2;
    cara_aux._2=(j+1)*2+1;
    caras.push_back(cara_aux);
    
    cara_aux._0=j*2;
    cara_aux._1=(j+1)*2+1;
    cara_aux._2=j*2+1;
    caras.push_back(cara_aux);
   }
   
// tapa inferior
vertice_aux.x=0;
vertice_aux.y=0;
vertice_aux.z=-ancho/2.0;
vertices.push_back(vertice_aux);

for (j=0;j<num;j++)
   {cara_aux._0=j*2;
    cara_aux._1=(j+1)*2;
    cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);
   }
  
// tapa superior
vertice_aux.x=0;
vertice_aux.y=0;
vertice_aux.z=ancho/2.0;
vertices.push_back(vertice_aux);

for (j=0;j<num;j++)
   {cara_aux._0=j*2+1;
    cara_aux._1=(j+1)*2+1;
    cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);
   }
  
    colors_chess(0.9,0.9,0.9,0.9,0.9,0.9);
  ambiente = _vertex4f(0.05,0.05,0.05,1.0);
  difuso = _vertex4f(0.5,0.5,0.5,1.0);
  especular = _vertex4f(0.7,0.7,0.7,1.0);
  brillo = 10.0;
    //practica 4 normales a caras
    calcular_normales_caras();
    calcular_normales_vertices();
}

//************************************************************************
//Base camara, antigua  sustentación
//************************************************************************

_baseCamaratripode::_baseCamaratripode() //Base camara ANTIGUA SUSTENTACION
{

base.colors_chess(0.2,0.0,0.0,0.2,0.0,0.0);
rueda.colors_chess(0.4,0.4,0.4,0.4,0.4,0.4);
 
    rueda.ambiente = _vertex4f(0.105882,0.058824,0.113725, 1.0);
    rueda.difuso = _vertex4f(0.427451,0.470588,0.541176, 1.0);
    rueda.especular = _vertex4f(0.333333, 0.333333, 0.521569, 1.0);
    rueda.brillo = 9.84615;
    rueda.calcular_normales_caras();
    rueda.calcular_normales_vertices();
    base.ambiente = _vertex4f(0.25, 0.148, 0.06475, 1.0);
    base.difuso = _vertex4f(0.4, 0.2368, 0.1036, 1.0);
    base.especular = _vertex4f(0.774597, 0.458561, 0.200621, 1.0);
    base.brillo = 76.8;
    base.calcular_normales_caras();
    base.calcular_normales_vertices();

};

void _baseCamaratripode::draw(_modo modo, float r, float g, float b, float grosor)
{
    
//rueda grande
glPushMatrix();
glTranslatef(0,-0.37,0);
//glRotatef(360,2,-2,-2);
glScalef(0.25, 0.10, 0.25);
rueda.draw(modo, r, g, b, grosor);
//rueda pequeña
glPopMatrix();
glPushMatrix();
glTranslatef(0,-0.57,0);
//glRotatef(360,2,-2,-2);
glScalef(0.15, 0.1, 0.15);

rueda.draw(modo, r, g, b, grosor);
glPopMatrix();

    //tripode pata 1
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(-37,1,0,0);
    glTranslatef(0,-0.85,-0.35);
    glScalef(0.03, 0.5, 0.03);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //tripode pata 2
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(-37,0,0,1);
    glTranslatef(0.35,-0.85,0);
    //glRotatef(70,0,1,0);
    glScalef(0.03, 0.5, 0.03);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //tripode pata 3
    glPushMatrix();
    glTranslatef(0.15,-0.03,-0.15);
    glRotatef(48,0,1,0);
    glTranslatef(0,-0.85,-0);
    glRotatef(37,0,0,1);
    glScalef(0.03, 0.5, 0.03);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //soportes ruedas 1
    glPushMatrix();
    glTranslatef(0,-1.3,0.52);
    glRotatef(0,0,0,0);
    glScalef(0.1, 0.024, 0.1);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //soportes ruedas 2
    glPushMatrix();
    glTranslatef(-0.52,-1.3,0);
    glRotatef(0,0,0,0);
    glScalef(0.1, 0.024, 0.1);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //soportes ruedas 3
    glPushMatrix();
    glTranslatef(0.35,-1.3,-0.36);
    glRotatef(0,0,0,0);
    glScalef(0.1, 0.024, 0.1);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //Agarre
    glPushMatrix();
    glTranslatef(-0.28,-0.38,0.19); //0,22
    glRotatef(90,0,0,1);
    glScalef(0.045, 0.4, 0.045);
  
    base.draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.28,-0.38,-0.19); //0,22
    glRotatef(90,0,0,1);
    glScalef(0.045, 0.4, 0.045);
    base.draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.45,-0.38,0);
    glRotatef(120,2,-2,-2);
    glScalef(0.023,0.2, 0.023);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

};




//************************************************************************
//Base camara, antigua  sustentación
//************************************************************************

_baseCamara::_baseCamara() //Base camara ANTIGUA SUSTENTACION
{
   
ancho=1.0;
alto=0.4;
fondo=0.4;
radio=0.15;
base.colors_chess(0.2,0.2,0.2,0.2,0.2,0.2);
rueda.colors_chess(1.0,0.5,0.0,1.0,0.5,0.0);

base.ambiente(0.04, 0.04, 0.04, 1.0);
base.difuso(0.02, 0.02, 0.02, 1.0);
base.especular(0.6, 0.6, 0.6, 1.0);
base.brillo = 10.0;
rueda.ambiente(0.02, 0.02, 0.02, 1.0);
rueda.difuso(0.01, 0.01, 0.01, 1.0);
rueda.especular(0.4, 0.4, 0.4, 1.0);
rueda.brillo = 10.0;
base.calcular_normales_caras();
base.calcular_normales_vertices();
rueda.calcular_normales_caras();
rueda.calcular_normales_vertices();


};

void _baseCamara::draw(_modo modo, float r, float g, float b, float grosor)
{


//glTranslatef(-2*ancho/6,-alto/2.0,0);
//cuerpo
glPushMatrix();
glScalef(ancho, alto, fondo);
base.draw(modo, r, g, b, grosor);
glPopMatrix();
   // mira
glPushMatrix();
glTranslatef(-0.53,0.18,0.11);
glRotatef(-90,0,0,1);
glTranslatef(0.04,0,0);
glScalef(0.04, 0.04, 0.04);
//SE aplica el movimiento a todos los de atrás
visor.draw(modo, r, g, b, grosor);
glPopMatrix();
//BASE PARA pantalla un lado
glPushMatrix();
glTranslatef(-0.37,0.2,-0.17); //0,22
glRotatef(20,0,0,1);
glScalef(0.12, alto, 0.018);
base.draw(modo, r, g, b, grosor);
glPopMatrix();
//SEGUNDABASE
glPushMatrix();
glTranslatef(-0.37,0.2,0.17); //0,22
glRotatef(20,0,0,1);
glScalef(0.12, alto, 0.018);
base.draw(modo, r, g, b, grosor);
glPopMatrix();
//RUEDECILLA 1 para base monitor
glPushMatrix();
glTranslatef(-0.43,0.38,0.147);
glRotatef(120,2,-2,-2);
glScalef(0.04,0.016, 0.04);
glColor3f(1.0,1.0,1.0);
rueda.draw(modo, r, g, b, grosor);
glPopMatrix();

//RUEDECILLA 2 para base monitor
glPushMatrix();
glTranslatef(-0.43,0.38,-0.147);
glRotatef(120,2,-2,-2);
glScalef(0.04,0.016, 0.04);
rueda.draw(modo, r, g, b, grosor);
glPopMatrix();




};
//************************************************************************
//Pantalla lateral, antigua  sustentación
//************************************************************************

_pantalla::_pantalla() //Base camara ANTIGUA SUSTENTACION
{
ancho=0.06;
alto=0.2;
fondo=0.26;
radio=0.1;
base.colors_chess(0.3,0.3,0.3,0.3,0.3,0.3);
piramide.colors_chess(0.0,0.6,0.6,0.0,0.6,0.6);

base.ambiente(0.04, 0.04, 0.04, 1.0);
base.difuso(0.02, 0.02, 0.02, 1.0);
base.especular(0.6, 0.6, 0.6, 1.0);
base.brillo = 10.0;
piramide.ambiente(0.1, 0.18725, 0.1745, 0.8);
piramide.difuso(0.396, 0.74151, 0.69102, 0.8);
piramide.especular(0.297254, 0.30829, 0.306678, 0.8);
piramide.brillo = 12.8;
base.calcular_normales_caras();
base.calcular_normales_vertices();
piramide.calcular_normales_caras();  
piramide.calcular_normales_vertices();


};

void _pantalla::draw(_modo modo, float r, float g, float b, float grosor)
{


//glTranslatef(-2*ancho/6,-alto/2.0,0);
    //pantalla
glPushMatrix();
glTranslatef(0,0,0); //-0.48,0.4,0
glRotatef(0,0,0,0);//(360,2,-2,-2)
glScalef(ancho, alto, fondo);
base.draw(modo, r, g, b, grosor);
glPopMatrix();
    
//protectores
glPushMatrix();
glTranslatef(-0.08,0,0.13); //-0.57,0.4,0.13
glRotatef(0,0,0,0);//(360,2,-2,-2)
glScalef(0.12, alto, 0.0001);
base.draw(modo, r, g, b, grosor);
glPopMatrix();
glPushMatrix();
glTranslatef(-0.08,0,-0.13); //-0.57,0.4,-0.13
glRotatef(0,0,0,0);//(360,2,-2,-2)
glScalef(0.12, alto, 0.0001);
base.draw(modo, r, g, b, grosor);
glPopMatrix();
    
glPushMatrix();
glTranslatef(-0.08,0.1,0); //-0.57,0.5,0
glRotatef(180,0,0,0);//(360,2,-2,-2)
glScalef(0.12,0.0001,0.26);
base.draw(modo, r, g, b, grosor);
glPopMatrix();

//cristal
glPushMatrix();
glTranslatef(-0.03,0,0); //-0.57,0.5,0
glRotatef(90,0,0,1);//(360,2,-2,-2)
glScalef(0.12,0.0001,0.24);
piramide.draw(modo, r, g, b, grosor);
glPopMatrix();


};

//************************************************************************
// rueda de encima del tripode
//************************************************************************

_basecirculo::_basecirculo()
{
ancho=0.1;
alto=0.1;
fondo=0.1;
circulo.colors_chess(0.1,0.1,0.0,0.1,0.1,0.0);

};

void _basecirculo::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glTranslatef(0,-0.30,0);
//glRotatef(360,2,-2,-2);
glScalef(ancho, alto, fondo);
circulo.draw(modo, r, g, b, grosor);
glPopMatrix();
};

//************************************************************************
// Objetivo 1 //antes brazo
//************************************************************************

_objetivo1::_objetivo1()
{
//ancho=0.4; //ancho de x(se pone mas largo el brazo
//alto=0.1;
fondo=0.05; //ancho de z se pone mas gordo
rueda.colors_chess(0.1,0.1,0.1,0.1,0.1,0.1);

rueda.ambiente(0.0, 0.0, 0.0, 1.0 );
rueda.difuso(0.01, 0.01, 0.01, 1.0 );
rueda.especular(0.50, 0.50, 0.50, 1.0);
rueda.brillo = 32.0;
rueda.calcular_normales_caras();
rueda.calcular_normales_vertices();

};


void _objetivo1::draw(_modo modo, float r, float g, float b, float grosor)
{
    glPushMatrix();
    glTranslatef(0.42,0,0);
    glRotatef(240,2,-2,-2);
    glScalef(0.16, fondo, 0.16);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

};
//************************************************************************
// Objetivo 2 //antes brazo 2
//************************************************************************

_objetivo2::_objetivo2()
{
ancho=0.4; //ancho de x(se pone mas largo el brazo
alto=0.1;
fondo=0.05; //ancho de z se pone mas gordo
rueda.colors_chess(0.4,0.4,0.4,0.4,0.4,0.4);
circulo.colors_chess(0.0,0.8,0.8,0.0,0.8,0.8);
rueda.ambiente(0.02, 0.02, 0.02, 1.0 );
rueda.difuso(0.01, 0.01, 0.01, 1.0 );
rueda.especular(0.04, 0.04, 0.04, 1.0);
rueda.brillo = 10.0;
rueda.calcular_normales_caras();
rueda.calcular_normales_vertices();
circulo.ambiente( 0.1, 0.18725, 0.1745, 0.8);
circulo.difuso( 0.396, 0.74151, 0.69102, 0.8);
circulo.especular(0.297254, 0.30829, 0.306678, 0.8);
circulo.brillo = 12.8;
};
void _objetivo2::draw(_modo modo, float r, float g, float b, float grosor)
{
    glPushMatrix();
    glTranslatef(0.45,0,0);
    glRotatef(240,2,-2,-2);
    glScalef(0.15, fondo, 0.15);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();
    //Lente
    glPushMatrix();
    glTranslatef(0.47,0,0);
    glRotatef(240,2,-2,-2);
    glScalef(0.145, 0.06, 0.145);
    circulo.draw(modo, r, g, b, grosor);
    glPopMatrix();

};

//************************************************************************
// Detalles 1//antes brazo MOVER
//************************************************************************

_detalles::_detalles()
{
ancho=0.02; //ancho de x(se pone mas largo el brazo
alto=0.02;
fondo=0.02; //ancho de z se pone mas gordo
rueda.colors_chess(1.0,0.,0.0,1.0,0.0,0.0);
rueda.ambiente( 0.1745, 0.01175, 0.01175, 0.55 );
rueda.difuso(0.61424, 0.04136, 0.04136, 0.55);
rueda.especular(0.727811, 0.626959, 0.626959, 0.55 );
rueda.brillo = 76.8;
rueda.calcular_normales_caras();
rueda.calcular_normales_vertices();

};


void _detalles::draw(_modo modo, float r, float g, float b, float grosor)
{
    glPushMatrix();
    glTranslatef(-0.4,0.08,0.2);
    glRotatef(90,1,0,0);
    glScalef(ancho,fondo,alto);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

};

//************************************************************************
// Detalles 2//antes brazo MOVER
//************************************************************************

_detalles2::_detalles2()
{
ancho=0.01; //ancho de x(se pone mas largo el brazo
alto=0.01;
fondo=0.03; //ancho de z se pone mas gordo
rueda.colors_chess(0.0,1.0,0.0,0.0,1.0,0.0);
base.colors_chess(0.0,0.6,0.6,0.0,0.6,0.6);
circulo.colors_chess(1.0,1.0,1.0,1.0,1.0,1.0);
base.calcular_normales_caras();
base.calcular_normales_vertices();
base.ambiente = _vertex4f(0.03125, 0.63125, 0.63125, 1.0);//brillante
base.difuso = _vertex4f(0.0775, 0.6775, 0.6775, 1.0);
base.especular = _vertex4f(0.773911, 0.773911, 0.773911, 1.0);
base.brillo = 20;
circulo.calcular_normales_caras();
circulo.calcular_normales_vertices();
circulo.ambiente = _vertex4f(0.25, 0.20725, 0.20725, 0.922);
circulo.difuso = _vertex4f(1.0, 0.829, 0.829, 0.922);
circulo.especular = _vertex4f(1.0, 0.829, 0.829, 0.922);
circulo.brillo = 11.264;
rueda.calcular_normales_caras();
rueda.calcular_normales_vertices();
rueda.ambiente = _vertex4f(0.0215, 0.1745, 0.0215, 0.55);
rueda.difuso = _vertex4f(0.07568, 0.61424, 0.07568, 0.55 );
rueda.especular = _vertex4f(0.633, 0.727811, 0.633, 0.55);
rueda.brillo = 76.8;
};


void _detalles2::draw(_modo modo, float r, float g, float b, float grosor)
{
    glPushMatrix();
    glTranslatef(-0.5,0.15,-0.02);
    glRotatef(90,1,0,0);
    glScalef(ancho,fondo,alto);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,0.14,0.109);
    glRotatef(90,0,0,1);
    glScalef(0.06,0.001,0.08);
    base.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.5,0.15,-0.16);
    glRotatef(0,0,0,0);
    glScalef(0.02,0.02,0.02);
    circulo.draw(modo, r, g, b, grosor);
    glPopMatrix();
  
    
    
    //pantalla
    glPushMatrix();
    glTranslatef(-0.5,-0.04,0);
    glRotatef(90,0,0,1);
    glScalef(0.16,0.001,0.22);
    base.draw(modo, r, g, b, grosor);
    glPopMatrix();


};

//************************************************************************
//ruedin1
//************************************************************************

_ruedin1::_ruedin1() //Base camara ANTIGUA SUSTENTACION
{

rueda.colors_chess(0.0,0.0,0.0,0.0,0.0,0.0);
rueda.calcular_normales_caras();
rueda.calcular_normales_vertices();
rueda.ambiente = _vertex4f(0.05,0.05,0.05,1.0);
rueda.difuso = _vertex4f(0.5,0.5,0.5,1.0);
rueda.especular = _vertex4f(0.7,0.7,0.7,1.0);
rueda.brillo = 10.0;
};

void _ruedin1::draw(_modo modo, float r, float g, float b, float grosor)
{
  
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(90,1,0,0);
    glScalef(0.06,0.03,0.06);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

};

//************************************************************************
//ruedin2
//************************************************************************

_ruedin2::_ruedin2() //Base camara ANTIGUA SUSTENTACION
{
rueda.colors_chess(0.0,0.0,0.0,0.0,0.0,0.0);
rueda.calcular_normales_caras();
rueda.calcular_normales_vertices();
rueda.ambiente = _vertex4f(0.05,0.05,0.05,1.0);
rueda.difuso = _vertex4f(0.5,0.5,0.5,1.0);
rueda.especular = _vertex4f(0.7,0.7,0.7,1.0);
rueda.brillo = 10.0;
};

void _ruedin2::draw(_modo modo, float r, float g, float b, float grosor)
{
  
    glPushMatrix();
   
    glTranslatef(0,0,0);//-0.11,-1.75,0
    glRotatef(90,1,0,0);
    glScalef(0.06,0.03,0.06);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

};

//************************************************************************
//ruedin3
//************************************************************************

_ruedin3::_ruedin3() //Base camara ANTIGUA SUSTENTACION
{
rueda.colors_chess(0.0,0.0,0.0,0.0,0.0,0.0);
rueda.calcular_normales_caras();
rueda.calcular_normales_vertices();
rueda.ambiente = _vertex4f(0.05,0.05,0.05,1.0);
rueda.difuso = _vertex4f(0.5,0.5,0.5,1.0);
rueda.especular = _vertex4f(0.7,0.7,0.7,1.0);
rueda.brillo = 10.0;
};

void _ruedin3::draw(_modo modo, float r, float g, float b, float grosor)
{
  
    glPushMatrix();
   
    glTranslatef(0,0,0);//-0.11,-1.75,0
    glRotatef(90,1,0,0);
    glScalef(0.06,0.03,0.06);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

_camara::_camara()
{
giro_camara = 0.0; //antiguo giro cambina
zoom = 0.0; //giro_primer_brazo
zoom_max = 0.06; //giro_primer_brazo_max
zoom_min = -0.03; //
movimientovertical = 0.0; //camara arriba y abajo
movimientovertical_max = 15; //camara arriba
movimientovertical_min = -10; //camara abajo
giro_monitor = 0.0; //giro_pala
giro_monitor_max = 50.0;
giro_monitor_min = -45.0;
giro_ruedin= 0.0;
giro_ruedin2= 0.0;
giro_ruedin3=0.0;

};


void _camara::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
   
   //Ruedin ejez
    glTranslatef(0,-1.38,0.52);
    //-0.11,-1.75,0
    glRotatef(giro_ruedin3,0,1,0);
    ruedin3.draw(modo, r, g, b, grosor);
   
    //TRIPODECAMARA
    glRotatef(-giro_ruedin3,0,1,0);
    glTranslatef(0,1.38,-0.52);
    glTranslatef(0,0,0);
    glRotatef(0,0,0,0);  //glRotqatef(giro_camara,0,1,0);
    baseCamaratripode.draw(modo, r, g, b, grosor);
       
    //Ruedin -x
    glTranslatef(-0.53,-1.38,0);//-0.11,-1.75,0
    glRotatef(giro_ruedin,0,1,0);
    ruedin1.draw(modo, r, g, b, grosor);
    
    //Circulo done se pone la camara
    glRotatef(-giro_ruedin,0,1,0);
    glTranslatef(0.53,1.38,0);
    glTranslatef(0,0,0);
    glRotatef(giro_camara,0,1,0);
    basecirculo.draw(modo, r, g, b, grosor);
    
    //Rueda eje x
    glRotatef(-giro_camara,0,1,0);
    glTranslatef(0.35,-1.38,-0.35);
    //-0.11,-1.75,0
    glRotatef(giro_ruedin2,0,1,0);
    ruedin2.draw(modo, r, g, b, grosor);
    
    //Cuerpo de la camara
    glRotatef(-giro_ruedin2,0,1,0);
    glTranslatef(-0.35,1.38,0.35);
    glTranslatef(0,0,0);
    glRotatef(giro_camara,0,1,0);
    glRotatef(movimientovertical,0,0,1);
    basecamara.draw(modo, r, g, b, grosor);
    
    //detalles 1
    glTranslatef(0,0,0);
    glRotatef(0,0,0,0);  //glRotqatef(giro_camara,0,1,0);
    detalles.draw(modo, r, g, b, grosor);
    
    //detallaes pantalla inferior y varios
    glTranslatef(0,0,0);
    glRotatef(0,0,0,0);  //glRotqatef(giro_camara,0,1,0);
    detalles2.draw(modo, r, g, b, grosor);
    
    //parte objetivo1 que no se mueve
    glTranslatef(basecirculo.ancho/2.0,0,0);
    glRotatef(0,0,0,0);
    objetivo1.draw(modo, r, g, b, grosor);

    //parte objetivo 2 que se mueve
    glTranslatef(zoom,0,0);
    glRotatef(0,0,0,0);
    objetivo2.draw(modo, r, g, b, grosor);
    
    //pantalla superior
    glTranslatef(-zoom,0,0);
    glTranslatef(-0.46,0.40,-0.00);
    glRotatef(giro_monitor,0,0,1);
    pantalla.draw(modo, r, g, b, grosor);
      
   

glPopMatrix();
};


