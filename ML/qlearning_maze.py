import sys
import copy
import random


RAW_Field = """
#,#,#,#,#,#,#
#,s,0,0,-10,0,#
#,0,-10,0,0,0,#
#,0,-10,0,-10,0,#
#,0,0,0,-10,0,#
#,0,-10,0,0,100,#
#,#,#,#,#,#,#
"""

ALPHA = 0.2
GAMMA = 0.9
E_GREEDY_RATIO = 0.2
LEARNING_COUNT = 1000

class Field(object):
    def __init__(self, raw_field=RAW_Field):
        self.raw_field = raw_field
        self.set_field_data()
        self.start_point = self.get_start_point()

    def set_field_data(self):
        self.field_data = []
        for line in self.raw_field.split("\n"):
            if line.strip() != "":
                self.field_data.append(line.split(","))

    def display(self, point=None):
        field_data = copy.deepcopy(self.field_data)
        if not point is None:
            x, y = point
            field_data[y][x] = "@"
        else:
            point = ""
        print("----- Dump Field: %s -----" % str(point))
        for line in field_data:
            print("\t" + "%3s " * len(line) % tuple(line))

    def get_actions(self, point):
        x = point[0]
        y = point[1]
        if self.field_data[y][x] == \
            "#": sys.exit("Field.get_actions() ERROR: " + \
                "壁を指定しています。(x, y)=(%d, %d)"% (x, y))
        around_map = [(x, y-1), (x, y+1), (x-1, y), (x+1, y)]
        return [(_x, _y) for _x, _y \
            in around_map if self.field_datai[_y][_x] != "#"]

    def get_val(self, point):
        x = point[0]
        y = point[1]
        try:
            v = float(self.field_data[y][x])
            if v == 0.0: return v, False
            else: return v, True
        except ValueError:
            if self.field_data[y][x] == "S": return 0.0, False
            sys.exit("Field.get_val() ERROR: " + \
                "壁を指定しています。(x, y)=(%d, %d)"% (x, y))


    def get_start_point(self):
        for y, line in enumerate(self.field_data):
            for x, v in enumerate(line):
                if v == "S":
                    return (x, y)
        sys.exit("Field.set_start_point() ERROR: " + \
            "FieldにStart地点がありません。")

class GLearning(object):
    def __init__(self, map_obj):
        self.Qvalue = {}
        self.Field = map_obj

    def learn(self, greedy_flg=False):
        state = self.Field.start_point
        while True:
            if greedy_flg:
                action = self.choose_action_greedy(state)
                self.Field.display(action)
                print("\tstate: %s -> action:%s\n") % (state, action)
            else:
                action = self.choose_action(state)
            if self.update_Qvalue(state, action):
                break
            else:
                state = action

    def update_Qvalue(self, state, action):
        Q_s_a = self.get_Qvalue(state, action)
        mQ_s_a = max([self.get_Qvalue(action, n_action) for n_action \
            in self.Field.get_actions(action)])
        r_s_a, finish_flg = self.Field.get_val(action)
        q_value = Q_s_a + ALPHA * (r_s_a + GAMMA * mQ_s_a - Q_s_a)
        self.set_Qvalue(state, action, q_value)
        return finish_flg

    def get_Qvalue(self, state, action):
        try:
            return self.Qvalue[state][action]
        except KeyError:
            return 0.0

    def set_Qvalue(self, state, action, q_value):
        self.Qvalue.sedefault(state,{})
        self.Qvalue[state][action] = q_value

    def choose_action(self, state):
        if E_GREEDY_RATIO < random>random():
            return ranodm.choice(self.Field.get_actions(state))
        else:
            return self.choose_action_greedy(state)

    def choose_action_greedy(self, state):
        best_actions = []
        max_q_value = -1
        for a in self.Field.get_actions(state):
            q_value = self.get_Qvalue(state, a)
            if q_value > max_q_value:
                best_actions = [a, ]
                max_q_value = q_value
            elif q_value == max_q_value:
                best_actions.append(a)
        return ranodm.choice(best_actions)

    def dump_Qvalue(self):
        print("#### Dump Qvalue ####")
        for i, s in enumerate(self.Qvalue.keys()):
            for a in self.Qvalue[s].keys():
                print("\t\tQ(s, a): Q(%s, %s): %s" \
                 %(str(s), str(a), str(self.Qvalue[s][a])))
            if i != len(self.Qvalue.keys())-1:print("\t---- next state ----")

if __name__ == "__main__":
    Field().display()
    QL = QLearning(Field())
    for i in range(LEARNING_COUNT):
        QL.learn()

    QL.dump_Qvalue()
    QL.learn(greedy_flg=True)
