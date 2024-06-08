#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>
#include <utility>
#include <functional> // std::hash 사용

using namespace std;

// pair<int, string>의 해시 함수를 정의하는 구조체
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

// 파싱 테이블 및 문법 규칙 정의
unordered_map<pair<int, string>, pair<string, int>, hash_pair> parsing_table = {
    {{0, "vtype"}, {"SHIFT", 4}},
    {{2, "vtype"}, {"SHIFT", 4}},
    {{3, "vtype"}, {"SHIFT", 4}},
    {{9, "vtype"}, {"REDUCE", 4}},
    {{10, "vtype"}, {"SHIFT", 14}},
    {{12, "vtype"}, {"REDUCE", 5}},
    {{30, "vtype"}, {"SHIFT", 42}},
    {{32, "vtype"}, {"SHIFT", 44}},
    {{37, "vtype"}, {"SHIFT", 42}},
    {{38, "vtype"}, {"REDUCE", 25}},
    {{48, "vtype"}, {"REDUCE", 26}},
    {{53, "vtype"}, {"REDUCE", 18}},
    {{64, "vtype"}, {"SHIFT", 42}},
    {{66, "vtype"}, {"SHIFT", 42}},
    {{69, "vtype"}, {"REDUCE", 33}},
    {{70, "vtype"}, {"REDUCE", 28}},
    {{71, "vtype"}, {"REDUCE", 27}},
    {{73, "vtype"}, {"SHIFT", 42}},
    {{75, "vtype"}, {"REDUCE", 32}},
    {{4, "id"}, {"SHIFT", 7}},
    {{9, "id"}, {"REDUCE", 4}},
    {{11, "id"}, {"SHIFT", 23}},
    {{12, "id"}, {"REDUCE", 5}},
    {{14, "id"}, {"SHIFT", 26}},
    {{22, "id"}, {"SHIFT", 23}},
    {{27, "id"}, {"SHIFT", 23}},
    {{28, "id"}, {"SHIFT", 23}},
    {{30, "id"}, {"SHIFT", 43}},
    {{37, "id"}, {"SHIFT", 43}},
    {{38, "id"}, {"REDUCE", 25}},
    {{42, "id"}, {"SHIFT", 51}},
    {{44, "id"}, {"SHIFT", 52}},
    {{46, "id"}, {"SHIFT", 23}},
    {{48, "id"}, {"REDUCE", 26}},
    {{64, "id"}, {"SHIFT", 43}},
    {{66, "id"}, {"SHIFT", 43}},
    {{69, "id"}, {"REDUCE", 33}},
    {{70, "id"}, {"REDUCE", 28}},
    {{71, "id"}, {"REDUCE", 27}},
    {{73, "id"}, {"SHIFT", 43}},
    {{75, "id"}, {"REDUCE", 32}},

    {{7, "semi"}, {"SHIFT", 9}},
    {{8, "semi"}, {"SHIFT", 12}},
    {{15, "semi"}, {"REDUCE", 6}},
    {{16, "semi"}, {"REDUCE", 7}},
    {{17, "semi"}, {"REDUCE", 8}},
    {{18, "semi"}, {"REDUCE", 9}},
    {{19, "semi"}, {"REDUCE", 10}},
    {{20, "semi"}, {"REDUCE", 12}},
    {{21, "semi"}, {"REDUCE", 14}},
    {{23, "semi"}, {"REDUCE", 16}},
    {{24, "semi"}, {"REDUCE", 17}},
    {{33, "semi"}, {"REDUCE", 11}},
    {{34, "semi"}, {"REDUCE", 13}},
    {{35, "semi"}, {"REDUCE", 15}},
    {{39, "semi"}, {"SHIFT", 48}},
    {{51, "semi"}, {"SHIFT", 9}},
    {{54, "semi"}, {"SHIFT", 60}},
    
    {{7, "assign"}, {"SHIFT", 11}},
    {{43, "assign"}, {"SHIFT", 11}},
    {{51, "assign"}, {"SHIFT", 11}},
    {{11, "literal"}, {"SHIFT", 17}},
    {{46, "literal"}, {"SHIFT", 17}},
    {{11, "character"}, {"SHIFT", 18}},
    {{46, "character"}, {"SHIFT", 18}},
    {{11, "boolstr"}, {"SHIFT", 19}},
    {{46, "boolstr"}, {"SHIFT", 19}},
    {{49, "boolstr"}, {"SHIFT", 57}},
    {{50, "boolstr"}, {"SHIFT", 57}},
    {{62, "boolstr"}, {"SHIFT", 57}},
    {{20, "addsub"}, {"SHIFT", 27}},
    {{21, "addsub"}, {"REDUCE", 14}},
    {{23, "addsub"}, {"REDUCE", 16}},
    {{24, "addsub"}, {"REDUCE", 17}},
    {{34, "addsub"}, {"REDUCE", 13}},
    {{35, "addsub"}, {"REDUCE", 15}},
    {{21, "multdiv"}, {"SHIFT", 28}},
    {{23, "multdiv"}, {"REDUCE", 16}},
    {{24, "multdiv"}, {"REDUCE", 17}},
    {{35, "multdiv"}, {"REDUCE", 15}},
    {{7, "lparen"}, {"SHIFT", 10}},
    {{11, "lparen"}, {"SHIFT", 22}},
    {{22, "lparen"}, {"SHIFT", 22}},
    {{27, "lparen"}, {"SHIFT", 22}},
    {{28, "lparen"}, {"SHIFT", 22}},
    {{40, "lparen"}, {"SHIFT", 49}},
    {{41, "lparen"}, {"SHIFT", 50}},
    {{46, "lparen"}, {"SHIFT", 22}},
    {{10, "rparen"}, {"REDUCE", 20}},
    {{13, "rparen"}, {"SHIFT", 25}},
    {{20, "rparen"}, {"REDUCE", 12}},
    {{21, "rparen"}, {"REDUCE", 14}},
    {{23, "rparen"}, {"REDUCE", 16}},
    {{24, "rparen"}, {"REDUCE", 17}},
    {{26, "rparen"}, {"REDUCE", 22}},
    {{29, "rparen"}, {"SHIFT", 35}},
    {{31, "rparen"}, {"REDUCE", 19}},
    {{33, "rparen"}, {"REDUCE", 11}},
    {{34, "rparen"}, {"REDUCE", 13}},
    {{35, "rparen"}, {"REDUCE", 15}},
    {{52, "rparen"}, {"REDUCE", 22}},
    {{55, "rparen"}, {"SHIFT", 61}},
    {{56, "rparen"}, {"REDUCE", 30}},
    {{57, "rparen"}, {"REDUCE", 31}},
    {{58, "rparen"}, {"SHIFT", 63}},
    {{59, "rparen"}, {"REDUCE", 21}},
    {{65, "rparen"}, {"REDUCE", 29}},
    {{11, "num"}, {"SHIFT", 24}},
    {{22, "num"}, {"SHIFT", 24}},
    {{27, "num"}, {"SHIFT", 24}},
    {{28, "num"}, {"SHIFT", 24}},
    {{46, "num"}, {"SHIFT", 24}},
    {{25, "lbrace"}, {"SHIFT", 30}},
    {{61, "lbrace"}, {"SHIFT", 64}},
    {{63, "lbrace"}, {"SHIFT", 66}},
    {{72, "lbrace"}, {"SHIFT", 73}},
    {{9, "rbrace"}, {"REDUCE", 4}},
    {{12, "rbrace"}, {"REDUCE", 5}},
    {{30, "rbrace"}, {"REDUCE", 24}},
    {{37, "rbrace"}, {"REDUCE", 24}},
    {{38, "rbrace"}, {"REDUCE", 25}},
    {{45, "rbrace"}, {"SHIFT", 53}},
    {{47, "rbrace"}, {"REDUCE", 23}},
    {{48, "rbrace"}, {"REDUCE", 26}},
    {{60, "rbrace"}, {"REDUCE", 34}},
    {{64, "rbrace"}, {"REDUCE", 24}},
    {{66, "rbrace"}, {"REDUCE", 24}},
    {{67, "rbrace"}, {"SHIFT", 69}},
    {{68, "rbrace"}, {"SHIFT", 70}},
    {{69, "rbrace"}, {"REDUCE", 33}},
    {{70, "rbrace"}, {"REDUCE", 28}},
    {{71, "rbrace"}, {"REDUCE", 27}},
    {{73, "rbrace"}, {"REDUCE", 24}},
    {{74, "rbrace"}, {"SHIFT", 75}},
    {{75, "rbrace"}, {"REDUCE", 32}},
    {{26, "comma"}, {"SHIFT", 32}},
    {{52, "comma"}, {"SHIFT", 32}},
    {{9, "if"}, {"REDUCE", 4}},
    {{12, "if"}, {"REDUCE", 5}},
    {{30, "if"}, {"SHIFT", 40}},
    {{37, "if"}, {"SHIFT", 40}},
    {{38, "if"}, {"REDUCE", 25}},
    {{48, "if"}, {"REDUCE", 26}},
    {{64, "if"}, {"SHIFT", 40}},
    {{66, "if"}, {"SHIFT", 40}},
    {{69, "if"}, {"REDUCE", 33}},
    {{70, "if"}, {"REDUCE", 28}},
    {{71, "if"}, {"REDUCE", 27}},
    {{73, "if"}, {"SHIFT", 40}},
    {{75, "if"}, {"REDUCE", 32}},
    {{9, "while"}, {"REDUCE", 4}},
    {{12, "while"}, {"REDUCE", 5}},
    {{30, "while"}, {"SHIFT", 41}},
    {{37, "while"}, {"SHIFT", 41}},
    {{38, "while"}, {"REDUCE", 25}},
    {{48, "while"}, {"REDUCE", 26}},
    {{64, "while"}, {"SHIFT", 41}},
    {{66, "while"}, {"SHIFT", 41}},
    {{69, "while"}, {"REDUCE", 33}},
    {{70, "while"}, {"REDUCE", 28}},
    {{71, "while"}, {"REDUCE", 27}},
    {{73, "while"}, {"SHIFT", 41}},
    {{75, "while"}, {"REDUCE", 32}},
    {{55, "comp"}, {"SHIFT", 62}},
    {{56, "comp"}, {"REDUCE", 30}},
    {{57, "comp"}, {"REDUCE", 31}},
    {{58, "comp"}, {"SHIFT", 62}},
    {{65, "comp"}, {"REDUCE", 29}},
    {{69, "else"}, {"SHIFT", 71}},
    {{9, "return"}, {"REDUCE", 4}},
    {{11, "return"}, {"REDUCE", 5}},
    {{30, "return"}, {"REDUCE", 24}},
    {{36, "return"}, {"SHIFT", 46}},
    {{37, "return"}, {"REDUCE", 24}},
    {{38, "return"}, {"REDUCE", 25}},
    {{47, "return"}, {"REDUCE", 23}},
    {{48, "return"}, {"REDUCE", 26}},
    {{64, "return"}, {"REDUCE", 24}},
    {{66, "return"}, {"REDUCE", 24}},
    {{69, "return"}, {"REDUCE", 33}},
    {{70, "return"}, {"REDUCE", 28}},
    {{71, "return"}, {"REDUCE", 27}},
    {{73, "return"}, {"REDUCE", 24}},
    {{75, "return"}, {"REDUCE", 32}},
    {{0, "$"}, {"REDUCE", 3}},
    {{1, "$"}, {"ACCEPT", 0}},
    {{2, "$"}, {"REDUCE", 3}},
    {{3, "$"}, {"REDUCE", 3}},
    {{5, "$"}, {"REDUCE", 1}},
    {{6, "$"}, {"REDUCE", 2}},
    {{9, "$"}, {"REDUCE", 4}},
    {{12, "$"}, {"REDUCE", 5}},
    {{53, "$"}, {"REDUCE", 18}},

    {{0, "CODE"}, {"GOTO", 1}},
    {{0, "VDECL"}, {"GOTO", 2}},
    {{0, "FDECL"}, {"GOTO", 3}},
    {{0, "vtype"}, {"GOTO", 4}},
    {{2, "CODE"}, {"GOTO", 5}},
    {{2, "VDECL"}, {"GOTO", 2}},
    {{2, "FDECL"}, {"GOTO", 3}},
    {{2, "vtype"}, {"GOTO", 4}},
    {{3, "CODE"}, {"GOTO", 6}},
    {{3, "VDECL"}, {"GOTO", 2}},
    {{3, "FDECL"}, {"GOTO", 3}},
    {{3, "vtype"}, {"GOTO", 4}},
    {{4, "id"}, {"GOTO", 7}},
    {{4, "ASSIGN"}, {"GOTO", 8}},
    {{7, "semi"}, {"GOTO", 9}},
    {{7, "lparen"}, {"GOTO", 10}},
    {{7, "assign"}, {"GOTO", 11}},
    {{8, "semi"}, {"GOTO", 12}},
    {{10, "ARG"}, {"GOTO", 13}},
    {{10, "vtype"}, {"GOTO", 14}},
    {{11, "RHS"}, {"GOTO", 15}},
    {{11, "EXPR"}, {"GOTO", 16}},
    {{11, "literal"}, {"GOTO", 17}},
    {{11, "character"}, {"GOTO", 18}},
    {{11, "boolstr"}, {"GOTO", 19}},
    {{11, "MDEXPR"}, {"GOTO", 20}},
    {{11, "PEXPR"}, {"GOTO", 21}},
    {{11, "lparen"}, {"GOTO", 22}},
    {{11, "id"}, {"GOTO", 23}},
    {{11, "num"}, {"GOTO", 24}},
    {{13, "rparen"}, {"GOTO", 25}},
    {{14, "id"}, {"GOTO", 26}},
    {{20, "addsub"}, {"GOTO", 27}},
    {{21, "multdiv"}, {"GOTO", 28}},
    {{22, "EXPR"}, {"GOTO", 29}},
    {{22, "MDEXPR"}, {"GOTO", 20}},
    {{22, "PEXPR"}, {"GOTO", 21}},
    {{22, "lparen"}, {"GOTO", 22}},
    {{22, "id"}, {"GOTO", 23}},
    {{22, "num"}, {"GOTO", 24}},
    {{25, "lbrace"}, {"GOTO", 30}},
    {{26, "MOREARGS"}, {"GOTO", 31}},
    {{26, "comma"}, {"GOTO", 32}},
    {{27, "EXPR"}, {"GOTO", 33}},
    {{27, "MDEXPR"}, {"GOTO", 20}},
    {{27, "PEXPR"}, {"GOTO", 21}},
    {{27, "lparen"}, {"GOTO", 22}},
    {{27, "id"}, {"GOTO", 23}},
    {{27, "num"}, {"GOTO", 24}},
    {{28, "MDEXPR"}, {"GOTO", 34}},
    {{28, "PEXPR"}, {"GOTO", 21}},
    {{28, "lparen"}, {"GOTO", 22}},
    {{28, "id"}, {"GOTO", 23}},
    {{28, "num"}, {"GOTO", 24}},
    {{29, "rparen"}, {"GOTO", 35}},
    {{30, "BLOCK"}, {"GOTO", 36}},
    {{30, "STMT"}, {"GOTO", 37}},
    {{30, "VDECL"}, {"GOTO", 38}},
    {{30, "ASSIGN"}, {"GOTO", 39}},
    {{30, "if"}, {"GOTO", 40}},
    {{30, "while"}, {"GOTO", 41}},
    {{30, "vtype"}, {"GOTO", 42}},
    {{30, "id"}, {"GOTO", 43}},
    {{32, "vtype"}, {"GOTO", 44}},
    {{36, "RETURN"}, {"GOTO", 45}},
    {{36, "return"}, {"GOTO", 46}},
    {{37, "BLOCK"}, {"GOTO", 47}},
    {{37, "STMT"}, {"GOTO", 37}},
    {{37, "VDECL"}, {"GOTO", 38}},
    {{37, "ASSIGN"}, {"GOTO", 39}},
    {{37, "if"}, {"GOTO", 40}},
    {{37, "while"}, {"GOTO", 41}},
    {{37, "vtype"}, {"GOTO", 42}},
    {{37, "id"}, {"GOTO", 43}},
    {{39, "semi"}, {"GOTO", 48}},
    {{40, "lparen"}, {"GOTO", 49}},
    {{41, "lparen"}, {"GOTO", 50}},
    {{42, "id"}, {"GOTO", 51}},
    {{42, "ASSIGN"}, {"GOTO", 8}},
    {{43, "assign"}, {"GOTO", 11}},
    {{44, "id"}, {"GOTO", 52}},
    {{45, "rbrace"}, {"GOTO", 53}},
    {{46, "RHS"}, {"GOTO", 54}},
    {{46, "EXPR"}, {"GOTO", 16}},
    {{46, "literal"}, {"GOTO", 17}},
    {{46, "character"}, {"GOTO", 18}},
    {{46, "boolstr"}, {"GOTO", 19}},
    {{46, "MDEXPR"}, {"GOTO", 20}},
    {{46, "PEXPR"}, {"GOTO", 21}},
    {{46, "lparen"}, {"GOTO", 22}},
    {{46, "id"}, {"GOTO", 23}},
    {{46, "num"}, {"GOTO", 24}},
    {{49, "COND"}, {"GOTO", 55}},
    {{49, "CONDD"}, {"GOTO", 56}},
    {{49, "boolstr"}, {"GOTO", 57}},
    {{50, "COND"}, {"GOTO", 58}},
    {{50, "CONDD"}, {"GOTO", 56}},
    {{50, "boolstr"}, {"GOTO", 57}},
    {{51, "semi"}, {"GOTO", 9}},
    {{51, "assign"}, {"GOTO", 11}},
    {{52, "MOREARGS"}, {"GOTO", 59}},
    {{52, "comma"}, {"GOTO", 32}},
    {{54, "semi"}, {"GOTO", 60}},
    {{55, "rparen"}, {"GOTO", 61}},
    {{55, "comp"}, {"GOTO", 62}},
    {{58, "rparen"}, {"GOTO", 63}},
    {{58, "comp"}, {"GOTO", 62}},
    {{61, "lbrace"}, {"GOTO", 64}},
    {{62, "CONDD"}, {"GOTO", 65}},
    {{62, "boolstr"}, {"GOTO", 57}},
    {{63, "lbrace"}, {"GOTO", 66}},
    {{64, "BLOCK"}, {"GOTO", 67}},
    {{64, "STMT"}, {"GOTO", 37}},
    {{64, "VDECL"}, {"GOTO", 38}},
    {{64, "ASSIGN"}, {"GOTO", 39}},
    {{64, "if"}, {"GOTO", 40}},
    {{64, "while"}, {"GOTO", 41}},
    {{64, "vtype"}, {"GOTO", 42}},
    {{64, "id"}, {"GOTO", 43}},
    {{66, "BLOCK"}, {"GOTO", 68}},
    {{66, "STMT"}, {"GOTO", 37}},
    {{66, "VDECL"}, {"GOTO", 38}},
    {{66, "ASSIGN"}, {"GOTO", 39}},
    {{66, "if"}, {"GOTO", 40}},
    {{66, "while"}, {"GOTO", 41}},
    {{66, "vtype"}, {"GOTO", 42}},
    {{66, "id"}, {"GOTO", 43}},
    {{67, "rbrace"}, {"GOTO", 69}},
    {{68, "rbrace"}, {"GOTO", 70}},
    {{69, "ELSE"}, {"GOTO", 71}},
    {{69, "else"}, {"GOTO", 72}},
    {{72, "lbrace"}, {"GOTO", 73}},
    {{73, "BLOCK"}, {"GOTO", 74}},
    {{73, "STMT"}, {"GOTO", 37}},
    {{73, "VDECL"}, {"GOTO", 38}},
    {{73, "ASSIGN"}, {"GOTO", 39}},
    {{73, "if"}, {"GOTO", 40}},
    {{73, "while"}, {"GOTO", 41}},
    {{73, "vtype"}, {"GOTO", 42}},
    {{73, "id"}, {"GOTO", 43}},
    {{74, "rbrace"}, {"GOTO", 75}}
};


