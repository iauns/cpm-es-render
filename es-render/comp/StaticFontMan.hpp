#ifndef IAUNS_RENDER_COMPONENT_STATIC_FONT_MAN_HPP
#define IAUNS_RENDER_COMPONENT_STATIC_FONT_MAN_HPP

#include <memory>
#include <es-cereal/ComponentSerialize.hpp>
#include "../FontMan.hpp"

namespace ren {

struct StaticFontMan
{
  // -- Data --
  std::unique_ptr<FontMan> instance;

  // -- Functions --
  StaticFontMan() : instance(new FontMan) {}
  StaticFontMan(const StaticFontMan&) : instance(new FontMan) {}
  StaticFontMan(StaticFontMan&& o) : instance(std::move(o.instance)) {}

  // This assignment operator is only used during modification calls inside
  // of the entity system. We don't care about those calls as they won't
  // affect this static shader man.
  StaticFontMan& operator=(const StaticFontMan&)
  {
    // We don't care about the incoming object. We've already created oun own
    // shader man and will continue to use that.
    return *this;
  }

  static const char* getName() {return "ren:StaticFontMan";}

private:
  friend class CPM_ES_CEREAL_NS::CerealHeap<StaticFontMan>;

  bool serialize(CPM_ES_CEREAL_NS::ComponentSerialize&, uint64_t)
  {
    // No need to serialize. But we do want that we were in the component
    // system to be serialized out.
    return true;
  }
};

} // namespace ren

#endif 
