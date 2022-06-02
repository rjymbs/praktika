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

//сортировка пузырьком
string* BubbleSort(string* wordArr) {
    string currentWord, followingWord, s_now, s_next;
    for (int i = 0; i < amountOfWords; i++)
        for (int j = 0; j < amountOfWords - 1; j++) {
            currentWord = wordArr[j];          // присваиваем текущее слово 
            followingWord = wordArr[j + 1];    // присваиваем следующее слово 
            s_now = tolower(currentWord[0]);    // присваиваем 1эл текущего слова 
            s_next = tolower(followingWord[0]);   // присваиваем 1эл следующего слова
                if (s_now[0] > s_next[0]) {             //сравниваем первые символы текущего и след. слова
                    //меняем слова местами
                   wordArr[j] = followingWord;
                   wordArr[j + 1] = currentWord;
            }
        }
    return wordArr;
}

//формирование файлов вывода result и analysis
void CreateOutput(string* textArr, string first_text) {
    string text = "", word, s;
    string alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"; // все буквы алфавита для проверки кириллицы 
    int* array_count = new int[alphabet.size()]; //массив с информацией о количестве каждого слова на каждую букву из кириллицы

    //Считаем количество слов на каждую букву алфавита и формируем слова начиная с "а" в алфавитном порядке
    for (int i = 0; i < alphabet.size(); i++) {
        int count = 0; 
        for (int j = 0; j < amountOfWords; j++) {
            word = textArr[j];
            s = tolower(word[0]);
            if (s[0] == alphabet[i]) {    // если 1 элемент слова совпадает с эл. из alphabet
                if (count == 0)         // если 1 эл строки еще не нашелся в alphabet
                    text += word;         // добавляем слово
                else
                    text += " " + word;     // если уже было, добавляем через пробел
                count++;    //подсчет кол-во слов в тексте на каждую букву alphabet
            }
        }
        if (count > 0)         //если счетчик слов больше 0
            text += "\n";      //добавляем в text перенос на след. строку, где будут следующие на слова на другой элемент
        array_count[i] = count;   // записываем кол-во слов на каждую букву алфавита
    }

    // вычисляем время сортировки
    unsigned int time_start = clock(); // время до запуска сортировки
    BubbleSort(textArr); // вызов сортировки
    unsigned int time_end = clock(); // время после сортировки
    Time = (time_end - time_start) / 1000.0; // нахождение времени 


    //формируем файл result
    ofstream targetFile("11.txt");
    targetFile << text;     // переписываем text в файл
    targetFile.close();     // закрываем файл

    //формируем файл analysis
    text = "Введенный текст:\n" + first_text + "\n\nВариант 13: кириллица, по алфавиту, по возрастанию, игнорировать числа, сортировка пузырьком\n";
    text += "Количество слов: " + to_string(amountOfWords) + "\n";
    stringstream stream;
    stream << Time;   
    text += "Время сортировки: " + stream.str() + " сек\n";
    text += "Статистика (количество слов на каждую букву алфавита):\n";

    //формирование количество слов по буквам алфавита
    for (int i = 0; i < alphabet.size(); i++) {
        text += alphabet[i];       // буква алфавита
        text += " - ";         
        text += to_string(array_count[i]);      // количество
        if (i < alphabet.size() - 1)
            text += "\n";          //переход к следующей букве на новую строку
    }
    
    targetFile.open("12.txt"); 
    targetFile << text; 
    targetFile.close();
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
        words = BubbleSort(words); //сортировка
        CreateOutput(words, initial_text);//формирование файла result и analysis
    }
}

int main()
{
    setlocale(LC_ALL, "ru"); //устанавливаем кодировку для кириллицы
    start(); // вызов стартовой функции
    return 0;
}