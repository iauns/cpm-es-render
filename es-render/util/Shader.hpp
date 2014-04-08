#ifndef IAUNS_ES_RENDER_UTIL_SHADER_HPP
#define IAUNS_ES_RENDER_UTIL_SHADER_HPP

#include <es-cereal/CerealCore.hpp>

namespace ren {

void addShaderVSFS(CPM_ES_CEREAL_NS::CerealCore& core, uint64_t entityID,
                   const std::string& shader);

} // namespace ren

#endif 
