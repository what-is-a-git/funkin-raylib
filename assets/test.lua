print('my balls')

function madre()
    print('tu madre')
end

local timer = 0.0
local frame = 0
local runs = 0

local metaMommy = {
    __index = function(table, key)
        if key == 'draw' then
            return drawPhighterBabyUwU
        end

        return nil
    end,
    __newindex = function(t, k, v)
        if k == 'x' then
            setX(v)
        end

        if k == 'y' then
            setY(v)
        end

        if k == 'scale' then
            setScale(v)
        end

        if k == 'rotation_degrees' then
            setAngle(v)
        end
    end
}

local myAss = setmetatable({}, metaMommy)

function update(elapsed)
    timer = timer + elapsed
    frame = frame + 1
    
    if frame >= 60 then
        frame = 0
        runs = runs + 1
        setText('Hey Guy #' .. tostring(runs) .. '!')
    end

    myAss.x = math.tan(timer) * 64.0 + 960.0
    myAss.y = 360.0 + math.cos(timer) * 4.0
    myAss.scale = 0.5 + (1.0 - (timer % 1.0)) / 2.0
    myAss.rotation_degrees = 90.0 + math.sin(timer) * 11.5
end

function draw()
    clearTheScreenOfFlies(255, math.floor((timer % 2) * 255), 128)
    drawMyBeautifulText(getText(), 640 - 240, 360 - 10, 20)
    myAss.draw()
    drawFPS(4, 4)
    drawFPS(math.floor(math.sin(timer) * 16.0), math.floor(math.tan(timer * 0.65) * 16.0))
end
