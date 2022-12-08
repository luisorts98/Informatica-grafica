//**************************************************************************
// Práctica 3
//**************************************************************************
//REVOLUCION:Revolución: genera una malla girando (rotando) una forma alrededor de un eje.
/*La técnica consiste en dibujar el “perfil” del objeto (o más bien, la mitad de este) 
para luego girarlo en torno al eje central y con ello, las superficies de revolución generarán la forma final.*/

#include "objetos_B2.h"
#include "file_ply_stl.hpp"
#include <time.h>
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
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //solo dibuja las aristas
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES); //hace los triangulos
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
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //dibuja en la cara de atras y de delante, fill dibuja puntos y lineas.
        glColor3f(r,g,b); //indica el color para todas las caras pasado por parametros
        glBegin(GL_TRIANGLES);
        for (i=0;i<caras.size();i++){
            glVertex3fv((GLfloat *) &vertices[caras[i]._0]); //recorre todas las caras
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
        glColor3f(colores_caras[i].r,colores_caras[i].g,colores_caras[i].b); //para cada cara pone un color diferente
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
        }
    glEnd();
    
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
for (i=0;i<n_c;i++) //para cada cara poner un color random
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
  {if (i%2==0) //para las cares pares poner un color
     {colores_caras[i].r=r1;
      colores_caras[i].g=g1;
      colores_caras[i].b=b1;
     }
   else //para las caras impares poner otro color
     {colores_caras[i].r=r2;
      colores_caras[i].g=g2;
      colores_caras[i].b=b2;
     }
  }
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
    vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam; //v0//pone los vertices en la zona tam de x y y z
    vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;//v1
    vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;//v2
    vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;//v3
    vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;//v4
    vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;//v5
    vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;//v6
    vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;//v7
	    //    v7----- v6
		//   /|      /|
		//  v3------v2|
		//  | |     | |
		//  | |v4---|-|v5
		//  |/      |/
		//  v0------v1
    // triangulos
    caras.resize(12);
    caras[0]._0=0;caras[0]._1=1;caras[0]._2=3; //v0, v1 y v3 forman un triangulo, siempre al contrario de las agujas
    caras[1]._0=3;caras[1]._1=1;caras[1]._2=2; //v3,v1,v2 "" //vale tambien _0=3,_1=2_2=1
    caras[2]._0=1;caras[2]._1=5;caras[2]._2=2; //v1,v5,v2 lateral de la zona +x
    caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;//v5,v6,v2 
    caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;//v5,v4,v6
    caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;//v4,v7,v6
    caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;//v0,v7,v4
    caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;//v0,v3,v7
    caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;//v3,v2,v7
    caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;//v2,v6,v7
    caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;//v0,v1,v4
    caras[11]._0=1;caras[11]._1=5;caras[11]._2=4; //v1,v5,v4
    //colores de las caras
    colors_random();
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices
vertices.resize(5);//numero de vertices //se hace la base de un cuadrado y se pone un vertice en el centro
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam; // se pone en la base con y =0;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;
        //v4
//     v3----- v2
//   /       /
//  v0------v1
caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4; //v0,v1,v4
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;//v1,v2,v4
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;//v2,v3,v4
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;//v3,v0,v4
caras[4]._0=0;caras[4]._1=1;caras[4]._2=3;//v3,v1,v0
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;//v3,v2,v0
    //colores de las caras
    colors_random();
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
perfil.push_back(aux); //permite añadir al final de la colección un nuevo dato
parametros(perfil,num,0,1,1);//perfil del objeto, num supongo que de vertices, tipo, tapa_inferior,tapa_superior
}

//*************************************************************************
// clase cono
//*************************************************************************
//REVOLUCION:Revolución: genera una malla girando (rotando) una forma alrededor de un eje.
/*La técnica consiste en dibujar el “perfil” del objeto (o más bien, la mitad de este) 
para luego girarlo en torno al eje central y con ello, las superficies de revolución generarán la forma final.*/
_cono::_cono(float radio, float altura, int num)
{
vector<_vertex3f> perfil;
_vertex3f aux;

aux.x=radio; aux.y=0; aux.z=0.0; //zona de abajo
perfil.push_back(aux);//añadir al final de la colección un nuevo dato
aux.x=0.0; aux.y=altura; aux.z=0.0; //zonas de arriba
perfil.push_back(aux);
parametros(perfil,num,1,1,1); //en este caso num será el numero de perfiles que se generan
}
//*************************************************************************
// clase esfera
//*************************************************************************

