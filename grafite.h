#ifndef GRAFITE_H
#define GRAFITE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#define internal static

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float r32;
typedef double r64;

typedef s32 b32;

#define gf_for_range(iter,start,end) for(s32 iter = start; iter < end; ++iter)
#define gf_for_range_i(start,end) gf_for_range(i,start,end)
#define gf_for_range_j(start,end) gf_for_range(j,start,end)
#define gf_for(iter,count) for(s32 iter = 0; iter < count; ++iter )
#define gf_for_i(count) gf_for(i,count)
#define gf_for_j(count) gf_for(j,count)

#define BIT(x) 1 << (x)

#define KiB(x) ((x) << 10)
#define MiB(x) (KiB(x) << 10)
#define GiB(x) (MiB(x) << 10)

#undef MIN
#undef MAX
#undef CLAMP
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define CLAMP(value,min,max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))


typedef union {
    r32 xy[2];        
    struct {
        r32 x,y;
    };
} gf_vec2;
#define gf_v2(x,y) ((gf_vec2){x,y})

internal inline gf_vec2 gf_vec2_add(gf_vec2 a, gf_vec2 b);
internal inline gf_vec2 gf_vec2_sub(gf_vec2 a, gf_vec2 b);
internal inline gf_vec2 gf_vec2_mul(gf_vec2 vec, r32 factor);
internal inline gf_vec2 gf_vec2_div(gf_vec2 vec, r32 factor);
internal inline gf_vec2 gf_vec2_negate(gf_vec2 vec);
internal inline gf_vec2 gf_vec2_perp_cw(gf_vec2 vec);
internal inline gf_vec2 gf_vec2_perp_ccw(gf_vec2 vec);
internal inline gf_vec2 gf_vec2_normalize(gf_vec2 vec);
internal inline gf_vec2 gf_vec2_to_length(gf_vec2 vec, r32 length);
internal inline r32 gf_vec2_len_sq(gf_vec2 vec);
internal inline r32 gf_vec2_len(gf_vec2 vec);
internal inline r32 gf_vec2_dist(gf_vec2 a, gf_vec2 b);
internal inline r32 gf_vec2_dot(gf_vec2 a, gf_vec2 b);


typedef union{
    r32 xyz[3];
    struct{
        r32 x,y,z;
    };
} gf_vec3;
#define gf_v3(x,y,z) ((gf_vec3){x,y,z})

internal inline gf_vec3 gf_vec3_add(gf_vec3 a, gf_vec3 b);
internal inline gf_vec3 gf_vec3_sub(gf_vec3 a, gf_vec3 b);
internal inline gf_vec3 gf_vec3_mul(gf_vec3 a, r32 factor);
internal inline gf_vec3 gf_vec3_div(gf_vec3 a, r32 factor);
internal inline gf_vec3 gf_vec3_negate(gf_vec3 vec);
internal inline gf_vec3 gf_vec3_cross(gf_vec3 a, gf_vec3 b);
internal inline gf_vec3 gf_vec3_normalize(gf_vec3 vec);
internal inline gf_vec3 gf_vec3_to_length(gf_vec3 vec, r32 length);
internal inline r32 gf_vec3_len_sq(gf_vec3 vec);
internal inline r32 gf_vec3_len(gf_vec3 vec);
internal inline r32 gf_vec3_dist(gf_vec3 a, gf_vec3 b);
internal inline r32 gf_vec3_dot(gf_vec3 a, gf_vec3 b);


internal inline r32 gf_map(r32 x, r32 in_min, r32 in_max, r32 out_min, r32 out_max);
internal inline r32 gf_lerp(r32 v0, r32 v1, r32 t);


//////////////////////////////
/// Color
//////////////////////////////
typedef struct {
    u8 r,g,b,a;
} gf_color;

internal inline gf_color gf_color_from_hex_string(const char * hex_string);


//////////////////////////////
/// Utility
//////////////////////////////

typedef struct {
    u8 *data;
    s64 size;
} gf_file_data;

internal inline gf_file_data *gf_read_entire_file(const char* file_path, b32 text);
internal inline void gf_free_file_data(gf_file_data *file_data);

//////////////////////////////
/// Graphics
//////////////////////////////
internal inline u32 gf_load_shader_from_source_gl(const char *vertex_source, const char *fragment_source);
internal inline u32 gf_load_shader_from_file_gl(const char* vertex_file, const char *fragment_file);
internal inline u32 gf_create_empty_texture(u32 width, u32 height);



//////////////////////////////
/// Framework
//////////////////////////////

