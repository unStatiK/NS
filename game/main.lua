require "nslib"

function love.load()
    window_width = love.graphics.getWidth()
    window_height = love.graphics.getHeight()
    love.window.setIcon(love.image.newImageData("assets/jack.png"))
    love.mouse.setVisible(false)
    nslib.refresh()
    clear_flags()
    init_global_vars()
    init_global_resource()
end

function init_global_vars()
    ScreenMode = { MODE_800_600 = 1, FULLSCREEN = 2 }
    input_text = "Enter your name"
    enter_name_flag = 0
    is_start_menu_flag = 0
    is_screen_option_flag = 0
    is_game_start_flag = 0
    is_game_load_from_file = 0
    command_result_flag = 0
    start_menu_position = 1
    screen_option_position = 1
    battle_round_result = 9
    show_interact_menu_flag = 0
    is_need_resize_windows = 0
    current_screen_mode = ScreenMode.MODE_800_600
    file_with_save_exist = is_file_with_save_exist()
end

function init_global_resource()
    start_menu_image = love.graphics.newImage("assets/ns.jpeg")
    start_menu_position_icon = love.graphics.newImage("assets/skull.png")
    create_name_menu_image = love.graphics.newImage("assets/start.jpeg")
    sk = love.graphics.newImage("assets/skull_s.png")
    al = love.graphics.newImage("assets/alch.png")
    cat = love.graphics.newImage("assets/Cat.png")
    zmb = love.graphics.newImage("assets/zombie.png")
    c1 = love.graphics.newImage("assets/cube.png")
    c2 = love.graphics.newImage("assets/cube2.png")
    gun = love.graphics.newImage("assets/gun.png")
    rck = love.graphics.newImage("assets/rocket.png")
    plz = love.graphics.newImage("assets/plazma.png")
    brn = love.graphics.newImage("assets/brain.png")

    game_font = "fonts/Monocraft.ttf"
    font24 = love.graphics.newFont(game_font, 24)
    font20 = love.graphics.newFont(game_font, 20)
    font16 = love.graphics.newFont(game_font, 16)
    font10 = love.graphics.newFont(game_font, 10)
end

function show_start_menu_strings()
    love.graphics.setFont(font24)
    love.graphics.print("NecroSilence", 200, 100)
    love.graphics.setFont(font16)
    love.graphics.print(" casual", 385, 110)
    love.graphics.setFont(font10)
    love.graphics.print("version: " .. nslib.get_lib_version(), 10, 580)
    love.graphics.draw(start_menu_image, 200, 140)
    love.graphics.setFont(font20)
end

function show_start_menu_screen_option_scene()
    show_start_menu_strings()
    love.graphics.setColor(255, 255, 35)

    if screen_option_position == 1 then
        love.graphics.setColor(150, 0, 0)
        love.graphics.print("800x600", 550, 190)
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("Fullscreen", 550, 215)
        love.graphics.print("Return", 550, 250)
        love.graphics.draw(start_menu_position_icon, 500, 185)
        love.graphics.setColor(255, 255, 255)
    elseif screen_option_position == 2 then
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("800x600", 550, 190)
        love.graphics.setColor(170, 0, 0)
        love.graphics.print("Fullscreen", 550, 215)
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("Return", 550, 250)
        love.graphics.draw(start_menu_position_icon, 500, 210)
    elseif screen_option_position == 3 then
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("800x600", 550, 190)
        love.graphics.print("Fullscreen", 550, 215)
        love.graphics.setColor(170, 0, 0)
        love.graphics.print("Return", 550, 250)
        love.graphics.setColor(255, 255, 255)
        love.graphics.draw(start_menu_position_icon, 500, 245)
    end
end

