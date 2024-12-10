
#ifndef OPENGL_HELPER
#define OPENGL_HELPER

#include <GLFW/glfw3.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>

namespace ogl
{
    class OpenGL_STATIC
    {
        private:
            std::ofstream initLog(std::string dir, std::string file) {
                std::ofstream logfile;                
                logfile.open(dir + file);
                if (logfile.bad()) {
                    std::cerr << "Error initializing the logfile path.";
                }
                return logfile;
            }

            void initGLFW() {
                if (!glfwInit())
                {
                    std::exit(EXIT_FAILURE);
                }
            }

        public:
            GLFWwindow * initAll() {
               try {
                initLog("build/","example.txt");
               } catch(std::bad_exception) {
                    std::cerr << "Failed to create log file.";
               } 
            }        
    };
};

#endif