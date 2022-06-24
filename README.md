# mini_kvcore

基于跳表的键值储存引擎

## 支持的操作

----------

* ```insert(Key_type key, Val_type val);```插入 key-val 对，时间复杂度 $O(logn)$
* ```search(Key_type key);```查询 key 储存的值，时间复杂度 $O(logn)$
* ```erase(Key_type key);```删除 key，时间复杂度 $O(logn)$
* ```size()```获取跳表中 key-val 对数量
* ```dump_file();```从内存保存数据进外存
* ```load_file()```从文件读数据进内存
