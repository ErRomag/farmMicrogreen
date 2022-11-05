#include <GyverButton.h>
#include <GyverOLED.h>

#define OLED_SOFT_BUFFER_64     // Буфер на стороне МК
GyverOLED<SSD1306_128x64> oled;

#define BUTTON_PIN A2

// создаём кнопки без привязки к пину
GButton myButtUP;
GButton myButtDOWN;
GButton myButtOK;

int buttonValue;

#define ITEMS 5          // Общее кол во пунктов в главном меню
#define ITEMS_SETTINGS 6 // Общее кол во пунктов в подменю 'Настройки'

void setup()
{
  buttonValue = 0;

  Serial.begin(9600);
  Serial.println ("Serial start");

  myButtUP.setType(LOW_PULL);
  myButtDOWN.setType(LOW_PULL);
  myButtOK.setType(LOW_PULL);

  oled.init();           // Инциализация дисплея
  oled.setContrast(255); // Макс. яркость
}

void loop()
{
  static int8_t pointer = 0; // Переменная указатель для меню

  buttonValue = analogRead(BUTTON_PIN);  // получаем значение напряжения с аналогового пина

  myButtUP.tick(buttonValue < 170 && buttonValue > 130);
  myButtDOWN.tick(buttonValue < 350 && buttonValue > 310);
  myButtOK.tick(buttonValue < 750 && buttonValue > 730);

  if (myButtUP.isClick() or myButtUP.isHold()) {  // Если кнопку нажали или удерживают
    pointer = constrain(pointer - 1, 0, ITEMS - 1); // Двигаем указатель в пределах дисплея
  }

  if (myButtDOWN.isClick() or myButtDOWN.isHold()) {
    pointer = constrain(pointer + 1, 0, ITEMS - 1);
  }

  if (myButtOK.isClick()) // Нажатие на ОК - переход в пункт меню
  {
    switch (pointer) {  // По номеру указателей располагаем вложенные функции (можно вложенные меню)
      case 0: showSummary();   break;  // По нажатию на ОК при наведении на 0й пункт вызвать функцию
      case 1: adjustAirflow(); break;
      case 2: adjustLight(); break;
      case 3: adjustWatering(); break;
      case 4: settings(); break;
    }
  }

  /* меню */
  oled.clear();           // Очищаем буфер
  oled.home();            // Курсор в левый верхний угол

  oled.print              // Вывод всех пунктов
  (F(
     "     Главное меню\n\r"
     "                 \n\r"
     "     Сводка      \n\r"  // Не забываем про '\n' - символ переноса строки
     "     Обдув       \n\r"  // и '\r' - символ возврата коретки
     "     Освещение   \n\r"
     "     Полив       \n\r"
     "     Настройки   \n\r"
   ));

  printPointer(pointer + 2);  // Вывод указателя. На 2 строку устанавливаем указатель
  oled.update();          // Выводим кадр на дисплей
}

void printPointer(uint8_t pointer) {
  // Символьный указатель - лучший выбор в многостраничном меню
  // Указатель в начале строки
  oled.setCursor(0, pointer);
  oled.print(">");
}

/*
    The ShowSummary void - показывает сводку
    с текущими парамтерами: датой, временем,
    значениями температуры и влажности
*/
void showSummary(void)
{
  Serial.println("Сводка");

  oled.clear();
  oled.home();
  oled.print("     Сводка");
  oled.setCursor(0, 1);
  oled.print("           ");
  oled.setCursor(0, 2);
  oled.print("11.22.2022");

  oled.setCursor(81, 2);
  oled.print("09:43:57");

  oled.update();
  while (1)
  {
    buttonValue = analogRead(BUTTON_PIN);  // получаем значение напряжения с аналогового пина
    myButtOK.tick(buttonValue < 750 && buttonValue > 730);

    if (myButtOK.isClick()) return; // return возвращает нас в предыдущее меню
    delay(10);
  }
}

