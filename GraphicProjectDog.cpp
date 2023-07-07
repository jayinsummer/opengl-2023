

/* Interactive Figure Program from Chapter 8 using cylinders (quadrics) */
/* Style similar to robot program but here we must traverse tree to display */
/* Cylinders are displayed as filled and light/material properties */
/* are set as in sphere approximation program */

//��ǻ�ͱ׷������α׷��� ������Ʈ2 _ 2016154�����

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <stdio.h>

#pragma comment (lib, "legacy_stdio_definitions.lib")

#define _CRT_SECURE_NO_WARNINGS
#define TORSO_HEIGHT 5.0
#define UPPER_ARM_HEIGHT 1.5
#define LOWER_ARM_HEIGHT 1.0
#define UPPER_LEG_RADIUS  0.5
#define LOWER_LEG_RADIUS  0.5
#define LOWER_LEG_HEIGHT 1.5
#define UPPER_LEG_HEIGHT 1.0
#define UPPER_LEG_RADIUS  0.5
#define TORSO_RADIUS 1.0
#define UPPER_ARM_RADIUS  0.5
#define LOWER_ARM_RADIUS  0.5
#define HEAD_HEIGHT 1.5
#define HEAD_RADIUS 1.0
#define TAIL_RADIUS 0.4
#define TAIL_HEIGHT 2.0

typedef float point[3];
unsigned int MyTextureObject[1];
AUX_RGBImageRec* pTextureImage[1];  //�ؽ��� ���� ������ ����Ű�� ������

// �ʿ��� ���� ��: 19��
static GLfloat theta[19] = { 0.0, 0.0, 0.0, 0.0, 0.0, 180.0, 0.0,
            180.0, 0.0, 0.0, 180.0, 0.0, 0.0, 0.0, 180.0, 0.0, 0.0, 0.0, 0.0 }; /* initial joint angles. 11���� ������ ��������Ʈ�� ���� */
static GLint angle = 0;

GLUquadricObj* t, * h, * lua, * lla, * rua, * rla, * lll, * rll, * rul, * lul, * tail;
//gluquadricobj: 2�� �Լ� �׸��� �뵵. ���� torso ���

double size = 1.0;

void torso()
{
    glPushMatrix(); //������ �־��� ���� ����϶�
    glRotatef(90.0, 0.0, 1.0, 0.0); // y������ 90�� ȸ��
    gluCylinder(t, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10); //2����� ������Ʈ, �Ʒ� �� ������, ����, ���� ����ȭ �� ��, ���� ����ȭ �� ��
    glPopMatrix(); //������ �����߾��� ��ǥ�� ���ƿ�
}

void head()
{
    glPushMatrix(); // 1) ���� �� �����ϰ�
    glTranslatef(5.5, 2.0 * HEAD_HEIGHT, 0.0);
    glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(h, 1.0, 10, 10);
    glPopMatrix(); // 2) ���� ��ǥ�� �ٽ� ���ƿ���
}

