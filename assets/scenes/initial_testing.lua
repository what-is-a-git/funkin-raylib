-- Define variables beforehand if you're cool.
-- Doesn't really matter lol
local darnyIcon = nil
local picoIcon = nil
local timer = 0.0

-- Called when the script is created.
function init()
    print('I Am Init!')
end

-- Called before the first update and draw are called.
function ready()
    print('I Am Ready!')

    darnyIcon = Sprite:new()
    -- Automatically adds assets/ if it's not there,
    -- as well as defaulting to .png if not specified.
    darnyIcon.texture = Assets.loadTexture(Assets.path('images/icons/icon-darnell.png'))
    darnyIcon.x = 320
    darnyIcon.y = 360

    picoIcon = Sprite:new()
    -- Both path methods work!
    picoIcon.texture = Assets.loadTexture(Assets.path('assets/images/icons/icon-pico.png'))
    picoIcon.x = 960
    picoIcon.y = 360
    picoIcon.flipX = true
end

-- Called every frame with delta time.
function update(elapsed)
    -- print('Updated! % ' .. tostring(elapsed) .. 's delta!')
    timer = timer + elapsed

    darnyIcon.x = 320 + math.sin(timer) * 60.0
    darnyIcon.angle = math.cos(timer * 1.5) * 11.5

    picoIcon.x = 960 + math.tan(timer) * 60.0
    picoIcon.angle = math.sin(timer * 2.0) * 6.5

    picoIcon.antialiased = timer % 1.0 > 0.5
end

-- Called every frame for issuing draw commands.
function draw()
    -- print('I Am Drawing!')

    clear()
    drawFPS(4, 4)

    darnyIcon:draw()
    picoIcon:draw()
end

-- Called when the script is no longer needed
-- and is about to be disposed of.
function free()
    print('UNLOADING: Begin')

    darnyIcon:free()
    picoIcon:free()

    print('UNLOADING: Done')
end