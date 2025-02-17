#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "raycaster.h"
#include "graphics-engine.h"
#include "engine.h"
#include <stddef.h>
#include <iostream>
#include "sdl-event-dispatcher.h"
#include "vector.h"
#include <cmath>

using namespace std;

#define GRID_WIDTH (100)
#define GRID_HEIGHT (100)
#define CELL_SIZE (1.0f)
#define NOTHING (0)
#define WALL (1)

Raycaster *Raycaster::s_instance = NULL;
static GLuint s_VAO;
static GLuint s_texture;
static GLuint s_shaderProgram;
static char *s_textureData;
static char s_grid[GRID_WIDTH][GRID_HEIGHT] = {NOTHING};
static Vector3f s_playerPosition;
static Vector3f s_playerDirection;
static Vector3f s_cameraPlane;
static int s_screenWidth = 640;
static int s_screenHeight = 480;
static int s_textureWidth = -1;
static int s_textureHeight = -1;

static void render(void)
{
    Raycaster::Instance()->Render();
}

static void init(void)
{
    Raycaster::Instance()->Init();
}

static void window_resized(int width, int height)
{
    Raycaster::Instance()->WindowResized(width, height);
}

// Vertex Shader Source
const char *vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec2 aPos;
    layout(location = 1) in vec2 aTexCoord;
    out vec2 TexCoord;
    void main() {
        gl_Position = vec4(aPos, 0.0, 1.0);
        TexCoord = aTexCoord;
    }
)";

// Fragment Shader Source
const char *fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec2 TexCoord;
    uniform sampler2D texture1;
    void main() {
        FragColor = texture(texture1, TexCoord);
    }
)";

// function to compile shader
static GLuint compileShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
             << infoLog << endl;
    }

    return shader;
}

// set a vertical column of pixels to a given color
static void setTextureData(int columnIndex, int yStart, int yEnd, int width, char r, char g, char b)
{
    for (int y = yStart; y < yEnd; ++y)
    {
        int index = (y * width + columnIndex) * 3;
        s_textureData[index] = r;
        s_textureData[index + 1] = g;
        s_textureData[index + 2] = b;
    }
}

static GLuint createTexture(int width, int height)
{
    s_textureData = new char[width * height * 3]; // RGB format
    s_textureWidth = width;
    s_textureHeight = height;

    // Fill with red on the left half and green on the right half
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = (y * width + x) * 3;
            if (x < width / 2)
            {                                 // Left half (Red)
                s_textureData[index] = 255;   // Red
                s_textureData[index + 1] = 0; // Green
                s_textureData[index + 2] = 0; // Blue
            }
            else
            {                                   // Right half (Green)
                s_textureData[index] = 0;       // Red
                s_textureData[index + 1] = 255; // Green
                s_textureData[index + 2] = 0;   // Blue
            }
        }
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, s_textureData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return texture;
}

// Function to create shader program
static GLuint createShaderProgram()
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
             << infoLog << endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

Raycaster *Raycaster::Instance()
{
    if (s_instance == NULL)
    {
        s_instance = new Raycaster();
    }

    return s_instance;
}

static void SetUpGrid()
{
    // place the player at the bottom row
    // looking at +z toward the center of the grid
    // put the player in the middle of a cell
    s_playerPosition = Vector3f((2 * GRID_WIDTH / 3) + CELL_SIZE / 2.0f, 0, CELL_SIZE / 2.0f);
    s_playerDirection = Vector3f(0, 0, 1);

    // camera is rotated 90 degree from player direction
    s_cameraPlane = Vector3f(1, 0, 0);

    // place a wall in the middle of the scene so that some rays
    // hit the wall and others do not
    int xStart = GRID_WIDTH / 4;
    int xEnd = 3 * GRID_WIDTH / 4;

    for (int x = xStart; x < xEnd; ++x)
    {
        // mark this cell as a wall
        s_grid[x][GRID_HEIGHT / 2] = WALL;
    }
}

