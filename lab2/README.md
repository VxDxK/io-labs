# Лабораторная работа 2

**Название:** "Разработка драйверов блочных устройств"

**Цель работы:** Получить знания и навыки разработки драйверов блочных устройств для операционной системы Linux.

## Описание функциональности драйвера
Три первичных раздела с размерами 10Мбайт, 25Мбайт и
15Мбайт. Каждый записываемый байт должен возводиться в куб.

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
Информация о дисках:
```
vxdxk@hucpa:~/lab2 $ lsblk 
NAME                      MAJ:MIN RM  SIZE RO TYPE MOUNTPOINTS
sr0                        11:0    1 1024M  0 rom  
vramdisk                  251:0    0   50M  0 disk 
├─vramdisk1               251:1    0   10M  0 part 
├─vramdisk2               251:2    0   25M  0 part 
└─vramdisk3               251:3    0   15M  0 part 
vda                       252:0    0   15G  0 disk 
├─vda1                    252:1    0    1M  0 part 
├─vda2                    252:2    0  1.8G  0 part /boot
└─vda3                    252:3    0 13.2G  0 part 
  └─ubuntu--vg-ubuntu--lv 253:0    0   10G  0 lvm  /
```

```
vxdxk@hucpa:~/lab2 $ sudo fdisk -l /dev/vramdisk
Disk /dev/vramdisk: 50 MiB, 52428800 bytes, 102400 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x36e5756d

Device         Boot Start   End Sectors Size Id Type
/dev/vramdisk1          1 20480   20480  10M 83 Linux
/dev/vramdisk2          1 51200   51200  25M 83 Linux
/dev/vramdisk3          1 30720   30720  15M 83 Linux
```

### Запись на диск
```
vxdxk@hucpa:~/lab2 $ echo "some dumb shield" | sudo dd of=/dev/vramdisk
0+1 records in
0+1 records out
17 bytes copied, 0.000325956 s, 52.2 kB/s
vxdxk@hucpa:~/lab2 $ sudo hexdump -C /dev/vramdisk
00000000  eb 4f b5 9d 00 40 4d b5  88 00 eb 00 f9 9d c0 40  |.O...@M........@|
...
```