_esfera::_esfera(float radio, int num1, int num2){
    vector<_vertex3f> perfil;
    _vertex3f aux;
    int i;
    for (i=1;i<num1;i++)//num1 es el numero de puntos que se generan
      {aux.x=radio*cos(M_PI*i/(num1*1.0)-M_PI/2.0);//genera el centro de la esfera en x
       aux.y=radio*sin(M_PI*i/(num1*1.0)-M_PI/2.0);//genera el centro de la esfera en y
       aux.z=0.0;//para rotacioon z en 0 siempre creo
       perfil.push_back(aux);
      }
    parametros(perfil,num2,2,1,1);//num2 es el numero de perfiles que se generaran
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
    
    n_ver=ver_ply.size()/3; //porque en el objeto ply pone x y z lo pone en 3 filas y entoces darás maas vertices
    //y caras de las qe realmente son
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
    colores_caras.resize(n_car);
    srand(10);
    // colores
    float sum;
    int n;
    colores_caras.resize(caras.size());
    for (i=0;i<caras.size();i++){
        if (vertices[caras[i]._0].y>=0){
        colores_caras[i].r=rand()%1000/1000.0;
        colores_caras[i].b=0.0;
        colores_caras[i].g=0.8;    //PARTE DE ARRIBA
    }
    else{
        n=rand()%10;
        sum=rand()%100/500.0;
        if (n<5) colores_caras[i].r=0.251+sum; //PARTE DE ABAJO
        else colores_caras[i].r=0.251-sum;
        if (n>5) colores_caras[i].b=0.805+sum;
        else colores_caras[i].b=0.805-sum;
        if (n>5) colores_caras[i].g=0.816+sum;
        else colores_caras[i].g=0.816-sum;
    }
    }
    
}



//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su)//num es el numero de caras que genera
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;
float radio;

// tratamiento de los vértice
radio=sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);//x^2+y^2

num_aux=perfil.size();
if (tipo==1) num_aux=num_aux-1; //tipo 1 cono PORQUE?
vertices.resize(num_aux*num+2);//Esto es por el numero de vertices mas los puntos de las tapas?
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+ //PORQUE ESTO
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
 if (tipo==2) vertices[total].y=-radio; //tipo 2 == esfera
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

//colores de las caras
colors_random();
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

}

//************************************************************************
//Base camara, antigua  sustentación
//************************************************************************

_baseCamaratripode::_baseCamaratripode() //Base camara ANTIGUA SUSTENTACION
{

base.colors_chess(0.2,0.0,0.0,0.2,0.0,0.0);
rueda.colors_chess(0.4,0.4,0.4,0.4,0.4,0.4);
   
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
    glRotatef(70,0,1,0);
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
//Base camara,   
//************************************************************************

_baseCamara::_baseCamara() //Base camara ANTIGUA SUSTENTACION
{
ancho=1.0;
alto=0.4;
fondo=0.4;
radio=0.15;
base.colors_chess(0.2,0.2,0.2,0.2,0.2,0.2);
rueda.colors_chess(1.0,0.5,0.0,1.0,0.5,0.0);
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
glTranslatef(-0.53,0.14,0.11);
glRotatef(-90,0,0,1);
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
//glColor3f(1.0,1.0,1.0);
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
//rueda.colors_chess(1.0,1.0,0.0,0.0,0.0,1.0);
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
    
//protectores/*

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
glScalef(ancho, alto, fondo);
circulo.draw(modo, r, g, b, grosor);
glPopMatrix();
};

//************************************************************************
// Objetivo 1 //antes brazo
//************************************************************************

_objetivo1::_objetivo1()
{
ancho=0.16; //ancho de x(se pone mas largo el brazo
alto=0.16;
fondo=0.05; //ancho de z se pone mas gordo
rueda.colors_chess(0.1,0.1,0.1,0.1,0.1,0.1);
};


void _objetivo1::draw(_modo modo, float r, float g, float b, float grosor)
{
    glPushMatrix();
    glTranslatef(0.42,0,0);
    glRotatef(240,2,-2,-2);
    glScalef(ancho, fondo, alto);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

};
//************************************************************************
// Objetivo 2 //antes brazo 2
//************************************************************************

_objetivo2::_objetivo2()
{
ancho=0.15; //ancho de x(se pone mas largo el brazo
alto=0.15;
fondo=0.05; //ancho de z se pone mas gordo
rueda.colors_chess(0.4,0.4,0.4,0.4,0.4,0.4);
circulo.colors_chess(0.0,0.8,0.8,0.0,0.8,0.8);
};
void _objetivo2::draw(_modo modo, float r, float g, float b, float grosor)
{
    glPushMatrix();
    glTranslatef(0.45,0,0);
    glRotatef(240,2,-2,-2);
    glScalef(ancho, fondo, alto);
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
rueda.colors_chess(1.3,0.0,0.0,1.3,0.0,0.0);
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

};


void _detalles2::draw(_modo modo, float r, float g, float b, float grosor)
{
    //luz verde
    glPushMatrix();
    glTranslatef(-0.5,0.15,-0.02);
    glRotatef(90,1,0,0);
    glScalef(ancho,fondo,alto);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

    //clistal mirilla
    glPushMatrix();
    glTranslatef(-0.5,0.14,0.109);
    glRotatef(90,0,0,1);
    glScalef(0.06,0.001,0.08);
    base.draw(modo, r, g, b, grosor);
    glPopMatrix();
    
    //boton blanco
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
// camara (montaje del objeto final)
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


