function love.conf(t)
    t.title = "NecroSilence"
    t.author = "M.T. Lab"
    t.identity = nil
    t.version = "0.10.2"
    t.console = false
    t.release = true
    t.window.width = 800
    t.window.height = 600
    t.window.vsync = true
    t.window.fsaa = 0
    t.modules.joystick = true
    t.modules.audio = false
    t.modules.keyboard = true
    t.modules.event = true
    t.modules.image = true
    t.modules.graphics = true
    t.modules.timer = true
    t.modules.mouse = true
    t.modules.sound = false
    t.modules.physics = false
end
