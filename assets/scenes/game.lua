local note = nil

function init()
    
end

function ready()
    note = Sprite:new()
    note.texture = Assets.loadTexture(Assets.path('images/game/notes/notes.png'))
    note.origin.x = 0.0
    note.origin.y = 0.0
end

function update(elapsed)
    
end

function draw()
    clear({0, 0, 0})

    note:draw()

    drawFPS(4, 4)
end

function free()
    
end