unordered_map<int, pair<string, string>> grammar_rules = {
    {0, {"START", "CODE"}},
    {1, {"CODE", "VDECL CODE"}},
    {2, {"CODE", "FDECL CODE"}},
    {3, {"CODE", ""}},
    {4, {"VDECL", "vtype id semi"}},
    {5, {"VDECL", "vtype ASSIGN semi"}},
    {6, {"ASSIGN", "id assign RHS"}},
    {7, {"RHS", "EXPR"}},
    {8, {"RHS", "literal"}},
    {9, {"RHS", "character"}},
    {10, {"RHS", "boolstr"}},
    {11, {"EXPR", "MDEXPR addsub EXPR"}},
    {12, {"EXPR", "MDEXPR"}},
    {13, {"MDEXPR", "PEXPR multdiv MDEXPR"}},
    {14, {"MDEXPR", "PEXPR"}},
    {15, {"PEXPR", "lparen EXPR rparen"}},
    {16, {"PEXPR", "id"}},
    {17, {"PEXPR", "num"}},
    {18, {"FDECL", "vtype id lparen ARG rparen lbrace BLOCK RETURN rbrace"}},
    {19, {"ARG", "vtype id MOREARGS"}},
    {20, {"ARG", ""}},
    {21, {"MOREARGS", "comma vtype id MOREARGS"}},
    {22, {"MOREARGS", ""}},
    {23, {"BLOCK", "STMT BLOCK"}},
    {24, {"BLOCK", ""}},
    {25, {"STMT", "VDECL"}},
    {26, {"STMT", "ASSIGN semi"}},
    {27, {"STMT", "if lparen COND rparen lbrace BLOCK rbrace ELSE"}},
    {28, {"STMT", "while lparen COND rparen lbrace BLOCK rbrace"}},
    {29, {"COND", "COND comp CONDD"}},
    {30, {"COND", "CONDD"}},
    {31, {"CONDD", "boolstr"}},
    {32, {"ELSE", "else lbrace BLOCK rbrace"}},
    {33, {"ELSE", ""}},
    {34, {"RETURN", "return RHS semi"}}
};
struct TreeNode {
    string name;
    vector<TreeNode*> children;

