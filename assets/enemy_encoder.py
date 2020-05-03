#!/bin/python3

MAP_FILE = "enemy.dat"

colors = {
    "white": [255, 255, 255, 255],
    "red": [255, 0, 0, 255],
    "green": [0, 255, 0, 255],
    "blue": [0, 0, 255, 255]
}

types = {
    "body"  : 'B',
    "loot"  : 'L',
    "shape" : 'S'
}
#def enemies : body -> point -> color | loot [id][quantity][prob[0,100]] | 100*100px max x50y50 max
enemies = [
    [
        200, 20, 20, 0,
        [
            [types["body"], [0, 0], [0, 50], [50, 50], [50, 0], colors["white"]],
            [types["body"], [0, 0], [0, 40], [40, 40], [40, 0], colors["green"]],
            [types["body"], [0, 0], [0, 30], [30, 30], [30, 0], colors["blue"]],
            [types["loot"], 0, 10, 70],
        ]
    ],
    [
        200, 40, 40, 100,
        [
            [types["body"], [0, 0], [0, 50], [50, 50], colors["red"]],
            [types["body"], [0, 0], [0, 40], [40, 40], [40, 0], colors["green"]],
            [types["body"], [0, 0], [0, 30], [30, 30], [30, 0], colors["blue"]],
            [types["loot"], 1, 5, 100],
        ]
    ]
]
#def loot : body -> point -> color 100*100px max Center : x50y50
loots = [
    [
        [
            [types["shape"], [25, 25], [75, 25], [75, 75], [25, 75], colors["green"]],
        ]
    ],
    [
        [
            [types["shape"], [25, 25], [75, 25], [75, 75], [25, 75], colors["red"]],
        ]
    ],
]

def write_map(data):
        f = open(MAP_FILE, 'wb')
        f.write(bytes(data))
        f.close()

def append_short(res, data):
    if data > 65536:
        print("Trying too write big value ! (%d)" % data)
    res.append((data >> 8) & 0xFF)
    res.append(data & 0xFF)

def append_color(res, color):
    if len(color) != 4:
        print("Incorrect color : ", color)
    for c in color:
        res.append(c)

def write_object(res, data):
    res.append(len(data) - 2)
    for point in data[1:-1]:
        append_short(res, point[0])
        append_short(res, point[1])
    append_color(res, data[-1])

def write_loot(res, data):
    res.append(data[1])
    res.append(data[2])
    res.append(data[3])

write_type = {
    types["body"]: write_object,
    types["loot"]: write_loot,
    types["shape"] : write_object,
}

def main():
    res = []
    for i, loot in enumerate(loots):
        res.append(ord('O'))
        res.append(i)
        for item in loot[0]:
            item_type = item[0]
            if item_type not in write_type:
                print("Incorrect item : unknown type %d ?" % item_type)
            res.append(ord(item_type))
            write_type[item_type](res, item)
    for i, enemy in enumerate(enemies):
        res.append(ord('E'))
        res.append(i)
        res.append(enemy[0])
        res.append(enemy[1])
        res.append(enemy[2])
        res.append(enemy[3])
        for item in enemy[4]:
            item_type = item[0]
            if item_type not in write_type:
                print("Incorrect item : unknown type %c ?" % item_type)
            res.append(ord(item_type))
            write_type[item_type](res, item)
    write_map(res)

if __name__ == "__main__":
    main()
