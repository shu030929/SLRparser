from anytree import Node, RenderTree
import sys

if len(sys.argv) == 1:
    print("Error : No Arguments")
    sys.exit()

file_path = sys.argv[1]

# 파싱 테이블 (parsing_table) 초기화 ************************************************************************************
parsing_table = {
    # (state, terminal): (action,post state)
    (0, "vtype"): ("SHIFT", 4),
    (2, "vtype"): ("SHIFT", 4),
    (3, "vtype"): ("SHIFT", 4),
    (9, "vtype"): ("REDUCE", 4),
    (10, "vtype"): ("SHIFT", 14),
    (12, "vtype"): ("REDUCE", 5),
    (30, "vtype"): ("SHIFT", 42),
    (32, "vtype"): ("SHIFT", 44),
    (37, "vtype"): ("SHIFT", 42),
    (38, "vtype"): ("REDUCE", 25),
    (48, "vtype"): ("REDUCE", 26),
    (53, "vtype"): ("REDUCE", 18),
    (64, "vtype"): ("SHIFT", 42),
    (66, "vtype"): ("SHIFT", 42),
    (69, "vtype"): ("REDUCE", 33),
    (70, "vtype"): ("REDUCE", 28),
    (71, "vtype"): ("REDUCE", 27),
    (73, "vtype"): ("SHIFT", 42),
    (75, "vtype"): ("REDUCE", 32),


    (4, "id"): ("SHIFT", 7),
    (9, "id"): ("REDUCE", 4),
    (11, "id"): ("SHIFT", 23),
    (12, "id"): ("REDUCE", 5),
    (14, "id"): ("SHIFT", 26),
    (22, "id"): ("SHIFT", 23),
    (27, "id"): ("SHIFT", 23),
    (28, "id"): ("SHIFT", 23),
    (30, "id"): ("SHIFT", 43),
    (37, "id"): ("SHIFT", 43),
    (38, "id"): ("REDUCE", 25),
    (42, "id"): ("SHIFT", 51),
    (44, "id"): ("SHIFT", 52),
    (46, "id"): ("SHIFT", 23),
    (48, "id"): ("REDUCE", 26),
    (64, "id"): ("SHIFT", 43),
    (66, "id"): ("SHIFT", 43),
    (69, "id"): ("REDUCE", 33),
    (70, "id"): ("REDUCE", 28),
    (71, "id"): ("REDUCE", 27),
    (73, "id"): ("SHIFT", 43),
    (75, "id"): ("REDUCE", 32),



    (7, "semi"): ("SHIFT", 9),
    (8, "semi"): ("SHIFT", 12),
    (15, "semi"): ("REDUCE", 6),
    (16, "semi"): ("REDUCE", 7),
    (17, "semi"): ("REDUCE", 8),
    (18, "semi"): ("REDUCE", 9),
    (19, "semi"): ("REDUCE", 10),
    (20, "semi"): ("REDUCE", 12),
    (21, "semi"): ("REDUCE", 14),
    (23, "semi"): ("REDUCE", 16),
    (24, "semi"): ("REDUCE", 17),
    (33, "semi"): ("REDUCE", 11),
    (34, "semi"): ("REDUCE", 13),
    (35, "semi"): ("REDUCE", 15),
    (39, "semi"): ("SHIFT", 48),
    (51, "semi"): ("SHIFT", 11),
    (54, "semi"): ("SHIFT", 60),

    (7, "assign"): ("SHIFT", 11),
    (43, "assign"): ("SHIFT", 11),
    (51, "assign"): ("SHIFT", 11),


    (11, "literal"): ("SHIFT", 17),
    (46, "literal"): ("SHIFT", 17),

    (11, "character"): ("SHIFT", 18),
    (46, "character"): ("SHIFT", 18),

    (11, "boolstr"): ("SHIFT", 19),
    (46, "boolstr"): ("SHIFT", 19),
    (49, "boolstr"): ("SHIFT", 57),
    (50, "boolstr"): ("SHIFT", 57),
    (62, "boolstr"): ("SHIFT", 57),

    (20, "addsub"): ("SHIFT", 27),
    (21, "addsub"): ("REDUCE", 14),
    (23, "addsub"): ("REDUCE", 16),
    (24, "addsub"): ("REDUCE", 17),
    (34, "addsub"): ("REDUCE", 13),
    (35, "addsub"): ("REDUCE", 15),

    (21, "multdiv"): ("SHIFT", 28),
    (23, "multdiv"): ("REDUCE", 16),
    (24, "multdiv"): ("REDUCE", 17),
    (35, "multdiv"): ("REDUCE", 15),

    (7, "lparen"): ("SHIFT", 10),
    (11, "lparen"): ("SHIFT", 22),
    (22, "lparen"): ("SHIFT", 22),
    (27, "lparen"): ("SHIFT", 22),
    (28, "lparen"): ("SHIFT", 22),
    (40, "lparen"): ("SHIFT", 49),
    (41, "lparen"): ("SHIFT", 50),
    (46, "lparen"): ("SHIFT", 22),

    (10, "rparen"): ("REDUCE", 20),
    (13, "rparen"): ("SHIFT", 25),
    (20, "rparen"): ("REDUCE", 12),
    (21, "rparen"): ("REDUCE", 14),
    (23, "rparen"): ("REDUCE", 16),
    (24, "rparen"): ("REDUCE", 17),
    (26, "rparen"): ("REDUCE", 22),
    (29, "rparen"): ("SHIFT", 35),
    (31, "rparen"): ("REDUCE", 19),
    (33, "rparen"): ("REDUCE", 11),
    (34, "rparen"): ("REDUCE", 13),
    (35, "rparen"): ("REDUCE", 15),
    (52, "rparen"): ("REDUCE", 22),
    (55, "rparen"): ("SHIFT", 61),
    (56, "rparen"): ("REDUCE", 30),
    (57, "rparen"): ("REDUCE", 31),
    (58, "rparen"): ("SHIFT", 63),
    (59, "rparen"): ("REDUCE", 21),
    (65, "rparen"): ("REDUCE", 29),


    (11, "num"): ("SHIFT", 24),
    (22, "num"): ("SHIFT", 24),
    (27, "num"): ("SHIFT", 24),
    (28, "num"): ("SHIFT", 24),
    (46, "num"): ("SHIFT", 24),

    (25, "lbrace"): ("SHIFT", 30),
    (61, "lbrace"): ("SHIFT", 64),
    (63, "lbrace"): ("SHIFT", 66),
    (72, "lbrace"): ("SHIFT", 73),


    (9, "rbrace"): ("REDUCE", 4),
    (12, "rbrace"): ("REDUCE", 5),
    (30, "rbrace"): ("REDUCE", 24),
    (37, "rbrace"): ("REDUCE", 24),
    (38, "rbrace"): ("REDUCE", 25),
    (45, "rbrace"): ("SHIFT", 53),
    (47, "rbrace"): ("REDUCE", 23),
    (48, "rbrace"): ("REDUCE", 26),
    (60, "rbrace"): ("REDUCE", 34),
    (64, "rbrace"): ("REDUCE", 24),
    (66, "rbrace"): ("REDUCE", 24),
    (67, "rbrace"): ("SHIFT", 69),
    (68, "rbrace"): ("SHIFT", 70),
    (69, "rbrace"): ("REDUCE", 33),
    (70, "rbrace"): ("REDUCE", 28),
    (71, "rbrace"): ("REDUCE", 27),
    (73, "rbrace"): ("REDUCE", 24),
    (74, "rbrace"): ("SHIFT", 75),
    (75, "rbrace"): ("REDUCE", 32),


    (26, "comma"): ("SHIFT", 32),
    (52, "comma"): ("SHIFT", 32),

    (9, "if"): ("REDUCE", 4),
    (12, "if"): ("REDUCE", 5),
    (30, "if"): ("SHIFT", 40),
    (37, "if"): ("SHIFT", 40),
    (38, "if"): ("REDUCE", 25),
    (48, "if"): ("REDUCE", 26),
    (64, "if"): ("SHIFT", 40),
    (66, "if"): ("SHIFT", 40),
    (69, "if"): ("REDUCE", 33),
    (70, "if"): ("REDUCE", 28),
    (71, "if"): ("REDUCE", 27),
    (73, "if"): ("SHIFT", 40),
    (75, "if"): ("REDUCE", 32),

    (9, "while"): ("REDUCE", 4),
    (12, "while"): ("REDUCE", 5),
    (30, "while"): ("SHIFT", 41),
    (37, "while"): ("SHIFT", 41),
    (38, "while"): ("REDUCE", 25),
    (48, "while"): ("REDUCE", 26),
    (64, "while"): ("SHIFT", 41),
    (66, "while"): ("SHIFT", 41),
    (69, "while"): ("REDUCE", 33),
    (70, "while"): ("REDUCE", 28),
    (71, "while"): ("REDUCE", 27),
    (73, "while"): ("SHIFT", 41),
    (75, "while"): ("REDUCE", 32),

    (55, "comp"): ("SHIFT", 62),
    (56, "comp"): ("REDUCE", 30),
    (57, "comp"): ("REDUCE", 31),
    (58, "comp"): ("SHIFT", 62),
    (65, "comp"): ("REDUCE", 29),

    (69, "else"): ("SHIFT", 72),

    (9, "return"): ("REDUCE", 4),
    (11, "return"): ("REDUCE", 5),
    (30, "return"): ("REDUCE", 24),
    (36, "return"): ("SHIFT", 46),
    (37, "return"): ("REDUCE", 24),
    (38, "return"): ("REDUCE", 25),

    (47, "return"): ("REDUCE", 23),
    (48, "return"): ("REDUCE", 26),
    (64, "return"): ("REDUCE", 24),
    (66, "return"): ("REDUCE", 24),

    (69, "return"): ("REDUCE", 33),
    (70, "return"): ("REDUCE", 28),
    (71, "return"): ("REDUCE", 27),

    (73, "return"): ("REDUCE", 24),
    (75, "return"): ("REDUCE", 32),

    (0, "$"): ("REDUCE", 3),
    (1, "$"): ("ACCEPT", None),
    (2, "$"): ("REDUCE", 3),
    (3, "$"): ("REDUCE", 3),
    (5, "$"): ("REDUCE", 1),
    (6, "$"): ("REDUCE", 2),
    (9, "$"): ("REDUCE", 4),
    (12, "$"): ("REDUCE", 5),
    (53, "$"): ("REDUCE", 18),


    # 아래는 goto문 (state, non-terminal) : goto state ************************************************************
    
   (0, "CODE"): (1),
   (0, "VDECL"): (2),
(0, "FDECL"): (3),
(2, "CODE"): (5),
(2, "VDECL"): (2),
(2, "FDECL"): (3),
(3, "CODE"): (6),
(3, "VDECL"): (2),
(3, "FDECL"): (3),
(4, "ASSIGN"): (8),
(10, "ARG"): (13),
(11, "RHS"): (15),
(11, "EXPR"): (16),
(11, "MDEXPR"): (20),
(11, "PEXPR"): (21),
(22, "EXPR"): (29),
(22, "MDEXPR"): (20),
(22, "PEXPR"): (21),
(26, "MOREARGS"): (31),
(27, "EXPR"): (33),
(27, "MDEXPR"): (20),
(27, "PEXPR"): (21),
(28, "MDEXPR"): (34),
(28, "PEXPR"): (21),
(30, "BLOCK"): (36),
(30, "STMT"): (37),
(30, "VDECL"): (38),
(30, "ASSIGN"): (39),
(36, "RETURN"): (45),
(37, "BLOCK"): (47),
(37, "STMT"): (37),
(37, "VDECL"): (38),
(37, "ASSIGN"): (39),
(42, "ASSIGN"): (8),
(46, "RHS"): (54),
(46, "EXPR"): (16),
(46, "MDEXPR"): (20),
(46, "PEXPR"): (21),
(49, "COND"): (55),
(49, "CONDD"): (56),
(50, "COND"): (58),
(50, "CONDD"): (56),
(52, "MOREARGS"): (59),
(62, "CONDD"): (65),
(64, "BLOCK"): (67),
(64, "STMT"): (37),
(64, "VDECL"): (38),
(64, "ASSIGN"): (39),
(66, "BLOCK"): (68),
(66, "STMT"): (37),
(66, "VDECL"): (38),
(66, "ASSIGN"): (39),
(73, "BLOCK"): (74),
(73, "STMT"): (37),
(73, "VDECL"): (38),
(73, "ASSIGN"): (39),

    
}




