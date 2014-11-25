GLfloat ver[][3] = {{-1.0,-1.0,1.0},{-1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,-1.0,1.0},{-1.0,-1.0,-1.0},
    {-1.0,1.0,-1.0},{1.0,1.0,-1.0}, {1.0,-1.0,-1.0}};
GLfloat colors_8[][3]={{0.0,0.0,0.0},{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,0.0},{1.0,0.0,1.0},{0.0,1.0,1.0},{1.0,1.0,1.0}};
void polygon_8(int a,int b,int c,int d)
{
    glBegin(GL_POLYGON);
    glColor3fv(colors_8[a]);
    glVertex3fv(ver[a]);
    glColor3fv(colors_8[b]);
    glVertex3fv(ver[b]);
    glColor3fv(colors_8[c]);
    glVertex3fv(ver[c]);
    glColor3fv(colors_8[d]);
    glVertex3fv(ver[d]);
    glEnd();
}
void colorcube_8()
{
    polygon_8(0,3,2,1);polygon_8(2,3,7,6);polygon_8(0,4,7,3);
    polygon_8(1,2,6,5);polygon_8(4,5,6,7);polygon_8(0,1,5,4);
}
GLfloat theta_8[]={0.0,0.0,0.0};
GLdouble viewer[]={0.0,0.0,5.0};


void display8()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(viewer[0],viewer[1],viewer[2],0.0,0.0,0.0,0.0,1.0,0.0);
    glRotatef(theta_8[0],1.0,0.0,0.0);
    glRotatef(theta_8[1],0.0,1.0,0.0);
    glRotatef(theta_8[2],0.0,0.0,1.0);
    colorcube_8();
    glFlush();
    glutSwapBuffers();
}
void spincube()
{
    theta_8[axis]+=0.5;
    if(theta_8[axis]>360.0) theta_8[axis]-=360.0;
    display8();
}
void keys(unsigned char key,int x,int y)
{
    if(key=='X') viewer[0]-=1.0;
    if(key=='x') viewer[0]+=1.0;
    if(key=='Y') viewer[1]-=1.0;
    if(key=='y') viewer[1]+=1.0;
    if(key=='Z') viewer[2]-=1.0;
    if(key=='z') viewer[2]+=1.0;
    display8();
}
void init_program8(int w,int h)
{
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutKeyboardFunc(keys);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
        glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
    else
        glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
    
    gluPerspective(50.0,w/h,1.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glutIdleFunc(spincube);
}
