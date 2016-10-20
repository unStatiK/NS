require "nslib"

function love.load()

txt = "Enter your name"
f_en = 0
f_start = 0
f_cr = 0
f_l = 0
f_fail = 0
pos = 1
res = 9

f_show_inv = 0

image = love.graphics.newImage("ns.jpeg")
ico = love.graphics.newImage("skull.png")
dr = love.graphics.newImage("start.jpeg")
sk = love.graphics.newImage("skull_s.png")
al = love.graphics.newImage("alch.png")
cat = love.graphics.newImage("Cat.png")
zmb = love.graphics.newImage("zombie.png")
c1  = love.graphics.newImage("cube.png")
c2  = love.graphics.newImage("cube2.png")
gun  = love.graphics.newImage("gun.png")
rck  = love.graphics.newImage("rocket.png")
plz  = love.graphics.newImage("plazma.png")
brn  = love.graphics.newImage("brain.png")
--main_ = love.graphics.newImage("jack.png")
main_ = love.image.newImageData("jack.png")
--love.graphics.setIcon(main_)
love.window.setIcon(main_)

font1 = love.graphics.newFont(24)
font2 = love.graphics.newFont(20)
font3 = love.graphics.newFont(16)
font4 = love.graphics.newFont(10)

end

function love.draw()  
  if f_start == 0 then
    love.graphics.setFont(font1)
    love.graphics.print( "NecroSilence" , 200, 100 )
    love.graphics.setFont(font3)
    love.graphics.print( " casual" , 360, 108 )
    love.graphics.setFont(font4)
    love.graphics.print( "version 0.1 beta" , 10, 580 )   
    love.graphics.draw(image,200,140)
    love.graphics.setFont(font2)	
	
	love.graphics.setColor(255, 255, 35)
	local vertices = {400, 375, 400, 425,
	500, 375, 500, 425,
	425, 350, 475, 350,
	425, 450, 475, 450,
	400, 375, 425, 350,
	475, 350, 500, 375,
	400, 425, 425, 450,
	475, 450, 500, 425}	

     if pos == 1 then 
       love.graphics.setColor(150, 0, 0)
       love.graphics.print( "Start" , 550, 190 )
       love.graphics.setColor(255, 255, 255)
       love.graphics.print( "Load" , 550, 215 )
       love.graphics.print( "Exit" , 550, 240 )
       love.graphics.draw(ico,500,185)
	   love.graphics.setColor(255, 255, 255)

     elseif pos == 2 then
        love.graphics.setColor(255, 255, 255)
        love.graphics.print( "Start" , 550, 190 )
        love.graphics.setColor(170, 0, 0)
        love.graphics.print( "Load" , 550, 215 )
        love.graphics.setColor(255, 255, 255)
        love.graphics.print( "Exit" , 550, 240 )
        love.graphics.draw(ico,500,210)
	   love.graphics.setColor(255, 255, 255)
     elseif pos == 3 then 
        love.graphics.setColor(255, 255, 255)
        love.graphics.print( "Start" , 550, 190 )
        love.graphics.print( "Load" , 550, 215)
        love.graphics.setColor(170, 0, 0)
        love.graphics.print( "Exit" , 550, 240 )
        love.graphics.setColor(255, 255, 255)
        love.graphics.draw(ico,500,235)
     end  
  elseif f_cr == 0 then
    love.graphics.setColor(190, 200, 0)
    love.graphics.print( txt , 200, 200 )
    love.graphics.setColor(255, 255, 255)
    love.graphics.rectangle("line", 190, 198 , 320 ,25)
    love.graphics.draw(dr,190,230)

    if f_show_inv == 1 then
      draw6rect(460, 300, 250)
      draw6rect(460, 300, 245)
      draw6rect(460, 300, 240)
    end
  elseif f_cr == 1 then
    if f_show_inv == 1 then
      draw6rect(460, 300, 250)
      draw6rect(460, 300, 245)
      draw6rect(460, 300, 240)
    end

    love.graphics.setColor(255, 255, 255)
    love.graphics.draw(zmb,340,5)

    if nslib.check_unit() == true then
     love.graphics.draw(al,370,5)
    end

    if nslib.check_necro() == true then
     love.graphics.draw(sk,400,5)
    end

    if nslib.check_armour() == true then
     love.graphics.draw(c1,430,5)
    end

    if nslib.check_superarmour() == true then
     love.graphics.draw(c2,460,7)
    end
    if nslib.check_gun() == true then
     love.graphics.draw(gun,490,5)
    end

    if nslib.check_rocket() == true then
     love.graphics.draw(rck,520,7)
    end

    if nslib.check_plazma() == true then
     love.graphics.draw(plz,550,7)
    end
    
    if nslib.check_neurosynaptic() == true then
     love.graphics.draw(brn,585,5)
    end

    love.graphics.draw(cat,0,360)
    love.graphics.setColor(255, 255, 255)
    love.graphics.rectangle("line", 20, 5 , 310 ,30)
    love.graphics.rectangle("line", 20, 45 , 130 ,170)
    love.graphics.rectangle("line", 160, 45 , 620 ,490)
    love.graphics.setColor(205, 127, 50)
    love.graphics.rectangle("line", 160, 550 , 620 ,30)
     love.graphics.setFont(font3)
     love.graphics.setColor(139, 137, 112)

      if f_wlc == 1 then
         love.graphics.print( "Welcome to Dark Century !" , 550, 50 )
         love.graphics.print( "h - show this help" , 170, 50 )
         love.graphics.print( "clr - clear info screen" , 170, 70 )
         love.graphics.print( "z - show zones info" , 170, 90 )
         love.graphics.print( "rs - restore all hp" , 170, 110 )
         love.graphics.print( "rn - read Necronomicon" , 170, 130 )
         love.graphics.print( "lm - read Alch. book and levelup LM" , 170, 150 )
         love.graphics.print( "cb - create boimechanics" , 170, 170 )
         love.graphics.print( "z1 - locate to zone 1" , 170, 190 )
         love.graphics.print( "z2 - locate to zone 2" , 170, 210 )
         love.graphics.print( "z3 - locate to zone 3" , 170, 230 )
         love.graphics.print( "z4 - locate to zone 4" , 170, 250 )
         love.graphics.print( "z5 - locate to zone 5" , 170, 270 )
         love.graphics.print( "s - save player" , 170, 290 )
         love.graphics.print( "q - exit" , 170, 310 )
      end

     love.graphics.setColor(0, 255, 0)
     plname = nslib.get_name_pl()
     love.graphics.print( "Player : " , 30, 10 )
     love.graphics.setColor(255, 236, 139)
     love.graphics.print( plname , 95, 10 )
     love.graphics.setColor(0, 255, 0)
     plhp = nslib.get_hp_pl()
     love.graphics.print( "HP : "..plhp , 30, 50 )
     plmaxhp = nslib.get_maxhp_pl()
     love.graphics.print( "MAX HP : "..plmaxhp , 30, 70 )
     plLC = nslib.get_call_level_skill_pl()
     love.graphics.print( "L.C. : "..plLC , 30, 90 )
     plLM = nslib.get_mechanics_level_skill_pl()
     love.graphics.print( "L.M. : "..plLM , 30, 110 )
     plexpLC = nslib.get_exp_cl_pl()
     love.graphics.print( "exp L.C. : "..plexpLC , 30, 130 )
     plexpLM = nslib.get_exp_ml_pl()
     love.graphics.print( "exp L.M. : "..plexpLM , 28, 150 )
     plmoney = nslib.get_money_pl()
     love.graphics.print( "$ : "..plmoney , 30, 170 )
    if nslib.check_unit() == true then
     love.graphics.setColor(255, 255, 255)
     love.graphics.rectangle("line", 20, 230 , 130 ,180)
     love.graphics.setColor(0, 255, 0)
     unhp = nslib.get_hp_unit()
     love.graphics.print( "HP : "..unhp , 30, 240 )
     unmaxhp = nslib.get_maxhp_unit()
     love.graphics.print( "MAX HP : "..unmaxhp , 30, 260 )
     unLD = nslib.get_ld_unit()
     love.graphics.print( "L.D. : "..unLD , 30, 280 )
     undamage = nslib.get_damage_unit()
     love.graphics.print( "damage : "..undamage , 30, 300 )
     unARM = nslib.get_armour_unit()
     love.graphics.print( "Arm : "..unARM , 30, 320 )
     unGUN = nslib.get_gun_unit()
     love.graphics.print( "Gun : "..unGUN , 30, 340 )
     unPLZ = nslib.get_plazma_unit()
     love.graphics.print( "Plz : "..unPLZ , 30, 360 )
     unNSNP = nslib.get_neirosynaptic_unit()
     love.graphics.print( "NSNP : "..unNSNP , 30, 380 )
    end

     love.graphics.setColor(190, 200, 0)
     love.graphics.print( txt , 165, 555 )
     love.graphics.setColor(119, 136, 153)
      if nslib.is_lab() == 1 then
         love.graphics.print( "Master's Lab" , 650, 50 )
      end
      if nslib.is_zone() == 1 then
         love.graphics.print( "Zone "..nslib.get_locate_id_zone() , 700, 50 )
      end
       if act_z1 == 1 then
          local x1 = 170
          local y1 = 50
          local x2 = 200
          local y2 = 70
          local nxt
          local dl
          local dstr
          nxt = nslib.get_zones_info()
          while (nxt ~= false) do
            dl = nslib.get_zone_min_daemon_LD()
             if dl ~= -1 then
                dstr = "| Daemons LD : "..dl.." - "..nslib.get_zone_max_daemon_LD()
             elseif dl == -1 then 
                dstr = ""
             end
            love.graphics.print( "Zone ID : "..nslib.get_id_zone() , x1, y1 )
            love.graphics.print( "Units LD : "..nslib.get_zone_min_unit_LD().." - "..nslib.get_zone_max_unit_LD()..dstr , x2, y2 )
            y1 = y1 + 40
            y2 = y2 + 40       
            nxt = nslib.get_zones_info()
          end
       end
       if act_z2 == 1 then
          local x1 = 170
          local y1 = 90
          local nxt
          local ld
          local hp
          local damage
          local type_u
          local type_str
          local dstr
          love.graphics.print("Zone have units : " , 170, 50 )
          nxt = nslib.get_zone_info()
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
            dstr = "HP: "..hp.." LD : "..ld.." damage: "..damage.." TYPE: "..type_str
            love.graphics.print( dstr , x1, y1 )
            y1 = y1 + 20   
            nxt = nslib.get_zone_info()
          end
       end
       if act_rs == 1 then
         love.graphics.print( "HP is restored !" , 170, 50 )
       end
       if act_rn == 1 then
         if f_fail == 0 then
           love.graphics.print( "You cannot read Necronomicon !" , 170, 50 )
         end
         if f_fail == 1 then
           love.graphics.print( "You read Necronomicon !" , 170, 50 )
         end
       end
       if act_ca == 1 then
         if f_fail == -1 then
           love.graphics.print( "No Unit !" , 170, 50 )
         end
         if f_fail == 0 then
           love.graphics.print( "You cannot create armour !" , 170, 50 )
         end
         if f_fail == 1 then
           love.graphics.print( "You create armour !" , 170, 50 )
         end
       end
       if act_csa == 1 then
         if f_fail == -1 then
           love.graphics.print( "No Unit !" , 170, 50 )
         end
         if f_fail == 0 then
           love.graphics.print( "You cannot create superarmour !" , 170, 50 )
         end
         if f_fail == 1 then
           love.graphics.print( "You create superarmour !" , 170, 50 )
         end
       end
       if act_cg == 1 then
         if f_fail == -1 then
           love.graphics.print( "No Unit !" , 170, 50 )
         end
         if f_fail == 0 then
           love.graphics.print( "You cannot create gun !" , 170, 50 )
         end
         if f_fail == 1 then
           love.graphics.print( "You create gun !" , 170, 50 )
         end
       end
       if act_cr == 1 then
         if f_fail == -1 then
           love.graphics.print( "No Unit !" , 170, 50 )
         end
         if f_fail == 0 then
           love.graphics.print( "You cannot create rocket !" , 170, 50 )
         end
         if f_fail == 1 then
           love.graphics.print( "You create rocket !" , 170, 50 )
         end
       end
       if act_cp == 1 then
         if f_fail == -1 then
           love.graphics.print( "No Unit !" , 170, 50 )
         end
         if f_fail == 0 then
           love.graphics.print( "You cannot create plazma !" , 170, 50 )
         end
         if f_fail == 1 then
           love.graphics.print( "You create plazma !" , 170, 50 )
         end
       end
       if act_cn == 1 then
         if f_fail == -1 then
           love.graphics.print( "No Unit !" , 170, 50 )
         end
         if f_fail == 0 then
           love.graphics.print( "You cannot create neurosynaptic !" , 170, 50 )
         end
         if f_fail == 1 then
           love.graphics.print( "You create neurosynaptic !" , 170, 50 )
         end
       end
       if act_lm == 1 then
         if f_fail == 0 then
           love.graphics.print( "You cannot levelup LM !" , 170, 50 )
         end
         if f_fail == 1 then
           love.graphics.print( "You read 1 part Alchemist's book !" , 170, 50 )
         end
         if f_fail == 2 then
           love.graphics.print( "You read 2 part Alchemist's book !" , 170, 50 )
         end
         if f_fail == 3 then
           love.graphics.print( "You read 3 part Alchemist's book !" , 170, 50 )
         end
         if f_fail == 4 then
           love.graphics.print( "You read 4 part Alchemist's book !" , 170, 50 )
         end
         if f_fail == 5 then
           love.graphics.print( "You read 5 part Alchemist's book !" , 170, 50 )
         end
         if f_fail == 6 then
           love.graphics.print( "You read 6 part Alchemist's book !" , 170, 50 )
         end
       end
       if act_c == 1 then
         if f_fail == -1 then
           love.graphics.print( "Fail call !" , 170, 50 )
         end
         if f_fail == 1 then
           love.graphics.print( "You call unit with LD "..nslib.get_ld_unit().." !" , 170, 50 )
         end
         if f_fail == 2 then
           love.graphics.print( "You call daemon with LD "..nslib.get_ld_unit().." !" , 170, 50 )
         end
       end
       if act_s == 1 then
           love.graphics.print( "Player save !" , 170, 50 )
       end
       if act_sf == 1 then
         if f_fail ~= 3 then 
         love.graphics.print( "enter UNIT danger_level for fight" , 170, 50 )
         elseif f_fail == 3 then
         love.graphics.print( "No UNIT for fight !" , 170, 50 )
         end
          if f_fail == 0 then
            love.graphics.print( "No unit with this LD at this zone!" , 170, 80 )
          end
       end
       if act_f == 1 then 
         love.graphics.print( "Fight with enemy LD "..nslib.get_zone_unit_ld() , 170, 50 )
          if nslib.check_finish_fight() ~= 1 and f_cont == 1 then
          res = nslib.fight()
           f_cont = 0
          end
          if f_cont == 0 then  
           love.graphics.print( "damage "..nslib.get_current_unit_damage().." to enemy" , 170, 70 )
           if res == 1 then
             love.graphics.print( "Enemy die !" , 170, 90 )
           end
           if res ~= 1 then
            if nslib.check_type_fight() == 0 then
              love.graphics.print( "damage "..nslib.get_enemy_damage().." enemy to you" , 170, 90 )
            end
            if nslib.check_type_fight() == 1 then
              love.graphics.print( "damage "..nslib.get_enemy_damage().." enemy to your unit" , 170, 90 )
            end
           end
           if res ~= 1 and res ~= -1 and res ~= 0 and nslib.check_finish_fight() ~= 1 then
              love.graphics.print( "Continue fight ? enter y/n " , 170, 110 )
           end
           if nslib.check_finish_fight() == 1 and nslib.get_hp_pl() == 0 then
             love.graphics.print( "You die!" , 170, 110 )
             nslib.return_home()
           end
           if nslib.check_finish_fight() == 1 and nslib.check_unit() == false and  nslib.get_hp_pl() > 0 then
             love.graphics.print( "Your unit is die !" , 170, 110 )
           end
          end
       end
       if act_h1 == 1 then
         love.graphics.print( "h - show this help" , 170, 50 )
         love.graphics.print( "clr - clear info screen" , 170, 70 )
         love.graphics.print( "z - show zones info" , 170, 90 )
         love.graphics.print( "rs - restore all hp" , 170, 110 )
         love.graphics.print( "rn - read Necronomicon" , 170, 130 )
         love.graphics.print( "lm - read Alch. book and levelup LM" , 170, 150 )
         love.graphics.print( "cb - create boimechanics" , 170, 170 )
         love.graphics.print( "z1 - locate to zone 1" , 170, 190 )
         love.graphics.print( "z2 - locate to zone 2" , 170, 210 )
         love.graphics.print( "z3 - locate to zone 3" , 170, 230 )
         love.graphics.print( "z4 - locate to zone 4" , 170, 250 )
         love.graphics.print( "z5 - locate to zone 5" , 170, 270 )
         love.graphics.print( "s - save player" , 170, 290 )
         love.graphics.print( "q - exit" , 170, 310 )
       end
       if act_h2 == 1 then
         love.graphics.print( "h - show this help" , 170, 50 )
         love.graphics.print( "clr - clear info screen" , 170, 70 )
         love.graphics.print( "ca - create armour" , 170, 90 )
         love.graphics.print( "csa - create superarmour" , 170, 110 )
         love.graphics.print( "cg - create gun" , 170, 130 )
         love.graphics.print( "cr - create rockets" , 170, 150 )
         love.graphics.print( "cp - create plazma" , 170, 170 )
         love.graphics.print( "cn - create neurosynaptic" , 170, 190 )
         love.graphics.print( "r - return home" , 170, 210 )
         love.graphics.print( "s - save player" , 170, 230 )
         love.graphics.print( "q - exit" , 170, 250 )
       end
       if act_h3 == 1 then
         love.graphics.print( "h - show this help" , 170, 50 )
         love.graphics.print( "clr - clear info screen" , 170, 70 )
         love.graphics.print( "z - show this zone info" , 170, 90 )
         love.graphics.print( "c - call unit" , 170, 110 )
         love.graphics.print( "f - fight with unit" , 170, 130 )
         love.graphics.print( "r - return home" , 170, 150 )
         love.graphics.print( "s - save player" , 170, 170 )
         love.graphics.print( "q - exit" , 170, 190 )
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