# 문법 규칙 (grammar_rules) 초기화 ******************************************************************************
grammar_rules = {
    0: ["START", "CODE"],
    1: ["CODE", "VDECL CODE"],
    2: ["CODE", "FDECL CODE"],
    3: ["CODE", ""],
    4: ["VDECL", "vtype id semi"],
    5: ["VDECL", "vtype ASSIGN semi"],
    6: ["ASSIGN", "id assign RHS"],
    7: ["RHS", "EXPR"],
    8: ["RHS", "literal"],
    9: ["RHS", "character"],
    10: ["RHS", "boolstr"],
    11: ["EXPR", "MDEXPR addsub EXPR"],
    12: ["EXPR", "MDEXPR"],
    13: ["MDEXPR", "PEXPR multdiv MDEXPR"],
    14: ["MDEXPR", "PEXPR"],
    15: ["PEXPR", "lparen EXPR rparen"],
    16: ["PEXPR", "id"],
    17: ["PEXPR", "num"],
    18: ["FDECL", "vtype id lparen ARG rparen lbrace BLOCK RETURN rbrace"],
    19: ["ARG", "vtype id MOREARGS"],
    20: ["ARG", ""],
    21: ["MOREARGS", "comma vtype id MOREARGS"],
    22: ["MOREARGS", ""],
    23: ["BLOCK", "STMT BLOCK"],
    24: ["BLOCK", ""],
    25: ["STMT", "VDECL"],
    26: ["STMT", "ASSIGN semi"],
    27: ["STMT", "if lparen COND rparen lbrace BLOCK rbrace ELSE"],
    28: ["STMT", "while lparen COND rparen lbrace BLOCK rbrace"],
    29: ["COND", "COND comp CONDD"],
    30: ["COND", "CONDD"],
    31: ["CONDD", "boolstr"],
    32: ["ELSE", "else lbrace BLOCK rbrace"],
    33: ["ELSE", ""],
    34: ["RETURN", "return RHS semi"],
}

