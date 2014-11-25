//
//  main.c
//  CPE
//
//  Created by vaibhav on 18/11/14.
//  Copyright (c) 2014 VaibhavDesai. All rights reserved.
//

//This the intialization code for openGl in mac.
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "house.h"
#include "tetra.h"
#include "cylinder.h"
#include "liang.h"
#include "colorCube.h"
#include "cohen.h"
#include "teapot.h"
#include "perspective.h"
#include "scanline.h"
#include "mesh.h"

float width = 1200.0;
float height = 900.0;
float buttons_pos[11] = {0.025,0.100,0.175,0.250,0.325,0.400,0.475,0.550,0.625,0.700,0.775};
char *butt_text[11]={"House","Tetrahedron","Cylinder","Lian-Barsky","Color Cube","Sutherland","Tea Pot","Perspective","Scan Line","Mesh","Paint"};
int mouseFlag =0;
int pressed_button = -1;
int userIn = 0;

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

void drawText(float x,float y, char *str,char *fontcolor)
{
    float *color = getColor(fontcolor);
    int len = strlen(str);
    glColor3fv(color);
    glRasterPos2d(x, y);
    for(int i=0;i<len;i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

void init()
{
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,width,0,height);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    
    
}

void drawSideBar()
{
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.50, 0.50);
    glVertex2f(0.0,0.0);
    glVertex2f((width*0.2),0.0);
    glVertex2f((width*0.2),height);
    glVertex2f(0.0, height);
    glEnd();
    glFlush();
    
}

void drawButton(char *str,char *fontColor,char *buttonColor,int x,int y)
{
    float *backgroundColor = getColor(buttonColor);
    glBegin(GL_POLYGON);
    glColor3fv(backgroundColor);
    glVertex2f(x, y);
    glVertex2f(x+(width*0.120), y);
    glVertex2f(x+(width*0.120), y+(height*0.050));
    glVertex2f(x, y+(height*0.050));
    glEnd();
    drawText(x+(width*0.010), y+(height*0.012), str, fontColor);
    
}

