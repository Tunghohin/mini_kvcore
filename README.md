# mini_kvcore

基于跳表的键值储存引擎

## 支持的操作

----------

* ```insert(Key_type key, Val_type val);```插入 kv 对，时间复杂度$O(logn)$
* ```search(Key_type key);```查询 key 储存的值，时间复杂度$O(logn)$
* ```erase(Key_type key);```删除 key，时间复杂度$O(logn)$
* ```dump_file();```
* ```load_file```

base on https://github.com/youngyangyang04/Skiplist-CPP
