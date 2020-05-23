//
// Created by Александр on 09.11.2019.
//

#ifndef AKINATOR_AKINATOR_TREE_H
#define AKINATOR_AKINATOR_TREE_H

#include "Tree.h"
#include "my_file_lib.h"
#include "color_printf.h"
#include "super_define.h"
#include "Akinator_languages.h"

//typedef char* str_t;
#define str_t char*

const char open_bracket  = '{';
const char close_bracket = '}';
const char nil_node[]    = "nil";

const char voice_command[] = "say ";

#define language common

struct Akinator_Tree : Tree<str_t> {

    bool edited = false;

    bool play_again = false;

    // Methods

    void free_str_s_rec(node<str_t>* el) {
        assert(el != nullptr);

        free(el->data_);

        if (el->left_ != nullptr)
            free_str_s_rec(el->left_);

        if (el->right_ != nullptr)
            free_str_s_rec(el->right_);
    }

    ~Akinator_Tree() {
        cout << "Akinator_Tree was destructed" << endl;
        if (head_ != nullptr) {
            free_str_s_rec(head_);
        }
    }

    void push_head_s(const str_t s) {
        char* tmp = (char*)calloc(strlen(s) + 1, sizeof(char));
        strcpy(tmp, s);
        push_head(tmp);
    }

    void push_left_s(node<str_t>* el, const str_t s) {
        char* tmp = (char*)calloc(strlen(s) + 1, sizeof(char));
        strcpy(tmp, s);
        push_left(el, tmp);
    }

    void push_right_s(node<str_t>* el, const str_t s) {
        char* tmp = (char*)calloc(strlen(s) + 1, sizeof(char));
        strcpy(tmp, s);
        push_right(el, tmp);
    }

    void dump_picture_rec(FILE* out, node<str_t>* el, int last = -1) {

        fprintf(out, "class %p {\n", el);

        if (last == 1) {
            fprintf(out, "YES\n");
        } else if (last == 0) {
            fprintf(out, "NO\n");
        } else {
            fprintf(out, "Default\n");
        }

        fprintf(out, "--\n");

        fprintf(out, "\"%s\"\n", el->data_);

        if (el->right_) {
            fprintf(out, "--\n");
            fprintf(out, "yes: %p\n", el->right_);
        }

        if (el->left_) {
            fprintf(out, "--\n");
            fprintf(out, "no: %p\n", el->left_);
        }

        fprintf(out, "}\n");

        if (el->right_) {
            fprintf(out, "%p -down-> %p\n", el, el->right_);

            dump_picture_rec(out, el->right_, 1);
        }

        if (el->left_) {
            fprintf(out, "%p -down-> %p\n", el, el->left_);

            dump_picture_rec(out, el->left_, 0);
        }
    }

    void dump_picture() {

        FILE* out = fopen("/Users/alex/Desktop/pictures/Akinator_uml.pu", "w");

        if (out == nullptr) {
            dump(DUMP_INFO, "file was not opened");
            return;
        }

        fprintf(out, "@startuml\n !define DARKORANGE\n !include style.puml\n class head_\n");

        fprintf(out, "head_ -down-> %p\n", head_);

        dump_picture_rec(out, head_);

        fprintf(out, "@enduml\n");
        fclose(out);

        system("java -jar --illegal-access=warn /Users/alex/plantuml.jar -tsvg /Users/alex/Desktop/pictures/Akinator_uml.pu");
        system("open /Users/alex/Desktop/pictures/Akinator_uml.svg");
    }

    char* skip_spaces(char* buff) {
        int n = 0;
        sscanf(buff, "%*[ \t]%n", &n);
        return buff + n;
    }

    char* build_tree_rec(char* buff, node<str_t>* *el, char* str_buff) {
        assert(el != nullptr);
        assert(buff != nullptr);
        assert(str_buff != nullptr);

        buff = skip_spaces(buff);

        assert(*buff == open_bracket);
        buff++;
        int n = 0;

        buff = skip_spaces(buff);

        sscanf(buff, "'%[^']'%n", str_buff, &n);
        buff += n;
        char* new_str = (char*)calloc(strlen(str_buff) + 1, sizeof(char));

        if (new_str == nullptr) {
            dump(DUMP_INFO, "memory was not allocated");
            assert(ERROR);
        }

        strcpy(new_str, str_buff);
        *el = make_node(new_str);

        buff = skip_spaces(buff);

        if (*buff == close_bracket)
            return buff + 1;


        buff = skip_spaces(buff);

        if (strncmp(buff, nil_node, strlen(nil_node)) == 0) {
            buff += strlen(nil_node);
        } else {
            buff = build_tree_rec(buff, &((*el)->left_), str_buff);
        }

        buff = skip_spaces(buff);

        if (strncmp(buff, nil_node, strlen(nil_node)) == 0) {
            buff += strlen(nil_node);
        } else {
            buff = build_tree_rec(buff, &((*el)->right_), str_buff);
        }

        buff = skip_spaces(buff);

        assert(*buff == close_bracket);
        return buff + 1;
    }

