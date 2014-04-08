#include "Shader.hpp"
#include "es-render/comp/StaticShaderMan.hpp"

namespace ren {

void addShaderVSFS(CPM_ES_CEREAL_NS::CerealCore& core, uint64_t entityID,
                   const std::string& shader)
{
  ren::ShaderMan& shaderMan = *core.getStaticComponent<ren::StaticShaderMan>()->instance;
  shaderMan.loadVertexAndFragmentShader(core, entityID, shader);
}

} // namespace ren

