/* simple painting program with text, lines, triangles,
rectangles, and points */

 // ��ǻ�� �׷��� ���α׷��� ������Ʈ1 _ 2016154 �����

#define NULL 0
#define LINE 1
#define RECTANGLE 2
#define TRIANGLE 3
#define PPOINTSS 4
#define TEXTT 5
#define CIRCLE 6
#define SPIRAL 7
#define OPEN 8
#define CLOSED 9

#include <GL/freeglut.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>


void mymouse(int, int, int, int); //���콺 �Է�
void key(unsigned char, int, int); //Ű���� �Է�
void drawSquare(int, int); //�簢�� �׸�
void myReshape(GLsizei, GLsizei); //ȭ�� ũ�⿡ ���� ������ �ٲ�
void mydisplay(void); //�ʱ�ȭ��
void myinit();

void screen_box(int, int, int); //�޴��ڽ�
void middle_menu(int); //���콺 ��� ��ư ������ ������ �޴�
void color_menu(int); // �� ���� ���� �޴�
void pixel_menu(int); // ���� ũ�� ���� �޴�
void fill_menu(int); // ���� ä��� �޴�
int pick(int, int); //���콺 Ŭ�� �޴�

/* globals */

GLsizei wh = 500, ww = 500; /* initial window size */
GLfloat size = 3.0;   /* half side length of square */
int draw_mode = 0; /* drawing mode */
int rx, ry; /*raster position*/

GLfloat r = 1.0, g = 1.0, b = 1.0; /* drawing color */
int fill = 0; /* fill flag */

double points[100][100]; //�ٰ��� �׸��⿡�� ����ڰ� Ŭ���ϴ� ���� ������ �迭

void drawSquare(int x, int y)
{
	y = wh - y;
	glColor3ub((char)rand() % 256, (char)rand() % 256, (char)rand() % 256);
	glBegin(GL_POLYGON);
	glVertex2f(x + size, y + size);
	glVertex2f(x - size, y + size);
	glVertex2f(x - size, y - size);
	glVertex2f(x + size, y - size);
	glEnd();
}


/* reshaping routine called whenever window is resized or moved */

