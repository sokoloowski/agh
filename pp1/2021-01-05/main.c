#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <stdio.h>

#define ROZ_X 100
#define ROZ_Y 100

static double powierz[ROZ_X][ROZ_Y] = {0};

GLfloat KAT = 0,
        PI = 3.14,
        PX = -ROZ_X / 2,
        PY = -2,
        PZ = -ROZ_Y / 2;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

void EnableOpenGL(HWND hwnd, HDC *, HGLRC *);

void DisableOpenGL(HWND, HDC, HGLRC);

void init();

void rysujPowierzchnie(HDC);

void gora(int, int, int, int, int);

void inicjujPlansze(int, int, int);

void inicjujTeksture(char *);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow) {
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          1024,
                          600,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    /* program main loop */
    init();
    inicjujPlansze(10, 20, 20);
    while (!bQuit) {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT) {
                bQuit = TRUE;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            rysujPowierzchnie(hDC);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    break;
                case VK_UP:
                    PX += sin(PI * KAT / 180);
                    PY = (powierz[(int) PX * -1][(int) PZ * -1] + 2) * -1;
                    PZ += cos(PI * KAT / 180);
                    break;
                case VK_DOWN:
                    PX -= sin(PI * KAT / 180);
                    PY = (powierz[(int) PX * -1][(int) PZ * -1] + 2) * -1;
                    PZ -= cos(PI * KAT / 180);
                    break;
                case VK_LEFT:
                    KAT += 4;
                    if (KAT > 360)
                        KAT -= 360;
                    break;
                case VK_RIGHT:
                    KAT -= 4;
                    if (KAT < 0)
                        KAT += 360;
                    break;

            }
        }
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC *hDC, HGLRC *hRC) {
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 160);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    inicjujTeksture("../grass.bmp");
}

void rysujPowierzchnie(HDC hDC) {
    glLoadIdentity();
    glRotatef(-KAT, 0, 1, 0);
    glTranslatef(PX, PY, PZ);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    for (int x = 0; x < ROZ_X - 1; x++)
        for (int y = 0; y < ROZ_Y - 1; y++) {
            glTexCoord2f(0, 0);
            glVertex3f(x, powierz[x][y], y);
            glTexCoord2f(0, 1);
            glVertex3f(x, powierz[x][y + 1], y + 1);
            glTexCoord2f(1, 1);
            glVertex3f(x + 1, powierz[x + 1][y + 1], y + 1);
            glTexCoord2f(1, 0);
            glVertex3f(x + 1, powierz[x + 1][y], y);
        }
    glEnd();
    SwapBuffers(hDC);
}

void gora(int px, int py, int r1, int r2, int wys) {
    int i, j;
    for (i = -r1 / 2; i < r1 / 2; i++)
        for (j = -r1 / 2; j < r1 / 2; j++)
            if (2 * sqrt(i * i + j * j) < r1)
                powierz[(i + px + ROZ_X) % ROZ_X][(j + py + ROZ_Y) % ROZ_Y] += min(
                        wys,
                        (r1 - 2 * sqrt(i * i + j * j)) * wys / (r1 - r2)
                );
}

void inicjujPlansze(int liczbaGor, int maxPromien, int maxWys) {
    int i, j, a, r1, r2, px, py, wys;
    for (a = 0; a < liczbaGor; a++) {
        r1 = rand() * maxPromien / RAND_MAX;
        r2 = rand() * r1 / 2 / RAND_MAX;
        wys = rand() * maxWys / RAND_MAX;
        px = rand() * ROZ_X / RAND_MAX;
        gora(px, py, r1, r2, wys);
    }
}

void inicjujTeksture(char nazwa[]) {
    long i, size = 256 * 256 * 3;
    unsigned char buf[size];
    FILE *texture;
    if ((texture = fopen(nazwa, "rb")) == NULL) {
        printf("Cannot open texture!");
        return;
    }
    fseek(texture, -size, SEEK_END);
    for (i = 0; i < size; i += 3) {
        buf[i + 2] = getc(texture);
        buf[i + 1] = getc(texture);
        buf[i] = getc(texture);
    }
    fclose(texture);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, buf);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_2D);
}