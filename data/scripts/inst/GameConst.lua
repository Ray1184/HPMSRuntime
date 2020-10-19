return {
    paths = {
        -- Entities paths.
        PATH_PLAYER = 'gen/models/Player.hmdat',


        -- Objects paths.
        DUMMY_WEAPON = 'data/models/DummyWeapon.hmdat',
        DEFAULT_ACTIONS = 'gen/models/Player.hmdat'
    },
    player_modes = {
        SEARCH = 0,
        COMBAT = 1,
        EQUIP_HANDGUN = 2,
        EQUIP_SHOTGUN = 3,
        EQUIP_RIFLE = 4,
        EQUIP_THROWABLE = 5,
        PUSH = 6,
        STEALTH = 7,
        SWIM = 8,
        JUMP = 9
    },
    item_types = {
        WEAPON = 0,
        CONSUMABLE = 1,
        READABLE = 2,
        SUPPORT = 3,
        ACTIONS = 4
    },
    item_license = {
        NONE = 0,
        NEEDED = 1,
        FORBIDDEN = 2
    },
    ammo_types = {
        DUMMY_NORMAL = 0,
        DUMMY_SUPER = 1
    }
}