    int get_tree_from_file(const char* name_of_file) {
        if (head_ != nullptr) {
            dump(DUMP_INFO, "head_ is not null");
            free_str_s_rec(head_);
            free_tree(head_);
            head_ = nullptr;
        }

        char* buff = nullptr;
        size_t buff_size = get_buffer(name_of_file, &buff);

        char str_buff[128] = {};

        build_tree_rec(buff, &head_, str_buff);

        free(buff);

        return 0;
    }

    void put_tree_rec(FILE* out, node<str_t>* el) {
        assert(out);
        assert(el);

        fprintf(out, "%c", open_bracket);

        fprintf(out, "'%s'", el->data_);

        if (el->left_ != nullptr || el->right_ != nullptr) {
            if (el->left_ != nullptr) {
                put_tree_rec(out, el->left_);
            } else {
                fprintf(out, "%s ", nil_node);
            }

            if (el->right_ != nullptr) {
                put_tree_rec(out, el->right_);
            } else {
                fprintf(out, "%s", nil_node);
            }
        }

        fprintf(out, "%c", close_bracket);
    }

    int put_tree_in_file(const char* name_of_file) {
        FILE* out = fopen(name_of_file, "w");

        if (out == nullptr) { // обязательна ли эта проверка
            dump(DUMP_INFO, "file was not opened");
            return 1;
        }

        if (head_ != nullptr)
            put_tree_rec(out, head_);
        else
            fprintf(out, "%s", nil_node);

        fclose(out);
        printf("Tree was rewrited\n");
        return 0;
    }

    void print_and_say(const str_t s) {
        char* command = concat(voice_command, s);
        printf("%s", s);
        fflush(stdout);
        system(command);
        free(command);
    }

    void ask_yes_no(char* s) {
        scanf("%s", s);
        while (strcmp(s, "нет") && strcmp(s, "да") &&
               strcmp(s, "no") && strcmp(s, "yes")) {
            print_and_say(language::repeat_yes_no);
            scanf("%s", s);
        }
    }

    node<str_t>* check_for_same_str(node<str_t>* el, const char* s) {
        if (strcmp(el->data_, s) == 0)
            return el;

        node<str_t>* u = nullptr;

        if (el->left_ != nullptr)
            u = check_for_same_str(el->left_, s);

        if (u == nullptr && el->right_ != nullptr)
            u = check_for_same_str(el->right_, s);

        return u;
    }

    bool get_definition(node<str_t>* el, const char* s) {
        if (strcmp(el->data_, s) == 0)
            return true;

        if (el->left_ != nullptr && get_definition(el->left_, s)) {
            char* neg_ans = concat("не ", el->data_);
            print_and_say(neg_ans);
            printf(", ");
            free(neg_ans);
            return true;
        }

        if (el->right_ != nullptr && get_definition(el->right_, s)) {
            print_and_say(el->data_);
            printf(", ");
            return true;
        }

        return false;
    }

    node<str_t>* LCA(node<str_t>* during, node<str_t>* el1, node<str_t>* el2) {
        assert(el1);
        assert(el2);

        if (during == nullptr)
            return nullptr;

        if (during == el1)
            return el1;

        if (during == el2)
            return el2;

        node<str_t>* tmp_left  = LCA(during->left_,  el1, el2);
        node<str_t>* tmp_right = LCA(during->right_, el1, el2);

        if (tmp_left != nullptr && tmp_right != nullptr)
            return during;

        if (tmp_left)
            return tmp_left;

        if (tmp_right)
            return tmp_right;

        return nullptr;
    }

    bool get_differences(node<str_t>* el1, node<str_t>* el2) {
        node<str_t>* LCA_tmp = LCA(head_, el1, el2);

//        print_and_say("Разница между вашим персонажем и вашими ответами\n");
        print_and_say(language::common_quality);

        get_definition(head_, LCA_tmp->data_);

        char* tmp = concat(el1->data_, " ");

        print_and_say(language::different_quality);
        print_and_say(tmp);
        get_definition(LCA_tmp, el1->data_);
        free(tmp);

        tmp = concat(el2->data_, " ");
        print_and_say(language::user_answers);
        print_and_say(tmp);
        get_definition(LCA_tmp, el2->data_);
        free(tmp);

        return 1;
    }

