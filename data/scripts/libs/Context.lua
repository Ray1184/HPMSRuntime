---
--- Created by Ray1184.
--- DateTime: 04/10/2020 17:04
---
--- Wrapper for cached context.
---

local cats = require('data/scripts/libs/Categories')
local utils = require('data/scripts/libs/Utils')

context = {}
function context:new()
    local ctx = { dummy = false }
    utils.debug('Creating context with categories:')
    for k, v in pairs(cats) do
        ctx[v] = {}
        utils.debug('- ' .. v)
    end
    setmetatable(ctx, self)
    self.__index = self
    return ctx
end

function context:set_mode_r25d()
    self.instance.mode = 'r25d'
end

function context:set_mode_3d()
    self.instance.mode = '3d'
end

function context:set_mode_gui()
    self.instance.mode = 'gui'
end

function context:is_mode_r25d()
    return instance.mode == 'r25d'
end

function context:is_mode_3d()
    return instance.mode == '3d'
end

function context:is_mode_gui()
    return instance.mode == 'gui'
end

function context:set_scene(s)
    self.instance.scene = s
end

function context:get_scene()
    if self.instance.scene == nil then
        utils.warn('Scene is nil in context.')
    end
    return self.instance.scene
end

function context:set_camera(c)
    self.instance.camera = c
end

function context:get_camera()
    if self.instance.camera == nil then
        utils.warn('Camera is nil in context.')
    end
    return self.instance.camera
end

function context:set_lang(lang)
    self.instance.lang = lang
end

function context:get_lang()
    if self.instance.lang == nil then
        self.instance.lang = 'it'
    end
    return self.instance.lang
end

function context:enable_dummy()
    self.instance.dummy = true
end

function context:disable_dummy()
    self.instance.dummy = false
end

function context:inst()
    if self.instance == nil then
        utils.debug("New context created.")
        self.instance = self:new()
    end
    return self.instance
end

function context:put_state(key, obj)
    if key == nil then
        utils.warn('Key cannot be nil.')
        return
    end
    self.instance[cats.STATE][key] = obj
end

function context:put(cat, key, obj)
    if cat == nil then
        utils.warn('Cannot put in context object with nil category.')
        return
    elseif self.instance[cat] == nil then
        utils.warn('Cannot put in context object: ' .. cat .. ' category unknown.')
        return
    end

    if key == nil then
        utils.warn('Key cannot be nil.')
        return
    end

    if obj.serializable == nil then
        utils.warn('For put object in context this must have a serializable block.')
        return
    end
    self.instance[cat][key] = obj.serializable
end

function context:get_state(key)
    if key == nil then
        utils.error('State object nil not allowed.')
        return nil
    end
    if self.instance[cats.STATE][key] == nil then
        utils.error('State object ' .. key .. ' was not initialized in context.')
        return nil
    end
    return self.instance[cats.STATE][key]
end

function context:get(cat, key, supplier_callback)
    if self.instance[cat] == nil then
        if cat == nil then
            utils.warn('Cannot get object from context with nil category.')
        else
            utils.warn('Cannot get object from context: ' .. cat .. ' category unknown.')
        end
        return nil
    end
    if self.instance[cat][key] == nil then
        if key == nil then
            utils.warn('Cannot get object from context with nil key.')
            return nil
        else
            self.instance:put(cat, key, supplier_callback())
        end
    end
    utils.debug('Object with key ' .. key .. ' and category ' .. cat .. ' found in context.')
    local obj = {}
    obj.serializable = self.instance[cat][key]
    return obj
end