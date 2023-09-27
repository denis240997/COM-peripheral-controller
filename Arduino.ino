
char data;

int N1 = 0, N3 = 0;  // переменные для чтения-записи ком порта
int N2 = 0, N4 = 0;
int N5 = 0;
int test = 36;
int i = 0;

byte Name1 = 30, Name2 = 1, Name3 = 1,
     Name4 = 4;  // данные для идентификации устройства
//  Name1=10  -насос  40 -шейкер    70 -детектор     90 -аспиратор

void setup() {
    // put your setup code here, to run once:

    Serial.begin(9600);

    pinMode(7, OUTPUT);
    digitalWrite(7, LOW);
}

void loop() {
    if (Serial.available() > 0)  // чтоние порта
    {
        N1 = Serial.read();
        delay(20);  // команда  от 10  до  19
        N2 = Serial.read();
        delay(20);  //  параметр 1
        N3 = Serial.read();
        delay(20);  //  параметр2
        N4 = Serial.read();
        delay(20);           // параметр 3
        N5 = Serial.read();  // delay(20); // параметр 3

        if (N1 == 1 && N2 == 2 && N3 == 3 &&
            N4 == 4) {  // запрос идентификации устройства

            //  записываем в com порт параметры для идентификации устройства
            Serial.write(Name1);
            delay(20);
            Serial.write(Name2);
            delay(20);
            Serial.write(Name3);
            delay(20);
            Serial.write(Name4);  // delay(10);
        }

        if (N1 != 1) {  // задание для выполнения
            Serial.write(Serial.available());

            ParametrAnaliser();  // разбираемся что означает команда N1-N4
        }

    }  // END чтоние порта
}

void ParametrAnaliser(
    void) {  //  функция анализа пришедшией с ком порта команды

    //-----------------------------------ДЕТЕКТОР КЛЕТ ПЛОТНОСТИ
    if (N1 == 71 && N4 == 5 &&
        N5 == 123) {  //  команда запрос температуры  (70, 0, 0, 5, 123)

        Serial.write(5);
        delay(10);  //  ответ на запрос температуры     вернет    5, 5, A, B где
                    //  А.B  - целая и дробная части float числа температуры
        Serial.write(5);
        delay(10);
        Serial.write(test);
        delay(10);
        Serial.write(71);
        delay(10);

        test++;
        if (test > 100)
            test = 0;
    }

    if (N1 == 75 &&
        N5 == 123) {  //  команда запрос клеточной плотности  (75, 0, 0, 0, 123)

        Serial.write(3);
        delay(10);  //  ответ на запрос клет лотности     вернет    3, 0, A, B
                    //  где А.B  - целая и дробная части float числа
        Serial.write(0);
        delay(10);
        Serial.write(test);
        delay(10);
        Serial.write(75);
        delay(10);

        test += 10;
        if (test > 100)
            test = 0;
    }

    //-----------------------------------НАСОС----------------
    if (N1 == 11 &&
        N5 == 123) {  //  старт перистальт насоса  11, 111 ,  1,  37,  123

        test = N4;
        digitalWrite(7, HIGH);
    }

    if (N1 == 10 &&
        N5 == 123) {  //  CТОП  перистальт насоса  10, 0 ,  0,  0,  123

        test = N4;
        digitalWrite(7, LOW);
    }

    //-----------------------------------АСПИРАТОР_______________________
    if (N1 == 91 &&
        N5 == 123) {  //  старт аспиратора насоса  91, 111 ,  1,  37,  123

        test = N4;
        digitalWrite(7, HIGH);
    }

    if (N1 == 90 &&
        N5 == 123) {  //  CТОП  аспиратора насоса  90, 0 ,  0,  0,  123

        test = N4;
        digitalWrite(7, LOW);
    }

    //-----------------------------------

    //-----------------------------------ШЕЙКЕР_______________________
    if (N1 == 41 && N5 == 123) {  //  старт шейкера насоса  41, 0 ,  0,  2,  123

        test = N4;
        digitalWrite(7, HIGH);
    }

    if (N1 == 40 && N5 == 123) {  //  CТОП  шейкера насоса  40, 0 ,  0,  0,  123

        test = N4;
        digitalWrite(7, LOW);
    }

    //-----------------------------------
}