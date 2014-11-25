//
//  main.c
//  vcx
//
//  Created by vaibhav on 31/10/14.
//  Copyright (c) 2014 vaibhav. All rights reserved.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <string.h>

//Variable Initilization
//This defines the dimentions of the window.
int WIDTH=600;
int HEIGHT=600;
double arr[5000][2];//This is the buffer that stores the co-ordinates of the screen.
int z=0;//This is used to keep track of the index of the arr.
int offset=0;//This is used to keep track of offset index of the arr, so that we avoid the line_strip.
int first=1;//This is to check wheather its the first window(Welcome screen).
int flag=0;
int flag1=0;
int press=0;

float perIncWidth = 0;
float perIncHeight = 0;

//Button1 initilization.
float button1posx = 0.0;
float button1posy = 0.0;
float button1width = 0.0;
float button1height = 0.0;
float toolBoxWidth = 0.0;

//redColor initilization.
float buttonRedposx = 0.0;
float buttonRedposy = 0.0;
float buttonRedwidth = 0.0;
float buttonRedheight = 0.0;

//blueColor initilization.
float buttonBlueposx = 0.0;
float buttonBlueposy = 0.0;
float buttonBluewidth = 0.0;
float buttonBlueheight = 0.0;

//greenColor initilization.
float buttonGreenposx = 0.0;
float buttonGreenposy = 0.0;
float buttonGreenwidth = 0.0;
float buttonGreenheight = 0.0;


//blackColor initilization.
float buttonBlackposx = 0.0;
float buttonBlackposy = 0.0;
float buttonBlackwidth = 0.0;
float buttonBlackheight = 0.0;

//purpleColor initilization.
float buttonPurpleposx = 0.0;
float buttonPurpleposy = 0.0;
float buttonPurplewidth = 0.0;
float buttonPurpleheight = 0.0;

//orangeColor initilization.
float buttonOrangeposx = 0.0;
float buttonOrangeposy = 0.0;
float buttonOrangewidth = 0.0;
float buttonOrangeheight = 0.0;


float *brushColor;


//Return the RGB values for the given color.
float *getColor(char *color)
{
    //RGB values of the prominent colors.
    static float red[] = {1.0,0.0,0.0};
    static float green[] = {0.0,1.0,0.0};
    static float blue[] = {0.0,0.0,1.0};
    static float yellow[] = {1.0,1.0,0.0};
    static float purple[] = {1.0,0.0,1.0};
    static float cyan[] = {1.0,0.0,1.0};
    static float white[] = {1.0,1.0,1.0};
    static float orange[] = {1.0,0.5,0.0};
    static float black[] = {0.0,0.0,0.0};
    if(strcmp(color,"red")==0) return red;
    if(strcmp(color,"green")==0) return green;
    if(strcmp(color,"blue")==0) return blue;
    if(strcmp(color,"yellow")==0) return yellow;
    if(strcmp(color,"purple")==0) return purple;
    if(strcmp(color,"cyan")==0) return cyan;
    if(strcmp(color,"white")==0) return  white;
    if(strcmp(color,"orange")==0) return orange;
    return black;
    
}
void init()
{
    glClearColor( 0.0, 0.0, 0.0, 1.0);
    glMatrixMode( GL_PROJECTION);
    gluOrtho2D(0.0,WIDTH,0.0,HEIGHT);
    memset(arr,0,5000);
    glPointSize(20.0);
}

//This draws the text at given coordinates and in given color.
void drawText(char *str,float x,float y,char *fontColor)
{
    int i;
    int len=strlen(str);
    float *color = getColor(fontColor);
    glColor3fv(color);
    glRasterPos2f(x,y);
    for(i=0;i<len;i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
}

//This is to clear the screen.
void resetAll()
{
    memset(arr,0,5000);
    z=0;
}

///OPENGL MAPPING///
float getOpenGLX(int x)
{
    double ox = x/ (double)WIDTH*(WIDTH);
    return ox;
}

float getOpenGLY(int y)
{
    double oy = (1 - y/ (double) HEIGHT)*HEIGHT;
    return oy;
}

void reDrawLines(int LL,int UL)
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0,0.0,0.0);
    for(int i=LL+1;i<UL;i++)
    {
        glVertex2f(arr[i][0],arr[i][1]);
    }
    glEnd();
}
//This is used to draw lines, from offset to z index of the array "arr"
void drawLines(float *Color)
{
    
    if(flag)
    {
        int UL=0,LL=0;
        for(int i=0;i<z;i++)
        {
            if(arr[i][0] == -1.000000)
            {
                LL = UL;
                UL = i;
                reDrawLines(LL, UL);
            }
        }
    }
    else{
    glBegin(GL_LINE_STRIP);
    glColor3fv(Color);
    for(int i=offset+1;i<z;i++)
    {
        glVertex2f(arr[i][0],arr[i][1]);
    }
    glEnd();
    }
}

