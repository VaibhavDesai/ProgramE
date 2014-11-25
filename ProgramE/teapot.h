void wall(double thickness)
{
    glPushMatrix();
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(1.0,thickness,1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}
void tableLeg(double thick,double len)  // draw one table leg
{
    glPushMatrix();
    glTranslated(0,len/2,0);
    glScaled(thick,len,thick);
    glutSolidCube(1.0);
    glPopMatrix();
}
void table(double topWid, double topThick,double legThick,double legLen)
{
    glPushMatrix();
    glTranslated(0,legLen,0);
    glScaled(topWid, topThick,topWid);
    glutSolidCube(1.0);
    glPopMatrix();
    double dist =0.95* topWid/2.0 - legThick/2.0;
    glPushMatrix();
    glTranslated(dist,0,dist);
    tableLeg(legThick,legLen);
    glTranslated(0.0,0.0,-2*dist);
    tableLeg(legThick,legLen);
    glTranslated(-2*dist,0,2*dist);
    tableLeg(legThick,legLen);
    glTranslated(0,0,-2*dist);
    tableLeg(legThick,legLen);
    glPopMatrix();
}
void display7(void)
{
    GLfloat mat_ambient[] = { 0.7f,0.7f,0.7f,1.0f};// gray
    GLfloat mat_diffuse[] = { 0.7f,0.7f,0.7f,1.0f};
    GLfloat mat_specular[] = { 1.0f,1.0f,1.0f,1.0f};
    GLfloat mat_shininess[]={50.0f};
    
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    
    // set the light sources propertis
    GLfloat lightIntensity[] ={ 1.0f,1.0f,1.0f,1.0f};
    GLfloat light_position[] ={ 2.0f,6.0f,3.0f,0.0f};
    glLightfv(GL_LIGHT0 ,GL_POSITION,light_position);
    glLightfv(GL_LIGHT0 ,GL_DIFFUSE,lightIntensity);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.33,1.33, -1,1,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.3,1.3,2.0,0.0,0.25,0.0,0.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated(0.4,0,0.4);
    table(0.6,0.02,0.02,0.3);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.6,0.38,0.5);
    glRotated(30,0,1,0);
    glutSolidTeapot(0.08);
    glPopMatrix();
    wall(0.02);
    glPushMatrix();
    glRotated(90.0,0.0,0.0,1.0);
    wall(0.02);
    glPopMatrix();
    glPushMatrix();
    glRotated(-90.0,1.0,0.0,0.0);
    wall(0.02);
    glPopMatrix();
    glFlush();
}
void init_program7()
{
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1,0.1,0.1,0.0);
}