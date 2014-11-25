GLfloat vertices[4][3] = {{0.0,0.0,1.0},{0.0,1.0,0.0,},{-1.0,-0.5,0.0},{1.0,-0.5,0.0}};
GLfloat color[4][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{0.0,0.0,0.0}};
int n=2;


void triangle(GLfloat *v1,GLfloat *v2,GLfloat *v3)
{
    glBegin(GL_TRIANGLES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glEnd();
}

void tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d)
{
    glColor3fv(color[0]);
    triangle(a, c, b);
    
    glColor3fv(color[1]);
    triangle(a, d, c);
    
    glColor3fv(color[2]);
    triangle(a, d, b);
    
    glColor3fv(color[3]);
    triangle(b, d, c);
}

void divide_tetra(GLfloat *v1,GLfloat *v2,GLfloat *v3,GLfloat *v4,int m)
{
    GLfloat a[6][3];
    int j=0;
    if(m>0)
    {
        for (j=0; j<3; j++) a[0][j] = (v1[j] + v2[j])/2;
        for (j=0; j<3; j++) a[1][j] = (v1[j] + v3[j])/2;
        for (j=0; j<3; j++) a[2][j] = (v1[j] + v4[j])/2;
        for (j=0; j<3; j++) a[3][j] = (v2[j] + v4[j])/2;
        for (j=0; j<3; j++) a[4][j] = (v4[j] + v3[j])/2;
        for (j=0; j<3; j++) a[5][j] = (v2[j] + v3[j])/2;
        
        divide_tetra(v1,a[0], a[1], a[2],m-1);
        divide_tetra(a[0],v2, a[3], a[5],m-1);
        divide_tetra(a[1],a[4], v3, a[5],m-1);
        divide_tetra(a[2], a[3], a[4],v4,m-1);
    }
    else
        tetra(v1, v2, v3, v4);
}


void display2()
{
    glBegin(GL_TRIANGLES);
    divide_tetra(vertices[0], vertices[1], vertices[2], vertices[3], n);
    glEnd();
    glFlush();
    glDisable(GL_DEPTH_TEST);
}

void init_program2()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glFlush();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
    
}