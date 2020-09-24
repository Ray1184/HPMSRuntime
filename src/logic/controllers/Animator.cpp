/*!
 * File Animator.cpp
 */

#include <logic/controllers/Animator.h>

void hpms::Animator::Update()
{
    if (!play && currentFrame >= currentRange.second)
    {
        Rewind();
        return;
    }
    if (frameCounter >= FRAMECOUNTER_MAX)
    {
        frameCounter = 0;
    }

    if (frameCounter++ % slowDownFactor == 0)
    {
        if (currentFrame < currentRange.second)
        {
            currentFrame++;
        } else if (loop)
        {
            Rewind();
        }
        entity->SetAnimCurrentIndex(currentAnimChannel);
        entity->SetAnimCurrentFrameIndex(currentFrame);
    }
}
