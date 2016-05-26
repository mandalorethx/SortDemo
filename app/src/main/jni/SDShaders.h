//
// Created by matt on 5/25/16.
//

#ifndef SORTDEMO_SDSHADERS_H
#define SORTDEMO_SDSHADERS_H

namespace SDShaders
{
    static const char* VertexShader =
            "layout(location=0) in vec3 in_position;\n"
            "layout(location=1) in vec3 in_normal;\n"
            "layout(location=2) in vec3 in_texcoord;\n"
            "layout(location=1) uniform mat4 uMvp;\n"
            "out vec3 v_texcoord;\n"
            "out vec3 v_normal;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = uMvp*vec4(in_position);\n"
            "    v_texcoord = in_texcoord;\n"
            "    vec4 vTmpNorm = uMvp*vec4(in_normal);\n"
            "    v_normal = vTmpNorm.xyz/vTmpNorm.w\n"
            "}\n";

    static const char* FragmentShader =
            "precision highp float; precision highp int;"
            "in vec3 v_texcoord\n"
            "in vec3 v_normal\n"
            "layout(location=0) uniform highp sampler2D uTex;\n"
            "layout(location=2) uniform vec3 uKa;\n"
            "layout(location=3) uniform vec3 uKd;\n"
            "layout(location=4) uniform vec3 uKs;\n"
            "layout(location=5) uniform foat ufNs;\n"
            "layout(location=6) uniform foat ufNi;\n"
            "layout(location=7) uniform foat ufD;\n"
            "layout(location=8) uniform int unIllum;\n"
            "out vec4 vFragColor;\n"
            "void main()\n"
            "{\n"
            "    vFragColor = vec4(1.0);\n"
            "}\n";

};

#endif //SORTDEMO_SDSHADERS_H