void drawHome()
{
    char *str = "Computer Graphics Project - Vaibhav J Desai";
    int len = strlen(str);
    glColor3fv(getColor("purple"));
    glRasterPos2d(300, 700);
    for(int i=0;i<len;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    drawText(500, 650, "12GAEC8070, UVCE", "purple");
    drawText(100, 550, "Paint - This is a paint editor to draw free hand.", "orange");
    drawText(100, 500,"House - :  Program to draw a color cube and spin it using OpenGL transformation matrices.", "orange");
    drawText(100,450, "Tetrahedron - Program to recursively subdivide a tetrahedron to from 3D Sierpinski gasket.", "orange");
    drawText(100, 400, "Cylinder - Program to draw parallelopiped.", "orange");
    drawText(100, 350, "Liang Barsky - Program to implement Liang-Barsky line clipping algorithm ", "orange");
    drawText(100, 300, "Color Cube - Program to draw a color cube and spin it using OpenGL transformation matrices.", "orange");
    drawText(100, 250, "Sutherland - Program to implement the Cohen-Sutherland line-clipping algorithm.", "orange");
    drawText(100, 200, "Tea Pot - Program to draw a simple shaded scene consisting of a tea pot on a table.", "orange");
    drawText(100, 150, "Perspective - Program to draw a color cube and allow the user to move the camera suitably to experiment with perspective viewing.", "orange");
    drawText(100, 100, "Scan Line - Program to fill any given polygon using scan-line area filling algorithm. ", "orange");
    drawText(100, 50, "Mesh - Program to display a set of values { fij } as a rectangular mesh.", "orange");
    
    
}

void display()
{
    //This is to clear the screen.
    glLoadIdentity();
    glClearColor(0.10,0.60,0.30,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //glViewport(0, 0, width, height);//To sets the entire window as the viewport.
    drawSideBar();
    
    
    //This is 45px from the left window, for the window size 700x700
    //Size of each button is 50px in height and 120px in width.
    drawButton("Home", "black", "red",width*0.030, height*0.90);
    for(int i=0;i<11;i++)
        drawButton(butt_text[i],"red","yellow",(width*0.030),height*buttons_pos[i]);
    
    glFlush();
    
    //This sets the drawing area as the view port.
    glViewport((width*0.2), 0, width-(width*0.2), height);
    glScissor((width*0.2), 0, width-(width*0.2), height);//This is to create the drawing area.
    glEnable(GL_SCISSOR_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawHome();
    glFlush();
}

void standardSettings()
{
    glViewport((width*0.2), 0, width-(width*0.2), height);
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1000,0,900);
    glMatrixMode(GL_MODELVIEW);
    glutIdleFunc(NULL);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glDisable(GL_DEPTH_TEST);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glutKeyboardFunc(NULL);
    
}

int inRange(float clickx,float clicky,int posx,int posy)
{
    if((clickx>posx && clickx<(posx+width*0.120)) && (clicky<posy&&clicky>posy-(height*0.05)))
    {
        printf("clicked!!\n");
        return 1;
    }
    else
    {
        printf("not clikced\n");
        return 0;
    }
}

void userInput(int button_no)
{
    if(button_no == 1)
    {
        drawText(400, 400, "Enter the angle in Terminal", "red");
        glFlush();
        rotate_theta = -180;
        printf("Enter the angle\n");
        scanf("%f",&rotate_theta);
    }
    
    if(button_no == 2)
    {
        drawText(400, 350, "Enter the value of 'N' in Terminal", "red");
        glFlush();
        printf("Enter the value of N\n");
        n=1;
        scanf("%d",&n);
    }
    
    if(button_no == 3)
    {
        drawText(350, 350, "Enter the value of N and M in Terminal", "red");
        glFlush();
        printf("Enter the value of N\n");
        scanf("%d",&n_rec);
        printf("Enter the value of M\n");
        scanf("%d",&n_cir);
    }
    if(button_no == 4)
    {
        drawText(350, 350, "Enter the value of P1 and P2 in Terminal", "red");
        glFlush();
        printf("Enter the value of x0 and y0\n");
        scanf("%lf %lf",&x40,&y40);
        printf("Enter the value of x1 and y1\n");
        scanf("%lf %lf",&x41,&y41);
    }
    if(button_no == 6)
    {
        drawText(350, 350, "Enter the value of P1 and P2 in Terminal", "red");
        glFlush();
        printf("Enter the value of x0 and y0\n");
        scanf("%lf %lf",&x60,&y60);
        printf("Enter the value of x1 and y1\n");
        scanf("%lf %lf",&x61,&y61);
    }
    if(button_no == 9)
    {
        drawText(350, 350, "Enter the value of P1,P2,P3 and P4 in Terminal", "red");
        glFlush();
        printf("Enter the value of x0 and y0\n");
        scanf("%f %f",&x90,&y90);
        printf("Enter the value of x1 and y1\n");
        scanf("%f %f",&x91,&y91);
        printf("Enter the value of x2 and y2\n");
        scanf("%f %f",&x92,&y92);
        printf("Enter the value of x3 and y3\n");
        scanf("%f %f",&x92,&y92);
    }
    if(button_no == 10)
    {
        drawText(350, 350, "Enter the value of N and M", "red");
        glFlush();
        printf("Enter the value of N and M\n");
        scanf("%d %d",&max10x,&max10y);
        
    }
}

void displayProg()
{
    if(pressed_button == 0)
    {
        standardSettings();
        drawHome();
        pressed_button = -1;
        
    }
    if(pressed_button == 1)//Rotate House program.
    {
        /*system("gcc -o hello /Users/vaibhavdesai/Documents/college/CG/CG_programs/house/house/main.c -framework Carbon -framework OpenGL -framework GLUT");
         system("./hello");*/
        standardSettings();
        if (userIn == 1)userInput(1);
        init_program1();
        display1();
        pressed_button=-1;
        glFlush();
    }
    
    if(pressed_button == 2)
    {
        standardSettings();
        if (userIn == 1)userInput(2);
        init_program2();
        display2();
        pressed_button=-1;
    }
    
    if(pressed_button == 3)
    {
        standardSettings();
        if (userIn == 1)userInput(3);
        init_program3();
        display3();
        pressed_button=-1;
    }
    if(pressed_button == 4)
    {
        standardSettings();
        if (userIn == 1)userInput(4);
        init_program4();
        display4();
        pressed_button=-1;
    }
    if(pressed_button == 5)
    {
        standardSettings();
        mouseFlag = 5;
        init_program5(1000, 700);
        pressed_button=-1;
    }
    if(pressed_button == 6)
    {
        standardSettings();
        if (userIn == 1)userInput(6);
        init_program6();
        display6();
        pressed_button=-1;
    }
    if(pressed_button == 7)
    {
        standardSettings();
        init_program7();
        display7();
        pressed_button=-1;
    }
    if(pressed_button == 8)
    {
        standardSettings();
        mouseFlag = 8;
        init_program8(1000, 700);
        pressed_button=-1;
    }
    if(pressed_button == 9)
    {
        standardSettings();
        if (userIn == 1)userInput(9);
        init_program9();
        display9();
        pressed_button=-1;
    }
    if(pressed_button == 10)
    {
        standardSettings();
        if (userIn == 1)userInput(10);
        init_program10();
        display10();
        pressed_button=-1;
    }
    if(pressed_button == 11)
    {
        standardSettings();
        system("gcc -o paint /Users/vaibhavdesai/Desktop/cg/testing/testing/paint.c -framework Carbon -framework OpenGL -framework GLUT");
        system("./paint");
        pressed_button = -1;
    }
    glFlush();
}

void myMouse(int button,int state,int x,int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        for(int i=0;i<11;i++)
            if(inRange(x,y,width*0.030,height*(1-buttons_pos[i])))
            {
                pressed_button = i+1;
            }
        if(inRange(x, y,width*0.030 ,height*(1-0.9)))
        {
            pressed_button = 0;
        }
        
    }
    if(mouseFlag == 5 || mouseFlag == 8)
    {
        if((x>width*0.2&&x<width)&&(y>0&&y<height))
        {
            if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
            if(button==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
            if(button==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
        }
    }
    displayProg();
}

void reshape(int w,int h)
{
    width = w;
    height = h;
    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

//This is the main function.
int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(width,height);
    glutCreateWindow("CG Program Editor");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}