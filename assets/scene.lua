print('hello lua')

local tex = loadTexture('assets/test.png')
local phighters = loadTexture('assets/peak.png')

local timer = 0.0
local frame = 0
local runs = 0

function dispose()
    print('unloading')
    unloadTexture(tex)
    unloadTexture(phighters)
    print('done unloading')
end


function update(elapsed)
    timer = timer + elapsed
    frame = frame + 1

    if frame >= 60 then
        frame = 0
        runs = runs + 1
        text = 'Hey Guy #' .. tostring(runs) .. '!'
    end
end

function draw()
    clearScreen(255, math.floor((timer % 2) * 255), 128)

    local xOffset = (timer * 60.0) % 250.0
    local yOffset = (timer * 60.0) % 250.0

    for x = 0, 6 do
        for y = 0, 4 do
            drawTexture(tex, x * 250.0 - 250.0 + xOffset, y * 250.0 - 250.0 + yOffset, 1.0, 0.0)
        end
    end

    drawText(text, 640 - 240, 360 - 10, 20, {64, 128, 255})

    local scale = 0.25 + math.cos(timer * 12.0) * 0.1
    drawTexture(phighters, math.sin(timer * 3.0) * (640.0 * (1.0 - scale)) + 1280.0 - (640.0 * scale), 720.0 - (360.0 * scale), scale, 0)

    drawFPS(4, 4)
    drawFPS(math.floor(math.sin(timer) * 16.0), math.floor(math.tan(timer * 0.65) * 16.0))
end

-- local metaMommy = {
--     __index = function(table, key)
--         if key == 'draw' then
--             return drawTexture
--         end

--         return nil
--     end,
--     __newindex = function(t, k, v)
--         if k == 'x' then
--             setX(v)
--         end

--         if k == 'y' then
--             setY(v)
--         end

--         if k == 'scale' then
--             setScale(v)
--         end

--         if k == 'rotation_degrees' then
--             setAngle(v)
--         end
--     end
-- }

-- local myAss = setmetatable({}, metaMommy)