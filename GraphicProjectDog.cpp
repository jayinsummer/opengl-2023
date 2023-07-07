

/* Interactive Figure Program from Chapter 8 using cylinders (quadrics) */
/* Style similar to robot program but here we must traverse tree to display */
/* Cylinders are displayed as filled and light/material properties */
/* are set as in sphere approximation program */

//컴퓨터그래픽프로그래밍 프로젝트2 _ 2016154유재원

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
AUX_RGBImageRec* pTextureImage[1];  //텍스쳐 저장 공간을 가리키는 포인터

// 필요한 관절 수: 19개
static GLfloat theta[19] = { 0.0, 0.0, 0.0, 0.0, 0.0, 180.0, 0.0,
            180.0, 0.0, 0.0, 180.0, 0.0, 0.0, 0.0, 180.0, 0.0, 0.0, 0.0, 0.0 }; /* initial joint angles. 11개의 관절의 시작포인트의 각도 */
static GLint angle = 0;

GLUquadricObj* t, * h, * lua, * lla, * rua, * rla, * lll, * rll, * rul, * lul, * tail;
//gluquadricobj: 2차 함수 그리는 용도. 각각 torso 등등

double size = 1.0;

void torso()
{
    glPushMatrix(); //기존에 있었던 것을 기억하라
    glRotatef(90.0, 0.0, 1.0, 0.0); // y축으로 90도 회전
    gluCylinder(t, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10); //2차곡면 오브젝트, 아래 위 반지름, 높이, 세로 세분화 면 수, 가로 세분화 면 수
    glPopMatrix(); //이전에 저장했었던 좌표로 돌아옴
}

void head()
{
    glPushMatrix(); // 1) 기존 것 저장하고
    glTranslatef(5.5, 2.0 * HEAD_HEIGHT, 0.0);
    glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(h, 1.0, 10, 10);
    glPopMatrix(); // 2) 원래 좌표로 다시 돌아오고
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //컬러 및 뎁쓰 클리어
    glLoadIdentity();
    
    //사과 텍스쳐 맵핑
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, -0.5f, 1.0f);  //앞면
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.3f, -0.5f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.3f, 0.5f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f, 0.5f, 1.0f);
    glEnd();

    glColor3f(0.0, 1.0, 0.5);
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    glRotatef(theta[1], 0.0, 0.0, 1.0);//이렇게 회전시키고
    torso(); //토르소 그리고
    glPushMatrix(); // 값 기억하고

    glColor3f(1.0, 0.6, 0.2);
    glTranslatef(0.0, -2.0 + 2.0 * HEAD_HEIGHT, 0.0); //좌표 이동하고
    glRotatef(theta[2], 1.0, 0.0, 0.0); //머리 갸우뚱
    glRotatef(theta[3], 0.0, 1.0, 0.0); //머리 끄덕
    glRotatef(theta[4], 0.0, 0.0, 1.0);  //머리 도리도리
    //glTranslatef(0.0, -2.0 * HEAD_HEIGHT, 0.0); //좌표 이동하고
    head(); //헤드 그리고

    //왼위뒷발
    glColor3f(0.5, 0.5, 0.5);
    glPopMatrix(); 
    glPushMatrix();
    glTranslatef(0.5, -0.5, 1.0);
    glRotatef(theta[5], 0.0, 0.0, 1.0);
    left_upper_arm();

    //왼아래뒷발
    glTranslatef(0.0, 1.5, 0.0);
    glRotatef(theta[6], 0.0, 0.0, 1.0);
    left_lower_arm();

    //오른위뒷발
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.5, -0.5, -1.0);
    glRotatef(theta[7], 0.0, 0.0, 1.0);
    right_upper_arm();

    //오른아래뒷발
    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[8], 0.0, 0.0, 1.0);
    right_lower_arm();

    //왼위앞발
    glColor3f(0.3, 0.2, 0.9);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4.5, -0.5, 1.0);
    glRotatef(theta[9], 0.0, 0.0, 1.0);
    glRotatef(theta[10], 1.0, 0.0, 0.0);
    left_upper_leg();

    //왼아래앞발
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[11], 0.0, 0.0, 1.0);
    glRotatef(theta[12], 1.0, 0.0, 0.0);
    left_lower_leg();

    //오른위앞발
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4.5, -0.5, -1.0);
    glRotatef(theta[13], 0.0, 0.0, 1.0);
    glRotatef(theta[14], 1.0, 0.0, 0.0);
    right_upper_leg();

    //오른아래앞발
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[15], 0.0, 0.0, 1.0);
    glRotatef(theta[16], 1.0, 0.0, 0.0);
    right_lower_leg();

    //꼬리
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
        return auxDIBImageLoad(szFilename);     //파일로부터 메모리로
    }
    return NULL;
}

int LoadGLTextures(char* szFilePath) {       //파일을 로드하고 텍스쳐로 변환
    int Status = FALSE;
    glClearColor(0.0, 0.0, 0.0, 0.5);
    memset(pTextureImage, 0, sizeof(void*) * 1);    //포인터를 널로

    if (pTextureImage[0] = LoadBMP(szFilePath)) {   //비트맵을 로드하고 오류확인
        Status = TRUE;                              //상태 플랙을 True로
        glGenTextures(1, &MyTextureObject[0]);      //텍스쳐 생성
        glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
            pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
            0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glEnable(GL_TEXTURE_2D);
    }
    if (pTextureImage[0]) {                 //텍스쳐가 존재하면
        if (pTextureImage[0]->data) {       //텍스쳐 영상이 존재하면
            free(pTextureImage[0]->data);   //텍스쳐 영상공간 반납
        }
        free(pTextureImage[0]);             //텍스쳐 반납
    }
    return Status;
}

void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        theta[angle] += 5.0;

        //몸통은 한계각도 없음
        if ((angle == 0) || (angle == 1)) {
            if (theta[angle] > 360.0) theta[angle] -= 360.0;
        }

        //기준 각도가 180도인 경우(왼위뒷발, 오른위뒷발, 왼위앞발2, 오른위앞발2)
        else if ((angle == 5) || (angle == 7) || (angle == 10) || (angle == 14)) {
            if (theta[angle] > 270.0) theta[angle] = 270.0;
        }

        //기준 각도가 0인 경우
        else {
            if (theta[angle] > 90.0) theta[angle] = 90.0;
        }
    }
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        theta[angle] -= 5.0;

        //몸통은 한계각도 없음
        if ((angle == 0) || (angle == 1)) {
            if (theta[angle] < 360.0) theta[angle] += 360.0;
        }

        //기준 각도가 180도인 경우(왼위뒷발, 오른위뒷발, 왼위앞발2, 오른위앞발2)
        else if ((angle == 5) || (angle == 7) || (angle == 10) || (angle == 14)) {
            if (theta[angle] < 90.0) theta[angle] = 90.0;
        }
        //기준 각도가 0인 경우
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
    GLfloat light_ambient1[] = { 0.0, 0.0, 0.0, 1.0 }; //조명
    GLfloat light_diffuse1[] = { 1.0, 1.0, 1.0, 1.0 }; //조명은 흰색
    GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 }; //흰색
    GLfloat light_position1[] = { 10.0, 10.0, 10.0, 0.0 };

    // 빛 연결
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

    h = gluNewQuadric(); // 2차 곡면 생성
    gluQuadricDrawStyle(h, GLU_FILL); //색칠해라
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