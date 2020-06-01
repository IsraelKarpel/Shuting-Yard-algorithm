//#ifndef UNTITLED3_ex1_CPP
//#define UNTITLED3_ex1_CPP

#include "ex1.h"
using namespace std;



        double Variable:: calculate() {
            return this->value;
        }

        Variable &Variable::operator++() {
            ++value;
            return *this;
        }

        Variable &Variable::operator--() {
            --value;
            return *this;
        }

        Variable &Variable::operator+=(double d) {
            value += d;
            return *this;
        }

        Variable &Variable::operator-=(double d) {
            value -= d;
            return *this;
        }

        Variable &Variable::operator++(int) {
            value++;
            return *this;
        }

        Variable &Variable::operator--(int) {
            value--;
            return *this;
        }

        double Value:: calculate() {
            return val;
        }

        double UPlus:: calculate() {
            return exp->calculate();
        }

        double UMinus:: calculate() {
            return (exp->calculate() * -1);
        }

        double Plus::calculate() {
            return exp1->calculate() + exp2->calculate();
        }

        double Minus:: calculate() {
            return exp1->calculate() - exp2->calculate();
        }

        double Mul:: calculate() {
            return exp1->calculate() * exp2->calculate();
        }

         double Div:: calculate() {
            if (exp2->calculate() == 0) {
                throw "cant devide ziro ";
                } else {
                return exp1->calculate() / exp2->calculate();
                }
        }

        Expression* Interpreter::interpret(string str) {
            queue<string> que;
            stack<string> stc;
            stack<Expression *> stc2;
            string d, r;
            bool oper;
            //checks for double operators
        oper = isOperator(str);
            if (!oper) {
                throw "two operators in a row";
            }
            for (unsigned int i = 0; i < str.size(); i++) {
                if (isdigit(str[i])) {
                    //checks if the number contains more then 1 digit
                    d = str[i];
                    unsigned int j = i + 1;
                    while (j < str.size())  {
                        if (isdigit(str[j]) || (str[j] == '.')) {
                        d += str[j];
                            i++;
                            j++;
                        } else {
                            break;
                        }
                    }
                    que.push(d);
                } else if (str[i] == '(') {
                    stc.push("(");
                } else if (str[i] == ')') {
                    while ("(" != stc.top()) {
                        que.push(stc.top());
                        stc.pop();
                            if (stc.empty()) {
                                throw "missing ( ";
                            }
                        }
                        stc.pop();
                } else {
                    // if is an operator
                        // if the stack is empty
                    if (('+' == str[i]) || ('-' == str[i]) || ('*' == str[i]) || ('/' == str[i])) {
                        //make sure the minus is for minus and nor unary
                        if (((stc.empty()) && str[i] != '-') || (stc.empty() && str[i] == '-' && i != 0 && (isdigit(str[i-1])))){
                            stc.push(fromCharToString(str[i]));
                        } else {
                            //unary minus
                            if (((str[i] == '-') && (i == 0)) || ((str[i] == '-') && !(isdigit(str[i - 1])))) {
                                //symbol that will represent Uminus
                                stc.push("#");
                            } else {
                                unsigned int found = str.find(str);
                                if (((str[i] == '+') && (i == 0)) || ((str[i] == '+') && found > i)) {
                                    //symbol that will represent UPlus
                                    stc.push("&");
                                } else {
                                    //find out where the operator should be at the stack
                                    while ((((('+' == str[i]) || ('-' == str[i])) &&
                                                     (((stc.top() == "*") || (stc.top() == "/")) || ((stc.top() == "&") || (stc.top() == "#")))) ||
                                            (((str[i] == '+') || (str[i] == '-')) &&
                                             ((stc.top() == "+") || (stc.top() == "-")))
                                            || (((((str[i] == '*') || (str[i] == '/')) || ((str[i] == '&') || (str[i] == '#'))) &&
                                            (((stc.top() == "*") || (stc.top() == "/")) || (((str[i] == '&') || (str[i] == '#')))))))
                                           && (stc.top() != ")")) {
                                        que.push(stc.top());
                                        stc.pop();
                                        if (stc.empty()) {
                                            break;
                                        }
                                    }
                                    stc.push(fromCharToString(str[i]));
                                }
                            }
                        }
                    }
                }
                //if there is a name we got from setVariables, replace it in his value;
                auto itr = varies.find(string(1,str[i]));
                if (itr != varies.end()) {
                    que.push(itr->second);
                }
            }
            while (!stc.empty()) {
                if (stc.top() == "(") {
                    throw "too much (";
                } else {
                    que.push(stc.top());
                    stc.pop();
                }
            }
            //from postfix to calculate
            while (!que.empty()) {
                if (que.front() == "+") {
                    Expression *vRight = stc2.top();
                    stc2.pop();
                    Expression *vLeft = stc2.top();
                    stc2.pop();
                    Expression *e1 = new Plus(vLeft, vRight);
                    stc2.push(e1);
                    que.pop();
                } else if (que.front() == "-") {
                    Expression *vRight = stc2.top();
                    stc2.pop();
                    Expression *vLeft = stc2.top();
                    stc2.pop();
                    Expression *e1 = new Minus(vLeft, vRight);
                    stc2.push(e1);
                    que.pop();
                } else if (que.front() == "*") {
                    Expression *vRight = stc2.top();
                    stc2.pop();
                    Expression *vLeft = stc2.top();
                    stc2.pop();
                    Expression *e1 = new Mul(vLeft, vRight);
                    stc2.push(e1);
                    que.pop();
                } else if (que.front() == "/") {
                    Expression *vRight = stc2.top();
                    stc2.pop();
                    Expression *vLeft = stc2.top();
                    stc2.pop();
                    Expression *e1 = new Div(vLeft, vRight);
                    stc2.push(e1);
                    que.pop();
                } else if (que.front() == "#") {
                    Expression *v = stc2.top();
                    stc2.pop();
                    Expression *e1 = new UMinus(v);
                    stc2.push(e1);
                    que.pop();
                } else if (que.front() == "&") {
                    Expression *v = stc2.top();
                    stc2.pop();
                    Expression *e1 = new UPlus(v);
                    stc2.push(e1);
                    que.pop();
                } else {
                    string s = que.front();
                    Expression *e1 = new Value(stod(s));
                    stc2.push(e1);
                    que.pop();
                }
            }
            inter = stc2.top();
            return inter;
        }

        string Interpreter:: fromCharToString(char c) {
            switch(c) {
                case '+':
                    return "+";
                    break;
                case '-':
                    return "-";
                    break;
                case '*':
                    return "*";
                    break;
                case '/':
                    return "/";
                    break;
                case '(':
                    return "(";
                    break;
                case ')':
                    return ")";
                    break;
                default:;
            }
            return "0";
        }

        double Interpreter:: calculate() {
            return inter->calculate();
        }

        void Interpreter:: setVariables(string set) {
            string set2 = set,oneHalf,  oneInteger, oneValue, set3;
            bool number, letter;
            int pos3;
            int pos = set.find(";");
            while (pos > 0) {
                oneHalf = set2.substr(0, pos);
                pos3 = oneHalf.find("=");
                    if (pos3 == 0) {
                        throw "bad syntax";
                    }
                oneInteger = oneHalf.substr(0, pos3);
                letter = isValidName(oneInteger);
                    if (!letter) {
                        throw "not a valid name";
                    }
                // if the integer akready exist we need to overrite him
                auto itr = varies.find(oneInteger);
                if (itr != varies.end()) {
                    varies.erase(oneInteger);
                }
                oneValue = oneHalf.substr(pos3 + 1, pos);
                number = isNumber(oneValue);
                   if (number == false) {
                        throw  "not a number";
                }

                varies.insert(pair<string, string>(oneInteger, oneValue));
                set3 = set2.substr(pos + 1);
                //finished the limit
                if ((set3 == set2) || (set3.length() == 0)){
                    return;
                }
                set2 = set3;
                pos = set2.find(";");
            }
                //one more time if the last name:value isnt end in ;
                oneHalf = set2.substr(0, pos);
                pos3 = set2.find("=");
                if (pos3 == 0) {
                    throw "bad syntax";
                }
                oneInteger = oneHalf.substr(0, pos3);
                letter = isValidName(oneInteger);
                    if (letter == false) {
                        throw "not a valid name";
                     }
                // if the integer akready exist we need to overrite him
                auto itr = varies.find(oneInteger);
                if (itr != varies.end()) {
                    varies.erase(oneInteger);
                }
                oneValue = oneHalf.substr(pos3 + 1, pos);
                number = isNumber(oneValue);
                if (number == false) {
                    throw "not a number";
                }
            varies.insert(pair<string, string>(oneInteger, oneValue));
            }

            bool Interpreter:: isNumber(string s) {
            int dotCounter = 0;
            for (unsigned int i = 0; i < s.length(); i++) {
                if (!isdigit(s[i])) {
                    if ((s[i] == '.') && ((i != 0) || (i != s.length() - 1))) {
                        dotCounter++;
                        if (dotCounter > 1) {
                            return false;
                        }
                    } else {
                        return false;
                    }
                }
            }
            return true;
        }

        bool Interpreter:: isValidName (string s) {
            if ((isalpha(s[0])) || (s[0] == '_')) {
                for (unsigned int i = 1; i < s.length(); i++) {
                    if (isalpha(s[i]) || (isdigit(s[i])) || s[i] == '_') {
                    } else {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        }

        bool Interpreter:: isOperator(string s) {
            int counter = 0;
            for (unsigned int i = 0; i < s.length(); i++) {
                if ((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/')) {
                    counter++;
                } else {
                    counter = 0;
                }
                if (counter > 1) {
                    return false;
                }
            }
            return true;
        }

//#endif