function show_start_menu_scene()
    show_start_menu_strings()
    love.graphics.setColor(255, 255, 35)

    if start_menu_position == 1 then
        love.graphics.setColor(150, 0, 0)
        love.graphics.print("Start", 550, 190)
        if file_with_save_exist == false then
            love.graphics.setColor(96, 96, 96)
        else
            love.graphics.setColor(255, 255, 255)
        end
        love.graphics.print("Load", 550, 215)
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("Screen option", 550, 240)
        love.graphics.print("Exit", 550, 265)
        love.graphics.draw(start_menu_position_icon, 500, 185)
        love.graphics.setColor(255, 255, 255)
    elseif start_menu_position == 2 then
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("Start", 550, 190)
        love.graphics.setColor(170, 0, 0)
        love.graphics.print("Load", 550, 215)
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("Screen option", 550, 240)
        love.graphics.print("Exit", 550, 265)
        love.graphics.draw(start_menu_position_icon, 500, 210)
        love.graphics.setColor(255, 255, 255)
    elseif start_menu_position == 3 then
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("Start", 550, 190)
        if file_with_save_exist == false then
            love.graphics.setColor(96, 96, 96)
        else
            love.graphics.setColor(255, 255, 255)
        end
        love.graphics.print("Load", 550, 215)
        love.graphics.setColor(170, 0, 0)
        love.graphics.print("Screen option", 550, 240)
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("Exit", 550, 265)
        love.graphics.draw(start_menu_position_icon, 500, 235)
    elseif start_menu_position == 4 then
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("Start", 550, 190)
        if file_with_save_exist == false then
            love.graphics.setColor(96, 96, 96)
        else
            love.graphics.setColor(255, 255, 255)
        end
        love.graphics.print("Load", 550, 215)
        love.graphics.setColor(255, 255, 255)
        love.graphics.print("Screen option", 550, 240)
        love.graphics.setColor(170, 0, 0)
        love.graphics.print("Exit", 550, 265)
        love.graphics.setColor(255, 255, 255)
        love.graphics.draw(start_menu_position_icon, 500, 260)
    end
end

function show_create_player_scene()
    love.graphics.setColor(190, 200, 0)
    love.graphics.print(input_text, 200, 195)
    love.graphics.setColor(255, 255, 255)
    love.graphics.rectangle("line", 190, 198, 320, 25)
    love.graphics.draw(create_name_menu_image, 190, 230)
end

function show_skills()
    love.graphics.draw(zmb, 340, 5)

    if nslib.check_unit() == true then
        love.graphics.draw(al, 370, 5)
    end

    if nslib.check_necro() == true then
        love.graphics.draw(sk, 400, 5)
    end

    if nslib.check_armour() == true then
        love.graphics.draw(c1, 430, 5)
    end

    if nslib.check_superarmour() == true then
        love.graphics.draw(c2, 460, 7)
    end

    if nslib.check_gun() == true then
        love.graphics.draw(gun, 490, 5)
    end

    if nslib.check_rocket() == true then
        love.graphics.draw(rck, 520, 7)
    end

    if nslib.check_plazma() == true then
        love.graphics.draw(plz, 550, 7)
    end

    if nslib.check_neurosynaptic() == true then
        love.graphics.draw(brn, 585, 5)
    end
end

function show_interact_menu()
    draw6rect(460, 300, 250)
    draw6rect(460, 300, 245)
    draw6rect(460, 300, 240)
    love.graphics.print("will be enable soon!", (460 - (250 / 2)) + 10, 300)
end

function show_welcome_help()
    love.graphics.setColor(139, 137, 112)
    love.graphics.print("Welcome to Dark Century !", 500, 50)
    love.graphics.print("h - show this help", 170, 50)
    love.graphics.print("clr - clear info screen", 170, 70)
    love.graphics.print("z - show zones info", 170, 90)
    love.graphics.print("rs - restore all hp", 170, 110)
    love.graphics.print("rn - read Necronomicon", 170, 130)
    love.graphics.print("lm - read Alch. book and levelup LM", 170, 150)
    love.graphics.print("cb - create biomechanics", 170, 170)
    love.graphics.print("z1 - locate to zone 1", 170, 190)
    love.graphics.print("z2 - locate to zone 2", 170, 210)
    love.graphics.print("z3 - locate to zone 3", 170, 230)
    love.graphics.print("z4 - locate to zone 4", 170, 250)
    love.graphics.print("z5 - locate to zone 5", 170, 270)
    love.graphics.print("s - save player", 170, 290)
    love.graphics.print("q - exit", 170, 310)
end