void myReshape(GLsizei w, GLsizei h)
{

	/* adjust clipping box */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* adjust viewport and clear */

	glViewport(0, 0, w, h);
	GLfloat WidthFactor = (GLfloat)w / (GLfloat)300;
	GLfloat HeightFactor = (GLfloat)h / (GLfloat)300;
	glClearColor((GLclampf)0.8, (GLclampf)0.8, (GLclampf)0.8, (GLclampf)1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	/* set global size for use by drawing routine */

	ww = w;
	wh = h;
}

void myinit()
{

	glViewport(0, 0, ww, wh);


	/* Pick 2D clipping window to match size of X window. This choice
	avoids having to scale object coordinates each time window is
	resized. */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)ww, 0.0, (GLdouble)wh, -1.0, 1.0);

	/* set clear color to black and clear window */

	glClearColor((GLclampf)0.8, (GLclampf)0.8, (GLclampf)0.8, (GLclampf)1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//���� �޴��� �� �ϳ��� Ŭ���ϸ� �ش� ������ �׸���
void mymouse(int btn, int state, int x, int y)
{
	static int count;
	int where;
	static int xp[2], yp[2];

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //���콺 ���ʹ�ư�� ������ ��
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS); //�� �����ϴ� �뵵
		where = pick(x, y); // where = ���콺 �Է��� ���� ���� ���� pick�Լ��� ���ϰ�(��, ��, ����..)
		glColor3f(r, g, b); //rgb���� �� ���

		if (where != 0)
		{
			count = 0;
			draw_mode = where;
		}

		else switch (draw_mode)
		{
		case(LINE): //LINE�� ���õ� ���
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				glBegin(GL_LINES); //line�� �׸�
				glVertex2i(x, wh - y);
				glVertex2i(xp[0], wh - yp[0]);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;


		case(RECTANGLE): //�簢���� ���õ� ���
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				if (fill) glBegin(GL_POLYGON); //���� ä��� ���

				else glBegin(GL_LINE_LOOP); //���� ä���� �ʴ� ���
				glVertex2i(x, wh - y);
				glVertex2i(x, wh - yp[0]);
				glVertex2i(xp[0], wh - yp[0]);
				glVertex2i(xp[0], wh - y);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;

		case (TRIANGLE): //�ﰢ���� ���õ� ���
			switch (count)
			{
			case(0):
				count++;
				xp[0] = x;
				yp[0] = y;
				break;

			case(1):
				count++;
				xp[1] = x;
				yp[1] = y;
				break;

			case(2):
				if (fill) glBegin(GL_POLYGON); //���� ä��� ���

				else glBegin(GL_LINE_LOOP); //���� ä���� �ʴ� ���
				glVertex2i(xp[0], wh - yp[0]);
				glVertex2i(xp[1], wh - yp[1]);
				glVertex2i(x, wh - y);
				glEnd();
				draw_mode = 0;
				count = 0;
			}

			break;

		case(PPOINTSS): //���� ���õ� ���
		{
			drawSquare(x, y);
			count++;
		}
		break;

		case(TEXTT): //���ڰ� ���õ� ���
		{
			rx = x;
			ry = wh - y;
			glRasterPos2i(rx, ry);
			count = 0;
		}

		case(CIRCLE): //���� ���õ� ���
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				if (fill) glBegin(GL_POLYGON); //���� ä��� ���

				else glBegin(GL_LINE_STRIP); //���� ä���� �ʴ� ���

				for (int i = 0; i <= 360; i++) {
					double angle = i * 2.0f * 3.141592 / 180;
					xp[1] = x + sqrt(pow(x - xp[0], 2) + pow(y - yp[0], 2)) * cos(angle);
					yp[1] = y + sqrt(pow(x - xp[0], 2) + pow(y - yp[0], 2)) * sin(angle);
					glVertex2f(xp[1], wh - yp[1]);
				}

				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;

		case(SPIRAL): //������ ���õ� ���
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				float radius = sqrt(pow(x - xp[0], 2) + pow(y - yp[0], 2));
				glBegin(GL_LINE_STRIP);

				for (float angle = 0; angle < 1440; angle += 1) {
					xp[1] = x + radius * cos(angle * M_PI / 180);
					yp[1] = y + radius * sin(angle * M_PI / 180);
					radius += 0.05f;
					glVertex2f(xp[1], wh - yp[1]);
				}

				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;

		case(OPEN): //���´ٰ����� ������ ��� - ���콺 ���� ��ư ���� ��
		{
			points[count][0] = x;
			points[count][1] = wh - y;
			count++;

			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < count; i++)
				glVertex2i(points[i][0], points[i][1]);
			glEnd();

			if (count > 1 && x == points[0][0] && wh - y == points[0][1])
			{
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < count - 1; i++)
					glVertex2i(points[i][0], points[i][1]);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
		}
		break;

		case (CLOSED): // ���� �ٰ����� ������ ��� - ���콺 ���� ��ư ���� ��
		{
			points[count][0] = x;
			points[count][1] = wh - y;
			count++;

			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < count; i++)
				glVertex2i(points[i][0], points[i][1]);
			glEnd();

			if (count > 1 && x == points[0][0] && wh - y == points[0][1])
			{
				if (fill) glBegin(GL_POLYGON); //���� ä��� ���

				else glBegin(GL_LINE_LOOP); //���� ä���� �ʴ� ���
				for (int i = 0; i < count; i++)
					glVertex2i(points[i][0], points[i][1]);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
		}break;


		}   /* end else switch*/
	}/*end if*/

	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) { //���콺 ������ ��ư ������ ��

		glColor3f(r, g, b);

		if (count > 1)
		{
			if (draw_mode == CLOSED) { //���� �ٰ��� �׸� ��

				glBegin(GL_LINE_STRIP);

				for (int i = 0; i < count; i++)
					glVertex2i(points[i][0], points[i][1]);

				glVertex2i(points[0][0], points[0][1]);
				glEnd();

				if (fill) glBegin(GL_POLYGON); //���� ä��� ���

				else glBegin(GL_LINE_LOOP); //���� ä���� �ʴ� ���
				for (int i = 0; i < count; i++)
					glVertex2i(points[i][0], points[i][1]);
				glEnd();
			}

			else if (draw_mode == OPEN) { //���� �ٰ��� �׸� ��
				glColor3f(r, g, b);
				if (count > 1)
				{
					glBegin(GL_LINE_STRIP);
					for (int i = 0; i < count - 1; i++)
						glVertex2i(points[i][0], points[i][1]);
					glEnd();
				}
			}
		}
		draw_mode = 0;
	}

	glPopAttrib();
	glFlush();
}



