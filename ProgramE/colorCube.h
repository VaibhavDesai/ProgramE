/*cube is centered at origin */
GLfloat cube_vertices[][3] = {{-1.0,-1.0,1.0},{-1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,-1.0,1.0} ,
{-1.0,-1.0,-1.0},{-1.0,1.0,-1.0},{1.0,1.0,-1.0}, {1.0,-1.0,-1.0}};
/*colors are assigned to the cube_vertices */
 GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0}, 
						{0.0,1.0,0.0}, {0.0,0.0,1.0}, {1.0,1.0,0.0},{1.0,0.0,1.0}, 
						{0.0,1.0,-1.0},{1.0,1.0,-1.0} };
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 1;

void polygon(int a, int b, int c, int d)
{	/* draw a polygon via list of cube_vertices */
	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex3fv(cube_vertices[a]);
		glColor3fv(colors[b]);
		glVertex3fv(cube_vertices[b]);
		glColor3fv(colors[c]);
		glVertex3fv(cube_vertices[c]);
		glColor3fv(colors[d]);
		glVertex3fv(cube_vertices[d]);
	glEnd();
}
void colorcube()
{	/* map cube_vertices to faces */
	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(0,4,7,3);
	polygon(1,2,6,5);
	polygon(4,5,6,7);
	polygon(0,1,5,4);
}
void display5()
{ /* display callback, clear frame buffer and z buffer,
   rotate cube and draw, swap buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	colorcube();
	glFlush();
	glutSwapBuffers();
	
    
	
}

void spinCube()
{	/* idle callback, spin cube 2 degrees about selected axis */
	theta[axis] += 0.5;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;	
	display5();
}
void mouse(int btn, int state, int x, int y)
{	/* mouse callback, selects an axis about which to rotate */
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}
void init_program5(int w, int h)
{
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glutIdleFunc(spinCube);
}
