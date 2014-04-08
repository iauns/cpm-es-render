#ifndef IAUNS_COMPONENT_RENDER_FONT_HPP
#define IAUNS_COMPONENT_RENDER_FONT_HPP

#include <es-cereal/ComponentSerialize.hpp>

#include <gl-platform/GLPlatform.hpp>
#include <es-cereal/CerealCore.hpp>
#include "FontPromise.hpp"
#include "StaticFontMan.hpp"

namespace ren {

struct Font
{
  // -- Data --
  uint64_t fontID;

  // -- Functions --
  Font()
  {
    fontID = 0;
  }

  static const char* getName() {return "ren:Font";}

  bool serialize(CPM_ES_CEREAL_NS::ComponentSerialize& s, uint64_t entityID)
  {
    // The logic below ensures we deserialize with promises, not with actual
    // font assets (which wouldn't make sense with OpenGL assets).
    if (s.isDeserializing())
    {
      std::string assetName;
      s.serialize("name", assetName);

      // Build font promise.
      FontPromise newPromise;
      newPromise.requestInitiated = false;
      newPromise.setAssetName(assetName.c_str());

      CPM_ES_CEREAL_NS::CerealCore* core = dynamic_cast<CPM_ES_CEREAL_NS::CerealCore*>(&s.getCore());
      if (core != nullptr)
      {
        core->addComponent(entityID, newPromise);
      }
      else
      {
        std::cerr << "Font.hpp bad cast." << std::endl;
      }

      return false; // We do not want to add this font component back into the components.
                    // Instead we rely on the font promise we created above.
    }
    else
    {
      CPM_ES_CEREAL_NS::CerealCore* core = dynamic_cast<CPM_ES_CEREAL_NS::CerealCore*>(&s.getCore());
      if (core != nullptr)
      {
        StaticFontMan* staticFontMan = core->getStaticComponent<StaticFontMan>();
        FontMan& fontMan = *staticFontMan->instance;

        // Find the asset name associated with our fontID and serialize it out.
        std::string assetName = fontMan.getAssetFromID(fontID);
        s.serialize("name", assetName);
      }
      else
      {
        std::cerr << "Font.hpp bad cast." << std::endl;
      }

      return true;
    }
  }
};

} // namespace ren

#endif 
