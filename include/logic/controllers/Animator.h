/*!
 * File Animator.h
 */


#pragma once

#include <core/items/Entity.h>
#include <unordered_map>
#include <logic/controllers/Controller.h>

#define FRAMECOUNTER_MAX 3628799

namespace hpms
{


    class Animator : public Controller
    {
    private:
        hpms::Entity* entity;
        std::unordered_map<int, std::unordered_map<std::string, std::pair<int, int>>> animSetsRange;
        int currentAnimChannel;
        std::pair<int, int> currentRange;
        int currentFrame;
        long frameCounter;
        int slowDownFactor;
        bool play;
        bool loop;

    public:


        Animator(Entity* entity) : entity(entity),
                                   currentAnimChannel(0),
                                   slowDownFactor(1),
                                   currentRange({0, 0}),
                                   currentFrame(0),
                                   play(false),
                                   frameCounter(0)
        {}

        inline void RegistryAnimation(const std::string& animName, int startFrame, int endFrame)
        {
            RegistryAnimation(currentAnimChannel, animName, startFrame, endFrame);
        }

        inline void RegistryAnimation(int animChannel, const std::string& animName, int startFrame, int endFrame)
        {
            animSetsRange[animChannel][animName] = std::make_pair(startFrame, endFrame);
        }

        inline int GetCurrentAnimChannel() const
        {
            return currentAnimChannel;
        }

        inline void SetCurrentAnimChannel(int currentAnimChannel)
        {
            Animator::currentAnimChannel = currentAnimChannel;
        }

        inline void SetCurrentAnimation(const std::string& name)
        {
            currentRange = animSetsRange[currentAnimChannel][name];
            Rewind();
        }

        inline int GetSlowDownFactor() const
        {
            return slowDownFactor;
        }

        inline void SetSlowDownFactor(int slowDownFactor)
        {
            Animator::slowDownFactor = slowDownFactor;
        }

        inline bool IsPlay() const
        {
            return play;
        }

        inline void SetPlay(bool play)
        {
            Animator::play = play;
        }

        inline bool IsLoop() const
        {
            return loop;
        }

        inline void SetLoop(bool loop)
        {
            Animator::loop = loop;
        }

        inline void Rewind()
        {
            currentFrame = currentRange.first;
        }


        void Update() override;

        inline const std::string Name() const override
        {
            return "Animator";
        }


    };
}
