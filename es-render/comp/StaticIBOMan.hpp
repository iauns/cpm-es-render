#ifndef IAUNS_RENDER_COMPONENT_STATIC_IBO_MAN_HPP
#define IAUNS_RENDER_COMPONENT_STATIC_IBO_MAN_HPP

#include <memory>
#include <es-cereal/ComponentSerialize.hpp>
#include "../IBOMan.hpp"

namespace ren {

struct StaticIBOMan
{
  // -- Data --
  IBOMan * instance_;
  // -- Functions --
  StaticIBOMan() : instance_(new IBOMan) {}
  StaticIBOMan(IBOMan * v) : instance_(v) {}
  static const char* getName() {return "ren:StaticIBOMan";}

  bool serialize(CPM_ES_CEREAL_NS::ComponentSerialize& /* s */, uint64_t /* entityID */)
  {
    // No need to serialize.
    return true;
  }
};

} // namespace ren

#endif 
