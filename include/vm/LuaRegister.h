/**
 * File LuaRegister.h
 */
#pragma once

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <vector>
#include <LuaBridge/LuaBridge.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vm/LuaExtensions.h>
#include <core/items/Entity.h>
#include <input/KeyEvent.h>
#include <logic/controllers/Collisor.h>
#include <logic/controllers/Animator.h>

using namespace luabridge;

namespace hpms
{
    class LuaRegister
    {
    public:


        static void RegisterAssetManager(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .addFunction("make_entity", &hpms::AMCreateEntity)
                    .addFunction("delete_entity", &hpms::AMDeleteEntity)
                    .addFunction("make_node", &hpms::AMCreateNode)
                    .addFunction("delete_node", &hpms::AMDeleteNode)
                    .addFunction("delete_node_deep", &hpms::AMDeleteNodeAndActors)
                    .addFunction("make_background", &hpms::AMCreateBackground)
                    .addFunction("delete_background", &hpms::AMDeleteBackground)
                    .addFunction("make_picture", &hpms::AMCreateForeground)
                    .addFunction("delete_picture", &hpms::AMDeleteForeground)
                    .addFunction("make_depth_mask", &hpms::AMCreateDepthMask)
                    .addFunction("delete_depth_mask", &hpms::AMDeleteDepthMask)
                    .addFunction("add_entity_to_scene", &hpms::AMAddEntityToScene)
                    .addFunction("set_node_entity", &hpms::AMSetNodeEntity)
                    .addFunction("add_node_to_scene", &hpms::AMAddNodeToScene)
                    .addFunction("add_picture_to_scene", &hpms::AMAddPictureToScene)
                    .endNamespace();
        }