//This adds the x,y coordinates of the mouse to the array arr.
void addValue(int x,int y)
{
    arr[z][0]=getOpenGLX(x);
    arr[z++][1]=getOpenGLY(y);
}

void myMouseStat(int button,int state,int x, int y)
{
    //Convert the coordinates in the current system.
    float posx = getOpenGLX(x);
    float posy = getOpenGLY(y);
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        //This is to start with welcome screen.
        if(first)
        {
            first=0;
            glClearColor(1.0, 1.0, 1.0, 1.0);//To clear up the "welcome" text.
            glClear( GL_COLOR_BUFFER_BIT);
            
        }
        //This is the first button, clear the button.
        if((posx>=button1posx && posx<=(button1posx+button1width)) &&(posy>=button1posy && posy<=(button1posy+button1height)))
        {
            printf("Button1 pressed");
            glClearColor(1.0, 1.0, 1.0, 1.0);//To clear up the "welcome" text.
            resetAll();
            glClear(GL_COLOR_BUFFER_BIT);
            press = 1;
        }
        
        if((posx>=buttonRedposx && posx<=(buttonRedposx+buttonRedwidth)) &&(posy>=buttonRedposy && posy<=(buttonRedposy+buttonRedheight)))
        {
            printf("ButtonRed pressed");
            brushColor = getColor("red");
            press = 1;
        }
        if((posx>=buttonBlueposx && posx<=(buttonBlueposx+buttonBluewidth)) &&(posy>=buttonBlueposy && posy<=(buttonBlueposy+buttonBlueheight)))
        {
            printf("ButtonBlue pressed");
            brushColor = getColor("blue");
            press = 1;
        }
        
        if((posx>=buttonGreenposx && posx<=(buttonGreenposx+buttonGreenwidth)) &&(posy>=buttonGreenposy && posy<=(buttonGreenposy+buttonGreenheight)))
        {
            printf("ButtonGreen pressed");
            brushColor = getColor("green");
            press = 1;
        }
        
        if((posx>=buttonOrangeposx && posx<=(buttonOrangeposx+buttonOrangewidth)) &&(posy>=buttonOrangeposy && posy<=(buttonOrangeposy+buttonOrangeheight)))
        {
            printf("ButtonOrange pressed");
            brushColor = getColor("orange");
            press = 1;
        }
        
        if((posx>=buttonPurpleposx && posx<=(buttonPurpleposx+buttonPurplewidth)) &&(posy>=buttonPurpleposy && posy<=(buttonPurpleposy+buttonPurpleheight)))
        {
            printf("ButtonPurple pressed");
            brushColor = getColor("purple");
            press = 1;
        }
        if((posx>=buttonBlackposx && posx<=(buttonBlackposx+buttonBlackwidth)) &&(posy>=buttonBlackposy && posy<=(buttonBlackposy+buttonBlackheight)))
        {
            printf("ButtonBlack pressed");
            brushColor = getColor("black");
            press = 1;
        }
    }
    if(button==GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        offset = z;
        if(press)
            press =0;
        if(first == 0 && press == 0)
        addValue(-1, -1);
        
        
        
    }
}

void myPressedMove(int x,int y)
{
    addValue(x,y);
}

void drawBox(GLfloat posx,GLfloat posy,GLfloat w,GLfloat h,char *boxColor,float thickness)
{
    float *color = getColor(boxColor);
    //float *backgroundColor = getColor(background);
    glLineWidth(thickness);//set the thickness of the line
    glColor3f(color[0], color[1], color[2]);//set the outLine color of the box
    glBegin(GL_POLYGON);
    glVertex2f(posx,posy);
    glVertex2f(posx+w, posy);
    glVertex2f(posx+w, posy+h);
    glVertex2f(posx, posy+h);
    glEnd();
}