function show_main_ui()
    love.graphics.draw(cat, 0, 360)
    love.graphics.setColor(255, 255, 255)
    -- draw player name box
    love.graphics.rectangle("line", 20, 5, 310, 30)
    -- draw player stat box
    love.graphics.rectangle("line", 20, 45, 130, 170)
    -- draw main box
    love.graphics.rectangle("line", 160, 45, 620, 490)
    love.graphics.setColor(205, 127, 50)
    -- draw input command box
    love.graphics.rectangle("line", 160, 550, 620, 30)
    love.graphics.setFont(font16)
    love.graphics.setColor(0, 255, 0)
    player_name = nslib.get_name_pl()
    love.graphics.print("Player: ", 30, 10)
    love.graphics.setColor(255, 236, 139)
    love.graphics.print(player_name, 110, 10)
    love.graphics.setColor(0, 255, 0)
    plhp = nslib.get_hp_pl()
    love.graphics.print("HP:" .. plhp, 30, 50)
    plmaxhp = nslib.get_maxhp_pl()
    love.graphics.print("MAX HP:" .. plmaxhp, 30, 70)
    plLC = nslib.get_call_level_skill_pl()
    love.graphics.print("L.C.:" .. plLC, 30, 90)
    plLM = nslib.get_mechanics_level_skill_pl()
    love.graphics.print("L.M.:" .. plLM, 30, 110)
    plexpLC = nslib.get_exp_cl_pl()
    love.graphics.print("↑L.C.:" .. plexpLC, 30, 130)
    plexpLM = nslib.get_exp_ml_pl()
    love.graphics.print("↑L.M.:" .. plexpLM, 30, 150)
    plmoney = nslib.get_money_pl()
    love.graphics.print("$:" .. plmoney, 28, 170)
    if nslib.check_unit() == true then
        local unit_type = nslib.get_unit_type()
        if unit_type == 2 then
            love.graphics.setColor(255, 0, 0)
        else
            love.graphics.setColor(255, 255, 255)
        end
        love.graphics.rectangle("line", 20, 230, 130, 180)
        love.graphics.setColor(0, 255, 0)
        unhp = nslib.get_hp_unit()
        love.graphics.print("HP:" .. unhp, 30, 240)
        unmaxhp = nslib.get_maxhp_unit()
        love.graphics.print("MAX HP:" .. unmaxhp, 30, 260)
        unLD = nslib.get_ld_unit()
        love.graphics.print("L.D.:" .. unLD, 30, 280)
        undamage = nslib.get_damage_unit()
        love.graphics.print("damage:" .. undamage, 30, 300)
        unARM = nslib.get_armour_unit()
        love.graphics.print("Arm:" .. unARM, 30, 320)
        unGUN = nslib.get_gun_unit()
        love.graphics.print("Gun:" .. unGUN, 30, 340)
        unPLZ = nslib.get_plazma_unit()
        love.graphics.print("Plz:" .. unPLZ, 30, 360)
        unNSNP = nslib.get_neirosynaptic_unit()
        love.graphics.print("NSNP:" .. unNSNP, 30, 380)
    end
end

function show_zone_info_1()
    local x1 = 170
    local y1 = 50
    local x2 = 200
    local y2 = 70
    local z_nxt = nslib.get_zones_info()
    local ld
    local max_ld_str
    while (z_nxt ~= false) do
        ld = nslib.get_zone_min_daemon_LD()
        if ld ~= -1 then
            max_ld_str = "| Daemons LD : " .. ld .. " - " .. nslib.get_zone_max_daemon_LD()
        elseif ld == -1 then
            max_ld_str = ""
        end
        love.graphics.print("Zone ID : " .. nslib.get_id_zone(), x1, y1)
        love.graphics.print("Units LD : " .. nslib.get_zone_min_unit_LD() .. " - " .. nslib.get_zone_max_unit_LD() .. max_ld_str, x2, y2)
        y1 = y1 + 40
        y2 = y2 + 40
        z_nxt = nslib.get_zones_info()
    end
end

function show_zone_info_2()
    local x1 = 170
    local y1 = 90
    local nxt = nslib.get_zone_info()
    local ld
    local hp
    local damage
    local type_u
    local type_str
    local dstr
    love.graphics.print("Zone have units : ", 170, 50)
    while (nxt ~= false) do
        hp = nslib.get_zone_unit_hp()
        ld = nslib.get_zone_unit_ld()
        damage = nslib.get_zone_unit_damage()
        type_u = nslib.get_zone_unit_type()
        if type_u == 1 then
            type_str = "unit"
        end
        if type_u == 2 then
            type_str = "daemon"
        end
        dstr = "HP: " .. hp .. " LD : " .. ld .. " damage: " .. damage .. " TYPE: " .. type_str
        love.graphics.print(dstr, x1, y1)
        y1 = y1 + 20
        nxt = nslib.get_zone_info()
    end
