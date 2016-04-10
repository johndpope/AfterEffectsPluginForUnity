#include "pch.h"
#include "Foundation.h"
#include "AfterEffectsPlugin.h"
#include "aepModule.h"
#include "aepInstance.h"
#include "aepParam.h"


aepModule::aepModule()
    : m_module()
    , m_entrypoint()
{

}

aepModule::~aepModule()
{
    unload();
}



bool aepModule::load(const char *path)
{
    unload();

    m_module = utj::DLLLoad(path);
    if (!m_module) { return false; }

    // check m_module is AfterEffects plugin
    (void*&)m_entrypoint = utj::DLLGetSymbol(m_module, "EntryPointFunc");
    if (!m_entrypoint) {
        (void*&)m_entrypoint = utj::DLLGetSymbol(m_module, "entryPointFunc");
    }

    if (!m_entrypoint) {
        unload();
        return false;
    }

    return true;
}

void aepModule::unload()
{
    if (m_module) {
        utj::DLLUnload(m_module);
        m_module = nullptr;
        m_entrypoint = nullptr;
    }
}

void aepModule::render()
{
    //m_entrypoint(PF_Cmd_RENDER);
}
