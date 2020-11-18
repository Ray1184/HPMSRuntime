-- Scene script.
common = require("data/scripts/libs/TransformsCommon")
input = require("data/scripts/libs/InputCommon")

scene = {
    name = "Scene_01",
    version = "1.0.0",
    mode = "R25D",
    quit = false,
    setup = function(scene, camera)
        ctx = { mode = 'play' }



        -- Init function callback.
        e = hpms.make_entity('data/models/01.hmdat')
        w = hpms.make_walkmap('data/maps/Basement.hrdat')
        a = hpms.make_animator(e)
        b = hpms.make_background('data/screens/B01_B.png')
        d = hpms.make_depth_mask('data/masks/B01_D.png')
        i = hpms.make_background('data/screens/Inventory.png')
        n = hpms.make_node("NODE_01")
        c = hpms.make_node_collisor(n, w, 1)
        --
        a.anim_channel = 0
        a.loop = true

        a.slow_down_factor = 2

        hpms.add_anim(a, 'move', 0, 25)
        hpms.set_anim(a, 'move')

        common.loc_rot_scale(e, 0, 1.0, 0, 0, 0, 0, 1.1, 1.1, 1.1)
        common.loc_rot_scale(n, 0, 0, 0, 0, 0, 0, 0.2, 0.2, 0.2)

        camera.position = hpms.vec3(3.5, 1, -3)
        camera.rotation = hpms.vec3(0, hpms.to_radians(-120), 0)
        scene.ambient_light = hpms.vec3(1, 1, 1)
        hpms.set_node_entity(n, e)
        hpms.add_node_to_scene(n, scene)
        --
        --hpms.add_entity_to_scene(e, scene)
        hpms.add_picture_to_scene(b, scene)
        hpms.add_picture_to_scene(d, scene)

        ctx.mode = 'play'
    end,
    input = function(keys)
        speed = 0
        rotate = 0


        -- Input function callback.

        if keys ~= nil then
            if hpms.action_performed(keys, 'ESC', input.PRESSED) then
                scene.quit = true
            end
            if hpms.action_performed(keys, 'UP', input.PRESSED) then
                speed = 4
            elseif hpms.action_performed(keys, 'DOWN', input.PRESSED) then
                speed = -4
            else
                speed = 0
            end

            if hpms.action_performed(keys, 'RIGHT', input.PRESSED) then
                rotate = -4
            elseif hpms.action_performed(keys, 'LEFT', input.PRESSED) then
                rotate = 4
            else
                rotate = 0
            end
            if hpms.action_performed(keys, 'I', input.PRESSED_FIRST_TIME) then
                if ctx.mode == 'play' then
                    ctx.mode = 'menu'
                else
                    ctx.mode = 'play'
                end
            end
        end
    end,
    update = function(scene, camera)
        -- Update loop function callback.

        if ctx.mode == 'play' then
            hpms.add_picture_to_scene(b, scene)
            camera.position = hpms.vec3(3.5, 1, -3)
            camera.rotation = hpms.vec3(0, hpms.to_radians(-120), 0)
            hpms.update_view(camera)
            hpms.update_animator(a)
            hpms.update_collisor(c)
            common.move_collisor_towards_direction(c, speed / 120.0)
            common.rotate(n, 0, rotate / 3.0, 0)
            if speed == 0 then
                a.play = false
            else
                a.play = true
            end
        else
            hpms.add_picture_to_scene(i, scene)
            camera.position = hpms.vec3(0, 0, 0)
            camera.rotation = hpms.vec3(0, 0, 0)
            hpms.update_view(camera)
        end

        hpms.add_picture_to_scene(b, scene)
        camera.position = hpms.vec3(3.5, 1, -3)
        camera.rotation = hpms.vec3(0, hpms.to_radians(-120), 0)
        hpms.update_view(camera)
        hpms.update_animator(a)
        hpms.update_collisor(c)
        common.move_collisor_towards_direction(c, speed / 120.0)
        common.rotate(n, 0, rotate / 3.0, 0)
        if speed == 0 then
            a.play = false
        else
            a.play = true
        end

    end,
    cleanup = function()
        -- Close function callback.
        hpms.delete_collisor(c)
        hpms.delete_node(n)
        hpms.delete_animator(a)
        hpms.delete_walkmap(w)
        hpms.delete_entity(e)
        hpms.delete_background(b)
        hpms.delete_depth_mask(d)

    end
}