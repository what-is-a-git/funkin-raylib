function printTable(t)
    for i,v in pairs(t) do
        if type(v) == 'table' then
            print(i .. ':')
            printTable(v)
        else
            print(i, v)
        end
    end

    print()
end

print('Sprite is ' .. tostring(Sprite))
printTable(Sprite)

local test = Sprite:new()
print('test is ' .. tostring(test))
printTable(test)