        static void RegisterEntity(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<hpms::Entity>("entity")
                    .addProperty("position", &hpms::Entity::GetPosition, &hpms::Entity::SetPosition)
                    .addProperty("scale", &hpms::Entity::GetScale, &hpms::Entity::SetScale)
                    .addProperty("rotation", &hpms::Entity::GetRotation, &hpms::Entity::SetRotation)
                    .addProperty("anim_index", &hpms::Entity::GetAnimCurrentIndex, &hpms::Entity::SetAnimCurrentIndex)
                    .addProperty("anim_frame_index", &hpms::Entity::GetAnimCurrentFrameIndex,
                                 &hpms::Entity::SetAnimCurrentFrameIndex)
                    .addProperty("visible", &hpms::Entity::IsVisible, &hpms::Entity::SetVisible)
                    .addProperty("anim_loop", &hpms::Entity::IsAnimLoop, &hpms::Entity::SetAnimLoop)
                    .addProperty("anim_play", &hpms::Entity::IsAnimPlay, &hpms::Entity::SetAnimPlay)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterNode(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<hpms::SceneNode>("node")
                    .addProperty("position", &hpms::SceneNode::GetPosition, &hpms::SceneNode::SetPosition)
                    .addProperty("scale", &hpms::SceneNode::GetScale, &hpms::SceneNode::SetScale)
                    .addProperty("rotation", &hpms::SceneNode::GetRotation, &hpms::SceneNode::SetRotation)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterPicture(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<hpms::Picture>("picture")
                    .addProperty("alpha", &hpms::Picture::GetAlpha, &hpms::Picture::SetAlpha)
                    .addProperty("x", &hpms::Picture::GetX, &hpms::Picture::SetX)
                    .addProperty("y", &hpms::Picture::GetY, &hpms::Picture::SetY)
                    .addProperty("visible", &hpms::Picture::IsVisible, &hpms::Picture::SetVisible)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterCommonMath(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .addFunction("to_radians", &hpms::ToRadians)
                    .addFunction("to_degrees", &hpms::ToDegrees)
                    .endNamespace();

        }

        static void RegisterQuaternion(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<glm::quat>("quat")
                    .addConstructor < void(*)
            (void) > ()
                    .addConstructor < void(*)
            (glm::quat) > ()
                    .addConstructor < void(*)
            (float, float, float, float) > ()
                    .addData("x", &glm::quat::x)
                    .addData("y", &glm::quat::y)
                    .addData("z", &glm::quat::z)
                    .addData("w", &glm::quat::w)
                    .endClass()
                    .addFunction("quat_mul", &hpms::MulQuat)
                    .addFunction("from_axis", &hpms::FromAxisQuat)
                    .addFunction("get_direction", &hpms::GetDirection)
                    .addFunction("from_euler", &hpms::FromEuler)
                    .endNamespace();

        }

        static void RegisterVector3(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<glm::vec3>("vec3")
                    .addConstructor < void(*)
            (void) > ()
                    .addConstructor < void(*)
            (float, float, float) > ()
                    .addData("x", &glm::vec3::x)
                    .addData("y", &glm::vec3::y)
                    .addData("z", &glm::vec3::z)
                    .endClass()
                    .addFunction("vec3_add", &hpms::SumVec3)
                    .addFunction("vec3_sub", &hpms::SubVec3)
                    .addFunction("vec3_mul", &hpms::MulVec3)
                    .addFunction("vec3_div", &hpms::DivVec3)
                    .addFunction("vec3_dist", &hpms::DistVec3)
                    .addFunction("vec3_dot", &hpms::DotVec3)
                    .addFunction("vec3_cross", &hpms::CrossVec3)
                    .endNamespace();

        }

        static void RegisterVector4(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<glm::vec4>("vec4")
                    .addConstructor < void(*)
            (void) > ()
                    .addConstructor < void(*)
            (float, float, float, float) > ()
                    .addData("w", &glm::vec4::w)
                    .addData("x", &glm::vec4::x)
                    .addData("y", &glm::vec4::y)
                    .addData("z", &glm::vec4::z)
                    .endClass()
                    .addFunction("vec4_add", &hpms::SumVec4)
                    .addFunction("vec4_sub", &hpms::SubVec4)
                    .addFunction("vec4_mul", &hpms::MulVec4)
                    .addFunction("vec4_div", &hpms::DivVec4)
                    .addFunction("vec4_dot", &hpms::DotVec4)
                    .endNamespace();

        }

        static void RegisterVector2(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<glm::vec2>("vec2")
                    .addConstructor < void(*)
            (void) > ()
                    .addConstructor < void(*)
            (float, float) > ()
                    .addData("x", &glm::vec2::x)
                    .addData("y", &glm::vec2::y)
                    .endClass()
                    .addFunction("vec2_add", &hpms::SumVec2)
                    .addFunction("vec2_sub", &hpms::SubVec2)
                    .addFunction("vec2_mul", &hpms::MulVec2)
                    .addFunction("vec2_div", &hpms::DivVec2)
                    .addFunction("vec2_dist", &hpms::DistVec2)
                    .addFunction("vec2_dot", &hpms::DotVec2)
                    .endNamespace();

        }

        static void RegisterMatrix4(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<glm::mat4>("mat4")
                    .addConstructor < void(*)
            (void) > ()
                    .endClass()
                    .addFunction("mat4_add", &hpms::SumMat4)
                    .addFunction("mat4_sub", &hpms::SubMat4)
                    .addFunction("mat4_mul", &hpms::MulMat4)
                    .addFunction("mat4_div", &hpms::DivMat4)
                    .addFunction("mat4_elem_at", &hpms::ElemAtMat4)
                    .endNamespace();

        }

        static void RegisterKeyEvent(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<KeyEvent>("key_event")
                    .addData("key", &KeyEvent::key)
                    .addData("input_type", &KeyEvent::inputType)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterKeyList(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<std::vector<KeyEvent>>("key_list")
                    .endClass()
                    .addFunction("action_performed", &hpms::KHKeyAction)
                    .endNamespace();
        }

        static void RegisterScene(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<Scene>("scene")
                    .addProperty("ambient_light", &hpms::Scene::GetAmbientLight, &hpms::Scene::SetAmbientLight)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterCamera(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<Camera>("camera")
                    .addProperty("position", &hpms::Camera::GetPosition, &hpms::Camera::SetPosition)
                    .addProperty("rotation", &hpms::Camera::GetRotation, &hpms::Camera::SetRotation)
                    .endClass()
                    .addFunction("update_view", &hpms::AMUpdateCamera)
                    .endNamespace();
        }

        static void RegisterLogic(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .addFunction("make_walkmap", &hpms::LCreateWalkMap)
                    .addFunction("delete_walkmap", &hpms::LDeleteWalkMap)
                    .addFunction("make_node_collisor", &hpms::LCreateNodeCollisor)
                    .addFunction("make_entity_collisor", &hpms::LCreateEntityCollisor)
                    .addFunction("delete_collisor", &hpms::LDeleteCollisor)
                    .addFunction("make_animator", &hpms::LCreateAnimator)
                    .addFunction("delete_animator", &hpms::LDeleteAnimator)
                    .addFunction("enable_controller", &hpms::LEnableController)
                    .addFunction("disable_controller", &hpms::LDisableController)
                    .addFunction("update_animator", &hpms::LUpdateAnimator)
                    .addFunction("update_collisor", &hpms::LUpdateCollisor)
                    .addFunction("move_collisor_dir", &hpms::LMoveCollisor)
                    .addFunction("add_anim", &hpms::LRegisterAnimation)
                    .addFunction("anim_sequence_terminated", &hpms::LIsAnimationSequenceFinished)
                    .addFunction("set_anim", &hpms::LSetAnimation)
                    .addFunction("rewind_anim", &hpms::LRewind)
                    .endNamespace();
        }

        static void RegisterWalkMap(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<WalkMap>("walkmap")
                    .addProperty("name", &hpms::WalkMap::GetName, &hpms::WalkMap::SetName)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterTriangle(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<Triangle>("sector")
                    .addProperty("id", &hpms::Triangle::GetSectorId, &hpms::Triangle::SetSectorId)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterCollisor(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<Collisor>("collisor")
                    .addProperty("position", &hpms::Collisor::GetPosition, &hpms::Collisor::SetPosition)
                    .addProperty("rotation", &hpms::Collisor::GetRotation, &hpms::Collisor::SetRotation)
                    .addProperty("sector", &hpms::Collisor::GetCurrentTriangle, &hpms::Collisor::SetCurrentTriangle)
                    .endClass()
                    .endNamespace();
        }

        static void RegisterAnimator(lua_State* state)
        {
            getGlobalNamespace(state)
                    .beginNamespace("hpms")
                    .beginClass<Animator>("animator")
                    .addProperty("anim_channel", &hpms::Animator::GetCurrentAnimChannel,
                                 &hpms::Animator::SetCurrentAnimChannel)
                    .addProperty("loop", &hpms::Animator::IsLoop, &hpms::Animator::SetLoop)
                    .addProperty("id", &hpms::Animator::GetId, &hpms::Animator::SetId)
                    .addProperty("play", &hpms::Animator::IsPlay, &hpms::Animator::SetPlay)
                    .addProperty("still_playing", &hpms::Animator::IsStillPlaying, &hpms::Animator::SetStillPlaying)
                    .addProperty("slow_down_factor", &hpms::Animator::GetSlowDownFactor,
                                 &hpms::Animator::SetSlowDownFactor)
                    .endClass()
                    .endNamespace();
        }


    };
}
