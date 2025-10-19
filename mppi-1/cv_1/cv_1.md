## Návrh aplikácie v jazyku assembler / Разработка приложения на языке ассемблера
### Cvičenie č. 1 / Упражнение №1
Všetky odpovede na otázky vložte ako komenty do vášho kódu (znak „;“ pred textom), ktorý si na konci cvičenia uložíte. Na začiatok kódu vložte vaše meno.
> Все ответы на вопросы вставьте в свой код в виде комментариев (символ `;` перед текстом). В начале кода укажите своё имя.

#### 1.
Preštudujte si zapojenie užívateľských LED diód D1 a D2 na vývojovej doske MSP-EXP430G2ET. Použite súbor „MSP-EXP430G2ET LaunchPad™ Development Kit slau772a.pdf“ z adresára „MPP_dokumenty,liter“.
Odpoveď: LED dióda D1 (zistite jej farbu) je pripojená na pin portu P1.?, LED dióda D2 ...

> Изучите схему подключения пользовательских светодиодов D1 и D2 на отладочной плате MSP-EXP430G2ET. Используйте файл «MSP-EXP430G2ET LaunchPad™ Development Kit slau772a.pdf» из каталога «MPP_dokumenty,liter».

> Ответ: Светодиод D1 (укажите его цвет) подключён к выводу порта P1.?, светодиод D2 ...

#### 2.
V prostredí CCS vytvorte nový projekt typu „assembly only“. Do vygenerovaného súboru main.asm vložte inštrukcie z priloženého súboru main_zdroj.asm. Skontrolujte funkčnosť na doske.
Odpoveď: Čo robili LED diódy?

> В среде CCS создайте новый проект типа «только ассемблер». Вставьте инструкции из файла main_zdroj.asm в main.asm и проверьте работу на плате.

> Ответ: Что делали светодиоды?

#### 3.
Nájdite v zdrojovom kóde direktívy “.text” a “.sect ".reset"”. Otvorte súbor “lnk_msp430g2553.cmd” a zistite adresy, na ktoré odkazujú.

> Найдите в исходном коде директивы “.text” и “.sect ".reset"”. Откройте файл “lnk_msp430g2553.cmd” и определите адреса, на которые они ссылаются.

#### 4.
Otvorte okno „Disassembly“ a zistite adresu, na ktorej program začína. Otvorte „Memory browser“ a zistite hodnotu uloženú na adrese vektora resetu. Ako súvisia tieto hodnoty so súborom “lnk_msp430g2553.cmd”?

> Откройте окно «Disassembly» и узнайте адрес, с которого начинается программа. В «Memory browser» найдите значение по адресу вектора сброса. Как связаны эти значения с содержимым файла “lnk_msp430g2553.cmd”?

#### 5.
Použite krokovanie programu a sledujte register R15, kým nedosiahne nulovú hodnotu. Sledujte zmenu stavu LED.
Odpoveď: Keď hodnota v registri dosiahla nulu a vykonala sa inštrukcia (doplniť), LED D(?) ...

> Используйте пошаговое выполнение программы и изменяйте значение регистра R15, пока оно не станет нулевым. Отслеживайте момент изменения состояния LED.

> Ответ: Когда значение регистра стало нулевым и выполнилась инструкция (указать), светодиод D(?) ...

#### 6.
Nastavte „Breakpoint“ ku inštrukcii „jmp Mainloop“ a sledujte správanie LED po viacerých spusteniach programu.
Odpoveď: LED dióda D(?) po každom spustení programu ...

> Установите «точку останова» перед инструкцией „jmp Mainloop“ и наблюдайте поведение светодиодов при нескольких запусках.

> Ответ: Светодиод D(?) при каждом запуске программы ...

#### 7.
Upravte program tak, aby blikala aj druhá LED – najprv súbežne s pôvodnou. Pôvodnú inštrukciu zakomentujte a pod ňu vložte novú.

> Измените программу так, чтобы мигал и второй светодиод — сначала одновременно с первым. Старую инструкцию закомментируйте и под ней напишите изменённую.

#### 8.
Upravte program tak, aby LED blikali striedavo.

> Измените программу так, чтобы светодиоды мигали попеременно.


#### 9.
Upravte program tak, aby LED blikali približne 2-krát rýchlejšie.

> Измените программу так, чтобы светодиоды мигали примерно в 2 раза быстрее.


#### 10.
Upravte program tak, aby LED blikali 2-krát pomalšie. Okómentujte doplnený kód. Aký problém ste zaznamenali?

> Измените программу так, чтобы светодиоды мигали в 2 раза медленнее. Прокомментируйте добавленный код. С какой проблемой вы столкнулись?

🧾 **Odovzdanie / Сдача работы:**
Elaborát odovzdajte v tlačenej alebo elektronickej forme (USB) na nasledujúcom cvičení.
> Работу сдайте в печатном виде или на USB-носителе на следующем занятии.

**Hodnotenie / Оценивание:**
* 0,5 bodu – len odovzdaný kód bez vedomostí / только сдача кода без понимания;
* 2 body – s dostatočnými vedomosťami / при достаточных знаниях;
* Prezentácia témy v jazyku C – 3 body / презентация на C – 3 балла;
* Testy – 12 a 13 bodov;
* Celkom 50 bodov + bonusy za aktivitu / всего 50 баллов + бонусы за активность.
