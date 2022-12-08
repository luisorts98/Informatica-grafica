//**************************************************************************
// Práctica 2
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


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
{
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
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
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
    caras[11]._0=4; caras[11]._1=6; caras[11]._2=7;}


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
}
//*************************************************************************
// clase objeto ply
//*************************************************************************
_cilindro::_cilindro(int num, float ancho, float altura)
{
  vector<_vertex3f> nullv;
  parametros(nullv, num, ancho, altura, 0, 1);
}
//*************************************************************************
// clase cono
//*************************************************************************

_cono::_cono(int num, float ancho, float altura)
{
  vector<_vertex3f> nullv;
  parametros(nullv, num, ancho, altura, 0, 2);
}
//*************************************************************************
// clase esfera
//*************************************************************************

_esfera::_esfera(float radio, int n, int m){
  vector<_vertex3f> perfil1;
  _vertex3f aux;
  int i;

  for(i=1; i<n; i++){
    aux.x=radio*cos(M_PI*i/n-M_PI/2.0); //x con el coseno regla de profe, en orden alfabetico // no ponemos dos pi porque queremos dar una vuelta de 180 grados
    aux.y=radio*sin(M_PI*i/n-M_PI/2.0); // y con seno
    aux.z=0;
    perfil1.push_back(aux);
  }
  parametros(perfil1, m, 0, 0, radio, 3);
}
//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply()
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}




