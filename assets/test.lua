print('my balls')

function madre()
    print('tu madre')
end

setScale(0.5)
setText('Hello Mario.')

local timer = 0.0
local frame = 0
local runs = 0

function update(elapsed)
    timer = timer + elapsed
    setPosition(math.tan(timer) * 64.0 + 512.0, 225.0)
    setAngle(90.0 + math.sin(timer) * 11.5)
    setScale(0.5 + (1.0 - (timer % 1.0)) / 2.0)

    frame = frame + 1

    if frame >= 60 then
        frame = 0
        runs = runs + 1
        setText('Hey Guy #' .. tostring(runs) .. '!')
    end
end

function draw()
    clearTheScreenOfFlies(255, math.floor((timer % 2) * 255), 128)
    drawMyBeautifulText(getText(), 190, 200, 20)
    drawPhighterBabyUwU()
    drawFPS(4, 4)
    drawFPS(math.floor(math.sin(timer) * 16.0), math.floor(math.tan(timer * 0.65) * 16.0))
end