end

function fight()
    local enemy_type = nslib.get_enemy_type()
    local enemy_prefix = ""
    if enemy_type == 2 then
        enemy_prefix = "daemon "
    end
    love.graphics.print("Fight with " .. enemy_prefix .. "enemy LD " .. nslib.get_zone_unit_ld(), 170, 50)
    if nslib.check_finish_fight() ~= 1 and f_cont == 1 then
        battle_round_result = nslib.fight()
        f_cont = 0
    end
    if f_cont == 0 then
        love.graphics.print("damage " .. nslib.get_current_unit_damage() .. " to enemy", 170, 70)
        if battle_round_result == 1 then
            love.graphics.print("Enemy die !", 170, 90)
        end
        if battle_round_result ~= 1 then
            if nslib.check_type_fight() == 0 then
                love.graphics.print("damage " .. nslib.get_enemy_damage() .. " enemy to you", 170, 90)
            end
            if nslib.check_type_fight() == 1 then
                love.graphics.print("damage " .. nslib.get_enemy_damage() .. " enemy to your unit", 170, 90)
            end
        end
        if battle_round_result ~= 1 and battle_round_result ~= -1 and battle_round_result ~= 0 and nslib.check_finish_fight() ~= 1 then
            love.graphics.print("Continue fight ? enter y/n ", 170, 110)
        end
        if nslib.check_finish_fight() == 1 and nslib.get_hp_pl() == 0 then
            love.graphics.print("You die!", 170, 110)
        end
        if nslib.check_finish_fight() == 1 and nslib.check_unit() == false and nslib.get_hp_pl() > 0 then
            love.graphics.print("Your unit is die !", 170, 110)
            nslib.set_finish_fight()
        end
    end
end

