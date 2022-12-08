//**************************************************************************
// Práctica 2
//**************************************************************************

#include <GLUT/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, CONO, CILINDRO, ESFERA, EXTRUSION, CAMARA} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=650,Window_high=650;


// objetos
bool light2on = false;
bool light1on = true;
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply;
_rotacion rotacion;
_cono cono(1,2,6);
_cilindro cilindro(1,2,6);
_esfera esfera(1, 16, 16);
_camara camara;
_extrusion *extrusion;


float giro=0;
float giro3=0;
float giro2=0;
float giro4=0;
float giro5=0;
float giro6=0;
float giro7=0;
int flag2=0;//para que se mueva con limites sin que se pare al llegar al limite
int flag3=0;
int flag4=0;
// _objeto_ply *ply;

float light_angle_y =0.0;

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
    
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos/Users/luisortsferrer/Downloads/Práctica3 (1)/practica_objetos_B3.cc
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
    case CUBO: cubo.draw(modo,1.0,0.0,0.0,5);break;
    case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,5);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,5);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,5);break;
        case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,5);break;
        case CONO: cono.draw(modo,1.0,0.0,0.0,5);break;
        case ESFERA: esfera.draw(modo,1.0,0.0,0.0,5);break;
        case CAMARA: camara.draw(modo,1.0,0.0,0.0,5);break;
        case EXTRUSION: extrusion->draw(modo,1.0,0.0,0.0,5);break;
   
    }

}



//**************************************************************************
//luces
//***************************************************************************
void luces(){ //creacioj de luz blanca
GLfloat luz_ambiente[ ]={0.2,0.2,0.2,1.0};
GLfloat luz_difusa[ ]={1.0,1.0,1.0,1.0}; // blanca
GLfloat luz_especular[ ]={1.0,1.0,1.0,1.0}; //el ultimo paramentro es un parametro que indica 
GLfloat posicion_luz[ ]={0.0,20.0,20.0,1.0}; //si ponemos een el ultimo parametro ponemos 0 todos los rayos de luz son paralelos

glLightfv(GL_LIGHT1,GL_AMBIENT,luz_ambiente); //son cuatro porque hay cuatro componentes
glLightfv(GL_LIGHT1,GL_DIFFUSE,luz_difusa);
glLightfv(GL_LIGHT1,GL_SPECULAR,luz_especular);
glLightfv(GL_LIGHT1,GL_POSITION,posicion_luz);


GLfloat posicion_luz2[] = {20.0,0.0,0.0,1.0};
GLfloat luz_ambiente2[] = {0.2, 0.2, 0.2, 1.0};
GLfloat luz_difusa2[] = {0.2, 0.2, 0.2, 1.0};
GLfloat luz_especular2[] = {0.5, 0.4, 0.3, 1.0};

glLightfv(GL_LIGHT2,GL_AMBIENT,luz_ambiente2); //son cuatro porque hay cuatro componentes
glLightfv(GL_LIGHT2,GL_DIFFUSE,luz_difusa2);
glLightfv(GL_LIGHT2,GL_SPECULAR,luz_especular2);
glLightfv(GL_LIGHT2,GL_POSITION,posicion_luz2);

glPushMatrix();
glRotatef(light_angle_y,0,1,0);
glLightfv(GL_LIGHT2,GL_POSITION,posicion_luz2);
glPopMatrix();

//glDisable(GL_LIGHT0);
if(light1on){
    glEnable(GL_LIGHT1);
}
else{
    glDisable(GL_LIGHT1);
}


if(light2on){ //PARA ENECEN LUZ
    glEnable(GL_LIGHT2);
}
else {
    glDisable(GL_LIGHT2);
}
} 

 //si ponemos een el ultimo parametro ponemos 0 todos los rayos de luz son paralelos
/*void moverLuz()
{

		angulo_luz1 += 0.5;
		glPushMatrix();
		glRotated(angulo_luz1, 0, 1, 0);
		glLightfv(GL_LIGHT0, GL_POSITION, posicion_luz1);
		glPopMatrix();

		glutPostRedisplay();
}*/

//**************************************************************************
//
//***************************************************************************

