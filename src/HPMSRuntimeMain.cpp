/**
 * File Main.cpp
 */

#include <core/CustomLogic.h>
#include <core/Simulator.h>
#include <states/HPMSLogic.h>


using namespace hpms;

int main()
{
    bool showTriang = hpms::GetConfB("WIREFRAME", false);
    bool showFps = hpms::GetConfB("SHOW_FPS", true);
    bool compProf = hpms::GetConfB("COMP_PROFILE", false);
    bool fullscreen = hpms::GetConfB("FULLSCREEN", false);
    bool vSync = hpms::GetConfB("HW_VSYNC", false);
    int width = hpms::GetConfI("WND_WIDTH", 1280);
    int height = hpms::GetConfI("WND_HEIGHT", 800);
    std::string name = hpms::GetConfS("RT_NAME", "Default HPMS");

    float fov = hpms::GetConfF("CAM_FOV", 60.0f);
    float zNear = hpms::GetConfF("CAM_ZNEAR", 0.5f);
    float zFar = hpms::GetConfF("CAM_ZFAR", 20.0f);

    Options opts(true, showTriang, showFps, compProf, fullscreen);
    CustomLogic* logic = hpms::SafeNew<HPMSLogic>();
    Perspective pers(glm::radians(fov), zNear, zFar);
    Simulator sim(name, width, height, vSync, opts, pers, logic);
    try
    {
        sim.Start();
    } catch (std::exception& e)
    {
        LOG_ERROR(e.what());
    }
    hpms::SafeDelete(logic);

#if !defined(_DEBUG) && !defined(NDEBUG)
    std::stringstream ss;
    ss << "Start memory dump report.\n------------------------------" << std::endl;
    int leaks = 0;
    for (const auto& pair : hpms::AllocCounter::Instance().allocMap)
    {
        ss << pair.first << ": " << pair.second << std::endl;
        leaks += pair.second;
    }
    ss << std::endl;
    if (leaks == 0)
    {
        ss << "OK, no potential memory leaks detected!" << std::endl;
    } else if (leaks > 0)
    {
        ss << "WARNING, potential memory leaks detected! " << leaks << " allocations not set free." << std::endl;
    } else
    {
        ss << "WARNING, unnecessary memory dealloc detected! " << -leaks << " useless de-allocations." << std::endl;
    }
    ss << "------------------------------";
    LOG_DEBUG(ss.str().c_str());
    LOG_DEBUG("End memory dump report.");
#endif
    return 0;
}
