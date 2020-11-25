/*!
 * File Animator.cpp
 */

#include <logic/controllers/Animator.h>

void hpms::Animator::Update()
{
    int first = std::get<0>(currentRange);
    int last = std::get<1>(currentRange);
    bool reverse = std::get<2>(currentRange) == BACKWARD;
    if (!play && currentFrame == first)
    {
        return;
    }
    if (frameCounter >= FRAMECOUNTER_MAX)
    {
        frameCounter = 0;
    }

    if (frameCounter++ % slowDownFactor == 0)
    {
        if (!reverse && currentFrame < last)
        {
            stillPlaying = true;
            currentFrame++;
        } else if (reverse && currentFrame > last)
        {
            stillPlaying = true;
            currentFrame--;
        } else
        {
            stillPlaying = false;
            if (loop)
            {
                Rewind();
            }
        }
        entity->SetAnimCurrentIndex(currentAnimChannel);
        entity->SetAnimCurrentFrameIndex(currentFrame);
    }
}

void hpms::Animator::CheckAndSetCurrentAnimation(const std::string& name)
{
    currentRange = animSetsRange[currentAnimChannel][name];
}