void draw(void)
{
clean_window();
change_observer();
luces();
draw_axis();
draw_objects();
glutSwapBuffers();



}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
luces(); //crear la función para hacer lo de las luces
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
        switch (toupper(Tecla1)){
            case 'Q':exit(0);
            case '1':modo=POINTS;break;
            case '2':modo=EDGES;break;
            case '3':modo=SOLID;break;
            case '4':modo=SOLID_COLORS;break;
            case '5':modo=SOLID_FLAT;break;
            case '6':modo=SOLID_SMOOTH;break;
                case 'P':t_objeto=PIRAMIDE;break;
                case 'C':t_objeto=CUBO;break;
                case 'I':if(light2on)light2on=false;
                         else light2on=true;
                         break;
                case 'V':if(light1on)light1on=false;
                         else light1on=true;
                         break;
                case 'O':t_objeto=OBJETO_PLY;break;
                case 'R':t_objeto=ROTACION;break;
                case 'L':t_objeto=CILINDRO;break;
                case 'N':t_objeto=CONO;break;
                case 'E':t_objeto=ESFERA;break;
                case 'A':t_objeto=CAMARA;break;
                case 'X':t_objeto=EXTRUSION;break;
            case '9':giro=3;giro2=3;giro3=0.001;giro4=1;giro5=5;giro6=5;giro7=5;break;
            case '0':giro=0;giro2=0;giro3=0;giro4=0;giro5=0;giro6=0;giro7=0;break;
                
    }
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
    case GLUT_KEY_LEFT:Observer_angle_y--;break;
    case GLUT_KEY_RIGHT:Observer_angle_y++;break;
    case GLUT_KEY_UP:Observer_angle_x--;break;
    case GLUT_KEY_DOWN:Observer_angle_x++;break;
    case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
    case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
        //PRACTICA 3
    case GLUT_KEY_F1:light_angle_y+=15;break;//era giro_cabina excavadora.giro_camara+=5
    case GLUT_KEY_F2:light_angle_y-=15;break; //eragexcavadora.giro_camara-=5
    case GLUT_KEY_F3:camara.zoom+=0.001;
         if (camara.zoom > camara.zoom_max)
             camara.zoom = camara.zoom_max;break;
    case GLUT_KEY_F4:camara.zoom-=0.001;
         if (camara.zoom < camara.zoom_min)
             camara.zoom = camara.zoom_min;break;
    case GLUT_KEY_F5:camara.movimientovertical+=5;
         if (camara.movimientovertical > camara.movimientovertical_max)
             camara.movimientovertical = camara.movimientovertical_max;break;
    case GLUT_KEY_F6:camara.movimientovertical-=1;
         if (camara.movimientovertical < camara.movimientovertical_min)
             camara.movimientovertical = camara.movimientovertical_min;break;
    case GLUT_KEY_F7:camara.giro_monitor+=1;
         if (camara.giro_monitor > camara.giro_monitor_max)
             camara.giro_monitor = camara.giro_monitor_max;break;
    case GLUT_KEY_F8:camara.giro_monitor-=1;
         if (camara.giro_monitor < camara.giro_monitor_min)
             camara.giro_monitor = camara.giro_monitor_min;break;
    case GLUT_KEY_F9:camara.giro_ruedin+=7;camara.giro_ruedin2+=7;camara.giro_ruedin3+=7;break;
    case GLUT_KEY_F10:camara.giro_ruedin-=7;camara.giro_ruedin2-=7;camara.giro_ruedin3-=7;break;
    }
glutPostRedisplay();
}

//***************************************************************************
// Funcion de animación automatica
//***************************************************************************

void movimiento(){
   // excavadora.giro_cabina+=5;
    camara.giro_camara+=giro;
    camara.giro_ruedin+=giro5;
    camara.giro_ruedin2+=giro6;
    camara.giro_ruedin3+=giro7;
    if (flag2==0) camara.giro_monitor+=giro2;///todo esto para los limites de los movimientos
    else camara.giro_monitor-=giro2;
    
    if (camara.giro_monitor > camara.giro_monitor_max)
    {camara.giro_monitor = camara.giro_monitor_max;
        flag2=1;}
if (camara.giro_monitor < camara.giro_monitor_min)
{ camara.giro_monitor = camara.giro_monitor_min;
    flag2=0;}
    
if (flag3==0) camara.zoom+=giro3;///todo esto para los limites de los movimientos
else camara.zoom-=giro3;
    
if (camara.zoom > camara.zoom_max)
{camara.zoom = camara.zoom_max;
    flag3=1;}
if (camara.zoom < camara.zoom_min)
{ camara.zoom = camara.zoom_min;
    flag3=0;}
    
if (flag4==0) camara.movimientovertical+=giro4;///todo esto para los limites de los movimientos
else camara.movimientovertical-=giro4;
if (camara.movimientovertical > camara.movimientovertical_max)
{camara.movimientovertical = camara.movimientovertical_max;
    flag4=1;}
if (camara.movimientovertical < camara.movimientovertical_min)
{ camara.movimientovertical = camara.movimientovertical_min;
    flag4=0;}
    glutPostRedisplay();
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica el color para limpiar la ventana    (r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
 
// perfil

vector<_vertex3f> perfil, poligono;
_vertex3f aux;

aux.x=1.0; aux.y=-1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.5; aux.y=0.0; aux.z=0.0; //puesto por el profesor
perfil.push_back(aux);
aux.x=1.0; aux.y=1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.5; aux.y=1.2; aux.z=0.0; //puesto por el profesor
perfil.push_back(aux);

rotacion.parametros(perfil,6,0,1,1);
//rotacion.parametros("sombrero");
aux.x=1.0; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);
aux.x=1.0; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-0.8; aux.y=0.0; aux.z=0.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);

extrusion= new _extrusion(poligono, 0.25, 1.0, 0.25);

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 3");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

glutIdleFunc(movimiento); //Para animación automatica
//glutIdleFunc(moverLuz);//REVISAR DE LA P4
// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);
 



//ply = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
