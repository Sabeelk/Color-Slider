//Sabeel Kazi | Computer Graphics | Project 2-2
//mac command: g++ graphics.cpp -framework OpenGL -framework GLUT -Wno-deprecated-declarations
//#include <gl/glut.h>
#include <iostream>
#include <string> 
#include <array>
#include <GLUT/glut.h>

float a[3] = {427.0, 427.0, 427.0}; //stored values of y coordinates (primary values)
float r[3] = {1.0, 1.0, 1.0};       //right interpolation color array
float l[3] = {0.0, 0.0, 0.0};       //left interpolation color array

void myinit(void)
{
    glClearColor(0.10,0.10,0.10,0.0);
    gluOrtho2D (0.0,1000.0,0.0,1000.0);
}

//function for the square representing the gradient
void quads(){
    glColor3f((a[0]-300)/(256.0), (a[1]-300)/(256.0), (a[2]-300)/(256.0));
    glBegin(GL_QUADS);
        glVertex2i(600, 500);                         //bottom left
        glVertex2i(900, 500);                         //bottom right
        glVertex2i(900, 800);                         //top right
        glVertex2i(600, 800);                         //top left
    glEnd();
}

//this function is for the interpolation rectangle, uses the r and l array declared at top
void interpolation(){
    //color is specified for each vertices to creat interpolation gradient
    glBegin(GL_QUADS);
        glColor3f(l[0], l[1], l[2]);
        glVertex2i(550, 200);                         //bottom left

        glColor3f(r[0], r[1], r[2]);
        glVertex2i(950, 200);                         //bottom right

        glColor3f(r[0], r[1], r[2]);
        glVertex2i(950, 300);                         //top right

        glColor3f(l[0], l[1], l[2]);
        glVertex2i(550, 300);                         //top left
    glEnd();
}

//square for the sliders at a center point
void centerQuads(int num, float x, float *y){
    glColor3f(0.50, 0.50, 0.50);
    glBegin(GL_QUADS);
        glVertex2f(x - 20, y[num]-10);
        glVertex2f(x + 20, y[num]-10);
        glVertex2f(x + 20, y[num]+10);
        glVertex2f(x - 20, y[num]+10);
    glEnd();

}

void lines(int x1, int y1, int x2, int y2){
    glLineWidth(1);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
        glVertex2i(x1, y1);                         //v1
        glVertex2i(x2, y2);                         //v2
    glEnd();
}

void text(int x, int y, char c){
    //depending on letter, display different color
    if (c == 'R') glColor3f(1.0, 0.0, 0.0);
    if (c == 'G') glColor3f(0.0, 1.0, 0.0);
    if (c == 'B') glColor3f(0.0, 0.0, 1.0);

    glRasterPos2i(x, y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);

    glEnd();
}

void rgbValues(int x, int y, char c, int s){
    s -= 300;
    //depending on letter, display different color
    if (c == 'R') glColor3f(1.0, 0.0, 0.0);
    if (c == 'G') glColor3f(0.0, 1.0, 0.0);
    if (c == 'B') glColor3f(0.0, 0.0, 1.0);

    //depending on the number of digits, offset to the left for symmetry
    if (s >= 100)       glRasterPos2i(x - 10, y);
    else if (s >= 10)   glRasterPos2i(x - 5, y);
    else                glRasterPos2i(x, y);

    //print each digit of the primary color values in same coordinate
    for(int i=0; i<std::to_string(s).length(); i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, std::to_string(s)[i]); 
    glEnd();
}

void mouse(int mouse, int state, int x, int y){
    y = 1000 - y -128;

    //case for moving the sliders
    if(mouse == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        //specify area for slider one to redisplay
        if(x >= 50 && x <=150 && y >= 300 && y <= 555) 
            a[0] = y;
        else if(x >= 151 && x <=250 && y >= 300 && y <= 555) 
            a[1] = y;
        else if(x >= 251 && x <=350 && y >= 300 && y <= 555) 
            a[2] = y;
        //case for clicking in the interpolation rectangle
        //**not working perfectly
        else if(x>= 550 && x <= 950 && y >= 200 && y <= 300 ){   
            a[0] =  (((r[0]-l[0])/(950.0-550.0)) * (x* 1.0-550.0) + l[0]) + 300.0;
            a[1] =  (((r[1]-l[1])/(950.0-550.0)) * (x*1.0-550.0) + l[1]) + 300.0;
            a[2] =  (((r[2]-l[2])/(950.0-550.0)) * (x*1.0-550.0) + l[2]) + 300.0;
        }
    glutPostRedisplay();
    }
}

void drag(int x, int y){
    y = 1000 - y -128;
    //specify area for slider to redisplay
    if(x >= 50 && x <=150 && y >= 300 && y <= 556) 
        a[0] = y;
    if(x >= 151 && x <=250 && y >= 300 && y <= 556) 
        a[1] = y;
    if(x >= 251 && x <=350 && y >= 300 && y <= 556) 
        a[2] = y;
    glutPostRedisplay();
}

void keyPressed (unsigned char key, int x, int y) { 
    //handle r button press for interpolation
    if(key == 'r'){
        r[0] = (a[0] - 300.0)/(256.0);
        r[1] = (a[1] - 300.0)/(256.0);
        r[2] = (a[2] - 300.0)/(256.0);
    }
    //hndle l button press for interpolation
    else if(key == 'l'){
        l[0] = (a[0] - 300.0)/(256.0);
        l[1] = (a[1] - 300.0)/(256.0);
        l[2] = (a[2] - 300.0)/(256.0);
    }

    glutPostRedisplay();
}  

void render(void)
{   
    glClear( GL_COLOR_BUFFER_BIT);
    glPointSize(10.0);

    //render the three slider lines
    lines(100, 300, 100, 556);
    lines(200, 300, 200, 556);
    lines(300, 300, 300, 556);

    //render the three slider bars
    centerQuads(0, 100, a);
    centerQuads(1, 200, a);
    centerQuads(2, 300, a);

    //render the rgb square    
    quads();

    //location of interpolation square
    interpolation();

    //draw words
    text(93, 250, 'R');
    text(193, 250, 'G');
    text(293, 250, 'B');

    //render the rgb values
    rgbValues(93, 606, 'R', a[0]);
    rgbValues(193, 606, 'G', a[1]);
    rgbValues(293, 606, 'B', a[2]);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500,100);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Color Mixer | Project 2");
    myinit();
    glutDisplayFunc(render);
    glutMotionFunc(drag);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyPressed);
    glutMainLoop();
}

