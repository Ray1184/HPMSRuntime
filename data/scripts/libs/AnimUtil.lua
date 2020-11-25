---
--- Created by Ray1184.
--- DateTime: 04/11/2020 17:04
---
--- Animation utilities.
---

local lib = require('data/scripts/libs/HPMSFacade')
local anim_by_entity = {}

return {
    play = function(strategy)
        local animator = strategy.animator
        local anim_sets = strategy.anim_sets
        local prev_valid = false
        for index = 1, #anim_sets do
            if not prev_valid then
                local sequence = anim_sets[index][1]
                local condition = anim_sets[index][2]
                if condition() and not animator.still_playing and anim_by_entity[animator.id] ~= sequence then
                    lib.rewind_anim(animator)
                    anim_by_entity[animator.id] = sequence
                    lib.set_anim(animator, sequence)
                    return
                end
            end
        end
    end
}