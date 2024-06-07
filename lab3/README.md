# Лабораторная работа 3

**Название:** "Разработка драйверов сетевых устройств"

**Цель работы:** получить знания и навыки разработки драйверов сетевых интерфейсов для операционной системы Linux.

## Описание функциональности драйвера
Пакеты протокола UDP, содержащие конкретные данные (строку `this packet`).
Вывести строку.

Состояние разбора пакетов необходимо выводить в кольцевой
буфер ядра.

## Инструкция по сборке
- `make` - собрать модуль
- `make load` - загрузить модуль
- `make uload` - выгрузить модуль
- `make lcheck` - проверить загружен ли модуль
- `make clean` - очистить сборочную директорию

## Инструкция пользователя
1. `make` - сборка модуля
2. `make load` - загрузка модуля
3. Драйвер готов к работе


## Примеры использования
Для тестирования использовался `netcat` (a.k.a `nc`)

Сервер:
```
vxdxk@hucpa:~ $ netcat -u -l -p 1337
lol just package
lol package with this packet
```

Клиент:
```
vxdxk@hucpa:~ $ netcat -u localhost 1337
lol just package
lol package with this packet
```

Логи драйвера:
```
vxdxk@hucpa:~/lab3 $ sudo dmesg
[  254.653537] virt_net_if: loading out-of-tree module taints kernel.
[  254.653629] virt_net_if: module verification failed: signature and/or required key missing - tainting kernel
[  254.655292] Module virt_net_if loaded
[  254.655296] virt_net_if: create link vni0
[  254.655299] virt_net_if: registered rx handler for lo
[  350.296619] Captured IPv4 with UDP packet, source: 127.0.0.1:51845, destination: 127.0.0.1:1337
                 data length: 29, data: lol package with this packet

```