function love.mousepressed(x, y, button)
  if button == "l" then

  end
end

function love.keypressed( key, unicode ) 
  if key == "i" and f_start == 1 and f_show_inv == 0 then
     f_show_inv = 1
     return
  elseif key == "i" and f_start == 1 and f_show_inv == 1 then
     f_show_inv = 0
     return
  end

  if f_start == 0 then
     if key == "up" and pos > 1 then
        pos = pos -1
     end
     if key == "down" and pos < 3 then
        pos = pos + 1
     end
     
     if key == "return" and f_start == 0 then
       if pos == 1 then
        f_start = 1
       elseif pos == 2 then
        e = love.filesystem.exists("save.ns")
        if e == false then
          love.event.push("quit")
        elseif e == true then
           nslib.load()
           f_cr = 1
           txt = ""
           f_start = 1
           f_l = 1
           f_wlc = 0
        end
       elseif pos == 3 then
        love.event.push("quit")
       end
     end
  else
    if f_en == 1 and string.len(key) < 2 and f_cr == 0 and string.len(txt) < 15 then
      txt = txt..key
    end
    if f_en == 0 and string.len(key) < 2 and f_cr == 0 then
      f_en = 1
      txt = ""
      txt = txt..key
    end

    if f_en == 1 and f_cr == 1 and string.len(key) < 2 and string.len(txt) < 5 then
      txt = txt..key
    end
    if f_en == 0 and f_cr == 1 and string.len(key) < 2 then
      f_en = 1
      txt = ""
      txt = txt..key
    end

    if key == "backspace" then
      txt = string.sub(txt, 0,string.len(txt)-1)
    end
    if key == "escape" and f_cr == 0 then
      txt = "Enter your name"
      f_en = 0
    end
    if key == "escape" and f_cr == 1 then
      txt=""
    end
    if key == "return" and f_en ~= 0 and f_cr == 0 and f_start == 1 then
      if f_l == 0 then
      nslib.init(txt)
      f_wlc = 1
      end
      f_cr = 1
      txt = ""
    end
     if key == "return" and f_cr == 1 then
      check_cli()
    end
  end 
