#define GRAFITE_IMPL
#define GRAFITE_GLFW_HIJACK_MAIN
#include "grafite.h"

void init(){
    printf("Hello From Init\n");
    glClearColor(1,0,0,1);
}

void update(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void deinit(){
    printf("Goodbye...\n");
}

gf_app_desc gf_main(int argc, char** argv){
    return (gf_app_desc){
        .init = init,
        .deinit = deinit,
        .update = update,
        .window_width = 800,
        .window_height = 600,
        .window_title = "Title"
    };
}