#include <stdio.h>
#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader/Shader330.h>
#include <stb/stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float mixValue = 0.2f;

int main() {
	printf("Hello, World!\n");
    glm::vec3 a{ 1.0, 0.0, 2.0 };
    glm::vec3 b{ 2.0, 1.0, 0.0 };

    printf("a + b = %f\n", glm::length(a + b));

    // glfw: initialize and configure
    glfwInit(); //initializes GLFW library
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //setting hints for next create window call
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //making sure version 3.3 is used
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //for Mac OS X

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //whenever window size changes

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //defines correct function depending on OS we are compliling for
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    /*

    //vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //replacing original code of the shader object
    glCompileShader(vertexShader);

    //checking if vertex shader complied
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\\n" << infoLog << std::endl;
    }

    //fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //checking if fragment shader complied
    int  successX;
    char infoLogX[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successX);
    if (!successX)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogX);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\\n" << infoLogX << std::endl;
    }

    //shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); //attaches shaders to the program

    //checking if program failed
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader); //both are in program now; not needed anymore
    glDeleteShader(fragmentShader);
    */

    // build and compile our shader zprogram
    Shader ourShader("../../Assets/3.3.shader.vs", "../../Assets/3.3.shader.fs"); //text files of vertex and fragment shaders 

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
    };


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); //create VAO
    glGenBuffers(1, &VBO); //create VBO
    glGenBuffers(1, &EBO); //create VBO 
  

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO); //any VBO, EBO, VertexAttribArray, EnableVertexAttribArray will be stored in this -> VAO

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//only one single buffer can be tied to each buffer type
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copying vertices array into a buffer for OpenGL to use -> VBO

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // -> EBO



    //where position attribute is in VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //how OpenGL should interpret VBO vertices. 
    glEnableVertexAttribArray(0); //by default is disabled

    //where color attribute is in VBO
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //1 is for this attribute being the second attribute in a VAO?? 
                       //(VAO attribute index, # of byte size of this attribute, data type of this attribute, normalize this?, byte offset between start of attribute to start of next iteration of this attribute (stride), where attribute first starts in array)
    glEnableVertexAttribArray(1); //same as above first argument

    //where texture coordinates attribute is in VBO
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); 
                       //(VAO attribute index,  # of byte size of this attribute, data type of this attribute, normalize this?, byte offset between start of attribute to start of next iteration of this attribute (stride), where attribute first starts in array)
    glEnableVertexAttribArray(2); //same as above first argument



    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VBO to this buffer type since VBO is configured now

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); //unbind VAO but not necessary since you always need to specificy the VAO to bind it


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    // load and create a texture
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1); //create texture 1 

    glBindTexture(GL_TEXTURE_2D, texture1); //supposed to active default texture first before binding but default texture is always activated so when bind texture is called, it is assigned to the activated texture0
    // set the texture wrapping/filtering options (on the currently bound texture object)

    //texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //s axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //t axis
    //texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); //pictures usually have top of image as y=0 and OpenGL expects bottom of picture to be y=0
    unsigned char* data = stbi_load("../../Assets/explosion.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //puts texture on bound objet 
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    glGenTextures(1, &texture2); //create texture 2

    glBindTexture(GL_TEXTURE_2D, texture2); //supposed to active default texture first before binding but default texture is always activated so when bind texture is called, it is assigned to the activated texture0
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //int width, height, nrChannels;
    data = stbi_load("../../Assets/moderndecisions.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //puts texture on bound objet 
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
   // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class
    ourShader.setInt("texture2", 1);




    while (!glfwWindowShouldClose(window)) {//render loop
        //input
        processInput(window);

        //rendering commands
        glClearColor(0.2, 0.1, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //which buffer we would like to clear

    
        /*
        // update the uniform color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//shader program must be in use before this to work
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); //set a uniform value 
        */
      
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader.use();

        //create transformations

        //model matrix (local to world)
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        //view matrix (world to view)
        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move (moving camera backwards is same as moving entire scene forwards)
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        //projection matrix (view to clip) 
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");

        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader.setMat4("projection", projection);

        /*
        glm::mat4 trans = glm::mat4(1.0f); //identity matrix must be made first or else who matrix will be 0 and any operations on it will be 0
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f)); //even though rotations happen before translations, translations should go first to ensure operations happen how you expect 
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); //if this is above translation- rotates around the the center of screen. if this is below translate- picture in corner and rotating around its center
       */
        
        /*
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); //rotate around z axis (a unit vector)
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));*/

        // set the texture mix value in the shader
        ourShader.setFloat("mixValue", mixValue);

    


        /*
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //location of uniform, how many matrices, transfose matrix?, matrix data but GLM doesn't do it in a way OpenGL likes, so have to use value ptr
        */
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        //check and call events and swap buffers
        glfwSwapBuffers(window); //swap color buffer (2D buffer that contains color values for each pixel in window)
        glfwPollEvents(); //checks if any events are triggered
    }

    // optional: de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate(); //delete all of GLFW allocated resources
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.01f; // change this value accordingly (might be too slow or too fast based on system hardware)
        std::cout << "mix up" << std::endl;
        if (mixValue >= 1.0f) {
            mixValue = 1.0f;
        }
            
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.01f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue <= 0.0f) {
            mixValue = 0.0f;
        }
    }

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