function love.draw()
    if is_start_menu_flag == 0 then
        show_start_menu_scene()
    elseif is_screen_option_flag == 1 then
        show_start_menu_screen_option_scene()
    elseif is_game_start_flag == 0 then
        show_create_player_scene()
    elseif is_game_start_flag == 1 then
        if show_interact_menu_flag == 1 then
            show_interact_menu()
        end
        love.graphics.setColor(255, 255, 255)
        show_skills()
        show_main_ui()

        if f_wlc == 1 then
            show_welcome_help()
        end

        love.graphics.setColor(190, 200, 0)
        love.graphics.print(input_text, 165, 555)
        love.graphics.setColor(119, 136, 153)

        if nslib.is_lab() == 1 then
            love.graphics.print("Master's Lab", 646, 50)
        end

        if nslib.is_zone() == 1 then
            love.graphics.print("Zone " .. nslib.get_locate_id_zone(), 700, 50)
        end

        if act_lhp == 1 then
            love.graphics.print("You should restored HP!", 170, 50)
        end

        if act_z1 == 1 then
            show_zone_info_1()
        end
        if act_z2 == 1 then
            show_zone_info_2()
        end

        if act_rs == 1 then
            if command_result_flag == 1 then
                love.graphics.print("HP is restored !", 170, 50)
            end
            if command_result_flag == -1 then
                love.graphics.print("Not enought money for HP restoring ! Need 100$", 170, 50)
            end
        end

        if act_rn == 1 then
            if command_result_flag == 0 then
                love.graphics.print("You cannot read Necronomicon !", 170, 50)
            end
            if command_result_flag == 1 then
                love.graphics.print("You read Necronomicon !", 170, 50)
            end
        end

        if act_ca == 1 then
            if command_result_flag == -1 then
                love.graphics.print("No Unit !", 170, 50)
            end
            if command_result_flag == 0 then
                love.graphics.print("You cannot create armour !", 170, 50)
            end
            if command_result_flag == 1 then
                love.graphics.print("You create armour !", 170, 50)
            end
        end

        if act_csa == 1 then
            if command_result_flag == -1 then
                love.graphics.print("No Unit !", 170, 50)
            end
            if command_result_flag == 0 then
                love.graphics.print("You cannot create superarmour !", 170, 50)
            end
            if command_result_flag == 1 then
                love.graphics.print("You create superarmour !", 170, 50)
            end
        end

        if act_cg == 1 then
            if command_result_flag == -1 then
                love.graphics.print("No Unit !", 170, 50)
            end
            if command_result_flag == 0 then
                love.graphics.print("You cannot create gun !", 170, 50)
            end
            if command_result_flag == 1 then
                love.graphics.print("You create gun !", 170, 50)
            end
        end

        if act_cr == 1 then
            if command_result_flag == -1 then
                love.graphics.print("No Unit !", 170, 50)
            end
            if command_result_flag == 0 then
                love.graphics.print("You cannot create rocket !", 170, 50)
            end
            if command_result_flag == 1 then
                love.graphics.print("You create rocket !", 170, 50)
            end
        end

        if act_cp == 1 then
            if command_result_flag == -1 then
                love.graphics.print("No Unit !", 170, 50)
            end
            if command_result_flag == 0 then
                love.graphics.print("You cannot create plazma !", 170, 50)
            end
            if command_result_flag == 1 then
                love.graphics.print("You create plazma !", 170, 50)
            end
        end

        if act_cn == 1 then
            if command_result_flag == -1 then
                love.graphics.print("No Unit !", 170, 50)
            end
            if command_result_flag == 0 then
                love.graphics.print("You cannot create neurosynaptic !", 170, 50)
            end
            if command_result_flag == 1 then
                love.graphics.print("You create neurosynaptic !", 170, 50)
            end
        end

        if act_lm == 1 then
            if command_result_flag <= 0 then
                local reason = "You cannot levelup LM !"
                if command_result_flag == -1 then
                    reason = reason .. " [not enough exp]"
                end
                if command_result_flag == -2 then
                    reason = reason .. " [not enough money]"
                end
                love.graphics.print(reason, 170, 50)
            end
            if command_result_flag == 1 then
                love.graphics.print("You read 1 part Alchemist's book !", 170, 50)
            end
            if command_result_flag == 2 then
                love.graphics.print("You read 2 part Alchemist's book !", 170, 50)
            end
            if command_result_flag == 3 then
                love.graphics.print("You read 3 part Alchemist's book !", 170, 50)
            end
            if command_result_flag == 4 then
                love.graphics.print("You read 4 part Alchemist's book !", 170, 50)
            end
            if command_result_flag == 5 then
                love.graphics.print("You read 5 part Alchemist's book !", 170, 50)
            end
            if command_result_flag == 6 then
                love.graphics.print("You read 6 part Alchemist's book !", 170, 50)
            end
        end

        if act_c == 1 then
            if command_result_flag == -1 then
                love.graphics.print("Fail call !", 170, 50)
            end
            if command_result_flag == 1 then
                love.graphics.print("You call unit with LD " .. nslib.get_ld_unit() .. " !", 170, 50)
            end
            if command_result_flag == 2 then
                love.graphics.print("You call daemon with LD " .. nslib.get_ld_unit() .. " !", 170, 50)
            end
        end

        if act_s == 1 then
            love.graphics.print("Player save !", 170, 50)
        end

        if act_sf == 1 then
            if command_result_flag ~= 3 then
                love.graphics.print("enter UNIT danger_level for fight", 170, 50)
            elseif command_result_flag == 3 then
                love.graphics.print("No UNIT for fight !", 170, 50)
                nslib.set_finish_fight()
            end
            if command_result_flag == 0 then
                love.graphics.print("No unit with this LD at this zone!", 170, 80)
                nslib.set_finish_fight()
            end
            if command_result_flag == 4 then
                love.graphics.print("Too small LD for battle!", 170, 80)
                nslib.set_finish_fight()
            end
        end

        if act_f == 1 then
            fight()
        end

        if act_h1 == 1 then
            love.graphics.print("h - show this help", 170, 50)
            love.graphics.print("clr - clear info screen", 170, 70)
            love.graphics.print("z - show zones info", 170, 90)
            love.graphics.print("rs - restore all hp", 170, 110)
            love.graphics.print("rn - read Necronomicon", 170, 130)
            love.graphics.print("lm - read Alch. book and levelup LM", 170, 150)
            love.graphics.print("cb - create biomechanics", 170, 170)
            love.graphics.print("z1 - locate to zone 1", 170, 190)
            love.graphics.print("z2 - locate to zone 2", 170, 210)
            love.graphics.print("z3 - locate to zone 3", 170, 230)
            love.graphics.print("z4 - locate to zone 4", 170, 250)
            love.graphics.print("z5 - locate to zone 5", 170, 270)
            love.graphics.print("s - save player", 170, 290)
            love.graphics.print("q - exit", 170, 310)
        end

        if act_h2 == 1 then
            love.graphics.print("h - show this help", 170, 50)
            love.graphics.print("clr - clear info screen", 170, 70)
            love.graphics.print("ca - create armour", 170, 90)
            love.graphics.print("csa - create superarmour", 170, 110)
            love.graphics.print("cg - create gun", 170, 130)
            love.graphics.print("cr - create rockets", 170, 150)
            love.graphics.print("cp - create plazma", 170, 170)
            love.graphics.print("cn - create neurosynaptic", 170, 190)
            love.graphics.print("r - return home", 170, 210)
            love.graphics.print("s - save player", 170, 230)
            love.graphics.print("q - exit", 170, 250)
        end

        if act_h3 == 1 then
            love.graphics.print("h - show this help", 170, 50)
            love.graphics.print("clr - clear info screen", 170, 70)
            love.graphics.print("z - show this zone info", 170, 90)
            love.graphics.print("c - call unit", 170, 110)
            love.graphics.print("f - fight with unit", 170, 130)
            love.graphics.print("r - return home", 170, 150)
            love.graphics.print("s - save player", 170, 170)
            love.graphics.print("q - exit", 170, 190)
        end

    end
