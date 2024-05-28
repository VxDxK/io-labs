# Лабораторная работа 3

**Название:** "Разработка драйверов сетевых устройств"

**Цель работы:** получить знания и навыки разработки драйверов сетевых интерфейсов для операционной системы Linux.



## Описание функциональности драйвера
Пакеты протокола UDP, содержащие конкретные данные (строку).
Вывести строку. Содержимое строки определяется исполнителями.

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
Для тестирования использовался [rup](https://github.com/svart/rup)

```
> ./rup server 0.0.0.0:13488
...

---

> ./rup client 127.0.0.1:1488
seq: 0 rtt: 700.466µs
seq: 1 rtt: 221.257µs
seq: 2 rtt: 422.489µs
seq: 3 rtt: 473.599µs
RTT statistics:
min = 221.257µs
med = 473.599µs
avg = 454.452µs
std_dev = 170.507µs
max = 700.466µs

```

```
[   38.444870] virt_net_if: loading out-of-tree module taints kernel.
[   38.444951] virt_net_if: module verification failed: signature and/or required key missing - tainting kernel
[   38.446549] Module virt_net_if loaded
[   38.446554] virt_net_if: create link vni0
[   38.446557] virt_net_if: registered rx handler for lo
[  252.688625] Captured IPv4 packet, source: 127.0.0.1, destination: 127.0.0.1
[  252.688908] Captured IPv4 packet, source: 127.0.0.1, destination: 127.0.0.1
[  253.689853] Captured IPv4 packet, source: 127.0.0.1, destination: 127.0.0.1
[  253.689971] Captured IPv4 packet, source: 127.0.0.1, destination: 127.0.0.1
[  254.691589] Captured IPv4 packet, source: 127.0.0.1, destination: 127.0.0.1
[  254.691804] Captured IPv4 packet, source: 127.0.0.1, destination: 127.0.0.1
[  255.692547] Captured IPv4 packet, source: 127.0.0.1, destination: 127.0.0.1
```