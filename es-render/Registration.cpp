#include "Registration.hpp"

// Systems
#include "systems/RenderSimpleGeomSys.hpp"
#include "systems/RenderFontSys.hpp"
#include "systems/ArcBallCameraSys.hpp"
#include "VBOMan.hpp"
#include "ShaderMan.hpp"
#include "GeomMan.hpp"
#include "TextureMan.hpp"

#include "systems/UtilViewPosAlignSys.hpp"
#include "systems/debug/RenderClickBox2DSys.hpp"

// Components
#include "comp/CommonUniforms.hpp"
#include "comp/GLState.hpp"
#include "comp/IBO.hpp"
#include "comp/MatUniform.hpp"
#include "comp/RenderSequence.hpp"
#include "comp/Shader.hpp"
#include "comp/ShaderPromiseVF.hpp"
#include "comp/RenderSimpleGeom.hpp"
#include "comp/SkinnedGeom.hpp"
#include "comp/StaticArcBallCam.hpp"
#include "comp/StaticGLState.hpp"
#include "comp/StaticShaderMan.hpp"
#include "comp/StaticVBOMan.hpp"
#include "comp/StaticGeomMan.hpp"
#include "comp/StaticTextureMan.hpp"
#include "comp/StaticFontMan.hpp"
#include "comp/StaticIBOMan.hpp"
#include "comp/GeomPromise.hpp"
#include "comp/Geom.hpp"
#include "comp/Font.hpp"
#include "comp/FontPromise.hpp"
#include "comp/Texture.hpp"
#include "comp/TexturePromise.hpp"
#include "comp/UniformLocation.hpp"
#include "comp/VBO.hpp"
#include "comp/VecUniform.hpp"
#include "comp/RenderFont.hpp"

#include "comp/UtilViewPosAlign.hpp"

namespace ren {

void registerAll(CPM_ES_ACORN_NS::Acorn& core)
{
  // Systems
  registerSystem_RenderSimpleGeom(core);
  registerSystem_RenderFont(core);
  registerSystem_ArcBallCameraMouse(core);
  registerSystem_DebugRenderClickBox2D(core);
  VBOMan::registerSystems(core);
  IBOMan::registerSystems(core);
  ShaderMan::registerSystems(core);
  GeomMan::registerSystems(core);
  TextureMan::registerSystems(core);
  FontMan::registerSystems(core);

  // Components
  core.registerComponent<CommonUniforms>();
  core.registerComponent<GLState>();
  core.registerComponent<IBO>();
  core.registerComponent<MatUniform>();
  core.registerComponent<RenderSequence>();
  core.registerComponent<Shader>();
  core.registerComponent<ShaderPromiseVF>();
  core.registerComponent<RenderSimpleGeom>();
  core.registerComponent<SkinnedGeom>();
  core.registerComponent<StaticArcBallCam>();
  core.registerComponent<StaticGLState>();
  core.registerComponent<StaticShaderMan>();
  core.registerComponent<StaticGeomMan>();
  core.registerComponent<StaticTextureMan>();
  core.registerComponent<StaticVBOMan>();
  core.registerComponent<StaticIBOMan>();
  core.registerComponent<StaticFontMan>();
  core.registerComponent<Font>();
  core.registerComponent<FontPromise>();
  core.registerComponent<RenderFont>();
  core.registerComponent<Texture>();
  core.registerComponent<TexturePromise>();
  core.registerComponent<UniformLocation>();
  core.registerComponent<VBO>();
  core.registerComponent<VecUniform>();
  core.registerComponent<Geom>();
  core.registerComponent<GeomPromise>();

  // Register utility systems
  registerSystem_UtilViewPosAlign(core);

  // Register utility components
  core.registerComponent<UtilViewPosAlign>();
}

} // namespace ren