int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

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
    /*    colores_caras.resize(n_car)
    colores_caras.color1();
    srand(10);
    for(int i=0; i<n_car;i++){
        if (vertices[caras[i]._0].y>0.0)
           {colores_caras[i].r=rand()%1000/1000.0;
            colores_caras[i].g=0.0;
            
        }else{ colores_caras[i].r=0.0;
            colores_caras[i].g=rand()%1000/1000.0;
            
        }
            colores_caras[i].b=0.0;
    }*/
    return 0;
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num,float ancho, float altura, float radio, int tipo)
{
    int i,j,c;
      _vertex3f vertice_aux; //auxiliar, tiene comp x,y,z
      _vertex3i cara_aux;
      _vertex3f punto;
      int num_aux; //num de vertices en un perfil
//radio =sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);
      // tratamiento de los vértice
      //tipo 2 cono
      if(tipo == 2){

        punto.x=ancho; punto.y=-(altura/2); punto.z=0.0;

        num_aux=1;
        vertices.resize(num_aux*num+3);
        for (j=0;j<num;j++){
          for (i=0;i<num_aux;i++){
              vertice_aux.x=punto.x*cos(2.0*M_PI*j/(1.0*num))+
                            punto.z*sin(2.0*M_PI*j/(1.0*num));
              vertice_aux.z=-punto.x*sin(2.0*M_PI*j/(1.0*num))+
                            punto.z*cos(2.0*M_PI*j/(1.0*num));
              vertice_aux.y=punto.y;
              vertices[i+j*num_aux]=vertice_aux;
          }
        }
      }
      else if(tipo == 0 || tipo == 3){ //tipo 0 rotacion estandar, tipo 3 cilindro
        num_aux=perfil.size();
        vertices.resize(num_aux*num+3);
        for (j=0;j<num;j++){
          for (i=0;i<num_aux;i++){

              vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
              vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
              vertice_aux.y=perfil[i].y;
              vertices[i+j*num_aux]=vertice_aux;
          }
        }
      }
      else if(tipo == 1){ //tipo 1 cilindro


        num_aux=2;

        punto.x=ancho; punto.y=altura/2; punto.z=0.0;
        perfil.push_back(punto);

        punto.x=ancho; punto.y=-(altura/2); punto.z=0.0;
        perfil.push_back(punto);

        vertices.resize(num_aux*num+3);
        for (j=0;j<num;j++){
          for (i=0;i<num_aux;i++){

              vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
              vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
              vertice_aux.y=perfil[i].y;
              vertices[i+j*num_aux]=vertice_aux;
          }
        }
      }

      

      // tratamiento de las caras
    //para una tira usamos el bucle for
    caras.resize(2*num_aux-1);
     c =0;
    for (i=0;i<num_aux-1; i++){ //numeros de segmentos menos 1 num_aux menos1}
        caras[c]._0=0+i;
        caras[c]._1=num_aux+i;
        caras[c]._2=1+i;
        c+=1;
        caras[c]._0=num_aux+i;
        caras[c]._1=num_aux+1+i;
        caras[c]._2=1+i;
        c+=1;
    }
    //PARA EL GIRO COMPLETO FUNCIONA HASTA LA ULTIMA CARA QUE HAY QUE HACER UN TRATAMIENTO ESPECIAL
    //caras.resize(2*num_aux-1)*num;
      caras.resize(2*(num_aux-1)*num+num*2);

      c=0;
      int var, vertic = num*num_aux;

      for(j=0; j<num;j++){
        for(i=0; i<num_aux-1; i++){

          
          caras[c]._0=(j*num_aux+i)%vertic;
          caras[c]._1=((j+1)*num_aux+i+1)%vertic;
          caras[c]._2=((j+1)*num_aux+i)%vertic;
          c++;
          
          caras[c]._0=(j*num_aux+i)%vertic;
          caras[c]._1=(j*num_aux+i+1)%vertic;
          caras[c]._2=((j+1)*num_aux+i+1)%vertic;
          c++;
          
        }

      }


      

      if(tipo == 0 || tipo == 1){
        // tapa inferior
        if (fabs(perfil[0].x)>0.0){
          _vertex3f vertice_tapa;
          _vertex3f vertice_abajo = perfil[num_aux-1];

          vertice_tapa.x=0;
          vertice_tapa.y=vertice_abajo.y;
          vertice_tapa.z=0;

          vertices[num*num_aux+1] = vertice_tapa;

          var=num_aux-1;

          for(int i=0; i<num; i++){ //num-1 -> casi todas de primeras y cara de ult con primero de forma indepe
            caras[c]._0 = var;
            var+=num_aux;
            if(var >= vertic) var = var%vertic;
            caras[c]._1 = var;
            caras[c]._2 = num*num_aux+1;

            c++;
          }
        }

        // tapa superior
        if (fabs(perfil[num_aux-1].x)>0.0){
          _vertex3f vertice_tapa;
          _vertex3f vertice_arriba = perfil[0];

          vertice_tapa.x=0;
          vertice_tapa.y=vertice_arriba.y;
          vertice_tapa.z=0;

          vertices[num*num_aux+2] = vertice_tapa;

          var=0;

          for(int i=0; i<num; i++){
            caras[c]._0 = var;
            var+=num_aux;
            if(var >= vertic) var = var%vertic;
            caras[c]._1 = var;
            caras[c]._2 = num*num_aux+2;

            c++;
          }
        }
      }
      else if(tipo == 2){
        // tapa inferior
        if (fabs(punto.x)>0.0){
          
          _vertex3f vertice_tapa;

          vertice_tapa.x=0;
          vertice_tapa.y=punto.y;
          vertice_tapa.z=0;

          vertices[num*num_aux+1] = vertice_tapa;

          var=num_aux-1;

          for(int i=0; i<num; i++){
            caras[c]._0 = var;
            var+=num_aux;
            if(var >= vertic) var = var%vertic;
            caras[c]._1 = var;
            caras[c]._2 = num*num_aux+1;

            c++;
          }
        }
        // tapa superior
        if (fabs(punto.x)>0.0){

          _vertex3f vertice_tapa;

          vertice_tapa.x=0;
          vertice_tapa.y=altura;
          vertice_tapa.z=0;

          vertices[num*num_aux+2] = vertice_tapa;

          var=0;

          for(int i=0; i<num; i++){
            caras[c]._0 = var;
            var+=num_aux;
            if(var >= vertic) var = var%vertic;
            caras[c]._1 = var;
            caras[c]._2 = num*num_aux+2;

            c++;
          }
        }
      }
      else if(tipo == 3){
        if (fabs(perfil[0].x)>0.0){
          _vertex3f vertice_tapa;

          vertice_tapa.x=0;
          vertice_tapa.y=radio;
          vertice_tapa.z=0;

          vertices[num*num_aux+1] = vertice_tapa;

          var=num_aux-1;

          for(int i=0; i<num; i++){
            caras[c]._0 = var;
            var+=num_aux;
            if(var >= vertic) var = var%vertic;
            caras[c]._1 = var;
            caras[c]._2 = num*num_aux+1;

            c++;
          }
        }
        
        // tapa superior
        if (fabs(perfil[num_aux-1].x)>0.0){
          _vertex3f vertice_tapa;

          vertice_tapa.x=0.0;
          vertice_tapa.y=-radio;
          vertice_tapa.z=0.0;

          vertices[num*num_aux+2] = vertice_tapa;

          var=0;

          for(int i=0; i<num; i++){
            caras[c]._0 = var;
            var+=num_aux;
            if(var >= vertic) var = var%vertic;
            caras[c]._1 = var;
            caras[c]._2 = num*num_aux+2;

            c++;
          }
        }

      }
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
    
}