end

function draw6rect(x, y, radius)
    len = radius / 2

    p1 = y - (len / 2)
    p2 = y + (len / 2)
    p3 = x - (len / 2)
    p4 = x + (len / 2)

    love.graphics.line(x - len, p1 + 1, x - len, p2 - 1)
    love.graphics.line(x + len, p1 + 1, x + len, p2 - 1)

    love.graphics.line(p3 + 1, y - len, p4 - 1, y - len)
    love.graphics.line(p3 + 1, y + len, p4 - 1, y + len)

    love.graphics.line(x - len, p1, p3, y - len)
    love.graphics.line(p4, y - len, x + len, p1)

    love.graphics.line(x - len, p2, p3, y + len)
    love.graphics.line(x + len, p2, p4, y + len)
end

function get_screen_mode()
    if screen_option_position == 1 then
        return ScreenMode.MODE_800_600
    elseif screen_option_position == 2 then
        return ScreenMode.FULLSCREEN
    end
    return current_screen_mode
end

function love.mousepressed(x, y, button)
    if button == "l" then
        -- stub for next version
    end
end

function love.keypressed(key, unicode)
    if key == "i" and is_game_start_flag == 1 and show_interact_menu_flag == 0 then
        clear_flags()
        show_interact_menu_flag = 1
        return
    elseif key == "i" and is_start_menu_flag == 1 and show_interact_menu_flag == 1 then
        show_interact_menu_flag = 0
        return
    end

    if is_start_menu_flag == 0 then
        if key == "up" and start_menu_position > 1 then
            local offset = 1
            if file_with_save_exist == false and start_menu_position == 3 then
                offset = 2
            end
            start_menu_position = start_menu_position - offset
        end
        if key == "down" and start_menu_position < 4 then
            local offset = 1
            if file_with_save_exist == false and start_menu_position == 1 then
                offset = 2
            end
            start_menu_position = start_menu_position + offset
        end

        if key == "return" and is_start_menu_flag == 0 then
            if start_menu_position == 1 then
                is_start_menu_flag = 1
            elseif start_menu_position == 2 then
                if file_with_save_exist == false then
                    love.event.push("quit")
                elseif file_with_save_exist == true then
                    nslib.refresh()
                    nslib.load()
                    is_game_start_flag = 1
                    input_text = ""
                    is_start_menu_flag = 1
                    is_game_load_from_file = 1
                    f_wlc = 0
                end
            elseif start_menu_position == 3 then
                old_screen_mode = current_screen_mode
                is_screen_option_flag = 1
                is_start_menu_flag = 1
            elseif start_menu_position == 4 then
                love.event.push("quit")
            end
        end
    elseif is_screen_option_flag == 1 then
        if key == "up" and screen_option_position > 1 then
            screen_option_position = screen_option_position - 1
            current_screen_mode = get_screen_mode()
        end
        if key == "down" and screen_option_position < 3 then
            screen_option_position = screen_option_position + 1
            current_screen_mode = get_screen_mode()
        end

        if key == "return" and is_screen_option_flag == 1 then
            if screen_option_position == 1 then
                current_screen_mode = ScreenMode.MODE_800_600
                is_screen_option_flag = 0
                is_start_menu_flag = 0
                if old_screen_mode ~= current_screen_mode then
                    is_need_resize_windows = 1
                end
            elseif screen_option_position == 2 then
                current_screen_mode = ScreenMode.FULLSCREEN
                is_screen_option_flag = 0
                is_start_menu_flag = 0
                if old_screen_mode ~= current_screen_mode then
                    is_need_resize_windows = 1
                end
            elseif screen_option_position == 3 then
                is_screen_option_flag = 0
                is_start_menu_flag = 0
            end
        end
    else
        if enter_name_flag == 1 and string.len(key) < 2 and is_game_start_flag == 0 and string.len(input_text) < 15 then
            input_text = input_text .. key
        end
        if enter_name_flag == 0 and string.len(key) < 2 and is_game_start_flag == 0 then
            enter_name_flag = 1
            input_text = ""
            input_text = input_text .. key
        end

        if enter_name_flag == 1 and is_game_start_flag == 1 and string.len(key) < 2 and string.len(input_text) < 5 then
            input_text = input_text .. key
        end
        if enter_name_flag == 0 and is_game_start_flag == 1 and string.len(key) < 2 then
            enter_name_flag = 1
            input_text = ""
            input_text = input_text .. key
        end

        if key == "backspace" then
            input_text = string.sub(input_text, 0, string.len(input_text) - 1)
        end
        if key == "escape" and is_game_start_flag == 0 then
            input_text = "Enter your name"
            enter_name_flag = 0
        end
        if key == "escape" and is_game_start_flag == 1 then
            input_text = ""
        end
        if key == "return" and enter_name_flag ~= 0 and is_game_start_flag == 0 and is_start_menu_flag == 1 then
            if is_game_load_from_file == 0 then
                nslib.refresh()
                nslib.init(input_text)
                f_wlc = 1
            end
            is_game_start_flag = 1
            input_text = ""
        end
        if key == "return" and is_game_start_flag == 1 then
            show_interact_menu_flag = 0
            check_cli()
        end
    end
