
#include <es-general/comp/Transform.hpp>

#include "Lines.hpp"
#include "es-render/comp/StaticVBOMan.hpp"
#include "es-render/comp/StaticIBOMan.hpp"
#include "es-render/comp/StaticShaderMan.hpp"
#include "es-render/comp/VBO.hpp"
#include "es-render/comp/IBO.hpp"

namespace ren {

std::pair<ren::VBO, ren::IBO> getLineUnitSquare(CPM_ES_CEREAL_NS::CerealCore& core)
{
  ren::VBOMan& vboMan = *core.getStaticComponent<ren::StaticVBOMan>()->instance;
  ren::IBOMan& iboMan = *core.getStaticComponent<ren::StaticIBOMan>()->instance;

  const std::string assetName = "_g_usqline";

  GLuint vbo = vboMan.hasVBO(assetName);
  if (vbo == 0)
  {
    // Build the vertex buffer object and add it to the vbo manager.
    // Build a VBO.
    const size_t vboFloatSize = 5*5;
    float vboData[vboFloatSize] =
    {
      // Position           'Circumfrence'
      -1.0f,  1.0f,  0.0f,  0.0f,
       1.0f,  1.0f,  0.0f,  1.0f,
       1.0f, -1.0f,  0.0f,  3.0f,
      -1.0f, -1.0f,  0.0f,  2.0f,
      -1.0f,  1.0f,  0.0f,  4.0f,   // Return to orign line.
    };
    size_t vboByteSize = vboFloatSize * sizeof(float);

    vbo = vboMan.addInMemoryVBO(
        static_cast<void*>(vboData), vboByteSize,
        { std::make_tuple("aPos", 3 * sizeof(float), false),
          std::make_tuple("aLineCircum", 1 * sizeof(float), false) },
        assetName);
  }

  // Build VBO component to add to the entityID.
  ren::VBO vboComp;
  vboComp.glid = vbo;

  const size_t iboIntSize = 8;
  ren::IBO iboComp;
  iboComp.primType = GL_UNSIGNED_SHORT;
  iboComp.primMode = GL_LINES;
  iboComp.numPrims = iboIntSize;

  GLuint ibo = iboMan.hasIBO(assetName);
  if (ibo == 0)
  {
    // Build an IBO
    uint16_t iboData[iboIntSize] =
    {
      0, 1, 1, 2, 2, 3, 3, 4
    };
    size_t iboByteSize = iboIntSize * sizeof(uint16_t);

    ibo = iboMan.addInMemoryIBO(static_cast<void*>(iboData), iboByteSize,
                                iboComp.primMode, iboComp.primType,
                                iboComp.numPrims, assetName);
  }

  iboComp.glid = ibo;

  return std::make_pair(vboComp, iboComp);
}

GLuint getColorLineShader(CPM_ES_CEREAL_NS::CerealCore& core)
{
  const char* colorLineShaderName = "_memColorLine";
  ren::ShaderMan& shaderMan = *core.getStaticComponent<ren::StaticShaderMan>()->instance;

  GLuint shaderID = shaderMan.getIDForAsset(colorLineShaderName);
  if (shaderID == 0)
  {
#ifndef ION_GLSL4
    const char* vs =
        "uniform mat4 uProjIVObject;\n"
        "uniform vec4 uColor;\n"
        "attribute vec3 aPos;\n"
        "varying vec4 fColor;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = uProjIVObject * vec4(aPos, 1.0);\n"
        "  fColor = uColor;\n"
        "}\n";
    const char* fs =
        "#ifdef OPENGL_ES\n"
        "  #ifdef GL_FRAGMENT_PRECISION_HIGH\n"
        "    precision highp float;\n"
        "  #else\n"
        "    precision mediump float;\n"
        "  #endif\n"
        "#endif\n"
        "varying vec4 fColor;\n"
        "void main()\n"
        "{\n"
        "  gl_FragColor = fColor;\n"
        "}\n";
#else
    const char* vs =
        "#version 400\n"
        "uniform mat4 uProjIVObject;\n"
        "uniform vec4 uColor;\n"
        "in vec3 aPos;\n"
        "out vec4 fColor;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = uProjIVObject * vec4(aPos, 1.0);\n"
        "  fColor = uColor;\n"
        "}\n";
    const char* fs =
        "#version 400\n"
        "in vec4 fColor;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "  FragColor = fColor;\n"
        "}\n";
#endif

    shaderID = shaderMan.addInMemoryVSFS(vs, fs, colorLineShaderName);
  }

  return shaderID;
}

} // namespace ren