root = []  # 트리의 루트 부분만 존재


def parse_input(input_tokens):
    stack = [0]  # 스택 초기화
    output = []  # 출력 스택 초기화

    while True:
        state = stack[-1]  # 스택의 최상위 상태 가져오기
        if input_tokens != []:  # 입력이 비었을 때 오류 방지
            token = input_tokens[0]  # 입력 토큰의 첫 번째 요소 가져오기

        action = parsing_table.get((state, token))  # 파싱 테이블에서 동작 가져오기

        if action is None:
            # 파싱 오류 처리
            print(
                "Parsing error: Unexpected token '{}' at position {}".format(
                    token, state
                )
            )
            return False, None
        action_type, action_value = action

        if action_type == "SHIFT":
            # SHIFT 동작 수행
            stack.append(token)  # 스택에 토큰 추가
            stack.append(action_value)  # 스택에 다음 상태 추가
            input_tokens = input_tokens[1:]  # 입력 토큰에서 처리한 토큰 제거
            root.append(Node(token))

        elif action_type == "REDUCE":
            # REDUCE 동작 수행
            reduce_rule = grammar_rules[action_value]  # 규칙 가져오기
            lhs, rhs = reduce_rule

            reduce_length = 2 * (rhs.count(" "))
            if rhs != "":
                reduce_length += 2  # 공백 수로 단어를 세므로 + 2

            for x in range(reduce_length):
                a = stack.pop()  # 스택에서 규칙에 해당하는 요소들 제거

            newNode = Node(lhs)  # 새로운 노드 생성
            index = len(root) - int(reduce_length / 2)
            for x in range(int(reduce_length / 2)):
                node = root.pop(index)  # 삭제하는 노드 수만큼 루트 배열에서 제거 (트리에는 남아있음)
                node.parent = newNode  # 새로 생성한 노드가 그것들의 부모가 됨
            root.append(newNode)  # 루트 배열에 부모 추가

            state = stack[-1]  # 스택의 최상위 상태 가져오기
            stack.append(lhs)  # 스택에 LHS(왼쪽 항) 추가

            goto = parsing_table.get((state, lhs))  # GOTO 동작 가져오기
            if goto is None:
                # 파싱 오류 처리
                print(
                    "Parsing error: Invalid goto at state '{}' with lhs '{}'".format(
                        state, lhs
                    )
                )
                return False, None

            goto_state = goto  # GOTO 동작에서 다음 상태 가져오기
            stack.append(goto_state)  # 스택에 다음 상태 추가
            output.append(reduce_rule)  # 출력 스택에 규칙 추가

        elif action_type == "ACCEPT":
            # ACCEPT 동작 수행
            break

    return True, output


try:
    input_file = open(file_path, "rt")
except FileNotFoundError:
    print("File Not Exist")
    sys.exit()


# 입력 토큰 문 split해서 배열로 넘겨 진행
input_tokens = input_file.read()

input_tokens_list = input_tokens.split(" ")
input_tokens_list.append("$")

# 파싱 수행
result, parse_tree = parse_input(input_tokens_list)

if result:
    print("Parsing successful!")
    print("Parse tree:")
    for pre, fill, node in RenderTree(root[0]):
        print("%s%s" % (pre, node.name))

else:
    print("Parsing failed.")
input_file.close()