end

function love.update(dt)
    if is_need_resize_windows == 1 then
        if current_screen_mode == ScreenMode.MODE_800_600 then
            love.window.setMode(800, 600)
        elseif current_screen_mode == ScreenMode.FULLSCREEN then
            love.window.setFullscreen(true, "exclusive")
        end
        window_width = love.graphics.getWidth()
        window_height = love.graphics.getHeight()
        is_need_resize_windows = 0
    end
end

function love.resize(w, h)
    window_width = w
    window_height = h
end

function set_flags(var_z1, var_z2, var_f_wlc, var_rs, var_h1, var_h2, var_h3, var_ca, var_csa, var_cg, var_cr, var_cp, var_cn, var_rn, var_lm, var_zl, var_c, var_s, var_sf, var_f, var_f_cont, var_lhp)

    act_z1 = var_z1
    act_z2 = var_z2
    f_wlc = var_f_wlc
    act_rs = var_rs
    act_h1 = var_h1
    act_h2 = var_h2
    act_h3 = var_h3
    act_ca = var_ca
    act_csa = var_csa
    act_cg = var_cg
    act_cr = var_cr
    act_cp = var_cp
    act_cn = var_cn
    act_rn = var_rn
    act_lm = var_lm
    act_zl = var_zl
    act_c = var_c
    act_s = var_s
    act_sf = var_sf
    act_f = var_f
    act_lhp = var_lhp
    f_cont = var_f_cont

end

function clear_flags()
    set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
end

