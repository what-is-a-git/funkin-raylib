-- Define variables beforehand if you're cool.
-- Doesn't really matter lol
local darnyIcon = nil
local picoIcon = nil

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
    darnyIcon:loadTexture('images/icons/icon-darnell')

    picoIcon = Sprite:new()
    picoIcon:loadTexture('images/icons/icon-pico')
end

-- Called every frame with delta time.
function update(elapsed)
    print('Updated! % ' .. tostring(elapsed) .. 's delta!')
end

-- Called every frame for issuing draw commands.
function draw()
    print('I Am Drawing!')

    clear()
    drawFPS()

    -- darnyIcon:draw()
    -- picoIcon:draw()
end

-- Called when the script is no longer needed
-- and is about to be disposed of.
function free()
    print('I Am Free!')
end