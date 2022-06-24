# mini_kvcore

基于跳表的键值储存引擎

## 支持的操作

----------

| 接口 | 功能 | 时间复杂度   | 返回值类型          |
|---|---|---------|----------------|
| ```insert(Key_type key, Val_type val);```  | 插入 key-val 对  | ```O(logn)``` | ```void```     |
|  ```search(Key_type key);``` | 查询 key 储存的值  | ```O(logn)```        | ```Val_type``` |
| ```erase(Key_type key);``` | 删除 key | ```O(1)```   | ```void```              |
| ```size()``` | 获取跳表中 key-val 对数量 |  ```O(1)```       | ```int```          |
| ```get_level()``` | 获取当前跳表最高索引层高 | ```O(1)```       | ```int```              |
| ```dump_file();``` | 从内存保存数据进外存 | ```O(n)```       | ```void```              |
| ```load_file()``` | 从文件读数据进内存 | ```O(nlonn)```       | ```void```              |