void drawToolBar()
{
    toolBoxWidth = (20*WIDTH)/100;//20% of the width of the total window.
    button1posx = (10*toolBoxWidth)/100;//10% of the width of the toolbox window.
    button1posy = (66*HEIGHT)/100; //66% of the height of the toolbox.
    button1width = (66*toolBoxWidth)/100;//66% of the width of the toolbox.
    button1height = (13*HEIGHT)/100;//13% of the height of the toolbox.
    
    //redColor initilization.
    buttonRedposx = (10*toolBoxWidth)/100;
    buttonRedposy = (40*HEIGHT)/100;
    buttonRedwidth = ((20*toolBoxWidth)/100);
    buttonRedheight = (5*HEIGHT)/100;
    
    //blueColor initilization.
    buttonBlueposx = (10*toolBoxWidth)/100;
    buttonBlueposy = (30*HEIGHT)/100;
    buttonBluewidth = ((20*toolBoxWidth)/100);
    buttonBlueheight = (5*HEIGHT)/100;
    
    //greenColor initilization.
    buttonGreenposx = (40*toolBoxWidth)/100;
    buttonGreenposy = (40*HEIGHT)/100;
    buttonGreenwidth = ((20*toolBoxWidth)/100);
    buttonGreenheight = (5*HEIGHT)/100;
    
    
    //blackColor initilization.
    buttonBlackposx = (70*toolBoxWidth)/100;
    buttonBlackposy = (30*HEIGHT)/100;
    buttonBlackwidth = ((20*toolBoxWidth)/100);
    buttonBlackheight = (5*HEIGHT)/100;
    
    //purpleColor initilization.
    buttonPurpleposx = (70*toolBoxWidth)/100;
    buttonPurpleposy = (40*HEIGHT)/100;
    buttonPurplewidth = ((20*toolBoxWidth)/100);
    buttonPurpleheight = (5*HEIGHT)/100;
    
    //orangeColor initilization.
    buttonOrangeposx = (40*toolBoxWidth)/100;
    buttonOrangeposy = (30*HEIGHT)/100;
    buttonOrangewidth = ((20*toolBoxWidth)/100);
    buttonOrangeheight = (5*HEIGHT)/100;
    
    
    drawBox(0.0, 0.0,toolBoxWidth,HEIGHT,"yellow",2.0);//To draw the tools bar.
    
    drawBox(button1posx, button1posy,button1width,button1height,"red",2.0);//Button1
    drawText("Clear All",(17.0*toolBoxWidth)/100,(71.0*HEIGHT)/100,"green");//17% of the toolbox width and 71% of toolbox height.
    
    //Red color brush.
    drawBox(buttonRedposx,buttonRedposy,buttonRedwidth,buttonRedheight, "red", 2.0);
    //Green color brush.
    drawBox(buttonGreenposx, buttonGreenposy,buttonGreenwidth, buttonGreenheight, "green", 2.0);
    //Yellow color brush.
    drawBox(buttonPurpleposx,buttonPurpleposy,buttonPurplewidth, buttonPurpleheight, "purple", 2.0);
    //Blue color brush.
    drawBox(buttonBlueposx,buttonBlueposy,buttonBluewidth,buttonBlueheight, "blue", 2.0);
    //Orange color brush.
    drawBox(buttonOrangeposx,buttonOrangeposy,buttonOrangewidth, buttonOrangeheight, "orange", 2.0);
    //Blue color brush.
    drawBox(buttonBlackposx,buttonBlackposy,buttonBlackwidth,buttonBlackheight, "black", 2.0);
    
}

void reCalCoordinates()
{
    for(int i=0;i<z;i++)
    {
        if(arr[i][0] != -1.000000)
        {
            arr[i][0] = arr[i][0]+perIncWidth;
            arr[i][1] = arr[i][1]+perIncHeight;
        }
    }
}

//This is the display func.
void myDisplay()
{
    if(first)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        drawText("Paint Editor",(41.0*WIDTH)/100,(50.0*HEIGHT)/100,"green");//The text starts from 41% and 50% of height and width of the window.
    }
    else
    {
        drawToolBar();
        glScissor(toolBoxWidth, 0, WIDTH, HEIGHT);//This is to create the drawing area.
        glEnable(GL_SCISSOR_TEST);
        drawLines(brushColor);
        if(flag)
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            reCalCoordinates();
            drawLines(brushColor);
            flag =0;
        }
    }
    
    glFlush();
    glutPostRedisplay();
}
void changeSize(int width,int height)
{
    glDisable(GL_SCISSOR_TEST);
    perIncWidth = (((float)width - (float)WIDTH));
    perIncHeight = (((float)height - (float)HEIGHT));
    //printf("%d\n",width);
    //printf("%d\n",WIDTH);
    //printf("%F\n",perIncWidth);
    WIDTH = width;
    HEIGHT = height;
    flag = 1;
    glViewport(0, 0, width, height); // reset the viewport
    glMatrixMode(GL_PROJECTION); // modify the projection matrix
    glLoadIdentity();            // load an identity matrix into the projection matrix
    glOrtho(0, width, 0, height, -1.0, 1.0); // create new projection matrix
    
    /// Important!!! You need to switch back to the model-view matrix
    /// or else your OpenGL calls are modifying the projection matrix!
    glMatrixMode(GL_MODELVIEW); // return to the model matrix
    glLoadIdentity();
}

int main( int argc, char ** argv)
{
    
    glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_SINGLE| GLUT_RGB);
    glutInitWindowPosition( 100, 100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow( "Testing");
    init();
    brushColor = getColor("yellow");
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouseStat);
    glutMotionFunc(myPressedMove);
    glutReshapeFunc(changeSize);
    glutMainLoop();
    return 0;
}