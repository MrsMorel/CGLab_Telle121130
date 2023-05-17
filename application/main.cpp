

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

struct Star
{
	GLfloat x, y, z; // Star position
	GLfloat r, g, b; // Star color
    GLfloat pointSize; // Star point size
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


std::vector<Star> generateStars(int numStars)
{
    std::vector<Star> stars;

    for (int i = 0; i < numStars; i++)
    {
        Star star;
        star.x = static_cast<GLfloat>(rand() % WINDOW_WIDTH - WINDOW_WIDTH / 2);
        star.y = static_cast<GLfloat>(rand() % WINDOW_HEIGHT - WINDOW_HEIGHT / 2);
        //star.x = static_cast<GLfloat>(rand() % (2 * WINDOW_WIDTH + 1) - WINDOW_WIDTH);
        //star.y = static_cast<GLfloat>(rand() % (2 * WINDOW_HEIGHT + 1) - WINDOW_HEIGHT);
        star.z = -1.0f;  // Because it's on 2D, so we sey the position of z as -1.0f
        star.r = static_cast<GLfloat>(rand()) / RAND_MAX;  // Generate a random red component between 0.0 and 1.0
        star.g = static_cast<GLfloat>(rand()) / RAND_MAX;  // Generate a random green component between 0.0 and 1.0
        star.b = static_cast<GLfloat>(rand()) / RAND_MAX;  // Generate a random blue component between 0.0 and 1.0
        star.pointSize = static_cast<GLfloat>(rand()) / RAND_MAX * 30.0f;
        //star.pointSize = starSize;
        stars.push_back(star);

        
        // Debug output
        std::cout << "Generated star " << i + 1 << ":"
            << " Position=(" << star.x << ", " << star.y << ", " << star.z << ")"
            << " Color=(" << star.r << ", " << star.g << ", " << star.b << ")"
            << " PointSize=" << star.pointSize
            << std::endl;
        
    }

    return stars;
}

GLuint createShaderProgram()
{
    // Create vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Vertex shader source
    const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    layout (location = 2) in float pointSize;
    
    out vec3 starColor;
    void main()
    {
        gl_Position = vec4(position, 1.0);
        starColor = color;
        gl_PointSize = pointSize;
    }
    )";

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr); // Specify the source code for the vertex shader
    glCompileShader(vertexShader); // Compile vertex shader objects
    // Check if the vertex shader compiles successfully
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Failed to compile vertex shader:\n" << infoLog << std::endl;
        return 0;
    }

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Fragment shader source
    const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 starColor;
    out vec4 fragColor;
    void main()
    {
        fragColor = vec4(starColor, 1.0);
    }
    )";
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr); // Specify the source code for the fragment shader
    glCompileShader(fragmentShader); // Compile fragment shader objects
    //  Check if the fragment shader compiles successfully
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Failed to compile fragment shader:\n" << infoLog << std::endl;
        return 0;
    }

    // Create shader program
    GLuint shaderProgram = glCreateProgram();
    // Attach vertex shader and fragment shader to shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Link shader program
    glLinkProgram(shaderProgram);
    // Check if the shader program is linked successfully
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Failed to link shader program:\n" << infoLog << std::endl;
        return 0;
    }

    // Delete vertex shader and fragment shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}


int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Stars", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Call createShaderProgram()
    GLuint shaderProgram = createShaderProgram();
    if (shaderProgram == 0)
    {
        glfwTerminate();
        return -1;
    }

    // Generate stars
    int numStars = 100;
    std::vector<Star> stars = generateStars(numStars);

    // Create VBO and VAO
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO and pass star data to OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(stars.size() * sizeof(Star)), stars.data(), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, stars.size() * sizeof(Star), stars.data(), GL_STATIC_DRAW);

    
   // Set vertex property pointer
   // Associate data for position, color, and pointSize attributes with vertex array objects and enable the corresponding vertex attribute arrays so that they can be passed and used correctly at render time
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)0);  // Position property
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)(3 * sizeof(GLfloat)));  // Color property
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Star), (void*)(6 * sizeof(GLfloat))); // pointSize property
    glEnableVertexAttribArray(2);

    // Unbind VAO, VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Rend loop
    while (!glfwWindowShouldClose(window))
    {
        // Clean screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        // Use shaderProgram
        glUseProgram(shaderProgram);

        glEnable(GL_PROGRAM_POINT_SIZE);

        // Bind VAO
        glBindVertexArray(VAO);

        // Draw stars
        glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(stars.size())); 
        //glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(stars.size()));
        //glDrawArrays(GL_POINTS, 0, stars.size());

        // Unbind VAO
        glBindVertexArray(0);

        //Check for OpenGL errors
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cout << "OpenGL Error: " << error << std::endl;
        }

        // Debug output
        // std::cout << "Rendering frame" << std::endl;

        // Check and call events, swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Delete vertex array objects and vertex buffer objects
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Clean up and close the GLFW window
    glfwTerminate();

    return 0;
}

