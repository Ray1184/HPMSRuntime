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

    enum AnimMode
    {
        FORWARD = 0,
        BACKWARD = 1
    };

    class Animator : public Controller
    {
    private:
        hpms::Entity* entity;
        std::unordered_map<int, std::unordered_map<std::string, std::tuple<int, int, int>>> animSetsRange;
        int currentAnimChannel;
        std::tuple<int, int, int> currentRange;
        int currentFrame;
        long frameCounter;
        int slowDownFactor;
        bool play;
        bool loop;
        bool stillPlaying;
        std::string lastAnim;
        int lastChannel;
        std::string animAfterInterpolate;
        bool interpolating;
        std::unordered_map<std::string, int> transitionsToInterpolate;

    public:


        Animator(Entity* entity) : entity(entity),
                                   currentAnimChannel(0),
                                   slowDownFactor(1),
                                   currentRange({0, 0, FORWARD}),
                                   currentFrame(0),
                                   play(false),
                                   frameCounter(0),
                                   stillPlaying(false),
                                   lastAnim("NONE"),
                                   interpolating(false)
        {}

        inline void RegisterAnimation(const std::string& animName, int startFrame, int endFrame)
        {
            RegisterAnimation(currentAnimChannel, animName, startFrame, endFrame);
        }

        inline void RegisterAnimation(int animChannel, const std::string& animName, int startFrame, int endFrame)
        {
            int mode = startFrame <= endFrame ? FORWARD : BACKWARD;
            animSetsRange[animChannel][animName] = std::make_tuple(startFrame, endFrame, mode);
        }

        inline int GetCurrentAnimChannel() const
        {
            return currentAnimChannel;
        }

        inline void SetCurrentAnimChannel(int currentAnimChannel)
        {
            Animator::currentAnimChannel = currentAnimChannel;
        }

        void CheckAndSetCurrentAnimation(const std::string& name);

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

        inline bool IsStillPlaying() const
        {
            return stillPlaying;
        }

        inline void SetStillPlaying(bool stillPlaying)
        {
            Animator::stillPlaying = stillPlaying;
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
            int mode = std::get<2>(currentRange);
            currentFrame = std::get<0>(currentRange);
        }

        inline void RegisterInterpolation(const std::string& fromAnim, const std::string& toAnim, int framesDuration)
        {
            std::string key = fromAnim + "_" + toAnim;
            transitionsToInterpolate.insert({key, framesDuration});
        }


        void Update() override;

        inline const std::string Name() const override
        {
            return "Animator";
        }


    };
}
