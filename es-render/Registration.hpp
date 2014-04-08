#ifndef IAUNS_REN_REGISTRATION_HPP
#define IAUNS_REN_REGISTRATION_HPP

#include <es-cereal/CerealCore.hpp>

namespace ren {

/// Registers all gameplay systems and components.
void registerAll(CPM_ES_CEREAL_NS::CerealCore& core);

} // namespace ren

#endif 