end


function love.update(dt)

end

function set_flags(var_z1,var_z2,var_f_wlc,var_rs,var_h1,var_h2,var_h3,var_ca,var_csa,var_cg,var_cr,var_cp,var_cn,var_rn,var_lm,var_zl,var_c,var_s,var_sf,var_f,var_f_cont)

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
     f_cont = var_f_cont

end  

function check_cli()
  txt = trim(txt)

if nslib.is_fight_mode() == 1 and txt == "y" then 
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1)
 end
 if nslib.is_fight_mode() == 1 and txt == "n" then 
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0)
     nslib.set_finish_fight()
 end  
 if nslib.is_start_fight_mode() == 1 then
  f_fail = nslib.check_zone_unit_ld(txt)
  txt = ""
   if f_fail == 1 then
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1)
     nslib.set_fight_mode()
   end
 end

 if  nslib.is_fight_mode() == 0 and nslib.is_start_fight_mode() == 0 then
  if txt=="q" then
     love.event.push("quit")
  end
  if txt=="z" then
    txt = ""
    if nslib.is_home() == 1 then
     set_flags(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
    end
    if nslib.is_zone() == 1 then
     set_flags(0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
    end 
  end
  if txt=="clr" then
    txt = ""
    set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
  end
  if txt=="rs" then
    if nslib.is_home() == 1 then
     txt = ""
     set_flags(0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
     nslib.restore()
    end
  end
  if txt=="rn" then
    if nslib.is_home() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0)
     f_fail = nslib.read_necro()
    end
  end
  if txt=="cb" then
   if nslib.is_home() == 1 then
    txt = ""
    set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
    nslib.into_lab()
   end
  end
  if txt=="r" then
    txt = ""
    set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
    nslib.return_home()
  end
  if txt=="h" then
     txt = ""
    if nslib.is_home() == 1 then
     set_flags(0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
    end
    if nslib.is_lab() == 1 then
     set_flags(0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
    end
    if nslib.is_zone() == 1 then
     set_flags(0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
    end
  end
  if txt=="ca" then
    if nslib.is_lab() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0)
     f_fail = nslib.build_armour()
    end
  end
  if txt=="csa" then
    if nslib.is_lab() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0)
     f_fail = nslib.build_superarmour()
    end
  end
  if txt=="cg" then
    if nslib.is_lab() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0)
     f_fail = nslib.build_gun()
    end
  end
  if txt=="cr" then
    if nslib.is_lab() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0)
     f_fail = nslib.build_rocket()
    end
  end
  if txt=="cp" then
    if nslib.is_lab() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0)
     f_fail = nslib.build_plazma()
    end
  end
   if txt=="cn" then
    if nslib.is_lab() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0)
     f_fail = nslib.build_neurosynaptic()
    end
  end
  if txt=="lm" then
    if nslib.is_home() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0)
     f_fail = nslib.lvlup_lm()
    end
  end
  if txt=="z1" then
    if nslib.is_home() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0)
     nslib.locate_zone(1)
    end
  end
  if txt=="z2" then
    if nslib.is_home() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0)
     nslib.locate_zone(2)
    end
  end
  if txt=="z3" then
    if nslib.is_home() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0)
     nslib.locate_zone(3)
    end
  end
  if txt=="z4" then
    if nslib.is_home() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0)
     nslib.locate_zone(4)
    end
  end
  if txt=="z5" then
    if nslib.is_home() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0)
     nslib.locate_zone(5)
    end
  end
  if txt=="c" then
    if nslib.is_zone() == 1 then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0)
     f_fail = nslib.call_unit()
    end
  end
  if txt=="s" then
     txt = ""
     set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0)
     nslib.save()
  end
  if txt=="f" then
   if nslib.check_unit() == true then 
    if nslib.is_zone() == 1 then
      if nslib.is_fight_mode() == 0 then
       txt = ""
       f_fail = -1
       set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0)
       nslib.set_start_fight_mode()
      end
    end
   end
   if nslib.check_unit() == false then
      if nslib.is_zone() == 1 then
       txt = ""
       set_flags(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0)
       f_fail = 3
     end
   end
  end
 end 
end

function trim(s)
  return s:match "^%s*(.-)%s*$"
end

function love.mousereleased(x, y, button)

end