    TreeNode(string name) : name(name) {}
};
void parse_input(vector<string>& input_tokens) {
    stack<int> state_stack; // 상태 스택
    stack<TreeNode*> parse_stack; // 파스 스택
    state_stack.push(0); // 초기 상태

    while (true) {
        int state = state_stack.top(); // 스택 최상위 상태 가져오기
        string token = input_tokens.front(); // 입력 토큰의 첫 번째 요소 가져오기

        auto action_iter = parsing_table.find(make_pair(state, token));
        if (action_iter == parsing_table.end()) {
            // 파싱 오류 처리
            cout << "Parsing error: Unexpected token '" << token << "' at state " << state << endl;
            // 주변 토큰 정보 출력
            cout << "Surrounding tokens: ";
            for (int i = 0; i < min(5, (int)input_tokens.size()); ++i) {
                cout << input_tokens[i] << " ";
            }
            cout << endl;
            return;
        }

        string action_type = action_iter->second.first;
        int action_value = action_iter->second.second;

        if (action_type == "SHIFT") {
            // SHIFT 동작 수행
            state_stack.push(action_value); // 상태 스택에 다음 상태 추가
            input_tokens.erase(input_tokens.begin()); // 입력 토큰에서 처리한 토큰 제거
            parse_stack.push(new TreeNode(token)); // 파스 스택에 토큰 추가
        } else if (action_type == "REDUCE") {
            // REDUCE 동작 수행
            auto rule = grammar_rules[action_value];
            string lhs = rule.first;
            string rhs = rule.second;
            vector<TreeNode*> children;

            if (!rhs.empty()) {
                int reduce_length = count(rhs.begin(), rhs.end(), ' ') + 1;
                for (int i = 0; i < reduce_length; ++i) {
                    state_stack.pop(); // 상태 스택에서 요소 제거
                    children.push_back(parse_stack.top()); // 파스 스택에서 요소 제거
                    parse_stack.pop();
                }
                reverse(children.begin(), children.end()); // 자식 노드 순서 변경
            }

            TreeNode* new_node = new TreeNode(lhs);
            new_node->children = children;
            parse_stack.push(new_node); // 파스 스택에 새로운 노드 추가

            auto goto_iter = parsing_table.find(make_pair(state_stack.top(), lhs));
            if (goto_iter == parsing_table.end()) {
                cout << "Parsing error: Invalid goto at state " << state_stack.top() << " with lhs " << lhs << endl;
                return;
            }
            int goto_state = goto_iter->second.second;
            state_stack.push(goto_state); // 상태 스택에 GOTO 상태 추가
        } else if (action_type == "ACCEPT") {
            // ACCEPT 동작 수행
            break;
        }
    }

    // 파싱 트리 출력
    cout << "Parsing successful!" << endl;
    cout << "Parse tree:" << endl;
    function<void(TreeNode*, string)> print_tree = [&](TreeNode* node, string indent) {
        cout << indent << node->name << endl;
        for (auto child : node->children) {
            print_tree(child, indent + "  ");
        }
    };

    // 보기 쉽게 트리 출력
    function<void(TreeNode*, string, bool)> print_tree_structure = [&](TreeNode* node, string prefix, bool is_last) {
        cout << prefix;

        if (is_last) {
            cout << "└── ";
            prefix += "    ";
        } else {
            cout << "├── ";
            prefix += "│   ";
        }

        cout << node->name << endl;

        for (size_t i = 0; i < node->children.size(); ++i) {
            print_tree_structure(node->children[i], prefix, i == node->children.size() - 1);
        }
    };

    print_tree_structure(parse_stack.top(), "", true);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Error: No arguments provided" << endl;
        return 1;
    }

    string file_path = argv[1];
    ifstream input_file(file_path);
    if (!input_file) {
        cerr << "File does not exist" << endl;
        return 1;
    }

    stringstream buffer;
    buffer << input_file.rdbuf();
    input_file.close();

    vector<string> input_tokens;
    string token;
    while (buffer >> token) {
        input_tokens.push_back(token);
    }
    input_tokens.push_back("$"); // 입력 토큰의 끝을 나타내기 위해 '$' 추가

    // 파싱 수행
    parse_input(input_tokens);

    return 0;
}
//commit 메세지 1