//���콺�� Ư�� ���� Ŭ�� �� �ش� �޴��� �ν�
int pick(int x, int y) //���콺�� Ŭ���ϸ� x,y���� ����
{
	y = wh - y;
	if (x < ww - ww / 10) return 0;
	else if (y > wh - ww / 10) return LINE; //���� �����̸� LINE�� ����
	else if (y > wh - 2 * (ww / 10)) return RECTANGLE;
	else if (y > wh - 3 * (ww / 10)) return TRIANGLE;
	else if (y > wh - 4 * (ww / 10)) return PPOINTSS;
	else if (y > wh - 5 * (ww / 10)) return TEXTT;
	else if (y > wh - 6 * (ww / 10)) return CIRCLE;
	else if (y > wh - 7 * (ww / 10)) return SPIRAL;
	else if (y > wh - 8 * (ww / 10)) return OPEN;
	else if (y > wh - 9 * (ww / 10)) return CLOSED;
	else return 0;
}

void screen_box(int x, int y, int s) //drawsquare�� �����
{
	glBegin(GL_QUADS); //�簢���� �׸��ٰ�
	glVertex2i(x, y);
	glVertex2i(x + s, y);
	glVertex2i(x + s, y + s);
	glVertex2i(x, y + s);
	glEnd();
}

void middle_menu(int id)
{
	if (id == 1) exit(0);
	else
	{
		glClearColor((GLclampf)0.8, (GLclampf)0.8, (GLclampf)0.8, (GLclampf)1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		mydisplay(); //�ʱ�ȭ������ ������
	}
	//�ϴ� ���� ������ �ݵ�� �ҷ���� �ϴ� �޴���� �Ͻ�
}

void color_menu(int id)
{
	if (id == 1) { r = 1.0; g = 0.0; b = 0.0; } //�۷ι� ������ ����
	else if (id == 2) { r = 0.0; g = 1.0; b = 0.0; }
	else if (id == 3) { r = 0.0; g = 0.0; b = 1.0; }
	else if (id == 4) { r = 0.0; g = 1.0; b = 1.0; }
	else if (id == 5) { r = 1.0; g = 0.0; b = 1.0; }
	else if (id == 6) { r = 1.0; g = 1.0; b = 0.0; }
	else if (id == 7) { r = 1.0; g = 1.0; b = 1.0; }
	else if (id == 8) { r = 0.0; g = 0.0; b = 0.0; }
}

void pixel_menu(int id)
{
	if (id == 1) size = 2 * size;
	else if (size > 1) size = size / 2;
}

void fill_menu(int id)
{
	if (id == 1) fill = 1;
	else fill = 0;
}

void key(unsigned char k, int xx, int yy) //Ű���� �̺�Ʈ�� ������ �� �Ҹ��� �Լ�
{
	if (draw_mode != TEXTT) return;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(rx, ry);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k); //�۾��� ũ�Ⱑ ���� 9, 15���
	/*glutStrokeCharacter(GLUT_STROKE_ROMAN,i); */
	rx += glutBitmapWidth(GLUT_BITMAP_9_BY_15, k);

}

