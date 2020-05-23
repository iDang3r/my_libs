//
// Created by Александр on 15.11.2019.
//

#ifndef AKINATOR_AKINATOR_LANGUAGES_H
#define AKINATOR_AKINATOR_LANGUAGES_H

namespace common {
    const char welcome[]           = "Привет, мой друг, я Акинатор, новая персона в сфере искусственного интеллекта!\n";
    const char enter_game[]        = "Давай, загадай персонажа, а я попробую его отгадать по вопросам!\n";
    const char yes_or_no[]         = "Отвечай только 'да' или 'нет'\n";
    const char repeat_yes_no[]     = "Вы можете отвечать только 'да' или 'нет'!!!\n";

    const char another_game[]      = "Хочешь сыграть ещё? ";
    const char thinking[]          = "Я думаю, что ваш персонаж это..... ";

    const char see_you_later[]     = "Жаль, увидимся позже\n";
    const char game_again[]        = "Ничего себе, какой ненасытный, ну, давай, сыграем ещё!\n";

    const char ask_for_character[] =  "Жаль, кого вы загадали? ";
    const char repeated_name[]     = "К сожалению, характеристика этого персонажа не совпадает с вашими ответами. упсссс\n";

    const char true_characterstc[] = "Вот правильная характеристика:\n";
    const char is_your_character[] = "Это ваш персонаж? ";

    const char not_used[]          = "Качество не должно содеражать частицы отрицания\n";
    const char computer_won[]      = "Ещё бы, кожаный мешок! Меня ещё никто и никогда не обыгрывал!\n";

    const char common_quality[]    = "Вот вы отгадали, что персонаж ";
    const char different_quality[] = "но есть отличия, ";
    // перечисление качеств + логическая связка
    const char user_answers[]      = "вот так-то! А вы ответили, что ";

    const char choose_mode[]       = "Выберите режим работы со мной [0 - выход, 1 - играть, 2 - получить определение, 3 - получить различия]: ";

    const char failed_mode_num[]   = "Вы можете отвечать только 0, 1, 2 или 3!!!\n";

    const char in_character[]      = "Введите название персонажа: ";
    const char in_othr_character[] = "Введите название другого персонажа: ";

    const char failed_name[]      = "К сожалению, такое имя не найдено...\n";
    const char definition[]       = "Вот ваше определение: ";
}

namespace gopstop {
    const char welcome[]           = "Дороу, я Аки, новый чел на районе искусственного интеллекта!\n";
    const char enter_game[]        = "Ну, загадай быстрее любую дичь, а я её быренько отгадаю!\n";
    const char yes_or_no[]         = "Если ответишь что-то кроме 'да' или 'нет', хребет сломаю\n";
    const char repeat_yes_no[]     = "Вы можете отвечать только 'да' или 'нет'!!!\n";

    const char another_game[]      = "Ну-ка, пацанчик, ещё катку? ";
    const char thinking[]          = "Базара нет, это..... ";

    const char see_you_later[]     = "Ну, ладно, на созвоне\n";
    const char game_again[]        = "Ничего, братиш, какой ненасытный, ну, давай, тряхнем ещё!\n";

    const char ask_for_character[] = "Блэээ, дядя, кого ты загадал? ";
    const char repeated_name[]     = "Облажался ты, перец, такую дичь я уже знаю, развести меня надумал?\n";

    const char true_characterstc[] = "Не очкуй, вот правильная характеристика:\n";
    const char is_your_character[] = "Ну, чо, это ваше? ";

    const char not_used[]          = "Не держи меня за лоха, мне не нужны тут отрицания\n";
    const char computer_won[]      = "Ещё бы, поц! Меня ещё никто и никогда не обыгрывал, я же гроза этого района!\n";

    const char common_quality[]    = "Так, тут братва пробила по базе, ты отгадал, что дичь ";
    const char different_quality[] = "но есть отличия, ";
    // перечисление качеств + логическая связка
    const char user_answers[]      = "во! Дядь! А ты ответил, что ";

    const char choose_mode[]       = "Куку, баклажан, все так же базарить будем или уже делом займемся? [0 - выход, 1 - играть, 2 - получить определение, 3 - получить различия]: ";

    const char failed_mode_num[]   = "У тебя что, абонемент в травмпункт? Нет? Ещё раз ответишь неправильной командой, я тебе путёвку туда выпишу\n";

    const char in_character[]      = "Давай название дичи: ";
    const char in_othr_character[] = "Ну, а, название другой дичи: ";

    const char failed_name[]      = "Ты чё, развести меня решиил? Я такого не слышал, у тебя 3 секунды чтобы унестить отсюда живым\n";
    const char definition[]       = "Ну, лови, пробили мы твою дичь: ";
}

#endif //AKINATOR_AKINATOR_LANGUAGES_H
