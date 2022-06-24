# mini_kvcore

众所周知，非关系型数据库redis其核心存储引擎的数据结构就是跳表。

mini_kvcore是基于跳表的轻量级键值储存引擎。
支持泛型，key值支持任何可比较的对象。

## 支持的操作

----------

| 接口 | 功能 | 时间复杂度   | 返回值类型          |
|---|---|---------|----------------|
| ```insert(Key_type key, Val_type val);```  | 插入 key-val 对  | ```O(logn)``` | ```void```     |
|  ```search(Key_type key);``` | 查询 key 储存的值  | ```O(logn)```        | ```Val_type``` |
| ```erase(Key_type key);``` | 删除 key | ```O(logn)```   | ```void```              |
| ```size()``` | 获取跳表中 key-val 对数量 |  ```O(1)```       | ```int```          |
| ```get_level()``` | 获取当前跳表最高索引层高 | ```O(1)```       | ```int```              |
| ```dump_file();``` | 从内存将数据写入文件 | ```O(n)```       | ```void```              |
| ```load_file()``` | 从文件读数据进内存 | ```O(nlogn)```       | ```void```              |