void mydisplay(void) //ù ȭ�鿡 ���� ����
{
	int shift = 0;

	glColor3f(1.0, 1.0, 1.0);
	screen_box(ww - ww / 10, wh - ww / 10, ww / 10);   // line box
	glColor3f(1.0, 0.0, 0.0);
	screen_box(ww - ww / 10, wh - 2 * (ww / 10), ww / 10);   //rectangle box
	glColor3f(0.0, 1.0, 0.0);
	screen_box(ww - ww / 10, wh - 3 * (ww / 10), ww / 10);    //triangle box
	glColor3f(0.0, 0.0, 1.0);
	screen_box(ww - ww / 10, wh - 4 * (ww / 10), ww / 10);   //point
	glColor3f(1.0, 1.0, 0.0);
	screen_box(ww - ww / 10, wh - 5 * (ww / 10), ww / 10);    //string
	glColor3f(0.3, 0.6, 0.6);
	screen_box(ww - ww / 10, wh - 6 * (ww / 10), ww / 10); //circle
	glColor3f(0.7, 0.2, 0.3);
	screen_box(ww - ww / 10, wh - 7 * (ww / 10), ww / 10); //spiral
	glColor3f(0.2, 0.1, 0.9);
	screen_box(ww - ww / 10, wh - 8 * (ww / 10), ww / 10); //���� �ٰ���
	glColor3f(0.1, 0.9, 0.2);
	screen_box(ww - ww / 10, wh - 9 * (ww / 10), ww / 10); //���� �ٰ���

	//���⼭���� ���� �� �޴��� � �޴����� ǥ�����ִ� ����
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES); //���� �޴� �� �� ǥ��
	glVertex2i(ww - ww / 50, wh - ww / 20);
	glVertex2i(ww - ww / 12, wh - ww / 20);
	glEnd();

	screen_box(ww - ww / 13, wh - ww / 5 + ww / 40, ww / 20); // ���� �޴� �� �簢�� ǥ��

	glBegin(GL_TRIANGLES); //���� �޴� �� �ﰢ�� ǥ��
	glVertex2i(ww - ww / 15, wh - ww / 3.5);
	glVertex2i(ww - ww / 40, wh - ww / 3.5);
	glVertex2i(ww - ww / 17 + 3, wh - ww / 4.5);
	glEnd();

	glPointSize(3.0); //���� �޴� �� �� ǥ��
	glBegin(GL_POINTS);
	glVertex2i(9 * ww / 10 + ww / 20, wh - ww / 2.9);
	glEnd();

	glRasterPos2i(ww - ww / 10.3, wh - ww / 2.1); //���� �޴� �� ���� ǥ��
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	glRasterPos2i(ww - ww / 13, wh - ww / 2.1);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
	glRasterPos2i(ww - ww / 18, wh - ww / 2.1);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glEnd();

	glBegin(GL_LINE_STRIP); //���� �޴� �� �� ǥ��
	for (int i = 0; i < 360; i++) {
		double angle, x, y;
		angle = i * 2.0f * 3.141592 / 180;
		x = (ww - ww / 18.5) + (wh / 60) * cos(angle);
		y = (wh - ww / 1.8) + (wh / 60) * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	float PI = 3.141592653589;
	float radius = 1.0f;
	float angle = 0.1f;
	float b = 0.5f;
	glBegin(GL_LINE_STRIP); //���� �޴� �� spiral ǥ��

	for (float i = 0; i < 5 * PI; i += angle) {
		float x = (radius + b * i) * cos(i) + 9.5 * ww / 10;
		float y = (radius + b * i) * sin(i) + wh - 10.5 * ww / 16;
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_LINE_STRIP); //���� �޴� �� ���� �ٰ��� ǥ��
	glVertex2i(ww - ww / 20, wh - ww/1.4);
	glVertex2i(ww - ww / 13, wh - ww/1.3);
	glVertex2f(ww - ww / 28, wh - ww / 1.3);
	glEnd();

	glBegin(GL_LINE_STRIP); //���� �޴� �� ���� �ٰ��� ǥ��
	glVertex2i(ww - ww / 15, wh - ww/1.2);
	glVertex2i(ww - ww / 15, wh - ww/1.14);
	glVertex2i(ww - ww / 25, wh - ww / 1.14);
	glVertex2i(ww - ww / 25, wh - ww / 1.2);
	glVertex2i(ww - ww / 15, wh - ww / 1.2);
	glEnd();

	glFinish();

	glFlush();

}


int main(int argc, char** argv)
{
	int c_menu, p_menu, f_menu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutCreateWindow("square");

	c_menu = glutCreateMenu(color_menu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Cyan", 4);
	glutAddMenuEntry("Magenta", 5);
	glutAddMenuEntry("Yellow", 6);
	glutAddMenuEntry("White", 7);
	glutAddMenuEntry("Black", 8); //������� c�޴�

	p_menu = glutCreateMenu(pixel_menu);
	glutAddMenuEntry("increase pixel size", 1);
	glutAddMenuEntry("decrease pixel size", 2);

	f_menu = glutCreateMenu(fill_menu);
	glutAddMenuEntry("fill on", 1);
	glutAddMenuEntry("fill off", 2);

	glutCreateMenu(middle_menu); //���콺 �� ��ư
	glutAddMenuEntry("quit", 1);
	glutAddMenuEntry("clear", 2);
	glutAddSubMenu("Colors", c_menu); //c�޴� ����
	glutAddSubMenu("Pixel Size", p_menu); //p�޴� ����
	glutAddSubMenu("Fill", f_menu); //f�޴� ����
	glutAttachMenu(GLUT_MIDDLE_BUTTON); //���콺 �ٹ�ư Ŭ���ϸ� ��������

	myinit();
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mymouse);
	glutDisplayFunc(mydisplay);
	glutMainLoop();

	return 0;
}