function check_cli()
    input_text = trim(input_text)

    if nslib.is_fight_mode() == 1 and input_text == "y" then
        input_text = ""
        set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0)
    end
    if nslib.is_fight_mode() == 1 and input_text == "n" then
        input_text = ""
        set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0)
        nslib.set_finish_fight()
    end
    if nslib.is_start_fight_mode() == 1 then
        command_result_flag = nslib.check_zone_unit_ld(input_text)
        input_text = ""
        if command_result_flag == 1 then
            set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0)
            nslib.set_fight_mode()
        end
    end

    if nslib.is_fight_mode() == 0 and nslib.is_start_fight_mode() == 0 then
        if input_text == "q" then
            nslib.save()
            love.event.push("quit")
        end
        if input_text == "z" then
            input_text = ""
            if nslib.is_home() == 1 then
                set_flags(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            end
            if nslib.is_zone() == 1 then
                set_flags(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            end
        end
        if input_text == "clr" then
            input_text = ""
            clear_flags()
        end
        if input_text == "rs" then
            if nslib.is_home() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                command_result_flag = nslib.restore()
            end
        end
        if input_text == "rn" then
            if nslib.is_home() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0)
                command_result_flag = nslib.read_necro()
            end
        end
        if input_text == "cb" then
            if nslib.is_home() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                nslib.into_lab()
            end
        end
        if input_text == "r" then
            input_text = ""
            set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            nslib.return_home()
        end
        if input_text == "h" then
            input_text = ""
            if nslib.is_home() == 1 then
                set_flags(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            end
            if nslib.is_lab() == 1 then
                set_flags(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            end
            if nslib.is_zone() == 1 then
                set_flags(0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
            end
        end
        if input_text == "ca" then
            if nslib.is_lab() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                command_result_flag = nslib.build_armour()
            end
        end
        if input_text == "csa" then
            if nslib.is_lab() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                command_result_flag = nslib.build_superarmour()
            end
        end
        if input_text == "cg" then
            if nslib.is_lab() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                command_result_flag = nslib.build_gun()
            end
        end
        if input_text == "cr" then
            if nslib.is_lab() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                command_result_flag = nslib.build_rocket()
            end
        end
        if input_text == "cp" then
            if nslib.is_lab() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                command_result_flag = nslib.build_plazma()
            end
        end
        if input_text == "cn" then
            if nslib.is_lab() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                command_result_flag = nslib.build_neurosynaptic()
            end
        end
        if input_text == "lm" then
            if nslib.is_home() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)
                command_result_flag = nslib.lvlup_lm()
            end
        end
        if input_text == "z1" then
            if nslib.is_home() == 1 then
                input_text = ""
                if nslib.get_hp_pl() <= 0 then
                    set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
                    return
                end
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0)
                nslib.locate_zone(1)
            end
        end
        if input_text == "z2" then
            if nslib.is_home() == 1 then
                input_text = ""
                if nslib.get_hp_pl() <= 0 then
                    set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
                    return
                end
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0)
                nslib.locate_zone(2)
            end
        end
        if input_text == "z3" then
            if nslib.is_home() == 1 then
                input_text = ""
                if nslib.get_hp_pl() <= 0 then
                    set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
                    return
                end
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0)
                nslib.locate_zone(3)
            end
        end
        if input_text == "z4" then
            if nslib.is_home() == 1 then
                input_text = ""
                if nslib.get_hp_pl() <= 0 then
                    set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
                    return
                end
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0)
                nslib.locate_zone(4)
            end
        end
        if input_text == "z5" then
            if nslib.is_home() == 1 then
                input_text = ""
                if nslib.get_hp_pl() <= 0 then
                    set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
                    return
                end
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0)
                nslib.locate_zone(5)
            end
        end
        if input_text == "c" then
            if nslib.is_zone() == 1 then
                input_text = ""
                set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0)
                command_result_flag = nslib.call_unit()
            end
        end
        if input_text == "s" then
            input_text = ""
            set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0)
            nslib.save()
        end
        if input_text == "f" then
            if nslib.check_unit() == true then
                if nslib.is_zone() == 1 then
                    if nslib.is_fight_mode() == 0 then
                        input_text = ""
                        command_result_flag = -1
                        set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0)
                        nslib.set_start_fight_mode()
                    end
                end
            end
            if nslib.check_unit() == false then
                if nslib.is_zone() == 1 then
                    input_text = ""
                    set_flags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0)
                    command_result_flag = 3
                end
            end
        end
    end
end

function is_file_with_save_exist()
    return love.filesystem.exists(nslib.get_filename_with_save())
end

function trim(s)
    return s:match "^%s*(.-)%s*$"
end

function love.mousereleased(x, y, button)

end

function love.gamepadpressed(joystick, button)

end

function love.gamepadreleased(joystick, button)

end