/*
    The adjustAirflow void - функция настройки
    обдува. Включает выбор номера вентилятора,
    время включения и отключения.
*/
void adjustAirflow(void)
{
  Serial.println("Обдув");

  oled.clear();
  oled.home();
  oled.print("     Обдув");
  oled.update();

  while (1)
  {
    buttonValue = analogRead(BUTTON_PIN);  // получаем значение напряжения с аналогового пина
    myButtOK.tick(buttonValue < 750 && buttonValue > 730);

    if (myButtOK.isClick()) return; // return возвращает нас в предыдущее меню
    delay(10);
  }
}

/*
    The adjustLight void - функция настройки
    освещения. Включает выбор номера лампы,
    время включения и отключения.
*/
void adjustLight(void)
{
  Serial.println("Освещение");

  oled.clear();
  oled.home();
  oled.print("     Освещение");
  oled.update();

  while (1)
  {
    buttonValue = analogRead(BUTTON_PIN);  // получаем значение напряжения с аналогового пина
    myButtOK.tick(buttonValue < 750 && buttonValue > 730);

    if (myButtOK.isClick()) return; // return возвращает нас в предыдущее меню
    delay(10);
  }
}

/*
    The adjustWatering void - функция настройки
    полив. Включает выбор номера насосв,
    время включения и отключения.
*/
void adjustWatering(void)
{
  Serial.println("Полив");

  oled.clear();
  oled.home();
  oled.print("     Полив");
  oled.update();

  while (1)
  {
    buttonValue = analogRead(BUTTON_PIN);  // получаем значение напряжения с аналогового пина
    myButtOK.tick(buttonValue < 750 && buttonValue > 730);

    if (myButtOK.isClick()) return; // return возвращает нас в предыдущее меню
    delay(10);
  }
}

/*
    The settings void - фунция настройки
    кол-ва вентиляторов, ламп освещения,
    насосов для полива,текущих даты и
    времени.
*/
void settings(void)
{
  while (1)
  {
    static int8_t pointer = 0; // Переменная указатель для меню

    buttonValue = analogRead(BUTTON_PIN);  // получаем значение напряжения с аналогового пина

    myButtUP.tick(buttonValue < 170 && buttonValue > 130);
    myButtDOWN.tick(buttonValue < 350 && buttonValue > 310);
    myButtOK.tick(buttonValue < 750 && buttonValue > 730);

    if (myButtUP.isClick() or myButtUP.isHold()) {  // Если кнопку нажали или удерживают
      pointer = constrain(pointer - 1, 0, ITEMS_SETTINGS - 1); // Двигаем указатель в пределах дисплея
    }

    if (myButtDOWN.isClick() or myButtDOWN.isHold()) {
      pointer = constrain(pointer + 1, 0, ITEMS_SETTINGS - 1);
    }

    if (myButtOK.isClick()) // Нажатие на ОК - переход в пункт меню
    {
      switch (pointer) {  // По номеру указателей располагаем вложенные функции (можно вложенные меню)
        case 0:
          {
            while (1)
            {
              buttonValue = analogRead(BUTTON_PIN);  // получаем значение напряжения с аналогового пина
              myButtUP.tick(buttonValue < 170 && buttonValue > 130);



              if (myButtOK.isClick()) return; // return возвращает нас в предыдущее меню
              delay(10);
            }

            //break;  // По нажатию на ОК при наведении на 0й пункт вызвать функцию
          }
          //case 1: adjustAirflow(); break;
          //case 2: adjustLight(); break;
          //case 3: adjustWatering(); break;
          //case 4: settings(); break;
          //case 5: settings(); break;
      }
    }

    /* меню */
    oled.clear();           // Очищаем буфер
    oled.home();            // Курсор в левый верхний угол

    oled.print              // Вывод всех пунктов
    (F(
       "     Настройки  \n\r"
       "                \n\r"
       "  Лампы:        \n\r"
       "  Вентиляторы:  \n\r"
       "  Насосы:       \n\r"
       "  Дата:         \n\r"
       "  Время:        \n\r"
       "  Сохранить:    \n\r"
     ));

    printPointer(pointer + 2);  // Вывод указателя. На 2 строку устанавливаем указатель
    oled.update();          // Выводим кадр на дисплей

    if (myButtOK.isClick()) return; // return возвращает нас в предыдущее меню
    delay(10);
  }
}
