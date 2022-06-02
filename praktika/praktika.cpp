#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

// глобал. перемен.
int amountOfWords = 0;  //количество слов
double Time = 0;        // время выполнения сортировки

//формирование слов
string* ScanForWords(string text) {
    string* result;   
    list<string> list_words;    // создаем контейнер (список) list
    text += " ";    
    string word = "", s;     
    bool wrdChck = false;    
    for (int i = 0; i < text.length(); i++) {    
        s = tolower(text[i]);           //перевод первой буквы слова к нижнему регистру
        if ((s >= "а" && s <= "я") || s == "ё") {     //если нашли букву
            word += text[i];    // в word записываем найденную букву
            wrdChck = true;     // нашли слово
        }
        else {    //если нашли другой символ не входящий в условие выше
            if (wrdChck)list_words.push_back(word);   //заносим наше слово в список
            wrdChck = false;  // для следующего захода цикла, показываем, что слово еще не найдено
            word = "";       // обнуляем переменную со словом
        }
    }
    amountOfWords = list_words.size();     //записываем кол-во найденных слов

    result = new string[amountOfWords]; //динамический массив слов для последующей сортировки
    for (int i = 0; i < amountOfWords; i++) {
        result[i] = list_words.front();   // Передаем первый элемент в списке.
        list_words.pop_front();     // удаляем 1 элемент в list
    }
    return result;
}



void start() {
    cout << "Введите название файла/путь к файлу: ";
    char nameFile[1024];
    cin >> nameFile;
    ifstream file(nameFile);
    if (file.is_open()) {   // проверяем открыт ли файл
        string initial_text, str;
        //читаем текст из файла

        while (getline(file, str)) {  // записываем в str, из file
            if (!file.eof()) {  // если file не достигнул конца
                initial_text += str + "\n";
            }else{
                initial_text += str;
            }
        }
        
        string* words = ScanForWords(initial_text);//формируем слова в массив
    }
}

int main()
{
    setlocale(LC_ALL, "ru"); //устанавливаем кодировку для кириллицы
    start(); // вызов стартовой функции
    return 0;
}