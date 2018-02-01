#!/usr/bin/env python3

import argparse
import sys
from collections import defaultdict
import math

CELL_SIZE = 10
WALL_WIDTH = 2
SOLUTION_WIDTH = 3
ROBOT_COLOR = "red"
BACKGROUND_COLOR = "white"
WALL_COLOR = "black"
GRID_COLOR = "grey"
EXIT_COLOR = "green"
KEY_COLOR = "blue"


MAX_OPERATIONS = 5000000
MAX_FOR_ITERATIONS = 100000

MAX_LINE_COUNT = 10 ** 7
MAX_LINE_LENGTH = 10 ** 7
MAX_CODE_LENGTH = 10 ** 7

getrgb = None

DIRS = {
    "up": (-1, 0),
    "left": (0, -1),
    "right": (0, 1),
    "down": (1, 0)
}


def quit_ok(points, text):
    assert(points >= 0 and points <= 1e18)
    print("points {:.4f} {}".format(points, text), file=sys.stderr)
    sys.exit(7)


def quit_pe(text):
    print(text, file=sys.stderr)
    sys.exit(2)


def quit_fail(text):
    print(text, file=sys.stderr)
    sys.exit(3)


class Maze:
    def __init__(self, data, gen_picture):
        numbers = []
        for line in data:
            numbers += list(map(int, line.strip().split()))
        def read():
            assert read.index < len(numbers)
            n = numbers[read.index]
            read.index += 1
            return n
        read.index = 0
        def read_p():
            return (read(), read())

        self.id = read()
        self.weight = read()
        self.height = read()
        self.width = read()
        self.start_position = read_p()
        wall_count = read()
        door_count = read()
        key_count = read()
        exit_count = read()

        self._walls = [(read_p(), read_p()) for _ in range(wall_count)]
        for i in range(0, self.height):
            self._walls.append(((i, -1), (i, 0)))
            self._walls.append(((i, self.width - 1), (i, self.width)))
        for i in range(0, self.width):
            self._walls.append(((-1, i), (0, i)))
            self._walls.append(((self.height - 1, i), (self.height, i)))
        self._wall_index = defaultdict(list)
        for wall in self._walls:
            self._wall_index[wall[0]].append(wall[1])
            self._wall_index[wall[1]].append(wall[0])

        self._initial_doors = set((read_p(), read_p()) for _ in range(door_count))
        self._initial_keys = set(read_p() for _ in range(key_count))
        self.exits = set(read_p() for _ in range(exit_count))
        self._doors = set()
        self._keys = set()
        assert self.exits

        self.cell_height = CELL_SIZE
        self.cell_width = CELL_SIZE

        if gen_picture:
            from PIL import Image, ImageDraw, ImageColor
            global getrgb
            getrgb = ImageColor.getrgb

            self.image = Image.new(
                    "RGB",
                    (self.width * self.cell_width + max(1, WALL_WIDTH // 2),
                        self.height * self.cell_height + max(1, WALL_WIDTH // 2)),
                    getrgb(BACKGROUND_COLOR))
            self.draw = ImageDraw.Draw(self.image)
        else:
            self.image = None
            self.draw = None

        for i in range(self.height):
            for j in range(self.width):
                self.create_wall_like((i, j), (i + 1, j), GRID_COLOR)
                self.create_wall_like((i, j), (i, j + 1), GRID_COLOR)
        self.reset()

        for src, dst in self._walls:
            self.create_wall_like(src, dst, WALL_COLOR, WALL_WIDTH)
        for exit in self.exits:
            self.create_circle(exit, EXIT_COLOR)

    def create_circle(self, position, color):
        if not self.draw:
            return
        self.draw.ellipse(
            ((self.cell_width * position[1] + WALL_WIDTH, self.cell_height * position[0] + WALL_WIDTH),
            (self.cell_width * (position[1] + 1) - WALL_WIDTH, self.cell_height * (position[0] + 1) - WALL_WIDTH)),
            fill=getrgb(color))

    def create_wall_like(self, src, dst, color, width=0):
        if not self.draw:
            return
        if src > dst:
            src, dst = dst, src
        if src[0] == dst[0]:
            self.draw.line(
                ((self.cell_width * (dst[1]), self.cell_height * (src[0])),
                (self.cell_width * (dst[1]), self.cell_height * (src[0] + 1))),
                fill=getrgb(color),
                width=width)
        else:
            self.draw.line(
                ((self.cell_width * (src[1]), self.cell_height * (dst[0])),
                (self.cell_width * (src[1] + 1), self.cell_height * (dst[0]))),
                fill=getrgb(color),
                width=width)

    def draw_move(self, src, dst, color):
        if not self.draw:
            return
        self.draw.line(
            ((src[1] * self.cell_width + self.cell_width // 2,
                src[0] * self.cell_height + self.cell_height // 2),
            (dst[1] * self.cell_width + self.cell_width // 2,
                dst[0] * self.cell_height + self.cell_height // 2)),
            fill=getrgb(color),
            width=SOLUTION_WIDTH
            )

    def save(self, filename):
        if self.draw:
            del self.draw
            self.image.save(open(filename, "wb"), "PNG")

    def reset(self):
        self._doors = set(door for door in self._initial_doors)
        for door in self._doors:
            self.create_wall_like(door[0], door[1], KEY_COLOR, WALL_WIDTH)
        self._keys = set(key for key in self._initial_keys)
        for key in self._keys:
            self.create_circle(key, KEY_COLOR)

    def take_key(self, position):
        if position in self._keys:
            self._keys.remove(position)
            return True
        return False

    def is_exit(self, position):
        return position in self.exits

    def open_door(self, src, dst):
        if (src, dst) in self._doors:
            self._doors.remove((src, dst))
            return True
        if (dst, src) in self._doors:
            self._doors.remove((dst, src))
            return True
        return False

    def is_passable(self, src, dst):
        return (
            dst not in self._wall_index[src] and
            (src, dst) not in self._doors and
            (dst, src) not in self._doors
        )


def get_move(direction, src):
    return src[0] + direction[0], src[1] + direction[1]


class MoveOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index
        self.direction = DIRS[op[5:]]

    @staticmethod
    def matches(op):
        return any(op == "move-" + d for d in DIRS.keys())


class OpenOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index
        self.direction = DIRS[op[5:]]

    @staticmethod
    def matches(op):
        return any(op == "open-" + d for d in DIRS.keys())


class EndOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index

    @staticmethod
    def matches(op):
        return op == "end"


class TakeOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index

    @staticmethod
    def matches(op):
        return op == "take"


class ForOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index
        self.iteration = None
        raw_iterations = op[4:]
        try:
            self.iterations = int(raw_iterations)
            if self.iterations < 1 or self.iterations > MAX_FOR_ITERATIONS:
                raise ValueError()
        except ValueError:
            quit_pe("'for-N' operation must contain an integer between 1 and {}, found: '{}' op_index: {}".format(
                MAX_FOR_ITERATIONS,
                raw_iterations,
                index))

    @staticmethod
    def matches(op):
        return op.startswith("for-")


class BreakOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index

    @staticmethod
    def matches(op):
        return op == "break"


class TerminateOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index

    @staticmethod
    def matches(op):
        return op == "terminate"


class ElseOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index

    @staticmethod
    def matches(op):
        return op == "else"


class EndIfOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index

    @staticmethod
    def matches(op):
        return op == "endif"


class IfOkOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index

    @staticmethod
    def matches(op):
        return op == "if-ok"


class ContinueOp:
    def __init__(self, op, index):
        self.name = op
        self.index = index

    @staticmethod
    def matches(op):
        return op == "continue"


ALL_OPS = [TerminateOp, MoveOp, TakeOp, ForOp, OpenOp, EndOp, BreakOp, ContinueOp, IfOkOp, ElseOp, EndIfOp]


class Robot:
    def __init__(self, maze, code):
        self.raw_ops = []
        self.maze = maze
        self.length = 0
        self.total_lines = 0

        for line in code:
            self.total_lines += 1
            if self.total_lines > MAX_LINE_COUNT:
                quit_pe("line count limit exceeded. limit: {}".format(MAX_LINE_COUNT))

            if len(line) > MAX_LINE_LENGTH:
                quit_pe("line length limit exceeded. line_length: {} limit: {}".format(len(line), MAX_LINE_LENGTH))

            ops = [o for o in line.split() if o]
            self.length += sum(len(o) for o in ops)
            if self.length >  MAX_CODE_LENGTH:
                quit_pe("length limit exceeded. code_length: {} limit: {}".format(self.length, MAX_CODE_LENGTH))

            self.raw_ops += ops

        if not self.raw_ops or self.raw_ops[-1] != "terminate":
            self.raw_ops.append("terminate")
        self.length = sum(len(o) for o in self.raw_ops)
        if self.length >  MAX_CODE_LENGTH:
            quit_pe("length limit exceeded. code_length: {} limit: {}".format(self.length, MAX_CODE_LENGTH))

        self.position = maze.start_position
        self.op_index = 0
        self.key_count = 0
        self.last_op_ok = True
        self.made_moves = 0
        self.made_ops = 0
        self.exit_found = False
        self.terminated = False
        self.color = ROBOT_COLOR
        self.call_stack = []
        maze.create_circle(self.position, self.color)

        self.ops = []
        for i, op_str in enumerate(self.raw_ops):
            for op_type in ALL_OPS:
                if op_type.matches(op_str):
                    self.ops.append(op_type(op_str, i))
                    break
            else:
                quit_pe("unkown operation: {} index: {}".format(op_str, i))

        unmatched_ops = []

        def expect_unmathed_op(op, expected_type):
            if not unmatched_ops or type(unmatched_ops[-1]) is not expected_type:
                quit_pe("unexpected operation: {} index: {}".format(op.name, op.index))

        for i, op in enumerate(self.ops):
            if type(op) is ForOp or type(op) is IfOkOp:
                unmatched_ops.append(op)
            elif type(op) is ElseOp:
                expect_unmathed_op(op, IfOkOp)
                if_op = unmatched_ops.pop()
                if_op.else_index = i
                op.if_index = if_op.index
                unmatched_ops.append(op)
            elif type(op) is EndIfOp:
                expect_unmathed_op(op, ElseOp)
                else_op = unmatched_ops.pop()
                self.ops[else_op.if_index].endif_index = i
                else_op.endif_index = i
            elif type(op) is EndOp:
                expect_unmathed_op(op, ForOp)
                for_op = unmatched_ops.pop()
                for_op.end_index = i
                op.for_index = for_op.index
            elif type(op) is ContinueOp or type(op) is BreakOp:
                for j in range(len(unmatched_ops) - 1, -1, -1):
                    if type(unmatched_ops[j]) is ForOp:
                        op.for_index = unmatched_ops[j].index
                        break
                else:
                    quit_pe("unmatched operation: {} index: {}".format(op.name, op.index))

        if unmatched_ops:
            for op in unmatched_ops:
                quit_pe("unmatched operation: {} index: {}".format(op.name, op.index))

    def execute(self, log_execution):
        op = self.ops[self.op_index]
        if self.made_ops >= MAX_OPERATIONS:
            if log_execution:
                print("operations limit exceeded : {}, terminating".format(MAX_OPERATIONS))
            self.terminated = True
            return

        if log_execution:
            print(
                    "executing:", op.name,
                    "op_index:", op.index,
                    "made_ops:", self.made_ops,
                    "made_moves:", self.made_moves,
                    "exit_found:", self.exit_found,
                    "position:", self.position,
                    "key_count:", self.key_count,
                    "last_op_ok:", self.last_op_ok
            )

        self.made_ops += 1

        assert (self.op_index < len(self.ops))

        if type(op) is TerminateOp:
            if log_execution:
                print("terminated by 'terminate' op, index:", self.op_index)
            self.terminated = True

        elif type(op) is MoveOp:
            dst = get_move(op.direction, self.position)
            self.last_op_ok = False
            if self.maze.is_passable(self.position, dst):
                self.maze.draw_move(self.position, dst, self.color)
                self.position = dst
                self.made_moves += 1
                self.last_op_ok = True
                if self.maze.is_exit(self.position):
                    self.exit_found = True
                    self.terminated = True
                    if log_execution:
                        print("exit found!")
            self.op_index += 1

        elif type(op) is OpenOp:
            dst = get_move(op.direction, self.position)
            self.last_op_ok = False
            if self.key_count > 0:
                if self.maze.open_door(self.position, dst):
                    self.key_count -= 1
                    self.last_op_ok = True
            self.op_index += 1

        elif type(op) is TakeOp:
            self.last_op_ok = False
            if self.maze.take_key(self.position):
                self.key_count += 1
                self.last_op_ok = True
            self.op_index += 1

        elif type(op) is ForOp:
            if op.iteration is None:
                if log_execution:
                    print("starting for:", op.name, "index:", op.index)
                op.iteration = 0
            else:
                op.iteration += 1
            if op.iteration >= op.iterations:
                op.iteration = None
                self.op_index = op.end_index + 1
            else:
                self.op_index += 1

        elif type(op) is ContinueOp:
            self.op_index = op.for_index

        elif type(op) is BreakOp:
            for_op = self.ops[op.for_index]
            for_op.iteration = None
            self.op_index = for_op.end_index + 1

        elif type(op) is IfOkOp:
            if self.last_op_ok:
                self.op_index += 1
            else:
                self.op_index = op.else_index + 1

        elif type(op) is ElseOp:
            if_op = self.ops[op.if_index]
            self.op_index = if_op.endif_index + 1
            self.made_ops -= 1

        elif type(op) is EndIfOp:
            self.op_index += 1
            self.made_ops -= 1

        elif type(op) is EndOp:
            self.op_index = op.for_index
            self.made_ops -= 1

        else:
            quit_fail("unsupported op: {} name: {} index: {}".format(op, op.name, op.index))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("maze", help="test input file")
    parser.add_argument("robot", help="participant's solution")
    parser.add_argument("jury", nargs="?", default=None, help="jury's solution, could be empty")
    parser.add_argument("--output-log", dest="output_log", action="store_true",
            help="output execution log to stdout")
    parser.add_argument("--image",
            help="image.png file to generate picture.\n" +
            "you need to install pillow to use that option:\n" +
            "'pip3 install pillow'")
    args = parser.parse_args()
    try:
        maze = Maze(open(args.maze), args.image is not None)
        robot = Robot(maze, open(args.robot))
        while not robot.terminated:
            robot.execute(args.output_log)
        if args.image:
            maze.save(args.image)

        Q = 10 * maze.width * maze.height
        if robot.exit_found:
            raw_score = maze.weight * (
                    math.log2(Q / (2 * robot.made_moves + robot.made_ops)) +
                    math.log2(Q / robot.length))
            score = min(max(10, raw_score), 300)
        else:
            score = 0.0
            raw_score = 0.0

        quit_ok(score,
                "exit_found: {} made_moves: {} made_ops: {} code_length: {} raw_score: {:.4f} maze_weight: {}".format(
                    robot.exit_found,
                    robot.made_moves,
                    robot.made_ops,
                    robot.length,
                    raw_score,
                    maze.weight))
    except Exception as e:
        raise e
        quit_fail("exception occured: {}".format(e))

if __name__ == "__main__":
    main()
