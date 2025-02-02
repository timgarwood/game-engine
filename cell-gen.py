import sys
import json

cells = []


class Cell:
    def __init__(self, x, y, size):
        self.x = x
        self.y = y
        self.size = size


class CellJsonEncoder(json.JSONEncoder):
    def default(self, o):
        return o.__dict__


if __name__ == "__main__":
    if len(sys.argv) != 5:
        print(
            'Usage: cell-gen.py <cell size> <width in cells> <height in cells> <out file>')
        sys.exit(1)

    cellSize = int(sys.argv[1])
    widthInCells = int(sys.argv[2])
    heightInCells = int(sys.argv[3])
    outFile = sys.argv[4]

    x = 0

    for c in range(0, widthInCells):
        y = 0
        for r in range(0, heightInCells):
            cells.append(Cell(x, y, cellSize))
            y += cellSize
        x += cellSize

    with open(outFile, 'w') as fp:
        json.dump(cells, fp, cls=CellJsonEncoder)