void Raycaster::Init(void)
{
    SetUpGrid();

    // Define square vertices (x, y, u, v)
    float vertices[] = {
        // Position    // TexCoords
        -1.0, -1.0f, 0.0f, 1.0f, // Bottom-left
        1.0f, -1.0f, 1.0f, 1.0f, // Bottom-right
        1.0f, 1.0f, 1.0f, 0.0f,  // Top-right
        -1.0f, 1.0f, 0.0f, 0.0f  // Top-left
    };

    // Define indices for drawing the square with two triangles
    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    // Create VAO, VBO, EBO
    GLuint VBO, EBO;
    glGenVertexArrays(1, &s_VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(s_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position Attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Texture Coordinate Attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load Shaders and Create Program
    s_shaderProgram = createShaderProgram();

    // Load Texture
    s_texture = createTexture(s_screenWidth, s_screenHeight);
}

static int s_renderCount = 1;

static float findLineLength(float x1, float z1, float x2, float z2)
{
    return sqrt(
        pow(z2 - z1, 2) + pow(x2 - x1, 2));
}

static bool findZIntercept(float rayDirX, float rayDirZ, float x, float z, int x2, float &zIntercept)
{
    // z = mx+b

    // check for a straight-ish vertical line
    // in this case, we'll never intersect
    if (rayDirX < 0.0001 && rayDirX > -0.0001)
        return false;

    zIntercept = ((rayDirZ / rayDirX) * (x2 - x)) + z;
    return true;
}

static bool findXIntercept(float rayDirX, float rayDirZ, float x, float z, int z2, float &xIntercept)
{
    // z = mx+b
    // we can allow b = 0
    // x = z / m

    // check for a straight-ish horizontal line
    // in this case, we'll never intersect
    if (rayDirZ < 0.0001 && rayDirZ > -0.0001)
        return false;

    xIntercept = ((z2 - z) / (rayDirZ / rayDirX)) + x;
    return true;
}

void Raycaster::Render()
{
    static bool goleft = true;
    if (s_playerPosition.x > 0 && goleft)
    {
        --s_playerPosition.x;
    }
    else
    {
        goleft = false;
    }

    if (s_playerPosition.x < GRID_WIDTH && !goleft)
    {
        ++s_playerPosition.x;
    }
    else
    {
        goleft = true;
    }

    for (int x = 0; x < s_screenWidth; ++x)
    {
        bool debug = false;
        if (s_renderCount == 1) // && (x == 0 || x == s_screenWidth - 1))
        {
            //    debug = true;
        }

        // convert the x screen value to a camera
        // position between -1 and 1
        float cameraScale = 2.0 * x / s_screenWidth - 1;

        // starting ray position
        float rayX = s_playerPosition.x;
        float rayZ = s_playerPosition.z;

        // calculate ray direction
        float rayDirX = s_playerDirection.x + (s_cameraPlane.x * cameraScale);
        float rayDirZ = s_playerDirection.z + (s_cameraPlane.z * cameraScale);

        // calculate player dx and dz
        // this is the x and z distance to the
        // cell boundary where the player is
        // so we need to take direction into account
        // float dx = s_playerPosition.x - floor(s_playerPosition.x);
        // float dz = s_playerPosition.z - floor(s_playerPosition.z);

        int hitCellX = -1;
        int hitCellZ = -1;
        float hitDistance = -1;

        int cellX = -1;
        int cellZ = -1;

        while (rayX > 0 && rayX < GRID_WIDTH && rayZ > 0 && rayZ < GRID_HEIGHT)
        {
            int nextCellX = -1;
            int nextCellZ = -1;
            if (rayDirX > 0)
            {
                nextCellX = (int)(rayX + 1);
            }
            else
            {
                nextCellX = (int)(rayX - 1);
            }

            if (rayDirZ > 0)
            {
                nextCellZ = (int)(rayZ + 1);
            }
            else
            {
                nextCellZ = (int)(rayZ - 1);
            }

            // find the Z coordinate where the ray intersects (nextCellX, z)
            float zIntercept;
            float zInterceptLength = numeric_limits<float>::max();
            bool zIntercepted = findZIntercept(rayDirX, rayDirZ, rayX, rayZ, nextCellX, zIntercept);

            // find the X coordinate where the ray intersects (x, nextCellZ)
            float xIntercept;
            float xInterceptLength = numeric_limits<float>::max();
            bool xIntercepted = findXIntercept(rayDirX, rayDirZ, rayX, rayZ, nextCellZ, xIntercept);

            if (zIntercepted)
            {
                zInterceptLength = findLineLength(rayX, rayZ, nextCellX, zIntercept);
            }

            if (xIntercepted)
            {
                xInterceptLength = findLineLength(rayX, rayZ, xIntercept, nextCellZ);
            }

            if (zInterceptLength < xInterceptLength)
            {
                rayX = nextCellX;
                rayZ = zIntercept;
                hitDistance = zInterceptLength;
            }
            else
            {
                rayX = xIntercept;
                rayZ = nextCellZ;
                hitDistance = xInterceptLength;
            }

            // test for a wall hit
            cellX = (int)rayX;
            cellZ = (int)rayZ;

            // if (rayZ > 48)
            // {
            //     cout << "wait here" << endl;
            // }

            if (s_grid[cellX][cellZ] == WALL)
            {
                hitCellX = cellX;
                hitCellZ = cellZ;
                break;
            }
        }

        if (hitCellX != -1 && hitCellZ != -1)
        {
            if (debug)
            {
                cout << "hit found at (" << hitCellX << "," << hitCellZ << ")" << endl;
            }
            // floor
            setTextureData(x, 0, s_textureHeight / 3, s_textureWidth, 255, 255, 255);
            // wall
            setTextureData(x, s_textureHeight / 3, 2 * s_textureHeight / 3, s_textureWidth, 0, 0, 255);
            // ceiling
            setTextureData(x, 2 * s_textureHeight / 3, s_textureHeight, s_textureWidth, 255, 255, 255);
        }
        else
        {
            if (debug)
            {
                cout << "empty found at (" << cellX << "," << cellZ << ")" << endl;
            }
            // empty space
            setTextureData(x, 0, s_textureHeight, s_textureWidth, 255, 255, 255);
        }
    }

    glBindTexture(GL_TEXTURE_2D, s_texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, s_textureWidth, s_textureHeight, GL_RGB, GL_UNSIGNED_BYTE, s_textureData);

    // Use shader and bind texture
    glUseProgram(s_shaderProgram);
    glBindTexture(GL_TEXTURE_2D, s_texture);
    glBindVertexArray(s_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    ++s_renderCount;
}

void Raycaster::WindowResized(int width, int height)
{
    s_screenWidth = width;
    s_screenHeight = height;

    if (s_textureData != NULL)
    {
        delete s_textureData;
        s_textureData = NULL;
    }

    s_texture = createTexture(width, height);
}

Raycaster::Raycaster()
{
    m_columns = NULL;
    GraphicsEngine::Instance()->RegisterRenderCallback(render);
    Engine::Instance()->RegisterModuleInitCallback(init);
    SDLEventDispatcher::Instance()->RegisterForWindowResized(window_resized);
}
