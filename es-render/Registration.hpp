#ifndef IAUNS_REN_REGISTRATION_HPP
#define IAUNS_REN_REGISTRATION_HPP

#include <es-acorn/Acorn.hpp>

namespace ren {

/// Registers all gameplay systems and components.
void registerAll(CPM_ES_ACORN_NS::Acorn& core);

} // namespace ren

#endif 
