# For learning C++

当前 README 覆盖 `24`、`25`、`26` 目录，`Sort`、`Search`、`Small_Projects` 暂不纳入。

<details>

- [24](#24)
- [25](#25)
- [26](#26)

</details>

## 24

### 3
<details>

	11.cout / cin 输入输出
	13.int 运算与整除判断
	25.输出内容对齐
	25(2).string 比较与拼接
	25(3).bool 布尔类型

</details>

### 4
<details>

	1.指针基础
	1(2).二级指针
	2.函数指针基础
	3.函数指针调用
	3(2).函数指针作为参数
	10.数组与指针遍历
	10(2).结构体定义与初始化
	22.结构体的使用
	23.结构体数组
	24.结构体 + 一维数组
	24(2).结构体 + 二维数组
	24(3).结构体嵌套结构体
	25.结构体成员中的动态数组指针
	30.引用基础

</details>

### 5
<details>

	4.const 引用参数与默认参数
	12.函数重载
	15.结构体成员函数
	19.class 基础

</details>

### 8
<details>

	6.不定量输入求和
	30.动态数组的创建与释放
	31.rand / srand 随机数

</details>

### 11
<details>

	2.class 类与对象
	4.构造函数与析构函数
	4(2).拷贝构造函数
	4(3).初始化列表
	4(4).const 成员函数与 mutable
	4(5).const 成员函数链式调用与返回 const 引用
	4(6).static 成员变量
	5.友元函数
	5(2).友元类
	6.友元方式重载 `+`
	6(2).成员方式重载 `+`
	6(3).关系运算符重载
	6(4).全局方式重载 `<<`
	6(5).成员方式重载 `<<`
	6(6).下标运算符 `[]` 重载
	7.赋值运算符重载与深拷贝
	10.重载 `new` / `delete`
	10(2).内存池初步
	11.函数调用运算符 `()`
	11(2).前置 / 后置 `++` 重载
	11(3).继承基础
	12.继承与访问权限
	12(2).通过公有接口间接访问基类私有成员
	12(3).继承中的权限变化
	12(4).基类与派生类的构造 / 析构顺序
	12(5).利用对象内存布局突破访问控制
	17.继承中的构造
	17(2).名称隐藏
	17(3).作用域解析访问同名成员
	17(4).显式调用基类同名函数
	17(5).在子类中修改继承来的成员
	17(6).基类指针调用派生类非虚函数（静态绑定）
	17(7).多继承
	17(8).虚继承
	18.基类指针指向派生类对象与虚函数
	18(2).多态菜单示例
	18(3).非虚析构的风险
	18(4).虚析构函数
	18(5).纯虚函数与抽象类
	19.dynamic_cast 将基类指针转回派生类
	19(2).typeid
	19(3).auto 类型推导
	19(4).auto 推导函数指针
	19(5).函数模板基础
	21.类中的成员函数模板
	21(2).函数模板 `Swap`
	21(3).多参数函数模板
	21(4).函数模板重载

</details>

## 25

### 1
<details>

	1.auto 与模板参数推导
	2.decltype
	11.后置返回类型与 `decltype`
	11(2).类模板
	13.栈类
	13(2).栈类模板
	13(3).定长数组类模板
	14.变长数组类模板
	21-fileuot.ofstream 文件输出
	21-fliein.ifstream 文件输入
	27.文件打开与读写
	27(2).嵌套模板：模板栈 + 模板数组
	29.浅拷贝示例
	29(2).Fibonacci 递归
	30.嵌套模板类
	30(2).类模板具体化

</details>

### 2
<details>

	2.模板类继承普通类
	2(2).普通类继承模板类实例
	3.普通类继承模板类
	3(2).模板类继承模板类
	3(3).模板类继承模板参数指定的基类
	3(4).模板类作为函数参数和返回值
	3(5).仿函数调用
	3(6).模板类与友元
	4.约束模板友元函数
	4(2).非类模板约束的友元函数
	4(3).类模板中的成员类模板与成员函数模板
	4(4).线性表模板类与模板模板参数
	5.预定义宏
	5(2).条件编译指令
	5(3).命名空间基础与别名
	5(4).匿名命名空间与多命名空间
	5(5).类型转换总览与 `static_cast`
	6.`reinterpret_cast`
	6(1).`const_cast`
	6(2).string 容器构造与容量
	7.string 容器常用操作
	7(2).vector 构造函数综述
	8.vector 基础与 `data()`
	8(2).vector 赋值与 `assign`
	8(3).vector `push_back` / `pop_back`
	8(4).vector 存放自定义类型
	8(5).嵌套 vector
	9.迭代器基础
	9(2).正向迭代器
	9(3).`insert` 返回迭代器
	9(4).区间插入
	9(5).迭代器遍历与范围 for
	9(6).自定义类型与 vector 扩容 / 拷贝
	9(7).list 容器基础
	10.list 遍历与基本操作
	10(2).list 常用操作
	10(3).pair 键值对
	10(4).map 容器基础
	13.map 查找与下标访问
	14.unordered_map 基础
	16.unordered_map 的 bucket
	16(2).`max_load_factor`
	16(3).unordered_map 装载因子与扩容
	16(4).queue 容器
	16(5).`std::array` 多维数组 / 嵌套模板
	16(6).手写 `for_each`
	17.STL `for_each`
	17(2).STL `sort`
	17(3).`for_each` + 仿函数统计
	18.`unique_ptr` 基础
	18(1).`unique_ptr` 接管裸指针
	18(2).`unique_ptr` 作为函数参数
	18(3).函数返回 `unique_ptr`
	18(4).`unique_ptr` 移动赋值
	18(5).`get` / `release` / `move`
	18(6).全局与局部 `unique_ptr` 的生命周期
	18(7).`unique_ptr<T[]>` 管理数组
	19.`shared_ptr` 基础与引用计数
	19(2).`shared_ptr` 拷贝 / 赋值与计数变化
	19(3).自定义删除器
	19(4).`weak_ptr` 打破循环引用
	19(5).`weak_ptr` 循环引用结构定义
	19(6).`weak_ptr::lock()` 与过期判断
	20.二进制文件写入
	21.二进制文件读取
	21(2).随机存取：写入
	21(3).随机存取：读取
	21(4).随机存取：读写指针
	21(5).随机存取：定位与覆盖
	21(6).文本文件写入与缓冲刷新
	21(7).文本文件读取
	22.C++ 异常基础
	23.`nothrow` 与内存分配失败
	23(2).断言 `assert`
	23(3).`initializer_list`
	23(4).`const` / `constexpr` 与变长数组
	24.委托构造
	24(2).继承构造
	24(3).Lambda 表达式
	24(4).Lambda 捕获列表
	25.右值引用
	26.移动语义

</details>

### 3
<details>

	1.完美转发
	1(2).可变参数模板
	1(3).`chrono` 时间类型
	2.系统时间
	2(2).计时器 `steady_clock`
	2(3).创建线程
	13.线程 `join()`
	14.线程 `detach()`
	14(2).`this_thread::get_id()`
	15.`sleep_for` / `sleep_until`
	18.线程 `swap`
	18(2).线程移动构造
	18(3).`call_once`
	18(4).`native_handle`
	20.线程安全问题
	21.`volatile` 与线程安全误区
	23.互斥锁 `mutex`
	23(2).递归互斥锁 `recursive_mutex`
	23(3).`lock_guard`
	24.条件变量：生产者 - 消费者模型
	24(2).条件变量 + 互斥锁
	24(3).条件变量 + 超时等待
	24(4).原子类型 `atomic`
	24(5).原子类型的标准操作
	26.原子类型 `compare_exchange`
	26(2).可调用对象：普通函数
	26(3).可调用对象：仿函数
	26(4).可调用对象：成员函数

</details>

### 4
<details>

	1.六种可调用对象与 `std::function`
	1(2).`std::bind`
	1(3).绑定六种可调用对象
	2.函数包装与 `std::function`
	4.条件变量 + 回调函数注册
	5.条件变量 + 回调函数注册（版本二）
	7.用 `std::function` 取代虚函数
	14.左值 / 右值练习
	16.移动语义练习
	16(2).左右值转发练习
	16(3).回调函数练习
	16(4).成员函数回调绑定
	18.回调绑定
	18(2).回调注册与触发
	21.Lambda 捕获与 `mutable`
	22.Lambda 混合捕获
	22(2).Lambda 与仿函数对比
	23.仿函数对象
	23(2).滑动窗口最大值
	23(3).LeetCode 9 回文数
	23(4).LeetCode 1 两数之和
	24.前缀和 + 哈希判断零和子数组
	27.匿名对象示例

</details>

### 5
<details>

	1.基类 / 派生类函数调用与 `A::func`

</details>

### 7
<details>

	10.二叉树的创建、深度优先遍历、广度优先遍历

</details>

### 8
<details>

	18.LeetCode 13 罗马数字转整数
	18(2).LeetCode 14 最长公共前缀
	19.LeetCode 20 有效括号
	19(2).LeetCode 21 合并两个有序链表
	19(3).LeetCode 26 删除有序数组中的重复项
	19(4).LeetCode 27 移除元素
	19(5).KMP 实现 `strStr()`
	19(6).LeetCode 35 搜索插入位置
	20.LeetCode 58 最后一个单词的长度
	20(2).LeetCode 66 加一
	21.LeetCode 69 x 的平方根（牛顿法）

</details>

### 9
<details>

	3.LeetCode 70 爬楼梯（动态规划）
	8.LeetCode 88 合并两个有序数组（从后往前双指针）

</details>

### 10
<details>

	1.LeetCode 1518 换酒问题（模拟）
	19.LeetCode 94 二叉树中序遍历（框架 / 待补全）

</details>

### 12
<details>

	8.数组下标与指针的等价关系：`a[i]`、`*(a+i)`、`i[a]`

</details>

## 26

### 1
<details>

	_check_container_type.Iterable / StackLike / QueueLike concepts
	_container_modify.基于 concepts 的通用删除 / 弹出
	_my_deque.基于链表实现双端队列
	_my_link_list.双向链表模板
	_my_queue.基于链表实现队列
	_my_queue_with_deque.基于 Deque 的队列适配器
	_my_stack.基于链表实现栈
	_print_container.基于 concepts 的容器打印
	19.递归判断回文字符串（忽略大小写与非字母数字）
	25.SQLite3：建库、建表、prepared statement 插入与查询
	26.vector::end() 与尾元素访问
	28.C++20 concepts + 自定义容器 + 括号匹配 + 表达式求值
	30.自定义队列测试（当前示例接口与实现未完全对齐）

</details>

### 2
<details>

	11.vector 的 `insert` / `erase` 与迭代器位置变化
	12.`new A`、`new A()`、临时对象构造
	13.顺序存储二叉搜索树与遍历框架
	14.函数模板打印数组与 `string::size()`
	22.XOR Cipher 基础实现
	22(2).XOR 加密 + 二进制文件读写
	22(3).凭据文件格式设计、key 混淆与文件解析

</details>

### 3
<details>

	1.手写优先队列（堆）+ 急诊病人调度模拟
	8_0.双重散列哈希表
	8_1.二次探测哈希表
	8_2.SQLite3 基础操作：`sqlite3_exec` 与回调打印
	11.vector::insert 基本示例
	16.Skip List 跳表：查找、插入、删除

</details>

### 4
<details>

	6.红黑树插入与颜色修复（删除待实现）
	11.无向图 DFS / BFS：邻接表、邻接矩阵、发现边与非树边
	18.图的边分类：discovery / forward / back / cross edge

</details>
