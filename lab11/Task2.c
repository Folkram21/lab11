#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <locale.h>

// стилизация
void print_centered(const char* text) {
    int len = strlen(text);
    int total_padding = 80 - 2 - len;
    int left_padding = total_padding / 2;
    int right_padding = total_padding - left_padding;

    printf("*");
    for (int i = 0; i < left_padding; i++) 
        printf(" ");
    printf("%s", text);
    for (int i = 0; i < right_padding; i++) 
        printf(" ");
    printf("*\n");
}

int main() {
    setlocale(LC_CTYPE, "RUS");

    struct tm* mytime;
    time_t t;
    char buffer[256]; // буфер для sprintf
    t = time(NULL);

    mytime = localtime(&t);

    printf("Московское время %02d:%02d:%02d \n\n",
        mytime->tm_hour, mytime->tm_min, mytime->tm_sec);

    // массивы для словесного вывода
    const char* days[] = { "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота" };
    const char* months[] = { "января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря" };
    const char* months_nom[] = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь" };
    const char* roman_months[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII" };

    printf("********************************************************************************\n");

    sprintf(buffer, "1. День недели: %s", days[mytime->tm_wday]);
    print_centered(buffer);

    sprintf(buffer, "2. Дата: %02d.%02d.%d", mytime->tm_mday, mytime->tm_mon + 1, mytime->tm_year + 1900);
    print_centered(buffer);

    sprintf(buffer, "3. Сегодня: %d %s", mytime->tm_mday, months[mytime->tm_mon]);
    print_centered(buffer);

    sprintf(buffer, "4. Сегодня %d-й день %d года", mytime->tm_yday + 1, mytime->tm_year + 1900);
    print_centered(buffer);

    int days_to_sun = (7 - mytime->tm_wday) % 7;
    int hours_to_sun = (24 - mytime->tm_hour) % 24;
    sprintf(buffer, "5. До воскресенья %d дней и %d часов", days_to_sun, hours_to_sun);
    print_centered(buffer);

    int elapsed_hours = mytime->tm_hour - 9;
    int elapsed_minutes = mytime->tm_min;
    sprintf(buffer, "6. С первой пары прошло %d часов %d минут", elapsed_hours, elapsed_minutes);
    print_centered(buffer);

    int months_left = 11 - mytime->tm_mon;
    int days_left_ny = 31 - mytime->tm_mday;
    struct tm ny_time = *mytime;
    ny_time.tm_mon = 11; ny_time.tm_mday = 31; ny_time.tm_hour = 23; ny_time.tm_min = 59; ny_time.tm_sec = 59;
    sprintf(buffer, "7. До Нового года осталось %d месяцев и %d дней", 12 - (mytime->tm_mon + 1), 31 - mytime->tm_mday);
    print_centered(buffer);

    // пара идет с 10:45 до 12:15. Вычислим время до ближайшего конца пары.
    int min_to_end = 0, sec_to_end = 0;
    if (mytime->tm_min <= 15 && mytime->tm_hour == 12) {
        min_to_end = 15 - mytime->tm_min; sec_to_end = 60 - mytime->tm_sec;
    }
    else {
        min_to_end = 30; sec_to_end = 0;
    }
    sprintf(buffer, "8. До конца пары %d минут и %d секунд", min_to_end, sec_to_end);
    print_centered(buffer);

    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int is_leap = ((mytime->tm_year + 1900) % 4 == 0 && (mytime->tm_year + 1900) % 100 != 0) || ((mytime->tm_year + 1900) % 400 == 0);
    if (is_leap) 
        days_in_month[1] = 29;
    int days_to_end_month = days_in_month[mytime->tm_mon] - mytime->tm_mday;
    sprintf(buffer, "9. До конца месяца %d дней, до конца года %d месяцев", days_to_end_month, 11 - mytime->tm_mon);
    print_centered(buffer);

    sprintf(buffer, "10. Месяц: %s, Год: %d", roman_months[mytime->tm_mon], mytime->tm_year + 1900);
    print_centered(buffer);

    const char* season = "Зима";
    int m = mytime->tm_mon;
    if (m >= 2 && m <= 4) 
        season = "Весна";
    else if (m >= 5 && m <= 7) 
        season = "Лето";
    else if (m >= 8 && m <= 10) 
        season = "Осень";
    sprintf(buffer, "11. Время года: %s, Год: %02d", season, (mytime->tm_year + 1900) % 100);
    print_centered(buffer);

    int day_of_season = 0;
    const char* current_season = "зимы";
    if (m == 11) { 
        day_of_season = mytime->tm_mday;
        current_season = "зимы"; 
    } else if (m == 0 || m == 1) { 
        day_of_season = 31 + mytime->tm_mday;
        current_season = "зимы";
    } else if (m >= 2 && m <= 4) { 
        day_of_season = mytime->tm_mday + (m == 3 ? 31 : (m == 4 ? 61 : 0)); 
        current_season = "весны"; 
    } else if (m >= 5 && m <= 7) { 
        day_of_season = mytime->tm_mday + (m == 6 ? 30 : (m == 7 ? 61 : 0)); 
        current_season = "лета"; 
    }
    else if (m >= 8 && m <= 10) {
        day_of_season = mytime->tm_mday + (m == 9 ? 31 : (m == 10 ? 61 : 0));
        current_season = "осени";
    };

    sprintf(buffer, "12. Идет %d день %s", day_of_season, current_season);
    print_centered(buffer);

    printf("********************************************************************************\n");

    return 0;
}