#define GS_TITLE_MAX_SIZE 256
typedef struct {
    u32 window_width;
    u32 window_height;
    const char window_title[GS_TITLE_MAX_SIZE];
    void(*init)(void);
    void(*update)(void);
    void(*deinit)(void);
} gf_app_desc;


#ifdef GRAFITE_IMPL

//////////////////////////////
/// Math Implementation
//////////////////////////////

/* gf_vec2 */
internal inline gf_vec2 gf_vec2_add(gf_vec2 a, gf_vec2 b){
    return gf_v2(a.x+b.x,a.y+b.y);
}
internal inline gf_vec2 gf_vec2_sub(gf_vec2 a, gf_vec2 b){
    return gf_v2(a.x-b.x,a.y-b.y);
}
internal inline gf_vec2 gf_vec2_mul(gf_vec2 vec, r32 factor){
    return gf_v2(vec.x*factor,vec.y*factor);
}
internal inline gf_vec2 gf_vec2_div(gf_vec2 vec, r32 factor){
    return gf_v2(vec.x/factor,vec.y/factor);
}
internal inline gf_vec2 gf_vec2_negate(gf_vec2 vec){
    return gf_v2(-vec.x,-vec.y);
}
internal inline gf_vec2 gf_vec2_perp_cw(gf_vec2 vec){
    return gf_v2(vec.y,-vec.x);
}
internal inline gf_vec2 gf_vec2_perp_ccw(gf_vec2 vec){
    return gf_v2(-vec.y,vec.x);
}
internal inline gf_vec2 gf_vec2_normalize(gf_vec2 vec){
    r32 l = gf_vec2_len(vec);
    return gf_v2(vec.x/l,vec.y/l);
}
internal inline gf_vec2 gf_vec2_to_length(gf_vec2 vec, r32 length){
    return gf_vec2_mul(gf_vec2_normalize(vec),length);
}
internal inline r32 gf_vec2_len_sq(gf_vec2 vec){
    return vec.x*vec.x + vec.y*vec.y;
}
internal inline r32 gf_vec2_len(gf_vec2 vec){
    return sqrtf(gf_vec2_len_sq(vec));
}
internal inline r32 gf_vec2_dist(gf_vec2 a, gf_vec2 b){
    return gf_vec2_len(gf_vec2_sub(b,a));
}
internal inline r32 gf_vec2_dot(gf_vec2 a, gf_vec2 b){
    return a.x*b.x+a.y*b.y;
}