void left_upper_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_lower_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_upper_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_lower_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_upper_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_lower_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_upper_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_lower_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void tail_draw() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(tail, TAIL_RADIUS, TAIL_RADIUS, TAIL_HEIGHT, 10, 10);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�÷� �� ���� Ŭ����
    glLoadIdentity();
    
    //��� �ؽ��� ����
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, -0.5f, 1.0f);  //�ո�
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.3f, -0.5f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.3f, 0.5f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f, 0.5f, 1.0f);
    glEnd();

    glColor3f(0.0, 1.0, 0.5);
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    glRotatef(theta[1], 0.0, 0.0, 1.0);//�̷��� ȸ����Ű��
    torso(); //�丣�� �׸���
    glPushMatrix(); // �� ����ϰ�

    glColor3f(1.0, 0.6, 0.2);
    glTranslatef(0.0, -2.0 + 2.0 * HEAD_HEIGHT, 0.0); //��ǥ �̵��ϰ�
    glRotatef(theta[2], 1.0, 0.0, 0.0); //�Ӹ� �����
    glRotatef(theta[3], 0.0, 1.0, 0.0); //�Ӹ� ����
    glRotatef(theta[4], 0.0, 0.0, 1.0);  //�Ӹ� ��������
    //glTranslatef(0.0, -2.0 * HEAD_HEIGHT, 0.0); //��ǥ �̵��ϰ�
    head(); //��� �׸���

    //�����޹�
    glColor3f(0.5, 0.5, 0.5);
    glPopMatrix(); 
    glPushMatrix();
    glTranslatef(0.5, -0.5, 1.0);
    glRotatef(theta[5], 0.0, 0.0, 1.0);
    left_upper_arm();

    //�޾Ʒ��޹�
    glTranslatef(0.0, 1.5, 0.0);
    glRotatef(theta[6], 0.0, 0.0, 1.0);
    left_lower_arm();

    //�������޹�
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.5, -0.5, -1.0);
    glRotatef(theta[7], 0.0, 0.0, 1.0);
    right_upper_arm();

    //�����Ʒ��޹�
    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[8], 0.0, 0.0, 1.0);
    right_lower_arm();

    //�����չ�
    glColor3f(0.3, 0.2, 0.9);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4.5, -0.5, 1.0);
    glRotatef(theta[9], 0.0, 0.0, 1.0);
    glRotatef(theta[10], 1.0, 0.0, 0.0);
    left_upper_leg();

    //�޾Ʒ��չ�
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[11], 0.0, 0.0, 1.0);
    glRotatef(theta[12], 1.0, 0.0, 0.0);
    left_lower_leg();

    //�������չ�
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4.5, -0.5, -1.0);
    glRotatef(theta[13], 0.0, 0.0, 1.0);
    glRotatef(theta[14], 1.0, 0.0, 0.0);
    right_upper_leg();

    //�����Ʒ��չ�
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[15], 0.0, 0.0, 1.0);
    glRotatef(theta[16], 1.0, 0.0, 0.0);
    right_lower_leg();

    //����
    glColor3f(1.0, 0.6, 0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.3, 0.5 * TAIL_HEIGHT, 0.0);
    glRotatef(theta[17], 1.0, 0.0, 0.0);
    glRotatef(theta[18], 0.0, 0.0, 1.0);
    tail_draw();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

AUX_RGBImageRec* LoadBMP(char* szFilename) {
    FILE* pFile = NULL;
    if (!szFilename) {
        return NULL;
    }
    fopen_s(&pFile, szFilename, "r");
    if (pFile) {
        fclose(pFile);
        return auxDIBImageLoad(szFilename);     //���Ϸκ��� �޸𸮷�
    }
    return NULL;
}

int LoadGLTextures(char* szFilePath) {       //������ �ε��ϰ� �ؽ��ķ� ��ȯ
    int Status = FALSE;
    glClearColor(0.0, 0.0, 0.0, 0.5);
    memset(pTextureImage, 0, sizeof(void*) * 1);    //�����͸� �η�

    if (pTextureImage[0] = LoadBMP(szFilePath)) {   //��Ʈ���� �ε��ϰ� ����Ȯ��
        Status = TRUE;                              //���� �÷��� True��
        glGenTextures(1, &MyTextureObject[0]);      //�ؽ��� ����
        glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
            pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
            0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glEnable(GL_TEXTURE_2D);
    }
    if (pTextureImage[0]) {                 //�ؽ��İ� �����ϸ�
        if (pTextureImage[0]->data) {       //�ؽ��� ������ �����ϸ�
            free(pTextureImage[0]->data);   //�ؽ��� ������� �ݳ�
        }
        free(pTextureImage[0]);             //�ؽ��� �ݳ�
    }
    return Status;
}

void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        theta[angle] += 5.0;

        //������ �Ѱ谢�� ����
        if ((angle == 0) || (angle == 1)) {
            if (theta[angle] > 360.0) theta[angle] -= 360.0;
        }

        //���� ������ 180���� ���(�����޹�, �������޹�, �����չ�2, �������չ�2)
        else if ((angle == 5) || (angle == 7) || (angle == 10) || (angle == 14)) {
            if (theta[angle] > 270.0) theta[angle] = 270.0;
        }

        //���� ������ 0�� ���
        else {
            if (theta[angle] > 90.0) theta[angle] = 90.0;
        }
    }
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        theta[angle] -= 5.0;

        //������ �Ѱ谢�� ����
        if ((angle == 0) || (angle == 1)) {
            if (theta[angle] < 360.0) theta[angle] += 360.0;
        }

        //���� ������ 180���� ���(�����޹�, �������޹�, �����չ�2, �������չ�2)
        else if ((angle == 5) || (angle == 7) || (angle == 10) || (angle == 14)) {
            if (theta[angle] < 90.0) theta[angle] = 90.0;
        }
        //���� ������ 0�� ���
        else {
            if (theta[angle] < -90) theta[angle] = -90.0;
        }
    }
    display();
}

