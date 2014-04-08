#ifndef IAUNS_RENDER_COMPONENT_STATIC_VBO_MAN_HPP
#define IAUNS_RENDER_COMPONENT_STATIC_VBO_MAN_HPP

#include <memory>
#include <es-cereal/ComponentSerialize.hpp>
#include "../VBOMan.hpp"

namespace ren {

class VBOMan;

struct StaticVBOMan
{
  // -- Data --
  std::unique_ptr<VBOMan> instance;

  // -- Functions --
  StaticVBOMan() : instance(new VBOMan) {}
  StaticVBOMan(const StaticVBOMan&) : instance(new VBOMan) {}
  StaticVBOMan(StaticVBOMan&& o) : instance(std::move(o.instance)) {}
  StaticVBOMan& operator=(const StaticVBOMan&) {return *this;}

  static const char* getName() {return "ren:StaticVBOMan";}

  bool serialize(CPM_ES_CEREAL_NS::ComponentSerialize& /* s */, uint64_t /* entityID */)
  {
    // No need to serialize.
    return true;
  }
};

} // namespace ren

#endif 