/* gf_vec3 */
internal inline gf_vec3 gf_vec3_add(gf_vec3 a, gf_vec3 b){
    return gf_v3(a.x+b.x,a.y+b.y,a.z+b.z);
}
internal inline gf_vec3 gf_vec3_sub(gf_vec3 a, gf_vec3 b){
    return gf_v3(a.x-b.x,a.y-b.y,a.z-b.z);
}
internal inline gf_vec3 gf_vec3_mul(gf_vec3 vec, r32 factor){
    return gf_v3(vec.x*factor,vec.y*factor,vec.z*factor);
}
internal inline gf_vec3 gf_vec3_div(gf_vec3 vec, r32 factor){
    return gf_v3(vec.x/factor,vec.y/factor,vec.z/factor);
}
internal inline gf_vec3 gf_vec3_negate(gf_vec3 vec){
    return gf_v3(-vec.x,-vec.y,-vec.z);
}
internal inline gf_vec3 gf_vec3_cross(gf_vec3 a, gf_vec3 b){
    return gf_v3(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}
internal inline gf_vec3 gf_vec3_normalize(gf_vec3 vec){
    r32 l = gf_vec3_len(vec);
    return gf_v3(vec.x/l,vec.y/l,vec.z/l);
}
internal inline gf_vec3 gf_vec3_to_length(gf_vec3 vec, r32 length){
    return gf_vec3_mul(gf_vec3_normalize(vec),length);
}
internal inline r32 gf_vec3_len_sq(gf_vec3 vec){
    return vec.x*vec.x+vec.y*vec.y+vec.z*vec.z;
}
internal inline r32 gf_vec3_len(gf_vec3 vec){
    return sqrtf(gf_vec3_len_sq(vec));
}
internal inline r32 gf_vec3_dist(gf_vec3 a, gf_vec3 b){
    return gf_vec3_len(gf_vec3_sub(b,a));
}
internal inline r32 gf_vec3_dot(gf_vec3 a, gf_vec3 b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

/* misc */
internal inline r32 gf_map(r32 x, r32 in_min, r32 in_max, r32 out_min, r32 out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

internal inline r32 gf_lerp(r32 v0, r32 v1, r32 t) {
  return v0 + t * (v1 - v0);
}



//////////////////////////////
/// Color Implementation
//////////////////////////////
internal inline gf_color gf_color_from_hex_string(const char * hex_string){
    //NOTE(Luna): This doesn't handle malformed inputs beware
    s64 packed = strtol(hex_string,NULL,16);
    gf_color ret;
    ret.r = (packed >> 16) & 0xFF;
    ret.g = (packed >> 8) & 0xFF;
    ret.b = (packed >> 0) & 0xFF;
    ret.a = 255;
    return ret;
}

//////////////////////////////
/// Utility Implementation
//////////////////////////////

internal inline gf_file_data* gf_read_entire_file(const char* file_path, b32 text){
    gf_file_data *file_data = (gf_file_data*)malloc(sizeof(gf_file_data));
    FILE *fd = fopen(file_path, text ? "rt" : "rb");
    fseek(fd,0,SEEK_END);
    file_data->size = ftell(fd);
    rewind(fd);
    file_data->data = (u8*)malloc(file_data->size + (text ? 1 : 0));
    fread(file_data->data,1,file_data->size,fd);
    if(text){
        file_data->data[file_data->size] = '\0';
    }
    fclose(fd);
    return file_data;
}

internal inline void gf_free_file_data(gf_file_data *file_data){
    free(file_data->data);
    file_data = NULL;
}


//////////////////////////////
/// Graphics Implementation
//////////////////////////////

#include "./external/glad/glad.h"
#define MAX_INFO_LOG_LENGTH 512
internal inline u32 gf_load_shader_from_file_gl(const char* vertex_path, const char *fragment_path){
    gf_file_data *vertex_file = gf_read_entire_file(vertex_path,1);
    gf_file_data *fragment_file = gf_read_entire_file(fragment_path,1);
    u32 program_id = gf_load_shader_from_source_gl(vertex_file->data,fragment_file->data);
    gf_free_file_data(vertex_file);
    gf_free_file_data(fragment_file);
    return program_id;
}
internal inline u32 gf_load_shader_from_source_gl(const char *vertex_source, const char *fragment_source){
    static char message_buffer[MAX_INFO_LOG_LENGTH];
    int32_t message_size;
    u32 vertex_id = glCreateShader(GL_VERTEX_SHADER);
    u32 fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    u32 program_id = glCreateProgram();

    glShaderSource(vertex_id, 1, &vertex_source, NULL);
    glShaderSource(fragment_id, 1, &fragment_source, NULL);
    glCompileShader(vertex_id);
    glGetShaderInfoLog(vertex_id, sizeof(message_buffer), &message_size, message_buffer);
    printf("[ShaderInfo - (Vertex)]:\n%s", message_buffer);
    glCompileShader(fragment_id);
    glGetShaderInfoLog(fragment_id, sizeof(message_buffer), &message_size, message_buffer);
    printf("[ShaderInfo - (Fragment)]:\n%s", message_buffer);
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glLinkProgram(program_id);
    glGetProgramInfoLog(program_id,sizeof(message_buffer),&message_size,message_buffer);
    printf("[ProgramInfo]:\n%s", message_buffer);
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    return program_id;
}
internal inline u32 gf_create_empty_texture(u32 width, u32 height){
    u32 texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return texture_id;
}

#undef GRAFITE_IMPL
#endif

#ifdef GRAFITE_GLFW_HIJACK_MAIN
#include <GLFW/glfw3.h>

extern gf_app_desc gf_main(int argc, char **argv);


//TODO(Luna): Make this usable -> eg engine / framework context etc. with input handling / callbacks etc. -> global framework/platfrom context
int main(int argc, char** argv){
    gf_app_desc app_desc = gf_main(argc,argv);
    
    glfwInit();
    GLFWwindow *main_window = glfwCreateWindow(app_desc.window_width,app_desc.window_height,app_desc.window_title,NULL,NULL);
    glfwMakeContextCurrent(main_window);
    gladLoadGL();

    if(app_desc.init)
        app_desc.init();

    while(!glfwWindowShouldClose(main_window)){
        if(app_desc.update)
            app_desc.update();
        glfwPollEvents();
        glfwSwapBuffers(main_window);
    }

    if(app_desc.deinit)
        app_desc.deinit();

    glfwDestroyWindow(main_window);
    glfwTerminate();
    
    return 0;   
}

#undef GRAFITE_GLFW_HIJACK_MAIN

#endif
#endif