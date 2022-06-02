# УЧЕБНАЯ ПРАКТИКА
Программа пузырьковой сортировки и доп. условия работы с файлами

Программа выполняется в программе VisualStudio на языке программирования C++. 
Необходимо, реализовать программу, которая будет считывать текст из файла, путь или название, которого 
указываем в консоле (original.txt)
и с минимальными погрешностями разбивать его на массив отдельных слов.
В соответствии с параметрами нужно реализовать сортировку слов в тексте по кириллице, по алфавиту, 
по возрастанию, игнорируя числа и сортировкой пузырьком. Символы и знаки препинания игнорируются и не включаются. 
Отсортированный массив необходимо будет вывести в файл (result.txt)  и информацию с простейшим анализом текста в (analysis.txt), 
которая будет включать в себя: исходный текст, параметры варианта, количество слов в исходном тексте, время выполнения сортировки, 
количество слов на каждую букву алфавита. Далее проводится тест работы программы с различными текстами от 3тыс. до 15тыс. символов.
 
Пример входного файла: 
![image](https://user-images.githubusercontent.com/106561581/171547138-98c27191-e872-49a2-8e52-7ff7e8d8d433.png)

Пример файла с анализом текста:
![image](https://user-images.githubusercontent.com/106561581/171547233-2e43cb75-dad3-4d22-88bb-7660df6ca215.png)

Пример файла с результатом работы:
![image](https://user-images.githubusercontent.com/106561581/171546835-a72e31e2-2583-4be7-962b-e6b8f4632fec.png)


Задание:

![image](https://user-images.githubusercontent.com/106561581/171547965-e0fca69e-9b6b-472c-ab82-6bac40c12288.png)

Описание выполнения данных условий 

Объяляем глобальные переменные: int amountOfWords = 0; (количество слов) double Time =0; (время выполнения сортировки)
В int main() вызывается функция start, в которой указывается сначала название файла или путь к файлу в консоль для открытия, через консоль записывает в переменную типа char nameFile[1024], который будет указателем пути ifstream file(nameFile). Делаем проверку открыт ли наш файл и создаем переменные string initial_text и str. Переписываем из файла в str и  пока файл не достиг конца, формируем конечный вид нашего текста из файла в initial_text. 
Вызываем функцию ScanForWords(initial_text) для формирования слов. Записывая результат в string* words. В функции создаем переменные string* result (результат), создаем список list, где будут храниться наши слова, в переданную переменную text добавляем пробел для использования условия в цикле далее i <  text.length(). String word = “”, s; (для слова и его первого символа). Bool wrdChck. Далее создаем цикл, где на каждый заход 1 элемент у слова будем переводить в нижний регистр для работы,  создается условие для поиска букв в диапазоне ((s>=”а” && s <= “я”) || s == “ё”), если нашли букву в переменную word записываем ее для формирования слова и wrdChck присваиваем true, чтобы при следующем выходе из условия, в случае если символ не попал в необходимый диапозон, занести это слово в наш список. В случае, если слово занесли в список, переменную word чистим присваивая = “”; и wrdChck присваиваем false. После выполнения данного цикла, в переменную amountOfWords записываем длинну нашего list. Создаем динамический массив для хранения всех слов, которые передаем из list с помощью цикла и возвращаем result.
Вызываем функцию string* BubbleSort(string* wordArr) (передаем words) для сортировки пузырьком. Объявляем 4 переменные под нынешнее слово/нынешний элемент, следующее слово/следующий элемент. С помощью 2 циклов перебираем все возможные варианты слов по возрастанию. Сравнивая 1 элементы слов и в случае, если нынешний элемент > следующего меняем их местами. Возвращаем значения wordArr.
Вызываем функцию CreateOutput, куда передаем (words, initial_text), создаем переменные под текст, слова и 1 символ слова, и строку со всеми буквами алфавита. Создаем динамический массив, который будет хранить количество каждого слова, на каждую букву алфавита.  В 1 цикле создаем int count = 0; С помощью 2 циклов проверяем, есть ли буква в слове находящиеся в алфавите, если условие выполняется проверяем чему равен наш счетчик, если (count == 0), значит слово еще не находили на данную букву алфавита и записываем его просто в text, если данная буква уже была (count != 0), то в text добавляем пробел и наше слово. После, как все возможные слова на данный символ прошли проверку и мы вышли с условия, проверяем (count > 0), если хоть 1 слово было найдено добавляем в text перенос на следующую строку, для следующего элемента алфавита и в array_count[i] присваиваем значение количества слов на определенную букву.  Далее вычисляем время сортировки, вычисляем время до начала, вызываем функцию сортировки BubbleSort(textArr)  и время после сортировки. После чего считаем искомое время при (time_end – time_start) / 1000.00; Далее формируем файл result. Передаем значения text в targetFile, указывающий на файл result и завершаем работу с данным файлом targetFile.close(); Формируем файл analysis, выводим текст согласно примеру данному для работы и варианту задания. Выводим количесьвл слов, изначальный текст, время сортировки, с помощью количества цикла выводим в столбик количество слов на определенную букву из алфавита. Передаем все в файл и закрываем его targetFile.close()
