# Реализация межсетевого экрана :no_entry:
## Возможности:  
:heavy_check_mark: добавление правил  
:heavy_check_mark: удаление правил  
:heavy_check_mark: просмотр всех правил  
:heavy_check_mark: сокрытие модуля в системе  
:heavy_check_mark: обнаружение модуля в системе  

## Фильтрация сетевых пакетов по:  
:heavy_check_mark: IP-адресу источника/назначения  
:heavy_check_mark: порту источника/назначения  
:heavy_check_mark: доменному имени (также предусмотрен анализ пакетов в обе стороны)  
:heavy_check_mark: протоколу (TCP/UDP)  

## Задание правил
```c
   --hide                           Hide the module
   --unhide                         Show the module
   
-a --add RULE                       Add a rule
-d --del RULE                       Delete the rule

    -i --in                         Input
    -o --out                        Output
    -p --protocol                   Protocol = {TCP, UDP}
    
        --src_ip IP                 Source IP
        --src_port PORT             Source port
        --src_domain DOMAIN         Source domain name
        
        --dest_ip IP                Destination IP
        --dest_port PORT            Destination port
        --dest_domain DOMAIN        Destination domain name
        
 -A --all                           Show all the rules
 -h --help                          Available commands
```

## Загрузка/выгрузка
```c
sudo insmod fw_module.ko
sudo rmmod fw_module
```
> ВАЖНО: при выгрузке модуль должен быть виден в системе, т.е. если до этого он был скрыт, необходимо вызвать команду ```--unhide```
