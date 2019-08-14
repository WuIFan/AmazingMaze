// final.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



int cam = 0,cam_rotate=0,j_time=0,j_flag=0,cam_on=0,god=0,start_tag=0;
float cam_x = 0.0, cam_y = 0.0, cam_z = 1.0, camed_x = 0.0, camed_y = 0.0, camed_z = 0.0, cam_angle = 270, pi = 3.14159265358979323846f, cam_rad = 0.0;
float play_x = 0.0, play_y = 0.0, play_z = 0.0, w_w = 1024, w_h = 768;
static GLint fogMode;
void maze(); void hit();
void drawfloor();
void jump();
void x_z_color();
void floor_x_15R();
void floor_x_15L();
void floor_x_10R();
void floor_x_10L();
void floor_x_5R();
void floor_x_5L();

void floor_z_15F();
void floor_z_15B();
void floor_z_10F();
void floor_z_10B();
void floor_z_5F();
void floor_z_5B();
void floor_z_5finish();

void floor_y_5FT();
void floor_y_5RT();
void floor_y_5RD();
void floor_y_5FD();
void floor_y_5LD();
void floor_y_5LT();
void floor_y_5BD();
void floor_y_5BT();

void hintf();
void hintb();
void hintr();
void hintl();
void hints();

void t();
void start();
void finish();
void fog();
void init(void)
{
	//GLfloat ambient[] = { 0.0, 0.0, 0.0, 0.0 };
	//GLfloat diffuse[] = { 0.0, 0.0, 0.0, 0.0 };
	//GLfloat specular[] = { 0.0, 0.0, 0.0, 0.0 };
	//GLfloat position[] = { 100.0, 1.0, 1.0, 1.0 };
	GLfloat ambient[] = { 0.3, 0.7, 0.7, 1.0 };
	GLfloat diffuse[] = { 0.3, 0.7, 0.7, 1.0 };
	GLfloat specular[] = { 0.3, 0.7, 0.7, 1.0 };
	GLfloat position[] = { 100.0, 100.0, 0.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat local_view[] = { 0.0 };

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
}



void display(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	if (start_tag == 1 && god == 0)	fog();
	else glDisable(GL_FOG);
	
	glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	if (start_tag == 0){		
		start();
	}
	if (start_tag == -1){
		finish();
	}
	if (start_tag == 1){

		switch (cam_rotate){
		case -1:
			cam_angle = cam_angle - 10;
			if (cam_angle <= -360)
				cam_angle = 0;
			cam_rotate = 0;
			break;
		case 1:
			cam_angle = cam_angle + 10;
			if (cam_angle >= 360)
				cam_angle = 0;
			cam_rotate = 0;
			break;
		}
		cam_rad = pi*cam_angle / 180;

		switch (cam){
		case 1://w		
			cam_x += 0.1*(float)cos(cam_rad);
			printf("%f\n", cos(cam_rad));
			cam_z += 0.1*(float)sin(cam_rad);
			cam = 0;
			break;
		case 2://a
			//cam_x -= 0.1;
			//camed_x -= 0.1;
			cam_x += 0.1*(float)sin(cam_rad);
			cam_z -= 0.1*(float)cos(cam_rad);
			cam = 0;
			break;
		case 3://s		
			cam_x -= 0.1*(float)cos(cam_rad);
			cam_z -= 0.1*(float)sin(cam_rad);
			cam = 0;
			break;
		case 4://d
			//cam_x += 0.1;
			//camed_x += 0.1;
			cam_x -= 0.1*(float)sin(cam_rad);
			cam_z += 0.1*(float)cos(cam_rad);
			cam = 0;
			break;
		}
		if (j_flag == 1){
			if (j_time <= 400){
				jump();
			}
			else{
				j_time = 0;
				j_flag = 0;
			}
		}
		if (god == 1){
			if (cam_on == 1){
				cam_y += 1;
				cam_on = 0;
			}
			else if (cam_on == -1){
				cam_y -= 1;
				cam_on = 0;
			}
		}
		
	}
	//camed_x = (float)sin(cam_rad);
	
	glTranslatef(0.0, -cam_y, 0.0);
	drawfloor();
	
	//glTranslatef(-cam_x, 0.0, -cam_z);
	
	/*glPushMatrix();
	t();
	glEnable(GL_TEXTURE_2D);	
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTranslatef(0, 2, -10);
	glTexCoord2f(0, 1); 
	glVertex3f(-1.0, 1.0, -5.0);
	glTexCoord2f(1, 0); 
	glVertex3f(-1.0, -1.0, -5.0);
	glTexCoord2f(1, 1); 
	glVertex3f(1.0, -1.0, -5.0);
	glTexCoord2f(0, 1); 
	glVertex3f(1.0, 1.0, -5.0);
	glEnd();	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();*/
		
	//glTranslatef(-cam_x, 0.0, -cam_z);
	//glRotatef(cam_angle, 0, 1, 0);
	//gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0, 1, 0);
	//gluLookAt(cam_x, cam_y, cam_z, camed_x, camed_y+cam_y, camed_z, 0, 1, 0);
	
	if (god == 0){
		hit();
	}
	if (cam_x >= 6.5 && cam_x <= 13.5 && cam_z >= 0.0 &&cam_z <= 10.0 && cam_y == 0)
		start_tag = -1;

	camed_x = float(cam_x + 1 * cos(cam_rad));
	camed_z = float(cam_z + 1 * sin(cam_rad));
	play_x = cam_x;
	play_y = cam_y;
	play_z = cam_z-1;
	
	gluLookAt(cam_x, cam_y, cam_z, camed_x, camed_y + cam_y, camed_z, 0, 1, 0);
	
	maze();
	
	
	printf("%f,%f,%f\n", cam_x, cam_y, cam_z);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glutSwapBuffers();	
}
void jump(){
	//cam_y = 0.0588*j_time - 0.00098*j_time*j_time / 2;
	//cam_y = 0.03*j_time - 0.0001*j_time*j_time / 2;//600
	cam_y = 0.05*j_time - 0.00025*j_time*j_time / 2;//400
	j_time++;
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h)
{	
	w_w = w;
	w_h = h;
	glViewport(0.0, 0.0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (GLfloat)w / (GLfloat)h / 2, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	keyboard(' ', 0, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		cam = 1;
		break;
	case 'a':
		cam = 2;
		break;
	case 's':
		cam = 3;
		break;
	case 'd':
		cam = 4;
		break;
	case 'q':
		cam_rotate = -1;
		break;
	case 'e':
		cam_rotate = 1;
		break;
	case ' ':
		//j_flag = 1;
		break;
	case '1':
		cam_on = 1;
		break;
	case'2':
		cam_on = -1;
		break;
	case'g':
		if (god == 1){
			god = 0;
		}
		else{
			god = 1;
		}
		break;
	case 'p':
		start_tag = 1;
		keyboard(' ',x,y);
		break;
	}
	
	display();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Amazing Maze");
	init();
	glewInit();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
void maze(){	
	glTranslatef(0.0, -2.0, 5);


	floor_z_10F();//(x,y,z):(0,0,5.0)->(0,0,-5.0)起點			
	glTranslatef(0.0, 0.0, -10.0);
	floor_y_5FT();//(x,y,z):(0,0,-5.0)->(0,3,-5.0)向上	
	glTranslatef(0.0, 5.0, 0.0);	
	hintf();
	floor_z_10F();//直線(1)	
	glTranslatef(0.0, 0.0, -10.0);	
	glPushMatrix(); {
		floor_z_15F();//直線(2)
		glTranslatef(0.0, 0.0, -15.0);		
		floor_z_5F();//直線(3)共30
		glTranslatef(0.0, 0.0, -5.0);
		floor_x_15L();//錯路c(1)
		glTranslatef(-15.0, 0.0, 0.0);
		floor_x_5L();//錯路c(2)
		glTranslatef(-5.0, 0.0, 0.0);
		floor_z_5B();//錯路d
		glTranslatef(0.0, 0.0, 5.0);
	}glPopMatrix();
	floor_x_15R();//右直線a
	glTranslatef(15.0, 0.0, 0.0);

	glPushMatrix(); {
		floor_y_5BT();//向上b
		glTranslatef(0.0, 5.0, 0.0);	
		hintb();
		floor_z_5B();//直線b(1)
		glTranslatef(0.0, 0.0, 5.0);
		glPushMatrix(); {
			floor_z_10B();//直線b(2)
			glTranslatef(0.0, 0.0, 10.0);
			floor_x_10R();//錯路a
			glTranslatef(10.0, 0.0, 0.0);
		}glPopMatrix();
		floor_x_5L();//左直線a(1)
		glTranslatef(-5.0, 0.0, 0.0);
		glPushMatrix(); {
			floor_x_5L();//左直線a(2)
			glTranslatef(-5.0, 0.0, 0.0);
			floor_y_5BT();//向上c
			glTranslatef(0.0, 5.0, 0.0);
			hintb();
			floor_z_10B();//錯路b
			glTranslatef(0.0, 0.0, 10.0);
		}glPopMatrix();
		floor_z_10F();//直線c
		glTranslatef(0.0, 0.0, -10.0);
		glPushMatrix(); {
			floor_z_10F();//錯路g
			glTranslatef(0.0, 0.0, -10.0);
			floor_x_15R();//錯路h
			glTranslatef(15.0, 0.0, 0.0);
		}glPopMatrix();
		/*glPushMatrix(); {			
			floor_x_10L();
			glTranslatef(-10.0, 0.0, 0.0);
			floor_z_5B();
			glTranslatef(0.0, 0.0, 5.0);
		}glPopMatrix();*/
		floor_y_5RT();//向上d
		glTranslatef(0.0, 5.0, 0.0);
		hintr();
		floor_x_15R();//直線d
		glTranslatef(15.0, 0.0, 0.0);
		glPushMatrix(); {
			floor_z_10B();//錯路i
			glTranslatef(0.0, 0.0, 10.0);
			floor_x_5R();//錯路j
			glTranslatef(5.0, 0.0, 0.0);
		}glPopMatrix();
		floor_z_15F();//直線e
		glTranslatef(0.0, 0.0, -15.0);
		floor_x_15L();//直線f(1)
		glTranslatef(-15.0, 0.0, 0.0);
		floor_x_15L();//直線f(2)
		glTranslatef(-15.0, 0.0, 0.0);		
		hints();
		floor_y_5BD();//向下a
		glTranslatef(0.0, -5.0, 0.0);
		floor_z_10B();//直線g
		glTranslatef(0.0, 0.0, 10.0);
		glPushMatrix(); {//錯路kkk
			floor_y_5BT();
			glTranslatef(0.0, 5.0, 0.0);
			hintb();
			floor_z_10B();
			glTranslatef(0.0, 0.0, 10.0);
			floor_x_5L();
			glTranslatef(-5.0, 0.0, 0.0);
			/*floor_y_5BD();
			glTranslatef(0.0, -5.0, 0.0);
			floor_z_5B();
			glTranslatef(0.0, 0.0, 5.0);*/
		}glPopMatrix();
		hints();
		floor_y_5LD();//向下b
		glTranslatef(0.0, -5.0, 0.0);
		floor_x_5L();//直線h(1)
		glTranslatef(-5.0, 0.0, 0.0);
		floor_z_10B();//直線h(2)
		glTranslatef(0.0, 0.0, 10.0);
		/*glPushMatrix(); {
			floor_y_5LD();
			glTranslatef(0.0, -5.0, 0.0);
			floor_x_5L();
			glTranslatef(-5.0, 0.0, 0.0);
			floor_z_10B();
			glTranslatef(0.0, 0.0, 10.0);
			floor_x_5R();
			glTranslatef(5.0, 0.0, 0.0);
		}glPopMatrix();*/
		hints();
		floor_y_5RD();//向下c
		glTranslatef(0.0, -5.0, 0.0);
		floor_x_15R();//直線i(1)
		glTranslatef(15.0, 0.0, 0.0);
		floor_x_5R();//直線i(2)
		glTranslatef(5.0, 0.0, 0.0);
		floor_z_10B();//直線j
		glTranslatef(0.0, 0.0, 10.0);		
		floor_z_5finish();//直線j(2)
		glTranslatef(0.0, 0.0, 5.0);
	}glPopMatrix();

	
	floor_z_10F();//錯路e
	glTranslatef(0.0, 0.0, -10.0);	
	floor_x_15R();//錯路f
	
}
void hit(){
	//起點
	if (cam_z <= 6.0&&cam_z >= -6.0&& cam_x >= 2.5&& cam_x <= 3.5 && cam_y == 0)
		cam_x = 2.4;	
	if (cam_z <= 6.0&&cam_z >= -6.0&&cam_x <= -2.5&&cam_x >= -3.5&&cam_y == 0)
		cam_x = -2.4;	
	if (cam_x <= 2.6&&cam_x >= -2.6&&cam_z >= 5.0&&cam_y == 0)
		cam_z = 4.9;
	//向上
	if (cam_x <= 2.5&&cam_x >= -2.5&&cam_z <= -4.0 &&cam_z >= -5.0 &&cam_y == 0){//跳上去
		cam_y = 3.0;
		cam_z = -6.1;
	}
	if (cam_x <= 2.5&&cam_x >= -2.5&&cam_z >= -6.0&&cam_y == 3){//跳下去		
		cam_y = 0.0;
		cam_z = -3.9;
	}
	//直線
	if (cam_z <= -6.0&&cam_z >= -9.0&&cam_x >= 2.5&&cam_x <= 3.5&&cam_y == 3)//右開口
		cam_x = 2.4;
	if (cam_z <= -16.0&&cam_z >= -36.0&&cam_x >= 2.5&&cam_x <= 3.5&&cam_y == 3)
		cam_x = 2.4;

	if (cam_z <= -5.0&&cam_z >= -30.0&& cam_x <= -2.5 && cam_x >= -2.6 &&cam_y == 3)
		cam_x = -2.4;
	if (cam_x <= 2.6&&cam_x >= -2.6&&cam_z <= -35.0&&cam_z >= -36.0&&cam_y == 3){
		cam_z = -34.9;
	}
	//錯路c
	if (cam_x >= -17.5&&cam_x <= -2.5&& cam_z >= -30.0 && cam_z <= -29.0 &&cam_y == 3)
		cam_z = -30.1;
	if (cam_x >= -22.5&&cam_x <= -2.5&&cam_z <= -35.0 &&cam_z >= -36.0 &&cam_y == 3)
		cam_z = -34.9;
	if (cam_z >= -36.0&& cam_z <= -29.0&&cam_x <= -22.5 && cam_x <= -22.5 && cam_y == 3)
		cam_x = -22.4;
	//錯路d
	if (cam_z <= -25.0&&cam_z >= -30.0&& cam_x >= -17.5&& cam_x <= -16.5 && cam_y == 3)
		cam_x = -17.6;
	if (cam_z <= -25.0&&cam_z >= -30.0&&cam_x <= -22.5&&cam_x >= -23.5&&cam_y == 3)
		cam_x = -22.4;
	if (cam_x <= -16.5&&cam_x >= -23.5&&cam_z >= -25.0&&cam_z <= -24.0&&cam_y == 3)
		cam_z = -25.1;
	//右直線a
	if (cam_x >= 2.5&&cam_x <= 12.5&& cam_z >= -10.0&& cam_z <= -9.0&&cam_y == 3)
		cam_z = -10.1;
	if (cam_x >= 2.5&&cam_x <= 12.5&&cam_z <= -15.0&&cam_z >= -16.0&&cam_y == 3)
		cam_z = -14.9;
	if (cam_z >= -16.0&& cam_z <= -9.0&&cam_x >= 17.5 && cam_x <= 18.5 && cam_y == 3)
		cam_x = 17.4;
	//錯路e
	if (cam_z <= -15.0&&cam_z >= -20.0&& cam_x >= 17.5&& cam_x <= 18.5 && cam_y == 3)
		cam_x = 17.4;
	if (cam_z <= -15.0&&cam_z >= -25.0&&cam_x <= 12.5&&cam_x >= 11.5&&cam_y == 3)
		cam_x = 12.6;
	if (cam_x <= 18.5&&cam_x >= 11.5&&cam_z <= -25.0&&cam_z >= -26.0&&cam_y == 3)
		cam_z = -24.9;
	//錯路f
	if (cam_x >= 17.5&&cam_x <= 32.5&& cam_z >= -20.0&& cam_z <= -19.0&&cam_y == 3)
		cam_z = -20.1;
	if (cam_x >= 17.5&&cam_x <= 32.5&&cam_z <= -25.0&&cam_z >= -26.0&&cam_y == 3)
		cam_z = -24.9;
	if (cam_z >= -26.0&& cam_z <= -19.0&&cam_x >= 32.5 && cam_x <= 33.5 && cam_y == 3)
		cam_x = 32.4;
	//向上b
	if (cam_x >= 12.5&&cam_x <= 17.5&&cam_z >= -11.0&&cam_z <= -10.0&&cam_y == 3){//跳上去
		cam_y = 6.0;
		cam_z = -8.9;
	}
	if (cam_x >= 12.5&&cam_x <= 17.5&&cam_z <= -9.0&&cam_z >= -10.0&&cam_y == 6){//跳下去		
		cam_y = 3;
		cam_z = -11.1;
	}
	//直線b
	if (cam_z >= -5.0 && cam_z <= 5.0 && cam_x <= 12.5&& cam_x >= 11.5 && cam_y == 6)//開
		cam_x = 12.6;
	if (cam_z >= -10.0 && cam_z <= -0.1 && cam_x >= 17.5&& cam_x <= 18.5 && cam_y == 6)//開
		cam_x = 17.4;
	if (cam_x >= 11.5 && cam_x <= 18.5 && cam_z >= 5.0&& cam_z <= 6.0 && cam_y == 6)
		cam_z = 4.9;
	//錯路a
	if (cam_x >= 17.5 && cam_x <= 27.5 && cam_z <= 0.0 && cam_z >= -1.0 && cam_y == 6)
		cam_z = 0.1;
	if (cam_x >= 17.5 && cam_x <= 27.5 && cam_z >= 5.0 && cam_z <= 6.0 && cam_y == 6)
		cam_z = 4.9;
	if (cam_z >= -1.0 && cam_z <= 6.0 && cam_x >= 27.5 && cam_x <= 28.5 && cam_y == 6)
		cam_x = 27.4;
	//左直線a
	if (cam_x >= 2.5&&camed_x <= 7.5&&camed_z >= -5.0 && camed_z <= -4.0 &&cam_y == 6)
		cam_z = -4.9;
	if (cam_x >= 2.5&&camed_x <= 7.4&&camed_z <= -10.0&&camed_z >= -11.0&&cam_y == 6)//開
		cam_z = -9.9;	
	if (cam_z >= -11.0 && cam_z <= -4.0 && cam_x <= 2.5 && cam_x >= 2.4 && cam_y == 6)
		cam_x = 2.6;
	//向上c
	if (cam_x >= 2.5&&cam_x <= 7.5&&cam_z >= -6.0&&cam_z <= -5.0&&cam_y == 6){//跳上去
		cam_y = 9.0;
		cam_z = -3.9;
	}
	if (cam_x >= 2.5&&cam_x <= 7.5&&cam_z <= -4.0 &&cam_z >= -4.1 &&cam_y == 9){//跳下去		
		cam_y = 6;
		cam_z = -6.1;
	}
	//錯路b
	if (cam_z <= 5 && cam_z >= -5.0&&cam_x <= 2.5&&cam_x >= 1.5&&cam_y == 9)
		cam_x = 2.6;
	if (cam_z <= 5 && cam_z >= -5.0&&cam_x >= 7.5&&cam_x <= 8.5&&cam_y == 9)
		cam_x = 7.4;
	if (cam_x >= 2.4&&cam_x <= 7.6&&cam_z >= 5.0&&cam_z <= 6.0 && cam_y == 9)
		cam_z = 4.9;
	//直線c
	if (cam_z >= -20.0&&cam_z <= -10.0&&cam_x <= 7.5&&cam_x >= 7.4&&cam_y == 6)
		cam_x = 7.6;
	if (cam_z >= -15.0&&cam_z <= -10.0&&cam_x >= 12.5&&cam_x <= 13.5&&cam_y == 6)
		cam_x = 12.4;
	//if (cam_x >= 7.5&&cam_x <= 12.5&&cam_z <= -20 && cam_y == 6)
	//	cam_z = -19.9;
	//向上d
	if (cam_z >= -20.0&&cam_z <= -15.0&&cam_x >= 11.5&&cam_x <= 12.5&&cam_y == 6){//跳上去
		cam_y = 9.0;
		cam_x = 13.6;
	}
	if (cam_z >= -20.0&&cam_z <= -15.0&&cam_x <= 13.5 &&cam_x >= 12.5 &&cam_y == 9){//跳下去		
		cam_y = 6;
		cam_x = 11.4;
	}
	//錯路g
	if (cam_z >= -30.0&&cam_z <= -20.0&&cam_x <= 7.5&&cam_x >= 7.4&&cam_y == 6)
		cam_x = 7.6;
	if (cam_z >= -25.0&&cam_z <= -20.0&&cam_x >= 12.5&&cam_x <= 13.5&&cam_y == 6)
		cam_x = 12.4;
	if (cam_x >= 6.5&&cam_x <= 13.5&&cam_z <= -30.0 && cam_z >= -31.0 && cam_y == 6)
		cam_z = -29.9;
	//錯路h
	if (cam_x >= 12.5 && cam_x <= 27.5 && cam_z <= -30.0 && cam_z >= -31.0 && cam_y == 6)
		cam_z = -29.9;
	if (cam_x >= 12.5 && cam_x <= 27.5 && cam_z >= -25.0 && cam_z <= -24.0 && cam_y == 6)
		cam_z = -25.1;
	if (cam_z >= -31.0 && cam_z <= -24.0 && cam_x >= 27.5 && cam_x <= 28.5 && cam_y == 6)
		cam_x = 27.4;
	//直線d
	if (cam_x >= 12.5 && cam_x <= 22.5 && cam_z <= -20.0 && cam_z >= -21.0 && cam_y == 9)//開
		cam_z = -19.9;
	if (cam_x >= 12.5 && cam_x <= 22.5 && cam_z >= -15.0 && cam_z <= -14.0 && cam_y == 9)
		cam_z = -15.1;
	if (cam_z >= -21.0 && cam_z <= -14.0 && cam_x >= 27.5 && cam_x <= 28.5 && cam_y == 9)
		cam_x = 27.4;
	//錯路i
	if (cam_z >= -15.0&&cam_z <= -5.0&&cam_x <= 22.5&&cam_x >= 21.5&&cam_y == 9)
		cam_x = 22.6;
	if (cam_z >= -15.0&&cam_z <= -10.0&&cam_x >= 27.5&&cam_x <= 28.5&&cam_y == 9)
		cam_x = 27.4;
	if (cam_x >= 21.5&&cam_x <= 28.5&&cam_z >= -5.0&&cam_z <= -4.0 && cam_y == 9)
		cam_z = -5.1;
	//錯路j
	if (cam_x >= 27.5 && cam_x <= 32.5 && cam_z <= -10.0 && cam_z >= -11.0 && cam_y == 9)
		cam_z = -9.9;
	if (cam_x >= 27.5 && cam_x <= 32.5 && cam_z >= -5.0 && cam_z <= -4.0 && cam_y == 9)
		cam_z = -5.1;
	if (cam_z >= -11.0 && cam_z <= -4.0 && cam_x >= 32.5 && cam_x <= 33.5 && cam_y == 9)
		cam_x = 32.4;
	//直線e
	if (cam_z >= -29.9&&cam_z <= -20.0&&cam_x <= 22.5&&cam_x >= 21.5&&cam_y == 9)//開
		cam_x = 22.6;
	if (cam_z >= -35.0&&cam_z <= -20.0&&cam_x >= 27.5&&cam_x <= 28.5&&cam_y == 9)
		cam_x = 27.4;
	if (cam_x >= 21.5&&cam_x <= 28.5&&cam_z <= -35.0&&cam_z >= -36.0 && cam_y == 9)
		cam_z = -34.9;
	//直線f
	if (cam_x >= -7.5 && cam_x <= 22.5 && cam_z <= -35.0 && cam_y == 9)
		cam_z = -34.9;
	if (cam_x >= -2.5 && cam_x <= 22.5 && cam_z >= -30.0 && cam_z<=-29.0 && cam_y == 9)
		cam_z = -30.1;
	//向下a
	if (cam_x >= -7.5&&cam_x <= -2.5&&cam_z <= -29 && cam_z >= -30 && cam_y == 6){//跳上去
		cam_y = 9.0;
		cam_z = -31.1;
	}
	if (cam_x >= -7.5&&cam_x <= -2.5&&cam_z >= -31 &&cam_z <= -30 &&cam_y == 9){//跳下去		
		cam_y = 6;
		cam_z = -28.9;
	}
	//直線g
	if (cam_z >= -30&&cam_z <= -25.0&&cam_x <= -7.5&&cam_x >= -7.6&&cam_y == 6)
		cam_x = -7.4;
	if (cam_z >= -30.0&&cam_z <= -20.0&&cam_x >= -2.5 &&cam_x <= -2.4 &&cam_y == 6)
		cam_x = -2.6;	
	//錯路kkk
	if (cam_x >= -7.5&&cam_x <= -2.5&&cam_z >= -21.0 && cam_z <= -20.0 && cam_y == 6){//跳上去
		cam_y = 9.0;
		cam_z = -18.9;
	}
	if (cam_x >= -7.5&&cam_x <= -2.5&&cam_z <= -19.0 && cam_z >= -20.0 && cam_y == 9){//跳下去		
		cam_y = 6.0;
		cam_z = -21.1;
	}
	//
	if (cam_z >= -20.0&&cam_z <= -10.0&&cam_x >= -2.5&&cam_x <= -1.5&&cam_y == 9)
		cam_x = -2.6;
	if (cam_z >= -20.0&&cam_z <= -15.0&&cam_x <= -7.5&&cam_x >= -8.5&&cam_y == 9)
		cam_x = -7.4;
	if (cam_x >= -8.5&&cam_x <= -1.5&&cam_z >= -10.0&&cam_z <= -9.0 && cam_y == 9)
		cam_z = -10.1;
	//
	if (cam_x >= -12.5 && cam_x <= -7.5 && cam_z <= -15.0 && cam_z >= -16.0 && cam_y == 9)
		cam_z = -14.9;
	if (cam_x >= -12.5 && cam_x <= -7.5 && cam_z >= -10.0 && cam_z <= -9.0 && cam_y == 9)
		cam_z = -10.1;
	if (cam_z >= -16.0 && cam_z <= -9.0 && cam_x <= -12.5 && cam_x >= -13.5 && cam_y == 9)
		cam_x = -12.4;
	//向下b
	if (cam_z >= -25.0&&cam_z <= -20.0&&cam_x >= -8.5 && cam_x <= -7.5 && cam_y == 3){//跳上去
		cam_y = 6.0;
		cam_x = -6.4;
	}
	if (cam_z >= -25.0&&cam_z <= -20.0&&cam_x <= -6.5 && cam_x >= -7.5 && cam_y == 6){//跳下去		
		cam_y = 3.0;
		cam_x = -8.6;
	}
	//直線h
	if (cam_z >= -25 && cam_z <= -10.0&&cam_x <= -12.5&&cam_x >= -13.5&&cam_y == 3)
		cam_x = -12.4;
	if (cam_z >= -20.0&&cam_z <= -10.0&&cam_x >= -7.5 &&cam_x <= -6.4 &&cam_y == 3)
		cam_x = -7.6;
	if (cam_x <= -7.5&&cam_x >= -12.5&&cam_z >= -10.0 &&cam_z <= -9.0 && cam_y == 3)
		cam_z = -10.1;
	if (cam_x <= -6.5&&cam_x >= -13.5&&cam_z <= -25.0 &&cam_z >= -26.0 && cam_y == 3)
		cam_z = -24.9;
	//向下c
	if (cam_z >= -15.0&&cam_z <= -10.0&&cam_x <= -6.5 && cam_x >= -7.5 && cam_y == 0){//跳上去
		cam_y = 3.0;
		cam_x = -8.6;
	}
	if (cam_z >= -15.0&&cam_z <= -10.0&&cam_x >= -8.5 && cam_x <= -7.5 && cam_y == 3){//跳下去		
		cam_y = 0.0;
		cam_x = -6.4;
	}
	//直線i
	if (cam_x >= -7.5 && cam_x <= 7.5 && cam_z >= -10.0 && cam_z <= -9.0 && cam_y == 0)
		cam_z = -10.1;
	if (cam_x >= -7.5 && cam_x <= 12.5 && cam_z <= -15.0 && cam_z >= -16.0 && cam_y == 0)
		cam_z = -14.9;
	if (cam_z >= -16.0 && cam_z <= -9.0 && cam_x >= 12.5 && cam_x <= 13.5  && cam_y == 0)
		cam_x = 12.4;
	//直線j
	if (cam_z >= -10.0 && cam_z <= 5.0&&cam_x <= 7.5&&cam_x >= 6.5&&cam_y == 0)
		cam_x = 7.6;
	if (cam_z >= -10.0 && cam_z <= 5.0&&cam_x >= 12.5 &&cam_x <= 13.5 &&cam_y == 0)
		cam_x = 12.4;
	if (cam_x >= 6.5 && cam_x <= 13.5 && cam_z >= 5.0 &&cam_z <= 6.0 && cam_y == 0)
		cam_z = 4.9;	
}
void drawfloor(){	
	glColor3f(0.0, 0.5, 0.5);
	glBegin(GL_QUADS);	
	glVertex3f(500.0, -100.0, -500.0);
	glVertex3f(-500.0, -100.0, -500.0);
	glVertex3f(-500.0, -100.0, 500.0);
	glVertex3f(500.0, -100.0, 500.0);
	glEnd();
	
}
void x_z_color(){
	glColor3f(1.0, 0.1, 0.5);
}
void floor_z_5F(){
	glPushMatrix();
	{
		//glColor3f(1.0, 0.0, 0.0);
		x_z_color();
		glTranslatef(0.0, 0.0, -2.5);
		glScalef(5.0, 1.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_z_5B(){
	glPushMatrix();
	{
		//glColor3f(1.0, 0.0, 0.0);
		x_z_color();
		glTranslatef(0.0, 0.0, 7.5);
		glScalef(5.0, 1.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_z_5finish(){
	glPushMatrix();
	{
		glColor3f(0.0, 0.0, 0.0);		
		glTranslatef(0.0, 0.0, 7.5);
		glScalef(5.0, 1.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_z_10F(){
	glPushMatrix();
	{
		x_z_color();
		glTranslatef(0.0, 0.0, -5.0);
		glScalef(5.0, 1.0, 10.0);
		glutSolidCube(1);

		/*glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTranslatef(0.0, 0.0, -5.0);
		
		glTexCoord2f(0, 0);		glVertex3f(-2.5, 0.0, 5.0);
		glTexCoord2f(1, 0);		glVertex3f(2.5, 0.0, 5.0);
		glTexCoord2f(1, 1);		glVertex3f(2.5, 0.0,  -5.0);
		glTexCoord2f(0, 1);		glVertex3f(-2.5, 0.0, -5.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();*/

	}glPopMatrix();
}
void floor_z_10B(){
	glPushMatrix();
	{
		//glColor3f(1.0, 0.0, 0.0);
		x_z_color(); 
		glTranslatef(0.0, 0.0, 10.0);
		glScalef(5.0, 1.0, 10.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_z_15F(){
	glPushMatrix();
	{
		//glColor3f(1.0, 0.0, 0.0);
		x_z_color();
		glTranslatef(0.0, 0.0, -7.5);
		glScalef(5.0, 1.0, 15.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_z_15B(){
	glPushMatrix();
	{
		//glColor3f(1.0, 0.0, 0.0);
		x_z_color(); 
		glTranslatef(0.0, 0.0, 12.5);
		glScalef(5.0, 1.0, 15.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_x_15R(){
	glPushMatrix();
	{		
		x_z_color(); 
		glTranslatef(10.0, 0.0, 2.5);
		glScalef(15.0, 1.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_x_15L(){
	glPushMatrix();
	{
		//glColor3f(0.0, 1.0, 0.0);
		x_z_color(); 
		glTranslatef(-10.0, 0.0, 2.5);
		glScalef(15.0, 1.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_x_5R(){
	glPushMatrix();
	{
		//glColor3f(0.0, 1.0, 0.0);
		x_z_color(); 
		glTranslatef(5.0, 0.0, 2.5);
		glScalef(5.0, 1.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_x_5L(){
	glPushMatrix();
	{
		//glColor3f(0.0, 1.0, 0.0);
		x_z_color(); 
		glTranslatef(-5.0, 0.0, 2.5);
		glScalef(5.0, 1.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_x_10R(){
	glPushMatrix();
	{
		//glColor3f(0.0, 1.0, 0.0);
		x_z_color(); 
		glTranslatef(7.5, 0.0, 2.5);
		glScalef(10.0, 1.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_x_10L(){
	glPushMatrix();
	{
		//glColor3f(0.0, 1.0, 0.0);
		x_z_color(); 
		glTranslatef(-7.5, 0.0, 2.5);
		glScalef(10.0, 1.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_y_5FT(){
	glPushMatrix();
	{
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(0.0, 2.0, -0.25);
		glScalef(5.0, 5.0, 0.5);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_y_5FD(){
	glPushMatrix();
	{
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(0.0, -3.0, -0.25);
		glScalef(5.0, 5.0, 0.5);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_y_5RT(){
	glPushMatrix();
	{
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(2.75, 2.0, 2.5);
		glScalef(0.5, 5.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_y_5RD(){
	glPushMatrix();
	{
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(2.25, -3.0, 2.5);
		glScalef(0.5, 5.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_y_5LD(){
	glPushMatrix();
	{
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(-2.25, -3.0, 2.5);
		glScalef(0.5, 5.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_y_5LT(){
	glPushMatrix();
	{
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(-2.75, 2.0, 2.5);
		glScalef(0.5, 5.0, 5.0);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_y_5BT(){
	glPushMatrix();
	{
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(0.0, 2.0, 5.25);
		glScalef(5.0, 5.0, 0.5);
		glutSolidCube(1);
	}glPopMatrix();
}
void floor_y_5BD(){
	glPushMatrix();
	{
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(0.0, -3.0, 4.75);
		glScalef(5.0, 5.0, 0.5);
		glutSolidCube(1);
	}glPopMatrix();
}
void hint_color(){
	glColor3f(0.8, 0.0, 0.2);
}
void hintf(){
	hint_color();
	glBegin(GL_QUADS);
	glVertex3f(-2.5, 0.501, 0.0);
	glVertex3f(2.5, 0.501, 0.0);
	glVertex3f(2.5, 0.501, -5.0);
	glVertex3f(-2.5, 0.501, -5.0);
	glEnd();
}
void hintb(){
	hint_color();
	glBegin(GL_QUADS);
	glVertex3f(-2.5, 0.501, 10.0);
	glVertex3f(2.5, 0.501, 10.0);
	glVertex3f(2.5, 0.501, 5.0);
	glVertex3f(-2.5, 0.501, 5.0);
	glEnd();
}
void hintr(){
	hint_color();
	glBegin(GL_QUADS);
	glVertex3f(2.5, 0.501, 5.0);
	glVertex3f(7.5, 0.501, 5.0);
	glVertex3f(7.5, 0.501, 0.0);
	glVertex3f(2.5, 0.501, 0.0);
	glEnd();
}
void hintl(){
	hint_color();
	glBegin(GL_QUADS);
	glVertex3f(-2.5, 0.501, 0.0);
	glVertex3f(2.5, 0.501, 0.0);
	glVertex3f(2.5, 0.501, -5.0);
	glVertex3f(-2.5, 0.501, -5.0);
	glEnd();
}
void hints(){
	hint_color();
	glBegin(GL_QUADS);
	glVertex3f(-2.5, 0.501, 5.0);
	glVertex3f(2.5, 0.501, 5.0);
	glVertex3f(2.5, 0.501, 0.0);
	glVertex3f(-2.5, 0.501, 0.0);
	glEnd();
}
static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte* pixeldata;
void t(){
	int width;
	int height;
	FILE* pfile = fopen("star.bmp", "rb");
	if (pfile == 0) exit(0);

	
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);


	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;

	
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);

	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);

	width = sizeof(imagewidth);
	height = sizeof(imageheight);


	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pfile);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//GL_REPEAT or GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//GL_REPEAT or GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//GL_LINEAR or GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//fclose(pfile);
	
}
void start(){
	int width;
	int height;
	FILE* pfile = fopen("start.bmp", "rb");
	if (pfile == 0) exit(0);


	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);


	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;


	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);

	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);

	width = sizeof(imagewidth);
	height = sizeof(imageheight);
	

	fclose(pfile);
	
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
	//printf("%d-%d", w_w, w_h);
	glPixelZoom(w_w/1024, w_h/768);
}
void finish(){
	int width;
	int height;
	FILE* pfile = fopen("finish.bmp", "rb");
	if (pfile == 0) exit(0);


	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);


	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;


	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);

	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);

	width = sizeof(imagewidth);
	height = sizeof(imageheight);



	fclose(pfile);
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
	glPixelZoom(w_w / 1024, w_h / 768);
}
void fog(){
	glEnable(GL_FOG);
	{
		GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };

		fogMode = GL_EXP;
		glFogi(GL_FOG_MODE, fogMode);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.15);
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		glFogf(GL_FOG_START, 2.0);
		glFogf(GL_FOG_END, 5.0);
	}
	glClearColor(0.5, 0.5, 0.5, 1.0);  /* fog color */
}