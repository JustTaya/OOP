# Владислав Точаненко
### 1. Наскільки моделі є зрозумілими, наскільки вони описують предметну область, структуру та поведінку відповідної системи?
Моделі є достатньо зрозумілими, предметна область, структура та поведінка повністю описані. Присутні усі типи діаграм.
### 2. Чи є якісь аспекти, які видаються важливими, але не відображені в моделі (на діаграмах)?
На Package diagram є пакети, для яких відсутні класи на Class діаграмі. Також є пакет Bookmark system та відповідно функція bookmarkStory(), але закладки ніде не зберігаються.
### 3. Чи є в моделі щось зайве, якісь аспекти описані занадто детально?
На деяких Sequence діаграмах занадто багато alt елементів.  Можна було б зробити декілька Sequence діаграм і об'єднати їх на Interaction Overview. На Use Case діаграмі можна було б не вказувати віднаслідувані сценарії.
### 4. Наскільки доцільно використані різні типи діаграм?
Можна було б зробити Interaction Overview діаграму замість перевантажених Sequence діаграм. 
### 5. Наскільки коректно використана нотація UML, різні елементи та конектори?
Всі конектори зображені правильно. На State діаграмі над Final State написано стан. Краще було б зробити окремий стан, оскільки зазвичай над Initial Pseudo State та Finale State нічого не пишуть.
### 6. Наскільки вдалим є глосарій? Чи всі важливі поняття предметної області описано? Чи немає неоднозначностей?
Не всі важливі поняття описані, наприклад, щодо Medium Subscription Services.
### 7. Чи всі важливі сценарії використання описано в моделі? Наскільки зрозумілі різні сценарії, зв’язки між ними?
Всі важливі сценарії використання, що описують функціонал Medium присутні. Взагалом доволі зрозуміло.
### 8. Наскільки доцільним є поділ системи на частини/компоненти/модулі/...?
Поділ на модулі є доцільним. Щодо компонент, клас User надто перевантажений.
### 9. Наскільки доцільними є зв’язки між компонентами/класами/об’єктами? Чи немає занадто тісно зв’язаних компонентів?
На Class діаграмі клас Comment зв'язаний відношенням агрегації з класами User та Story, клас Story зв'язаний відношенням агрегації з класом User. Тобто у класа Comment є зайвий зв'язок з класом User.
### 10. Наскільки object-oriented design відповідає загальним принципам?
Клас User занадто перевантажений. Це є антипатерном God Object, якого варто уникати.