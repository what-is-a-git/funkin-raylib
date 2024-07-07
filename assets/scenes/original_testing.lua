print('Hello, ' .. _G._VERSION .. '!')

local test = nil
local phighters = nil

local timer = 0.0
local frame = 0
local runs = 0

function init()
    -- pass
end

function ready()
    test = Sprite:new()
    test.texture = Assets.loadTexture(Assets.path('images/test.png'))

    phighters = Sprite:new()
    phighters.texture = Assets.loadTexture(Assets.path('images/peak.png'))
end

function update(elapsed)
    timer = timer + elapsed
    frame = frame + 1

    if frame >= 60 then
        frame = 0
        runs = runs + 1
        text = 'Hey Guy #' .. tostring(runs) .. '!'
    end

    local scale = 0.25 + math.cos(timer * 12.0) * 0.1
    phighters.scale.x = scale
    phighters.scale.y = scale
    phighters.x = math.sin(timer * 3.0) * (640.0 * (1.0 - scale)) + 1280.0 - (640.0 * scale)
    phighters.y = 720.0 - (360.0 * scale)
end

function draw()
    clear()

    local xOffset = (timer * 60.0) % 250.0
    local yOffset = (timer * 60.0) % 250.0

    for x = 0, 6 do
        for y = 0, 4 do
            test.x = x * 250.0 - 250.0 + xOffset
            test.y = y * 250.0 - 250.0 + yOffset
            test:draw()
        end
    end

    drawText(text, 640 - 240, 360 - 10, 20, {(timer * 64.0) % 255.0, 128, 255})
    phighters:draw()

    drawFPS(4, 4)
    drawFPS(math.floor(math.sin(timer) * 16.0), math.floor(math.tan(timer * 0.65) * 16.0))
end

function free()
    print('UNLOADING: Begin')

    unloadTexture(test.texture)
    unloadTexture(phighters.texture)

    print('UNLOADING: Done')
end