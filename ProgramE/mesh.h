
int max10x =10;
int max10y =15;
#define dx 15
#define dy 10
void init_program10()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1000,0.0,700);
}

void display10(void)
{
    GLfloat x[100]={0.0},y[100]={0.0};
    GLfloat x0=200,y0=200;
    GLint i,j;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    for(i=0;i<max10x;i++)
        x[i]=x0+i*dx;
    for(j=0;j<max10y;j++)
        y[j]=y0+j*dy;
    
    glColor3f(1.0,0.0,0.0);
    for(i=0;i<max10x-1;i++)
        for(j=0;j<max10y-1;j++)
        {
            glColor3f(1.0,0.0,0.0);
            glBegin(GL_LINE_LOOP);
            glVertex2f(x[i],y[j]);
            glVertex2f(x[i],y[j+1]);
            glVertex2f(x[i+1],y[j+1]);
            glVertex2f(x[i+1],y[j]);
            glEnd();
            glFlush();
        }
}