    void ask_for_another_game(char* str_buff) {
        print_and_say(language::another_game);
        ask_yes_no(str_buff);
        if (strcmp(str_buff, "no") == 0 || strcmp(str_buff, "нет") == 0) {
            print_and_say(language::see_you_later);
            play_again = false;
        } else {
            print_and_say(language::game_again);
            play_again = true;
        }
    }

    void gaming_rec(node<str_t>* el, str_t str_buff) {
        if (el->left_ == nullptr && el->right_ == nullptr) {
            print_and_say(language::thinking);
            printf("\033[1;32m");
            print_and_say(el->data_);
            printf("\033[0m\n");

            print_and_say(language::is_your_character);
            ask_yes_no(str_buff);

            if (strcmp(str_buff, "no") == 0 || strcmp(str_buff, "нет") == 0) {

                print_and_say(language::ask_for_character);
                scanf("\n%[^\n]", str_buff);

                node<str_t>* same_node_tmp = check_for_same_str(head_, str_buff);

                if (same_node_tmp) {
                    print_and_say(language::repeated_name);

//                    print_and_say(language::true_characterstc);  // вывод простой характеристики
                    get_differences(same_node_tmp, el);

                    ask_for_another_game(str_buff);
                    return;
                }

                char* new_answer = (char*)calloc(strlen(str_buff) + 1, sizeof(char));
                if (new_answer == nullptr) {                // насколько корректно программа должна на такое реагировать и продолжать работу
                    dump(DUMP_INFO, "memory was not allocated");
                    assert(ERROR);
                }

                strcpy(new_answer, str_buff);

                char* tmp1 = concat("Какое качество есть у ", new_answer);
                char* tmp2 = concat(tmp1, ", но нет у ");
                free(tmp1);
                tmp1 = concat(tmp2, el->data_);
                free(tmp2);
                tmp2 = concat(tmp1, "? ");

                print_and_say(tmp2);

                free(tmp2);

                scanf("\n%[^\n]", str_buff);

                while (strstr(str_buff, "не ") || strstr(str_buff, "not ")) {
                    print_and_say(language::not_used);
                    scanf("\n%[^\n]", str_buff);
                }

                char* new_question = (char*)calloc(strlen(str_buff) + 1, sizeof(char));
                if (new_question == nullptr) {
                    dump(DUMP_INFO, "memory was not allocated");
                    assert(ERROR);
                }

                strcpy(new_question, str_buff);

                push_left(el, el->data_);
                push_right(el, new_answer);
                el->data_ = new_question;

                edited = true;

            } else {
                print_and_say(language::computer_won);
            }

            ask_for_another_game(str_buff);

            return;
        }

        char* question = concat(el->data_, "? ");
        print_and_say(question);
        free(question);

        ask_yes_no(str_buff);

        if (strcmp(str_buff, "no") == 0 || strcmp(str_buff, "нет") == 0) {
            gaming_rec(el->left_, str_buff);
        } else {
            gaming_rec(el->right_, str_buff);
        }

    }

    void game() {
        print_and_say(language::enter_game);
        print_and_say(language::yes_or_no);

        char str_buff[64] = {};
        gaming_rec(head_, str_buff);

        while (play_again)
            gaming_rec(head_, str_buff);

    }

    void mode_get_def() {
        char name[64] = {};

        print_and_say(language::in_character);
        scanf("%[^\n]", name);

        node<str_t>* el = check_for_same_str(head_, name);

        if (el == nullptr) {
            print_and_say(language::failed_name);
            return;
        }

        print_and_say(language::definition);
        get_definition(head_, name);
        printf("\n");
    }

    void mode_get_dif() {
        char name_1[64] = {};
        char name_2[64] = {};

        print_and_say(language::in_character);
        scanf("%s", name_1);

        w(name_1);

        node<str_t>* ch1 = check_for_same_str(head_, name_1);

        if (ch1 == nullptr) {
            print_and_say(language::failed_name);
            return;
        }

        print_and_say(language::in_othr_character);
        scanf("%s", name_2);

        w(name_2);

        node<str_t>* ch2 = check_for_same_str(head_, name_2);

         if (ch2 == nullptr) {
             print_and_say(language::failed_name);
             return;
        }

        get_differences(ch1, ch2);
    }

    void main_logic() {
        int code = -1;

        print_and_say(language::welcome);

        while (code) {
            print_and_say(language::choose_mode);

            scanf("%d", &code);

            while (code < 0 || 3 < code) {
                print_and_say(language::failed_mode_num);
                scanf("%d", &code);
            }

            scanf("%*c");

            switch (code) {
                case 0:
                    return;
                case 1:
                    game();
                    break;
                case 2:
                    mode_get_def();
                    break;
                case 3:
                    mode_get_dif();
                    break;
                default:
                    assert(ERROR);
            }
        }

    }

};

#endif //AKINATOR_AKINATOR_TREE_H