void menu(int id)
{
    if (id < 19) angle = id;
    if (id == 19) exit(0);
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-15.0, 15.0, -15.0 * (GLfloat)h / (GLfloat)w,
            15.0 * (GLfloat)h / (GLfloat)w, -15.0, 15.0);
    else
        glOrtho(-15.0 * (GLfloat)w / (GLfloat)h,
            15.0 * (GLfloat)w / (GLfloat)h, 0.0, 15.0, -15.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myinit()
{
    // light
    GLfloat light_ambient1[] = { 0.0, 0.0, 0.0, 1.0 }; //����
    GLfloat light_diffuse1[] = { 1.0, 1.0, 1.0, 1.0 }; //������ ���
    GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 }; //���
    GLfloat light_position1[] = { 10.0, 10.0, 10.0, 0.0 };

    // �� ����
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular1);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);

    /* allocate quadrics with filled drawing style */

    h = gluNewQuadric(); // 2�� ��� ����
    gluQuadricDrawStyle(h, GLU_FILL); //��ĥ�ض�
    t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    lua = gluNewQuadric();
    gluQuadricDrawStyle(lua, GLU_FILL);
    lla = gluNewQuadric();
    gluQuadricDrawStyle(lla, GLU_FILL);
    rua = gluNewQuadric();
    gluQuadricDrawStyle(rua, GLU_FILL);
    rla = gluNewQuadric();
    gluQuadricDrawStyle(rla, GLU_FILL);
    lul = gluNewQuadric();
    gluQuadricDrawStyle(lul, GLU_FILL);
    lll = gluNewQuadric();
    gluQuadricDrawStyle(lll, GLU_FILL);
    rul = gluNewQuadric();
    gluQuadricDrawStyle(rul, GLU_FILL);
    rll = gluNewQuadric();
    gluQuadricDrawStyle(rll, GLU_FILL);
    tail = gluNewQuadric();
    gluQuadricDrawStyle(tail, GLU_FILL);
}

void main(int argc, char** argv)
{
    printf("argc = %d", argc);
    if (argc <= 1) {
        printf("\n%s\n\n", "Usage : TextureDLG3_Consol.exe [BMPFileName.bmp]");
        exit(1);
    }
    else if (argc > 2) {
        printf("\nToo Many Arguments!\nArgument is Only one\n");
        exit(1);
    }
    else {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(700, 700);
        glutCreateWindow("dog");
        myinit();
        glutReshapeFunc(myReshape);
        glutDisplayFunc(display);
        glutMouseFunc(mouse);

        glutCreateMenu(menu);
        glutAddMenuEntry("torso1", 0);
        glutAddMenuEntry("torso2", 1);
        glutAddMenuEntry("head1", 2);
        glutAddMenuEntry("head2", 3);
        glutAddMenuEntry("head3", 4);
        glutAddMenuEntry("lubf", 5);
        glutAddMenuEntry("llbf", 6);
        glutAddMenuEntry("rubf", 7);
        glutAddMenuEntry("rlbf", 8);
        glutAddMenuEntry("luff1", 9);
        glutAddMenuEntry("luff2", 10);
        glutAddMenuEntry("llff1", 11);
        glutAddMenuEntry("llff2", 12);
        glutAddMenuEntry("ruff1", 13);
        glutAddMenuEntry("ruff2", 14);
        glutAddMenuEntry("rlff1", 15);
        glutAddMenuEntry("rlff2", 16);
        glutAddMenuEntry("tail1", 17);
        glutAddMenuEntry("tail2", 18);
        glutAddMenuEntry("quit", 19);
        glutAttachMenu(GLUT_MIDDLE_BUTTON);

        if (LoadGLTextures(argv[1])) {
            glClearColor(1.0, 1.0, 1.0, 0.0);
            glEnable(GL_TEXTURE_2D);
            glClearDepth(1.0);
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        }
        glutMainLoop();
    }

}