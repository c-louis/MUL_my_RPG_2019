#!/bin/python3

MAP_FILE = "map.dat"

colors = {
    "white": [255, 255, 255, 255]
}

types = {
    "object" : 'W',
    "light": 'L',
    "entity": 'E'
}

light_status = {
    "on": 1,
    "off": 0
}

entity_type = {
    "START_POSITION": 0,
    "END_POSITION": 1,
    "ENNEMY": 2,
    "NPC": 3
}

rooms = [
    [
        1000, 1000, colors["white"],
        [
            [types["object"], [1, 1], [100, 1], [100, 100], [1, 100]],
#            [types["light"], 100, light_status["on"], [200, 200]],
#            [types["entity"], entity_type["START_POSITION"], [12, 12]],
#            [types["entity"], entity_type["NPC"], [42, 23]],
#            [types["light"], 100, light_status["off"], [1234, 4321]],
            [types["object"], [12, 1], [1005, 1], [1040, 1100], [1, 1100]],
            [types["object"], [1, 14], [1010, 1], [1300, 1010], [1, 1004]]
        ]
    ]
]

def write_map(data):
    f = open(MAP_FILE, 'wb')
    f.write(bytes(data))
    f.close()

def append_short(res, data):
    if data > 65535:
        print("Trying to write too big value ! (%d)" % data)
    res.append((data >> 8) & 0xFF)
    res.append(data & 0xFF)

def append_color(res, color):
    if len(color) != 4:
        print("Incorrect color : ", color)
    for c in color:
        res.append(c)

def write_object(res, data):
    res.append(len(data) - 1)
    for point in data[1:]:
        append_short(res, point[0])
        append_short(res, point[1])

def write_light(res, data):
    append_short(res, data[1])
    if data[2] not in [0, 1]:
        print("Unknown light status:", data[2])
    append_short(res, data[3][0])
    append_short(res, data[3][1])

def write_entity(res, data):
    if data[1] not in entity_type.values():
        print("Unknown entity type:", data[1])
    res.append(data[1])
    append_short(res, data[2][0])
    append_short(res, data[2][1])

write_type = {
    types["object"]: write_object,
    types["light"]: write_light,
    types["entity"]: write_entity
}

def main():
    res = []
    for i, room in enumerate(rooms):
        res.append(ord('R'))
        res.append(i)
        append_short(res, room[0])
        append_short(res, room[1])
        append_color(res, room[2])
        for item in room[3]:
            item_type = item[0];
            if item_type not in write_type:
                print("Incorrect item : unknown type %c ?" % item_type)
            res.append(ord(item_type))
            write_type[item_type](res, item)
    write_map(res)

if __name__ == "__main__":
    main()
