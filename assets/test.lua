print('my balls')

function madre()
    print('tu madre')
end

setScale(0.5)

local timer = 0.0

function update(elapsed)
    timer = timer + elapsed * 4.0
    setPosition(math.tan(timer) * 64.0 + 256.0, math.cos(timer) * 64.0 + 192.0)
    setAngle(math.sin(timer) * 90.0)
end
