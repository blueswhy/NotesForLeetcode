## C++ Prime 5th Edition

*Written For C++11 Standard, Sranley B.Lippman, Josee Lajoie, Barbara E.Moo*

### Preface

#### C++11年标准

1. 语言标准化，更容易学和上手；

2. 标准库使用起来更简单，安全，提高使用效率；

3. 写有效率的抽象概念和库函数时更简单。

#### Why Read This Book?

现代C++需要理解以下三部分：

1. low-level更底层的语言，很多语言习惯和模式直接继承C语言。C++面向对象（更严格的定义是面向过程和面向对象的混合型语言），C语言面向过程，相对而言，C++中使用的成型库更多，定义的原始数据类更灵活，拥有class这个数据类型可以将各个对象实例化；
2. 高级语言的特点是允许程序员自定义类型，实现大规模项目和系统的编程；
3. 使用以上高级特点的标准库可以提供更有用的数据结构和算法。

 这本书在介绍C++的时候先忽略其作为C语言衍生所具备的底层编程的特点，先介绍C++面向对象时的方便性。举个例子，先介绍string和vector在矩阵类型运算的优势，然后再引申到传统的指针上来。本书的一大特点是不仅仅告诉怎么做，还要让读者明白为什么这样做。这样不仅了解了语言这门工具，对计算机也有更深入的理解。

#### Structure of This Book

* 第一部分和第二部分讲解，C++语言中的基础知识，需要熟练掌握（注意其中的抽象数据类型）；

* 第三部分和第四部分开始教你如何创造自己的抽象类，前者是基础知识，后者是特殊功能介绍；

* 每小节后都有对本节内容的总结，读者应当以该总结为参考复习所学知识，巩固学习成果。建议看该整理文档的同学，结合原著中的总结，如果有发现整理文档中未提及的知识，到原著中找相关知识。当然，直接看原著在理解C++方面是最好的选择。

#### Getting Started

*介绍C++中最基本的元素：类型type、变量var、表达式exp、语句statement和函数func。最后简单介绍电脑是如何编译和执行一段代码的。*

以图书管理为例，实现该目的需要以下步骤：

* 定义变量，价格、书的数目、书的名字、书的ISBN/书号；
* 输入和输出过程；
* 定义书这个数据结构囊括以上书的固有属性；
* 测试书库中书号能不能作为唯一标识，即有没有两个书号相同的实例；
* Loop，在日志文件（Transaction File）中包含处理的详细记录。

##### 函数定义

返回值类型，函数名，参数表，函数主体。C++和C相同，每一句执行完毕需要分号;，否则会有编译问题。

```c++
int func_myplus(int a, int b)   // defination
{

      return a+b;  //statement

}
```

##### 函数的编译和执行

大多数PC编译器依赖于集成开发环境（IDE，intergrated development environment)。自带有bulid和analysis工具的编译器。

一般我们编写的是源文件（source files），后缀经常为.cc，.cxx，.cpp，.cp，.C表示为C++文件。

使用命令行接口编码时，一般在一个console window中编译代码，编译过程：prog1.cc->\$ CC prog1.cc->prog1.exe->\$ prog1（\$表示系统标识符）。在有些系统中需要指明编译文件和可执行文件的存储位置，此时可以打上\$ .\prog1创建一个路径（不同系统中符号的指示有所不同）。

C++语言中的输入输出一般使用<iostream>这个头文件，指的是字节流输入输出。

```c++
#include <iostream>
using namespace std;
int main()
{
    cout << "Please enter two integers:" << endl;
    /*op << left-hand is an ostream object;the right-hand is a value to print.
     *endl as a manipulator, which has the effect of ending the current line 
     *and flushing the buffer.
    */
    int a = 2, b = 4;     // default value.
    cin >> a >> b;        // input two numbers gapped by space or enter
    cout << "The sum of " << a << " and " << b
        << " is " << a + b << endl;
    return 0;
}
```

* namespace相当于一个类对象，如果用using直接声明就可以用cin来直接代替std:: cin更方便一些。命名空间这种调用方式可以有效避免重名冲突，所有和标准库函数有关的名字都在std 命名空间内。但是当两个库里有同一种变量名时，为避免冲突，需要在变量前加上相应的命名空间。而函数或者变量加双冒号，是为了限制相应对象的作用域。
* cin在执行过程中不加endl，当碰到字节流中的不合法输入或者字节流的终止符时，会停止。一般情况下，Ctrl+z或者enter或return属于终止符，在UNIX系统中Ctrl+d是终止符。
* cerr用来反馈系统的警告和错误信息，clog用来翻译在执行代码时产生的日志文件。
* 一般变量，初始化带上初值。不过和C比起来，定义更灵活，不一定必须在开头定义。
* //用来区分一行的comment，/* \*/用来区分注释块。为了格式更整齐，写注释块时在分行过程中在每一行开头加上\*。注释块不要嵌套使用，打一层注释一般就足够了。
* free-format。机器读代码的时候不注重格式，但是为了代码的可读性，还是选择一种固定的写作模式，并坚持下去。C++允许不同的格式，但是对每个编码者而言，最好只选择一种是适合的。

##### Flow of Control

一般情况下，语句是串行执行的。为了避免重复语句的书写，定义一些控制流语句。

* while语句：在满足条件的情况下执行循环体。格式如下。

  ```c++
  int val = 0, sum = 0;      // 在循环体外部定义初值
  while (val <= 10){
      sum += val;             // 执行计算
      ++val;                  // 控制循环次数，防止死循环
  }
  ```

* for语句。初值，循环次数，循环体都有定义。

  ```c++
  for (int val = 1, sum = 0; val <= 10; ++val)
      sum += val;
  ```

* 编译只是识别出代码中的语法错误，对于代码是否按照原理实现，编译器无法探测，这项工作需要编码者用debug来探究。一个语义错误会引起一系列错误。遵守规则：edit-complie-debug。

* 条件语句，if else。作二分法判断分支。

##### class

对一个类而言，可以有属性，也可以有相应的类函数。为了方便，将特定的类存在头文件中。当引用的时候使用特定的头文件即可（后缀有很多，.h，.hpp，.hxx等。）每个类的名字就是其定义变量的type。本部分先不介绍class的定义，简单介绍其使用。当定义相应的方法之后，可以利用符号=,+等实现相应的操作。一般需要定义赋值、加、输入输出。

调用属性时可以直接用Item1.isbn调用（即dot表示从属关系），类函数也可以这样调用。

### Part 1:  The Basics

C++语言中增加了面向对象这一特点，对象的类型决定了可以对该对象进行的操作，也决定了包含该对象的语句是否合法。和python、Smalltalk这些面向对象的语言相比，它们是一边执行一边确认对象类型，而C++则是将对象的类型静态定义好，在编译过程中检查确认（因此对对象的定义更繁琐一些）。对于非面向对象的语言来说，只能用struct语句将语言内部的build-in类型拼凑成一个新的结构体类型，但是面向对象在定义时还可以增添新方法，使用起来和那些bulid-in类型一样方便。

#### 1.1. Variables and Basic Types

##### 1.1.1. Primitive Built-in Types

* void，空值类型。一般用于定义那些不需要返回值的函数（但是一般可以通过指针传参）。
* 算术型变量。从C继承来(下面用bit区分），包括int(16 bits)，long(32 bits), long long(64 bits), short(16 bits), float(32bits)，double(64 bits), long double(128 bits), bool, char(8 bits), wchar_t(16 bits), char16_t(16 bits), char32_t(32 bits)。8 bits ——1 byte（占位一个地址空间）, 4 bytes——1 word。为了区分正负，用signed和unsigned加以区分整数型变量（相应地表示的数据范围有所不同）。
* char和bool型变量不属于正统的算术型，在算术型表达式中不要使用。以bool型变量b1、b2为例，已知b1=true，然后赋值b2 = -b1，最终返回结果b2依然为true。因为遵循的是非空即真、非零即真原则，b2赋值过程中，先是把b1转换为整型常量1，赋值-1返回给b2，b2再进行类型转换为bool型对应true。
* 虽然大部分书上定义int是16bits，但是实际上很多系统已经将int改成32bits和long类型没有区别了。
* 类型转换，包括强制转换、自动转换、**隐式转换**。低bit向高bit转换，但是不能超过变量本身的范围。如果int i= 3.14, 那么i就是3, 小数部分被省去。当有正负数限制时，先都转换成无符号类型，再进行计算。
* 对于整数而言，20是十进制，020是八进制，0x20是十六进制。-42在赋值时，-不是直接赋值到42上成为一个复数的，而是经过运算0-42再赋值给变量的。
* 转义字符+字母得到输出格式，\n 换行符，\t, 水平制表符tab, \v 纵向制表符等。或者用\\+数字表示ASCII码，转义字符至多解释数字中的前三位。
* 字符前缀。u(char16_t)，U(char32_t)，L(wchar_t)，u8(char)。
* 字符后缀。u/U(unsigned)，f/F(float)，l/L（long double for float and long for int)，ll/LL(long long)。

##### 1.1.2. Variables

* C++中的对象：定义完毕之后赋给一个地址空间，存放其类型和数据。定义是按照从左至右进行的。对于变量的初始化和赋值是分开进行的。初始化是指变量在被创建的时候赋予其初值，而赋值是指删去已存在变量的当前值，替换为新值。
* Default Initialization。如果在定义变量的时候没有赋初值，系统会默认初始化，此时初始化的值取决于变量类型和变量的地址。而一些特殊变量，如string，如果没有初始化，默认为空字符串。养成定义即初始化的好习惯。
* 一个变量在使用过程中只能定义一次，但是可以被声明很多次。由于C++是一种静态类型语言，在使用一个变量之前必须声明，让系统知道其类型。系统在编译过程中会做类型检查，如果做了类型不允许的事情，编译器就会返回错误信息不生成可执行文件。
* 变量名不能和C++中的keywords重名，但是可以以类型_变量名来命名，最好能自己掌握一套命名法则，在起名字的过程中可以省去很多时间。
* 考虑函数域变量域，对象定义最好在对象刚用的地方。如果在函数外部和内部都定义了相同的变量名reusedVar，一个是全局变量reusedVar，另外一个为局部变量reusedVar。在函数内部调用时，在变量名前面加两个冒号::reusedVar表示全局变量，否则为局部变量。

###### 命名规则

常用的命名方法有：驼峰命名法、匈牙利命名法、帕斯卡命名法、下划线命名法。

**驼峰命名法**： printEmployeePaychecks()。用大小写字母来作逻辑断点区分，但是首字母小写。

**帕斯卡命名法**：PrintEmployeePaychecks()。命名规则与驼峰类似，但是首字母大写。

**下划线命名法**：print_employee_paychecks()。C语言常用，用下划线标识逻辑断点。

**匈牙利命名法**： m_lpszStr(一个指向0字符结尾的字符串长指针成员变量)。Miscrosoft Windouws常用。在变量名前加上小写字母作为前缀，标识变量的作用域类型等，m就代指members。后续指明变量的用途。lp指示是长指针，sz表示结尾为0，Str指的是字符串。

* 一般函数命名用上述前三种方式，变量命名用匈牙利命名法则。

* **标识符**命名要清晰、明了。尽量选用全英文增加可读性，公认缩写有，temp->tmp, flag->flg，statistic->stat，increment->inc，message->msg。
* 若有特殊缩写要有注释说明，或者用一种头文件来封装变量名。
* 保证特有的命名风格，自始至终保持一致。整个项目组的风格也要统一。
* **变量**命名中，禁止取单个字符。i,j,k只有作为局部循环变量才被允许。因为局部变量在敲写时，很容易因为单个而打错，最后检查错误时而废掉不少时间。
* 尽量不用数字或者奇怪的字符来定义标识符。
* 为了防止不同文件中的变量引起冲突，可以在起名的过程中在变量名前加上 相应模块 标识。
* 常见英文标识。add-remove，begin-end，creat-destroy，increment-decrement，insert-delete，fist-last，get-release，put-get，lock-unlock，open-close，min-max，old-new，start-stop，next-previous，source-target，show-hide，send-receive，source-destination，cut-paste，up-down。
* 变量命名中的开头映射法则。bool-b，int-i，short int-n，char-c，unsigned char -by，float-f，double-d，unsigned int(WORD)-w，unsigned long int(DWORD)-dw，string-s，sz-结尾为0的字符串。
* **指针**命名。基础为p(point)，然后在后面加约束项。pf->float*型指针变量，pp->二重指针。
* 全局变量g_varType_varName。静态变量s_varType_varName。
* 枚举变量用EM作前缀，要求全部变量大写。
* struct或者union类型开头大写S或U。常量一般也全部大写，多个单词时用_连接。
* **函数名**长度不得少于8个字母，动词在前，名词在后。避免使用无意义的动词（不是process、handle而是get，delete这样更具体的操作）。
* **函参**命名参照变量命名。为了提高程序运行效率，应当使用指针或者引用方式传递大结构的参数，减少参数占用的堆栈。
* 为了便于其他程序员识别指针参数属于输入参数或者输出参数，应该在输入参数（input)前加上const标志。
* **文件名**命名要求长度不超过5个字母，禁止出现file1或者myfile这样的文件名。

##### 1.1.3. Compound Types

C++中有很多复合类型，这里介绍两种地址符&（reference)和指针标识*。

* 使用**地址**符来初始化变量时，实际上是将两个变量绑定在一起，因为两个变量的地址是相同的，地址中存放的值发生变化，两个变量的值都会发生变化。地址符在绑定过程中只能在初始化过程中实现，无法在后续赋值改变地址。换一种说法，地址符只是对已经存在的对象起的另外一个名字，用来调用。引用变量本身不是一个对象，初始化后就无法改变。
* 不允许直接将引用变量赋值一个确定性地址，只能是已经分配地址的实际对象。
* 由于一个地址中存放的不仅有值还有数据类型，地址赋值时类型必须和原变量一致。
* **指针**同样是指向地址的变量，但是指针使用起来更灵活。在其生存周期中，可以多次赋值，指向不同地址。指针也不需要在定义过程中初始化赋予初值。但是由于指针的这种灵活性，在调试过程中会引起很多困扰。
* 初始化过程中，进行指针赋值时，前面要加*标识（以一级指针\*p为例)，p表示指向特定地址。定义完毕后，直接使用变量p是对指针赋值，带上\*表示对p当前所指地址的值进行赋值。指针在赋值过程中，也要遵从类型一致性。
* 空指针。有三种表达方式，nullptr，0，NULL。因为非初始化的指针会在不经意间出错，对所有的指针进行初始化，不知道指向哪的时候，可以赋值空指针。在使用链表数据结构时，经常用空指针来表示结尾。当使用条件语句判断时，利用if (p->next)表示指针是否到达链表结尾。
* void \*pv, 空指针。pv同样可以指向任何对象的地址，但是地址存放的对象的类型是未知的。因此，对于一个空指针，我们只能进行指针操作（指针比较，传递参数，赋值给void\*指针），无法取其中的值。
* 书写过程中不建议 int\*  p这种写法，写成int  \*p，因为\*这个标识符作用的是p而不是int。
* \*\*定义指向指针的指针，\*\*\*定义指向二级指针的指针。在理解复杂指针结构时，从右向左来理解会更简单。

##### 1.1.4. Const Qualifier

常数变量用于定义一些使用过程中不发生改变的对象，比如数组的长度 iBufSize。对于一个本地常数变量而言，在其域中无法赋值，必须在定义过程中初始化。常数变量使用过程中最重要的约束是，操作不能改变常数变量对象（包含地址和数值）。常数变量作为等号右边只是提取值，不会被改变。

* 一个常对象是对应文件中的本地不变量。const只是对变量的作用域作出规定，不改变其类型。

* 如果在多个文件中共用一个const对象，需要借助extern。

  ```c++
  // In file_func1.cpp
  extern const int iBufSize = 512;
  // In file_func1.h
  extern const int iBufSize;
  ```

  其中，在cpp文件和头文件中都对iBufSize进行了常变量声明，在cpp中对常变量进行了初始化，extern表示允许其他文件共用iBufSize变量。而在头文件中，extern表示iBufSize不是本地变量，允许在其他文件中对其定义/声明。

* 对于一个引用变量而言，加const和不加const其实在使用上没有影响。因为C++中引用变量本身就无法在初始化后被改变，相当于一个常变量，只不过不是一个具体对象。但是当想要定义一个指向常变量的引用变量时，在书写规则上必须加上const标识。

* Pointers and const。和引用变量类似，定义一个指向常变量的指针时也要加const约束。此时该指针只负责存储对应常变量的地址，const限定的是地址中所存的值无法发生改变。即const指针可以指向非const同类型变量，只要不通过该指针改变对应变量的值。不过这和const所加的位置也有关系，Pointers and const 和const Pointers是不同的。

  ```c++
  double pi = 3.14;
  const double *cdptr = &pi;   // cdptr points to pi, but can not change pi.
  double *const dcptr = &pi;   // dcptr always points to pi, can change pi by it.
  const double *const cdcptr = &pi// can not change value and always point to pi.
  ```

* 扩展constexpr：常语句。常语句一般用来声明常变量，在constexpr约束下的变量自动为常变量，而且只能通过常语句（常函数，常变量）进行初始化。

  ```c++
  const int *ciptr = NULL;   // ciptr is a pointer to const int
  constexpr int *ceiptr = NULL; // ceiptr is a const pointer to int
  ```

##### 1.1.5. Dealing with Types

* typedef。当一个类型过长的时候，可以用typedef加以别名简写。对于一个数据结构而言，可以使用using进行简写，using SI = Sales_Item。
* auto。在一个巨大的工程中，想要知道一个具体的变量的类型不简单。利用auto可以让编译器通过表达式推断出未知类型变量的类型。auto相当于一次初始化，所以只能对非定义变量使用。
* decltype。利用decltype中的表达式或者函数来对变量的类型进行推断，但是该表达式不参与变量初始化。编译过程中，只查看表达式返回值的类型，不执行表达式，将其类型赋给相应变量。decltype((var))指的是指向var的引用变量代表的类型，返回类型一定包含引用。

##### 1.1.6. Defining Our Own Data Structure

首先用结构体定义基本数据结构如下。

```c++
struct Sales_data{
    std::string sBookNo;
    std::string sBookName;
    unsigned wUnitSold = 0;
    double dRevenue = 0;
};     // Warning: don't forget the semicolon at the end of a class definition.
```

而后创建一个关于以上数据结构的一个类。为了将类函数限定在一个文件内，一般将一个类的属性和方法放在一个头文件中。在C++中头文件是允许被编译多次的，因此源文件用到的头文件一定都要引用重新编译，从而得到那些新的或者被改变的声明，但是其中的一些变量可能被重定义多次而报错。为了防止这种错误，使用#ifndef-#define-#endif方法，防止定义错误。对于头文件而言其中的 \. 要转换成 \_ 。

#### 1.2. Strings, Vectors and Arrays

本部分介绍一些基本数组类型，相应的变量不再仅仅包含一个数据，而是一个集合。其中string和vector是原始的数组类型，一个用来存放字符，一个用来存放数，而且都是可变长度的。

##### 1.2.1. Namespace Using Declarations

函数库中的变量名为了区分和显示含义，一般变量名会很长，直接引用会显得很臃肿。因此将这些长变量名以假名的方式放在相应的命名空间内，使用时直接引用变量空间中的假名就行。

* 如果只有一个命名空间，其空间名如std可以省略，但是如果有两个时，最好加上指代具体的命名空间，防止出现重名导致编译出错。这一点和python中import类似。
* 头文件中尽量不要使用using。因为一旦引用了头文件，表示也用了其中的命名空间，有时可能出现无法预料名字冲突。

##### 1.2.2. String

```c++
#include<iostream>
using std::string
string s1;         // s1 is an empty string.
string s2("value");// equivalent to s2 = "value".
string s3 = s1;    // Initialize s3 and s3 = s1.
string s4(n, 'c'); // Initialize s4 with n copies of the char 'c'.
```

* 上述初始化过程中，等号为复制初始化，括号为直接初始化。
* 关于字符串处理，有以下基本函数。字符串比较时先看前面字母排序再看长度，相当于字典排序。

```c++
os << s; //return os:write s onto output stream os.
is >> s; //return is:reads whitespace-sperated string from is into s.
getline(is, s);//return is:reads a line of input from is into s.
s.empty();//return true if s is empty.
s.size();// numbers of characters in s.
s[n]; // return a reference to the char at position n in s.
s1 + s2; //return a string that is the concatenation of s1 and s2.
s1 = s2; //replace s1 with a copy of s2.
s1 == s2; // return true when s1 and s2 are the same.
<,<=,>,>=;// comparisions are case-sensitive and use dictionary ordering.
```

* 使用cin对字符串赋值时，输入空格，换行符，制表符都会使得输入终止。因此可以采用while循环的方式。只有当输入不合法或者结束标志Crtl+z时，才会结束输入。使用getline()函数可以直接将空格给定到变量中。

```c++
string word;
while (cin >> word)
    cout << word << ' '<< endl;
while (getline(cin, line))
    if(!line.empty())
        cout << line << endl; //stop lpop if input an empty line or end-of-file
```

* 使用+号时，至少有一个是string类型，不能全部都是原始字符串。
* 清除输入缓冲区。while ((c = getchar()) != ‘\n’)。
* 如果要对字符串中的某个字符进行处理，引用cctype头文件。在C++中，为了合并C的一些功能，一些专属于C的头文件依旧使用.h的格式。而对于C++而言，新使用的头文件不再加后缀.h表示其头文件属性，而是在文件开头加上一个c字母作为标识。
* 为了遍历字符串中的字符，结合for循环使用range for函数。

```c++
for (auto c：s)
    cout << c << endl;
```

* 取数组元素，利用引用变量s[n]即可。若用该方法遍历，必须确认n在s.size()的范围中。

##### 1.2.3.Vector

向量是一群有着相同类型的对象的动态有序集合，每个对象都有对应的下标。为了使用vector类型，需要作相应函数库调用如下。vector是一个类模板，而模板（template)本身不是一个函数或者类，被当作编译器用来生成类或者函数的一系列指令（或者看作是抽样函数的实例化）。因此在使用vector过程中，一定要指明类型。

* 初始化。vector之间用=赋值时，两边变量的类型必须相同。注意{}和()的区别。

```c++
#include <vector>
using std::vector;
vector<int> ivec1;                 // empty vector
vector<Sales_item> vecSales;
vector<vector<string>> vecFile;
vector<int> ivec2(ivec1);          // equivalent to ivec2 = ivec1
vector<int> ivec3(n, val=0);       // ivec3 has n elements with value val=0.
vector<int> ivec4{i1, i2, i3 ...}; // ivec4 is intialized by the sequence of i1, i2...
vector<string> svec1{10}
```

* 对于string变量svec1而言，10作为1个整型变量，不是字符串，不能直接编译。此时编译器就会自动将代码合理化，认为是在创建含有10个字符串变量的vector。将{}当作()用。
* vector元素过多，初始化不能直接以可列数据写显得很笨重，利用push_back（）函数。

```c++
vector<int> ivec2;
for (int i = 0; i <= 100; i++)
    ivec2.push_back(i);
```

* 除非规定所有元素需要一个特定大小来约束，一般不要给vector定义大小。常用方法是，初始化一个空vector，然后在逐个添加元素。不过目前C++而言，即使初始化规定了vector的大小，其大小依然可以通过push_back()来改变。
* 如果循环体对vector中的元素有删除，增加等操作影响了变量的大小，不能使用for range对vector变量进行遍历。可以按照指针来。
* 使用vector[n]方式访问向量元素时，元素必须有实际地址。

##### 1.2.4. Iterator

迭代器变量需要用到成员函数begin()和end()，begin返回指示数组第一个元素的迭代器，而end返回指示数组最后一个元素的末端迭代器（off-the-end iterator)。使用过程中，不需要关注迭代器的具体类型，使用auto来生成即可。使用迭代器来遍历数组的好处是，不需要使用下标来访问数组。但是如果要访问迭代器指示的具体元素，需要在前面加上*指示符。

* 迭代器遍历数组时使用++来进行。在使用迭代器的过程中，逻辑判断用！=更常见。

```c++
    for (auto iter = s.begin(); iter != s.end(); ++iter)
        if(isalpha(*iter)){
            *iter = toupper(*iter);
            // (*iter).empty -- iter->empty
        }
```

* 正常使用不需要以定义的方式建立指向已生成数组的迭代器。特殊使用情况，可以用const_iterator来定义一个常迭代器，不过具体类型要看其指示数组。string:: const_iterotor scIter。常迭代器即指示常数组的迭代器。
* 迭代器不能直接引用成员函数，需要以上述注释那样使用成员函数。
* 和for range循环相同，带有迭代器的循环也不能对其指示数组进行动态操作。即不能对数组元素进行增加、删除操作。
* 类似于指针，迭代器也可以使用算术操作实现指向元素的跳转操作。使用迭代器进行算术操作的经典例子是有序数组的二值搜索。

##### 1.3.5. Array

array是一个有着相同类型的变量的静态有序集合。和vector不同，array在定义时必须指明实际空间大小，而且一旦定义，就无法改变，也就是说，无法给array对象增加一个元素。不过由于array的这种静态属性，在一些特定场景下，会获得更好的运行时间性能。

* 声明array过程中，如果想使用变量来对应数组大小，该变量必须满足常变量属性（一般加一个constexpr即可），否则会有编译错误。
* 初始化array的常用方法。字符数组在定义的时候，如果使用字符串初始化一定要留一个位置给‘\0'作为结束标志，否则会报错。因此对于字符数组初始化，一般不直接指明大小。注意字符串数组和字符串定义时使用的标识符的差别，[]/{}()。

```c++
    const unsigned szArray = 3;
    int iArray1[sz] = {1, 2, 3};
    int iArray2[] = {1, 2, 3};
    int iArray3[5] = {1, 2, 3};   // equivalent to iArray3[]={1, 2, 3, 0, 0}
    char cArray1[] = "c++";       // null terminator added automatically
    char cArray2[] = {'c', '+', '+', '\0'};
    char cArray3[3] = "c++";     // wrong, no space for null
    string sArray1[3] = {"c++", "python", "java"};
```

* array对象之间不能在初始化时直接复制，在后续使用过程中也不能两个array对象整体赋值。不过有些编译器会通过这种方式（compiler extension），严格来讲，不提倡这种不标准的赋值方式。

* 只有指针array和array指针，不存在引用变量集合为一个array的。对于复杂的指针array定义，从数组的名字出发从内部向外部理解会更简单。

  ```c++
  int *iptrs[10];       // iptrs is an array of 10 pointers to int.
  int (*iptrs)[10] = & iArray;  // one pointer,iptrs points to an array of ten ints.
  ```

* 使用下标遍历时iArray[n]，C++中遍历元素从0开始，n指的是离开头元素地址的元素偏移量。类似于用迭代器遍历动态数组，可以利用指针也可以遍历array元素。为了防止出现溢出错误，使用如下方式进行指针遍历，begin()和end()函数放在iterator头文件中。

  为了下标的可移植性，在定义数组下标时，使用const size_t进行引用，size_t是定义在cstddef头文件中和机器有关的无符号整数类型，大小足以保证对象在内存中的大小。

  ```c++
  #include<iterator>
  int iArray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
  int *iArrayBeg = begin(iArray);
  int *iArrayEnd = end(iArray);
  for (int *ipArray = iArrayBeg; ipArray != iArrayEnd; ipArray++)
      cout << *ipArray << endl;
  ```

* 如果延续传统C语言中对字符串操作的函数，引用cstring库，使用strlen、strcmp、strcat、strcpy函数。对于字符数组而言，如果初始化过程中，没有给结束标志null，无法使用指针作为输入参数的函数。对于字符数组而言，其比较需要用到strcmp函数，因为它们不属于string类型。C++对以前用C写的代码或者早起版本的C++是比较兼容的，写接口更简单。

##### 1.3.6. Multidimensional Arrays

为了简单，将静态数组array简写为数组。严格地讲，在原生C++语言里没有多维数组（张量类型）。本节讲的实际上是数组的数组。以二维数组为例，C++中是以行优先存储的，当将一个一维数组转换为二维数组时，先填满第一行，随之填到最后一个元素。因此，在C++中用列优先遍历时，比行优先遍历要慢（存在Cache机制，CPU访问内存，不是每次都直接从内存上进行操作，而是先访问Cache，而静态二维数组是行存储的，即其属于同一行的元素的地址是连续的，在同一个Cache中概率更高。）

* 当用for range循环来遍历一个多维数组时，内循环遍历参量必须是一个引用变量（有地址符标识）。

  ```c++
  int iAArray[3][4] = {0};     // initialize all elements to 0
  for (const auto &row :iAArray)
      for (auto col: row){
          col = cnt;
          ++cnt;
      }
  ```

* 当给一个多维数组定义指针时，注意指针的层数，因为数组对应的是一个数组的数组。如果仅仅定义为一层，指针返回的结果是行数组对应的引用变量。其相应加减也是在行数组的维度进行的。

* 使用迭代器的方式对多维数组进行遍历。

  ```c++
  for (auto p = begin(iAArray); p != end(iAArray); ++p)
      for (auto q = begin(*p); q != end(*p); ++q)
          cout << *q << ' ';
  cout << endl;
  ```

#### 1.4. Expressions

##### 1.4.1. Fundamentals

* 运算符优先级、隐式转换、单运算符、复合运算符在C中都有，在此就不再赘述。
* 简单来说，一个对象作为左值，就是使用该对象的地址，一个对象作为右值，就是使用该对象的值。
* 当表达式中符号优先级相同时，并不一定是按照从左向右的方式编译。比如 iCnt = f1()*f2()，无法准确知道是f1先被调用还是f2先被调用。如果有这种形式，而两个函数又刚好相同的返回参数，最好是按顺序执行。换一种说法，操作数本身的计算是独立于操作符所规定的的优先级和结合顺序的。不过在C++中，有四个符号是准确地规定执行顺序的，逻辑与&&，逻辑或||，条件符？：，逗号，。
* 为了确定优先级和代码可读性，多用（）。而当改变某个值的时候，仅仅改变该值，然后再进行相关操作。避免*++iter这种表达式。

##### 1.4.2. Arithmetic Operators

* 注意不要使用bool、char类型进行算术运算。注意除法非零原则，变量溢出错误、除法自动整除等。
* %作为取余运算，两边操作数必须为整数。当取余遇到负号时要注意%和/的差别，-m/n和m/-n最终都相当于-（m/n)。而m%(-n)和(-m)%n中，前者等同于m%n，或者等同于-（m%n）。以一个正常运算而言，m = -n*(m/-n) + m%(-n)。为了余数不出错，使用rem函数最好。

##### 1.4.3. Logical and Relational Operators

* 除了非！操作符是右结合外，其余逻辑操作符都是左结合。
* &&和||先计算左边再计算右边的逻辑被视为短路表达式。对于逻辑与而言，可以将对右边表达式的约束放在左边，当左边表达式不成立时，就不再执行右边表达式了。
* 关系操作符使用时注意不要级联/嵌套（和python中的简写不同），i<j<k的意思是当i<j而且k大于1的情况下该逻辑表达式就返回true，因为（i<j)的返回值是bool型变量。准确的表达应该是i<j&&j<k。关系运算实际上是用左值-右值的方式和0作比较，因此bool型和char型变量也不要直接用在关系运算中。

##### 1.4.4. Assignment Operators

赋值运算符是右结合的，其左值必须是个可变的变量。等号和简单的运算操作符或位操作符构成的复合操作符a op= b，理解为a = a op b。

##### 1.4.5. Increment and Decrement Operators

即++和--。而且++i和i++在遇到赋值操作符时不一样，j=i++指的是先对j赋值当前的i，然后i再自动加1。而j=++i指的是先对i自动加1，然后再赋值给j(i++;j=i)。因此在使用i++或者i--这种后缀表达形式，要注意是否有存储当前使用值的需要。初学者为了可读性，可以分成两步来写。遇到\*beg = toupper(\*beg++)这种格式，编译器可能有两种执行方式。

##### 1.4.6. Access Operators

. 或者->主要用于调用成员属性、成员函数和指针上。ptr->mem 等同于 （\*ptr).mem，注意.的优先级高于\*，因此使用括号定优先级。

##### 1.4.7. Conditional Operators

cond? exp1：exp2: 判断条件cond，如果为真，执行exp1，否则执行exp2。条件运算在嵌套时，先判断左边的条件，然后再判断内层条件。条件运算的操作符优先级靠后，因此使用过程中要常加（）。

```c++
cout << ((grade < 60) ? "fail" : "pass");  // prints "pass" or "fail"
cout << (grade < 60) ? "fail" : "pass";    // print 1 or 0
cout << grade < 60 ? "fail" : "pass";      // error compare cout to 60.
```

##### 1.4.8. Other Operators

* bit操作符：~是bit非，<<或>>是bit左移或者右移，&是位与运算，|是位或运算，^是位异或运算。一般使用unsigned 来定义bit数。

* sizeof运算符。返回变量在寄存器中实际占用的地址空间大小，bytes作为计量单位。对于一个常用变量而言，sizeof返回对应数据类型的bytes值。对string或者vector这种动态数组而言，返回的不一定是其大小而是系统赋予的固定值（用成员函数.size（）可以得到实际大小）。对于一个静态数组array而言，返回的是其实际大小。

* 类型转换，分为显示转换和隐式转换。显示转换使用格式为 cast-name\<type\>(exp)，cast-name决定转换的类型，有以下四种，static_cast，dynamic_cast，const_cast，reinterpret_cast。一般用static_cast即可。四种转换的使用场合如下。

  static_cast: 大型对象（占用bytes)转换为小型对象，编译器无法自动生成的类型转换。

  dynamic_cast: 可以支持运行时的类型检测。

  const_cast: 仅仅改变对象的常属性。一般是去除其常属性。

  reinterpret_cast: 对操作数的bit样式做一次低阶重新解释。即改了个称号，但是实际使用时在内存中的数据类型不变。如果使用，需要熟悉编译器的编译细节。

  延续C语言使用习惯，可以直接（type）exp，相当于编译器自动转换成上述cast格式。

  隐式转换规则：以内存单元大小来看，占用小的自动向占用大的转换；非bool型变量转换为bool变量；初始化和赋值中，右值转化为左值类型。

* 操作符优先级总结。

  ：：> 成员调用符> 括号[]，()> i++、i-->typeid、cast> ++i、--i> ~、& > -a,、+a、*a> 类型转换（type）> sizeof()> new> delete> noexpr> 算术运算符> 位移动运算符> 关系运算符 > 位操作运算符> 逻辑运算符> 条件运算符> 赋值运算符（包括复合）> throw > 逗号运算符

#### 1.5. Statements

##### 1.5.1. Simple Statements

* C++语句中，除了用逗号分开执行外，一句话结束需要用；分开表示结束。
* 声明函数域时构成一个block，需要利用{}作指示。C++中，block不需要加；作为结束标志。

##### 1.5.2. Statement Scope

如果在while、for，if，switch控制语句中定义变量，则该变量仅在其控制block中有定义，在外部无法使用。

##### 1.5.3. Conditional Statements

* if else 语句使用构成中可以多重嵌套，但是嵌套逻辑需要弄清楚。为了不出错，最好每次在条件后加上作用域{}。不过很多IDE都支持自动缩进，以观察嵌套逻辑。
* switch -case-break分支语句。break语句视情况可以不必要每次都加，break的用处是在对应条件后，执行case内语句，直到遇到break语句为止。一般switch语句是和循环语句配合使用的。case语句后的条件必须符合整数常数表达式，不允许两个case有相同的label。对于无法列出全部的case而言，使用default来区分其他值。

##### 1.5.4. Iterative Statements

* while循环。循环体内需要设置语句，保证每次循环后判断条件表达式有所改变，防止死循环出现。while循环条件或者循环体随着每次迭代被创建和销毁。
* for循环，初始化语句-判断条件-最后控制表达式。初始化语句和控制表达式都可以借助，设置多条。
* do while语句中在while的条件后需要加；作为结束标志。

##### 1.5.5. Jump Statements

C++中提供四种中断跳转方法：break，continue，goto，return。

* break语句结合while，for，switch语句使用。观察其所在函数作用域，遇到则直接跳出函数域到外部执行。
* continue语句结合while，for循环使用。指的是终止当前迭代，直接跳到下一次迭代过程。
* goto label。label指示跳转的地方，需要加上：作为label要执行的语句。label：statement和goto：label必须在同一个函数域下。使用jump要注意是否直接跳过会对其中的某个变量的定义，而后退对一个初始化变量重定义是可以编译的（此时会先销毁变量，然后再初始化）。一般不使用goto语句。

##### 1.5.6. Try Blocks and Exception Handling

try  block exception语句用于异常说明。当block在执行过程中检测到一个无法解决的问题时，交给系统显示异常信息或者移交给上一层函数处理（raise 函数）。使用thtow或者exception函数时，指明返回的相应错误类型，在错误类型函数中补充反馈的错误提示信息。错误提示函数在stdexcept头文件中。

#### 1.6. Funtions

对于复杂的问题，写函数一般有两种处理方向，递归和迭代。

* 递归可以将大问题转换为小问题，精简代码，增强代码的可读性。但递归调用浪费了空间（函数调用时要找程序栈），而且递归过深容易造成堆栈的溢出。
* 迭代其运行时间仅仅和循环次数有关，空间开销可控。使得其代码运行效率高，但简洁度不如递归算法。

##### 1.6.1. Function Basics

建立函数时需要注意函数输入函数类型、输出类型、函数域等，使用函数需要提前声明。函数在实际编译时，先在函数域中对输入参数进行初始化，然后再代入函数块进行计算，直到结束或者遇到return返回相应值。

* 如果一个函数不需要输入参数，需要用void说明，有以下两种说明方式。

```c++
void f1(){}
void f1(void){}
```

* 在函数定义过程中，必须对每个参数进行类型说明，不能像普通的初始化那样合并处理。
* 函数内部定义一个static变量，该变量不会随着函数的结束而被销毁，会一直持续到项目结束。
* 对于一个具体的项目而言，所有函数的声明应该放在统一的头文件中，而函数定义在源文件内。

##### 1.6.2. Argument Passing

* 用实参传值。直接将值复制给形参，在函数内部处理。值传递方式不会影响实参。

* 使用指针作为参数时，对于两个指针而言，也是指针值的复制。但是形参所代表的指针可以影响指针所指示数组的很多元素。在C语言中，大多数编程者习惯使用指针来作为实参，而C++中更习惯用引用&作为参数地址。

* 使用引用可以有效防止大规模变量的复制。因为传值，编译处理时需要先复制将值传递给形参，而使用引用形式只需要传递地址即可，不需要复制地址空间中所有的元素值。

* 如果一个函数中，没有改变引用参数，该引用应该设置为常量const。

* 有多个参数返回的时候，可以使用指示变量来传递输出。

  ```c++
  string::size_type find_char(const string &s, char c, string::size_type &occurs)
  {
      auto ret = s.size();
      occurs = 0;
      for (decltype(ret) i = 0 ; i != s.size(); i++)
          if (s[i] == c){
              if (ret == s.size())
                  ret = i;
              ++occurs;
          }
      return ret;
  }
  ```

* 在使用array作参数传递时，只传递其指针，无法了解原array的界限，因此需要提供额外的信息管理指针的作用范围。对于一个字符数组而言，利用其最后一位是空值作为结束标志；直接传递数组的begin指针和end指针，确定其范围；传递开头指针的时候，传递其大小参数。

* 传递一个限制大小数组的指针。

  ```c++
  void func_arr_print(int (&arr)[10]){
      for (auto elem : arr)
          cout << elem << endl;
  }
  ```

* 传递一个多维数组。

  ```c++
  void func_multi_arr_print(int (*matrix)[10], int rowSize);
  void func_multi_arr_print(int matrix[][10], int rowSize);
  ```

* 向main函数传递字符串，后者是指向传入字符串的指针，argc指示传入字符串的个数。使用时注意argv[0]系统自动填充项目名称，自己添加字段从argv[1]开始。

  ```c++
  int main(int argc, int char **argv)
  ```

* 当不清楚传递参数的个数时，可以使用...表示传递一个数目变化的参数集。这种方法用在接口到C代码的情况下，用在对C和C++都适用的数据类型中。大多数class类型的对象在使用省略号传递参数时，无法被合理地复制传递。

##### 1.6.3. Return Types and Statement

* 对于一个非void函数而言，一个循环结束之后没有return相应值，往往会导致循环中不满足条件直接结束而无法返回相应值。这种错误很多编译器常常难以检测。

* 对于一个引用函数而言，return加一个属于函数内部的变量地址是错误的。因为这些地址都是函数运行期间临时分配的，不具有实际意义。

* 一个返回引用值的函数，函数在调用时可以充当左值。

* 递归函数。最简单的阶乘为例。

  ```c++
  int iFactorial(int val){
      if (val > 1)
          return val*iFactorial(val - 1);
      return 1;
  }
  ```

* 返回一个指向数组的指针。

  ```c++
  typedef int arrT[10];
  using arrT = int[10];
  arrT* func(int i);
  int (*func(int i))[10];     // return argument
  ```

##### 1.6.4. Overloaded Functions

在调用函数过程中，函数名可以相同，但是只要函数中定义的形参不同就不会引起冲突，因为编译器会在编译过程中根据传递的参数推断出我们想要使用的函数。重载的好处是，对于执行类似功能的函数，定义时不需要考虑复杂的函数名，调用时也不需要使用针对类型的函数名。

```c++
Record lookup(const Account&);   // find by Account
Record lookup(const Phone&);     // find by Phone
Record lookup(const Name&);      // find by Name
Account acct;
Phone phone;
Record r1 = lookup(acct);
Record r2 = lookup(phone);
```

虽然利用overloading方法可以使我们避免我们因为类型不同而换名字，但是实际使用时应当用在当多个函数很相似，只是类型不同的情况，增加程序的可读性。在调用一个overloaded函数时，要特别注意其类型和使用参数。

##### 1.6.5. Features for Specialized Uses

* 函数定义过程中可以赋初值，这样调用时如果省略某个变量（注意多个变量时，使用，间隔表示不直接传递值），系统直接赋以初值。参数的初值最好放在头文件中的函数声明中。
* inline和constexpr用在函数声明中，放在头文件中。inline函数是对编译器的请求。编译器可以选择忽略该请求。consetexpr函数用来检测调用函数过程中使用的是否为const表达式，而不是要求返回值必须是一个常数表达式。
* inline函数目的是提高函数的执行效率，对于一些经常使用的函数而言，频繁地调用函数，会降低程序的时间效率，为此使用inline用空间来换取时间。inline必须和函数定义体放在一起才能实现函数内联，仅仅吧inline放在函数声明前面不起任何作用。内联函数应当简洁，包含语句不宜过多，内联函数体中，不能有循环语句、if语句或者switch语句，否则，函数定义时及时有inline关键字，也会作为非内联函数处理。内联函数必须在被调用之前声明。
* assert预处理程序，放在cassert头文件中，调用时直接使用assert，没有using这一命名空间。assert一般用于控制输入变量的某些特性。

##### 1.6.6. Function Matching

对于一些定义变量数目相同但变量类型不同的overloaded函数，由于类型转换，需要考虑函数的匹配。函数匹配第一步是确定函数的候选集合。第二步，选择可以被调用的可实现集合（viable functions，传递参数数目相匹配，类型也相匹配，或者能隐式转换）。当函数有缺省值参数时，调用时倾向于更少的参数。第三步，从可实现集合中确定一个匹配度最高的函数。

* 当编译器发现有两个匹配项各有优势时，会拒绝调用，因为这种调用具有模糊性。
* 对于上述有模糊性的调用，强制更改方式是引用cast类型转换。但是对于一个规矩的重载函数而言，不需要也不应该使用cast约束，使用cast约束说明参数集合设计的很差劲。

##### 1.6.7. Pointers to Functions

指向函数的指针，指向一个特殊的类型，函数的类型和其函数名无关，仅仅和其输入输出类型有关。

* 使用指向函数的指针，可以直接让指针指向函数，也可以指向函数的地址，不需要dereference指针。

  ```c++
  bool lengthCompare(const string &, const string &){};
  bool (*pf)(const string &, const string &);
  pf = lengthCompare;
  pf = &lengthCompare;
  bool b1 = pf("hello", "goodbye");
  bool b2 = (*pf)("hello", "goodbye");
  bool b3 = lengthCompare("hello", "goodbye");
  ```

* 在使用指向函数的指针时，可以类比于指向array的指针（不过array是一个实体对象，函数不是）。我们无法定义函数类型的参数，但是可以有一个参数作为指向函数的指针。将函数本身作为参数调用，在C++中形式上是允许的，因为编译过程中会自动转换成指针类型。

  ```c++
  void useBigger(const string &s1, const string &s2, bool pf(const string &, const string &)); // converted to the statement below automatically
  void useBigger(const string &s1, const string &s2, bool (*pf)(const string &, const string &));
  ```

* 无法返回一个函数类型，但是可以返回一个指向函数类型的指针。

##### 1.6.8. Template

C++中采用类型作为参数的程序设计，支持通用程序设计。模板是一种对类型参数化的工具，包括函数模板和类模板。

* 函数模板，针对仅参数类型不同的函数。实现函数的实现与类型无关。

  ```c++
  template <class para1, class para2, ...>
      returnType funcName(arguments){
      funcBody;
  }
  template <class T> void swap(T& a, T&b);
  ```

  以swap为例，当a,b都是double类型，则模板函数变成两个double类型的变量。不过在函数模板调用过程中，只能用具体的对象传递类型，不能直接以int或者double这些类型定义词来传递。

* 类模板，针对仅数据成员和成员函数类型不同的类。类模板中有两个类时，调用时的类传递说明要用逗号分开。模板的定义或者声明只能在全局、命名空间或者类范围内进行。不能在局部范围，也不能在一个函数内部进行。

  ```c++
  template<class para1, class para2>
      class className{...};
  template<class T> class A
  {
      public:
          T a;
          T b;
          T hy(T c, T &d);
  };
  template<class T1, class T2> void A<T1, T2>::h(){}
  A<int, double> A_m;
  ```

* 模板的非类型形参，即内置类型形参，如template<class T, int a> class B {}；中的整型即为非类型形参。非类型形参在模板定义的内部用来处理常量，而且只能用整型、指针或者引用。作为非类型模板形参的实参的必须符合常量表达式约束，比如传入一个指针或者引用要加const说明。

* 模板的实例化。

  ```c++
  // 隐式实例化，只有在运行的时候生成实例，影响运行效率
  swap<int>(a, b);
  // 显式实例化，在编译时生成实例，不影响运行效率，增加编译时间。
  template void swap<int>(int &a, int &b);
  // 特化，处理用户自定义类型
  template <> void swap<job>(job a, job b){}
  ```

* 模板类的继承。包括普通类继承模板类、模板类继承了普通类、类模板继承类模板、模板类继承类模板。

  ```c++
  // 普通类继承模板类
  template<class T>
      class TBase{
          T data;
          ...
      };
  class Derived: public TBase<int>{
      ...
  };
  // 模板类继承普通类
  class TBase{
      ...
  };
  template<class T>
      class TDerived:public TBase{
          T data;
          ...
      };
  // 类模板继承类模板
  template<class T>
      class TBase{
          T data;
          ...
      };
  template<class T1, class T2>
      class TDerived:public TBase<T1>{
          T2 data2;
      };
  // 模板类继承模板参数给出的基类，继承基类由模板参数决定
  ```

* 在使用类模板时，只有当代码中使用了类模板的一个实例的名字，而且上下文环境要求必须存在类的定义时，这个类模板才被实例化。

#### 1.7. Classes

书中的第13节讲了当对象被复制、移动、赋值或销毁时，如何设置事件。在第14节中学习如何定义私人操作符（类方法）。

##### 1.7.1. Defining Abstract Data Types

* 虽然在一些特定的场合中，一个类的设计者就是类的使用者，将这两个身份区分开依然对编程有益。当我们设计类接口时，需要考虑这个类使用时的便利性；当我们使用这个类时，只考虑其功能，而不应该思考其具体实现方式。

* 在定义成员函数的时候，考虑和原有函数的相似性。成员函数内部必须对所属类作内部声明。定义可以在类结构外也可以在类结构内部。一些非成员函数，如add/read/print，在类结构外部进行声明和定义。构造函数作为C++中特殊的成员函数，名字和类名相同，没有返回值，用户无法显式调用，而是在创建对象时自动执行（一般用于初始化），如果想调用构造函数，需要在创建对象的同时传递实参，实参用括号（）包围；构造函数必须是public属性，设为private、protected属性没有用；构造函数没有返回值，函数名前面不允许出现返回值类型，函数体中也不能出现return语句。

  ```c++
  struct Sales_data{
      Sales_data() = default;
      // constructor initializer list
      Sales_data(const std::string &s: bookNo(s)){}
      Sales_data(const std::string &s, unsigned n, double p):\
          bookNo(s), units_sold(n), revenue(p*n){}
      Sales_data(std::istream &);
      std::string isbn() const{return bookNo;}
      Sales_data &combine(const Sales_data&);
      double avg_price() const;
      std::string bookNo;
      unsigned units_sold = 0;
      double revenue = 0.0;
  };
  Sales_data add(const Sales_data&, const Sales_data&);
  std::ostream &print(std::ostream&, const Sales_data&);
  std::istream &read(std::istream&, Sales_data&);
  std::string isbn() const{return bookNo;}
  
  istream &read(istream &is, Sales_data &item){
      double price = 0;
      is >> item.bookNo >> item.units_sold >> price;
      item.revenue = price*item.units_sold;
      return is;
  }
  ostream &print(ostream &os, const Sales_data &item){
      os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " <<item.avg_price();
      return os;
  }
  ```

* 一般而言，非成员函数作为类接口的一部分，应该在包含其类的头文件处被声明。
* 定义结束一个class后，可以Sales_data total语句直接初始化。对于这种不声明构造函数的情况，系统初始化的时候，使用一种无需任何参数的缺省构造函数（default constructor)。当类对象内部含有类对象，这些对象是一种复合类型（compound type)时，需要借助于自动缺省构造函数。
* 对于一些需要动态存储的类而言，使用vector或者string类型。
* 复制、赋值和删除。不定义的话，系统会自动实现这些功能，但不一定符合个人特定要求。具体细节转到书中第13节（[3.1.](#3.1.-copy-control)）。

##### 1.7.2. Access Control and Encapsulation

* C++中使用public和private说明符（access specifier)实现封装。公用部分，项目中任何部分都可以使用。私立部分，只能被使用该class的对象使用。**一般而言，构造函数和接口函数属于公用部分，数据属性成员和执行功能函数属于私立部分。**

* 一个类的定义常用class而不是struct，二者在定义一个类对象的唯一区别在于缺省调用层次。对一些在access specifier之前被定义的成员而言，如果使用struct方法，该成员属于public类，如果使用class方法，该成员属于private类。

* 如果class A将class B设置为其friend，那么A就可以调用B的非公有成员。声明friend的位置最好集中在class定义的开头或者结尾。一般情况下，使用friend函数，其声明在class外部且在被使用之前（和编译机制有关，部分编译器没有该规定）。

  ```c++
  class Sales_data{
      // friend declaration for nonmenber Sales_data operation added
      friend Sales_data add(const Sales_data&, const Sales_data&);
      friend std::istream &read(std::istream&, Sales_data&);
      friend std::ostream &print(std::ostream&, const Sales_data&);
      public:
      Sales_data() = default;
      Sales_data(const std::string &s: bookNo(s)){}
      Sales_data(const std::string &s, unsigned n, double p):\
          bookNo(s), units_sold(n), revenue(p*n){}
      Sales_data(std::istream &);
      std::string isbn() const{return bookNo;}
      Sales_data &combine(const Sales_data&);
      private:
      std::string bookNo;
      unsigned units_sold = 0;
      double revenue = 0.0;
  };
  // declarations for nonmember parts of Sales_data interface
  Sales_data add(const Sales_data&, const Sales_data&);
  std::istream &read(std::istream&, Sales_data&);
  std::ostream &print(std::ostream&, const Sales_data&);
  ```

##### 1.7.3. Addtional Class Features

* 使用公用部分进行类型简写。如果class内部也有重载函数，则选择函数中同样遵守函数匹配机制。

  ```c++
  class Screen{
      public:
      typedef std::string::size_type pos;
      // using pos = std::string::size_type;
      private:
      pos cursor = 0;
      pos height = 0, width = 0;
      std::string contents;
  }
  ```

* 可变的数据成员（mutable Data members)。 一经定义，即使处在一个const对象下，也具有可变属性。

* 返回\*this的函数。表示函数在对数组等对象进行操作之后，返回该对象本身，而不是该对象的复制对象。对于常成员函数，在使用\*this作为返回值时，需要有一个指向const的引用返回值。

* class定义的名字不同，所属对象的类型也不相同。

* 在使用一个class之前，必须对其成员进行完整的定义。也就是说，构建一个链表类型时，把*next指针放到最后定义。

  ```c++
  class Link_screen{
      Screen window;
      Link_screen *next;
      Link_screen *prev;
  }
  ```

* class之间的friendship不具有传递性，即每个class有各自的朋友圈。定义class的朋友可以是一个class，也可以是它的类函数。不过将类成员函数class A.fA()作为classB的friend的实现比较繁琐：首先定义classA,但是不能直接定义fA函数，在classA对fA成员函数作出声明，以便在classA外部定义；然后定义classB，并在B中声明fA是B的friend，最后再定义classA.fA函数，此时由于已知fA是classB的朋友，可以在fA中调用classB的任何成员。

##### 1.7.4. Class Scope

* 名字匹配机制。首先，在名字使用前找到进程声明语句。如果没有找到，到函数/类域内部找，找不到编译器会报错。同时，类定义被编译通过分两步，所有成员声明被编译和在整个类被找到后，函数部分被编译。
* 成员函数中的变量名要指明。

##### 1.7.5. Constructors Revisited

成员具有const属性，或者成员是引用变量的情况下，该成员必须被初始化才能使用。对于这两类成员，使用构造函数进行初始化。实际应用中，如果在类外部已经有构造函数定义了，在类中提供一个缺省构造函数也不会出错。

```c++
class ConstRef{
    public:
    ConstRef(int ii);
    private:
    int i;
    const int ci;
    int &ri;
};
// constructor
ConstRef::ConstRef(int ii): i(ii), ci(ii), ri(i){}
```

* 聚合类（aggregate class），不加约束的类。所有成员都是public属性，没有定义任何构造函数，没有内部初始化，没有base classes和virtual functions。在调用过程中，注意成员的顺序，如果在类函数中增加或者移除一个属性，则所有关于该类的初始化都需要被更新才能使用。

##### 1.7.6. Static Class Members

以银行账户数据类为例，需要一个成员来存放当前的最低利率。但是这个成员只需要这个类知道就可以，不需要每个使用该类的具体对象拥有（具备改动权利），也就是说class需要这种对象只能进行读操作不可写操作的成员。这也就是静态成员。

```c++
class Account{
    public:
    void calculate(){ amount += amount * interestRate;}
    static double rate{ return interestRate; }
    static void rate(double);
    private:
    std::string owner;
    static constexpr int period = 30;
    double amount[period];
    static double interestRate;
    static double initRate();
};
// access a static member using the scope operator
double r;
r = Account::rate();
// defining static members
void Account::rate(double newRate){
    interestRate = newRate;
}
//definition of the static member
constexpr int Account::period;
```

* 对于Account定义的对象而言，实际拥有的成员是owner和amount，interestRate利率成员是被所有Account对象共享的。static成员函数不会绑定到对象中，也不具备this指针。

* 成员函数的static属性可以在类外赋予，也可以在类内部给定。不过当在类外部使用已经定义过的static成员时，不要重复使用static这个标识符，该标识符只需要出现在类内部声明部分。

* 在类内部可以初始化一个const static成员，如果确定只有其内部成员使用，可以不在外部声明。但是为了程序的扩展性，使得该成员可以被外部成员函数利用，应该在类外部提供定义。

* static成员的存在在写操作上和类所定义的对象是独立的。static变量可以是原class类型，而且和指针成员相同，类型不必要完全定义，但是非static变量如果用class类型，需要定义为指向对象的指针或者引用。

  ```c++
  class Bar{
      public:
      //...
      private:
      static Bar mem1;  // ok
      Bar *mem2;        // ok
      Bar mem3;         // error: data members must have complete type
  };
  ```

### Part 2:  The C++ Library

随着C++语言的不断更新，其库也变的越来越强大。因为不可能对C++所有的库都进行详细讲解，挑选其中比较重要的库函数来讲解其核心用途。

#### 2.1. The IO Library

C++语言不直接处理其输入输出，借助IO这个标准库实现人和电脑之间的交互，交互方式利用string对象形成指令，输出结果。[章节14](#3.2.-overloaded-operations-and-conversions)中会讲到如何写私人的输入输出操作符，[章节17](#4.1.-specialized-library-facilities)中讲到如何控制输出格式和实现文件的随机访问。

##### 2.1.1. The IO Classes

IO中常用的是char类型数据，而程序经常需要读写文件，一般需要借助string实现文件名的存储。和IO有关的函数存在以下三个库：iostream，定义读写一个流的基本类型；fstream，定义读写文件名的类型；sstream，定义读写内存内部字符串的类。为了支持使用宽字符的语言（中文字符是按照wchar来处理的，所以又被称作word类型），定义了wchar_t类型，占用一个字word的长度来表达相应字符。其相应的函数版本也在开头加上w。

* IO类型不能直接进行copy或者assign操作。

* 如果想确保输入正确然后再进行相应操作，可以借助while(cin>>word)这种形式来检查。但是想了解输入流为何出错，需要借助badbit、eofbit、failbit等函数。

* 清除输出缓存，如果是单句形式，可以用endl、flush、ends函数。为了方便，直接使用unitbuf使得后续的cout函数直接清除缓存，结束该限定用nounitbuf。

  ```c++
  cout << "hi!" << endl;  // writes hi and a newline, the flushes the buffer
  cout << "hi!" << flush; // writes hi and flushes the buffer, adds no data
  cout << "hi!" << ends;  // writes hi and a null, then flushes the buffer
  cout << unitbuf;
  cout << nounitbuf;
  ```

* 如果程序中途崩溃，缓存是不会被清理的。

##### 2.1.2. File Input and Output

fstream提供三种处理文件的函数：ifstream读取一个给定的文件，ofstream写一个给定的文件，fstream对于一个给定的文件进行读写操作。

* 使用read（input, obj1)和print(output, obj2)进行文件读写操作。

* 当fstream对象被销毁时，相应的close函数会自动执行。

* 文件使用模式：“in"，input模式；”out",output模式；“app"，append模式，每次在文件末尾写；”ate"，打开文件后立即调到文件末尾；“trunc"，截断文件；：binary"，二进制文件处理。

  ```c++
  ofstream fout("file1");
  ofstream fout2("file1", ofstream::out);
  ofstream fout3("file1", ofstream::out|ofstream::trunc);
  ofstream app("file2", ofstream::app|ofstream::out);
  ```

* 一旦打开一个文件，其模式显式或者隐式地被设置。

##### 2.1.3. string Streams

sstream头文件提供三种支持内存IO的类型：istringstream读一个字符串，ostringstream写一个字符串，stringstream读写一个字符串。

* 当我们对文件按整行处理时，使用istringstream函数。下面的代码中使用>>和cin类似，遇到空格或者字符串结束标识时，就结束读，相当于按照空格分词，按照end_of_file标志结束。

  ```c++
  struct PersonInfo{
      string name;
      vector<string> phones;
  };
  string line, word;
  vector<PersonInfo> people;
  while(getline(cin, line)){
      PersonInfo info;
      istringstream record(line);
      record >> info.name;
      while(record >> word)
          info.phones.push_back(word);
      people.push_back(info);
  }
  ```

* 使用ostringstream即是以字符串的方式改写文件。下面的例子中，formatted存放筛选后的信息，badNums存放筛选过程中出现的那些错误号码信息。

  ```c++
  for (const auto &entry : people){
      ostringstream formatted, badNums;    
      for (const auto &nums : entry.phones){
          if (!valid(nums)){
              badNums << " " << nums;
          }
          else
              formatted << " " << format(nums);    
      }
      if(badNums.str().empty())
          os << entry.name << " " << formatted.str() << endl;
      else
          cerr << "input error:" << entry.name << " invalid number(s) "
          << badNums.str() << endl;
  }
  ```

#### 2.2. Sequential Containers

本部分相当于对[第3章节](#1.2.-Strings,-Vectors-and-Arrays)的一个扩展，完善对标准库中序列化容器的介绍。在一个序列化容器中，元素的存放顺序取决于其加入容器的位置。不过，[第11章节](#2.4.-Associative-Containers)也会介绍一种结合容器（associative container，类似于字典），元素的位置取决于对应key的位置。

##### 2.2.1. Overview of the Sequential Containers

不同类型的序列化容器在以下两方面作不同的权衡（tradeoff)，向容器中增加或者删除一个元素的代价和以非序列化方式访问元素的代价。以vector、string而言，虽然能够随机存取，但是在数组中间增加或者删除一个元素的时候，考虑其元素的次序，需要将后续元素先缓存，然后一个接一个向后移动，空出中间一个位置，再进行插入。而链表类型就没有这个考虑，只需要找到中间位置，直接以指针的方式插入或者删除。不过链表在查找一个元素时，需要从头部指针开始按次序访问，无法以下标的方式直接访问元素。

* vector。动态数组。支持快速随机访问。但是插入或者删除元素和下面的数据类型相比更慢。
* deque。双向队列。支持快速随机访问。能从两端对元素快速插入和删除。
* list。双向链表。只支持双向序列化访问。能实现在一个点处快速的插入和删除。
* forward_list。单向链表。只支持单向序列化访问。支持在一个点处的快速插入和删除。不能直接对end()成员进行访问和其余操作。
* array。静态数组。支持快速随机访问。由于静态性，不能增加或者删除元素。
* string。类似于vector，但是只存储字符类型。支持随机访问。可以在末端实现快速插入和删除。
* 除非实现特殊功能，一般使用vector作为container。

##### 2.2.2. Container Library Overview

容器不仅可以自我嵌套，也能互相嵌套使用。

* 迭代器。对于迭代器范围的概念是对基础库的基础知识。一般用begin和end函数指示容器的第一个和最后一个元素（last)。不过last严格意义上指的是最后一个元素后的元素（不属于container的作用域）。可以根据begin和end之间的差值，判断容器中给的元素个数。

* 部分容器提供反迭代器功能，即如果使用++操作，迭代器向begin端挪动一格。迭代器的声明如下。不清楚container的类型时，使用auto。但是如果在begin前加上c，就会返回一个const_iterator，不管这个容器自身的类型如何。因此如果对于一个序列化容器的访问过程中不需要写操作时，直接使用cbegin和cend。

  ```c++
  list<string>::iterator iter;
  vector<int>::difference_type count;
  auto iter = a.begin();
  auto iter = a.cbegin();
  ```

* 当我们用复制容器的方法初始化另外一个容器的时候，要保证两个容器的类型和元素的类型都一致。

* 容器的初始化，可以直接在定义的时候初始化，也可以建立相关的构造函数初始化。使用构造函数不能对associative container进行初始化。

  ```c++
  list<string> authors = {"Milton", "Shakespeare", "Austen"};
  vector<int> ivec(10, -1);
  list<string> svec(10, "hi!");
  array<int, 42> iArray;
  array<string, 10> sArray = {"Never", "Mind"};
  ```

* array只能在初始化时赋值in_built类型，后续操作中必须保证赋值符号左右类型相同。如果要用常类型来赋值，需要调用assign函数。

  ```c++
  list<string> slist1(1);       // one element, which is the empty string
  slist1.assign(10, "Hiya!");   // ten elements, each one is "Hiya!"
  ```

* swap函数。除了array外，对两个容器对象使用swap函数可以在常数时间内，保证快速的互换。互换的本质是container名字的变化，但是元素在内存中没有作改动。但是如果对array使用swap函数，其内部元素在内存上有变化，因此swap两个array用时正比于两个静态数组的大小。尽管swap有成员函数和非成员函数，但是为了养成好习惯，最好用非成员函数版本的swap函数。

* 显示容器的大小，一般用empty函数，也有些用max_size和size函数表示容器大小（和容器类型有关）。

* 关系运算。两个相同类型的容器在进行比较的时候，和string类似，服从字典排序（只不过字典中的字母变成了数字）。

##### 2.2.3. Sequential Container Operations

序列化容器和结合型容器区别在于管理元素的方式，影响了元素存储、访问、添加和删除的方式。

* 除了静态数组array外，其余序列化容器都提供了添加元素的方法。包括push_back，emplace_back，push_front，emplace_front，insert等。以上插入方式中，只有insert返回指针p，指向的是第一个被插入在容器中的位置，其余方法都返回void值。

  ```c++
  vector<string> svec = {"quasi", "simba", "scar", "frollo"};
  list<string> slist;
  slist.insert(slist.begin(), "Hello");
  svec.insert(svec.end(), 10, "Anna");
  slist.insert(slist.begin(), svec.end() - 2, svec.end());
  svec.emplace_back("192381929", 25, 15.66);
  svec.push_back("192381929", 25, 15.66);           //error:three arguments
  svec.push_back(Sales_data("192381929", 25, 15.66));
  ```

* 使用insert函数可以在vector、deque、string类型的任何地方进行插入操作。但是这样做很费时间。insert的插入位置在所给指针位置的前面。使用insert(p, v1, v2)用两个iterator来指定插入值范围时，p和v不能指向同一个容器。

* 使用push或者insert进行插入时，是将被插入容器的元素类型和插入对象复制后，再插入到容器中。使用emplace函数进行插入时，我们是将参数传递给针对该容器元素类型的构造函数，利用该构造函数直接在容器内构造一个相应元素，省掉了中间变量这部操作。

* 访问容器中的元素可用back()、front()、c[n]、c.at[n]四种函数。其中back()和end()不同，back函数返回的是指向容器中最后一个元素的&地址（如果容器空，undefined，因此使用时加上非空判断条件），而end函数返回的是指向容器最后一个元素后的元素的迭代器，即使容器是空的，也可以返回值。而且back()函数不能用于单向链表中（单向链表只能按前向顺序访问节点）。

  ```c++
  if (!c.empty()){
      auto cVal = *c.begin(), cVal2 = c.front();
      auto cLast = c.end();
      auto cVal3 = c.back(); // not supported by forward_list
  }
  ```

* 由于back()和front()函数返回的都是reference，使用auto进行赋值，只会得到相应的值，不会构建和原容器相应元素之间的约束（即改变cVal3的值，不会改变容器c中相应位置的元素）。

* c[n]和c.at[n]的区别是，如果n作为下标超过了容器范围，不会报错，而是返回out-of-range的exception错误。

* 从容器中删除元素的指令有pop_back，pop_front，erase，clear。pop指令删除容器开头或者结尾的一个元素。erase可以删除一个元素，也可以删除一个范围的元素。clear是删除容器中的全部元素。不过删除之前，编译器是不会检查是否有相应元素的。因此，编程者自己要确保指定位置有元素存在。

* 由于单向链表的特殊性，在使用以上操作时，一般要加上after表示其指向性，如insert_after。

* 对于静态数组而言，可以使用resize来改变其大小，但是resize一般用来做一维数组的改变。而且resize都是从array的后面元素进行删除和添加的。

* 使用指针，引用和迭代器（统称为pri)来访问容器元素时，对于deque而言，除头部和尾部元素增删对pri没有影响，其余地方都会使pri不合法。对于vector、string，如果出现容器再分配的情况，相应pri会变不合法；而对于链表而言，pri一般都是合法的。使用不合法的pri，会出现run-time错误。

##### 2.2.4. How a vector Grows

* 对于vector或者string容器而言，所有元素是顺序连续存储的。因此遇到增加元素时，经常要开辟新空间，造成很大的时间开销。因此，当系统在生成一个vector或者string变量时，会自动分配足够多的空间给相应对象，使得对于新元素的加入不需要重新分配空间。
* size是当前容器已经容纳的元素个数，而capacity是在容器被重分配之前所能容纳的元素最大数目。使用reserve函数可以给vector或者string容器设置最低容量。如果在增加元素的过程中，size超过了容量，那么系统需要对该容器进行重分配。

##### 2.2.5. Additional String Operations

* 改变string对象，可以直接使用string函数初始化赋值，也可以用substr函数赋值。其余修改方法有，insert，erase，assign，append，repalce，对于一个字符串而言，处理元素是字符。
* assgin和append函数不需要指明改变的位置。assign函数总是将string对象全部替代，而append总是在结尾添加相应字符。
* 搜索方法：find，refind，find_first_of，find_last_of，find_first_not_of，find_last_not_of。分别返回遇到指定字符串的第一个位置，最后一个位置，第一个位置（字符串数组中的任意一个），最后一个位置（字符串数组中的最后一个），第一个非元素位置，最后一个非元素位置。搜索过程中区分大小写。可以定义正则表达式进行搜索。
* 比较函数compare，和strcmp类似，不过返回值对应的是负值、0和正值。

##### 2.2.6. Container Adaptors

适配器是在库函数中的一种广义概念，包括容器、迭代器和函数适配器，作为一种机制，创造类似已知方法的新方法。容器适配器就是以当前已知容器出发，作一些改动。库中有三种类型：栈、队列、优先级队列。栈和队列的默认容器为deque，priority_queue是从vector出发的。改变默认容器的方法如下。

```c++
stack <int> stk(deq);
stack<string, vector<string>> str_stk; // use vector as the adaptor of str_stk
```

* 栈。存放于stack头文件。First in last out。只能用push_back，pop_back和back指令，因为只允许对顶部元素进行操作。使用指令时，要用相应的push，pop指令，不能用push_back对栈对象进行操作。
* 队列。存放在queue头文件。First in  first out。只能用back，push_back，front，push_front，可以用list或者vector，但是不能用vector来构建。queue使用的函数为，pop，front，back。
* 优先级队列。存放于queue头文件。允许元素带有优先级，新进来的元素放在所有元素之前，被分配一个低优先级。允许随机存取和front、push_back，pop_back函数。可以建立在vector或者deque基础上，不能用list重构。可以使用pop，front，push，emplace函数。

#### 2.3. Generic Algorithms

本章的算法指排序、搜索这些经典有序容器算法，而通用性指容器所用的数据类型不仅仅是vector和list，还有[上一章](#2.2.-Sequential-Containers)学到的其他序列类型。

##### 2.3.1. Overview

很多经典算法存放在algorithm模块和numeric模块。这些经典算法在操作时，使用迭代器访问元素，因此不依赖于容器的类型。同时也遵守一条原则，算法不会改变所指容器的size。虽然算法可能对其中存在的元素的值进行改变、替换，但是不会直接增加或者删除元素。

##### 2.3.2. A First Look at the Algorithms

除却个别算法，经典算法需要输入待操作元素范围，也就是给迭代器指明begin和end。可以从读、写和重整顺序这三个方面对经典算法分类。

* 只读算法·。find、count、accumulate（记录某一范围的元素总和，元素类型要对应）、equal。
* 可写算法。fill函数给指定范围赋值，和assign类似。fill_n是以一个iterator为起点，填充后续n个元素，但是有超出容器capacity的风险。因此，需要借助insert iterator。经常用的是back_interator函数；copy函数。将容器A范围内的元素复制到容器B中。
* 排序算法。常用sort函数，unique函数（去除重复项）。使用unique之后，原容器的size时不变，不过会返回一个end_unique指针指向最后一个非重复元素的off-end，这时再使用erase函数就可以删除冗余项。

##### 2.3.3. Customizing Operators

以上一小节的sort函数为例，对字符串数组进行排序时，使用的是字典排序，以首字母作为第一排序元素。如果想按字符串长度进行排序，需要自己定义比较方法，sort中有扩展，第三个参数叫做predicate，sort的缺省值是<，可以改成不同的bool函数建立不同的比较规则。

* lambda表达式，一段可调用的代码单元。语句中不要包换return 空值。lambda表达式引用local变量时必须将该变量引用在CaptureList中，而且不能是const变量。如果使用的是local static变量，那么可以直接用。不过如果传参太多，直接建一个函数就解决问题。

  ```c++
  // [CaptureList](ParameterList)->ReturnType{FunctionBody}, CaptureList is often empty
  auto f = [] { return 43; };
  cout << f() << endl;
  [sz](const string &a){ return a.size() >= sz; };
  void biggies(vector<string> &words, vector<string>::size_type sz,
              ostream &os = cout, char c = ' '){
      for_each(word.begin(), words.end(), 
              [&os, c](const string &s){ os << s << c; });
  }
  // Specifying the Lambda Return Type
  transform(vi.begin(), vi.end(), vi.begin(),
           [](int i){ return i < 0 ? -i : i; });
  ```

* bind函数，定义在functional头文件中。bind函数将一个可调用函数其中的参数，赋予相应值，构造成一个子函数使用。参数列表中，\_k表示前k个参数，后续跟上赋值。不过使用\_k必须声明using namespace std:: placeholders。

##### 2.3.4. Revisiting Iterators

除了指向容器的iterator外，在iterator有文件中，还有一些其他种类的iterator。分为四种，插入型迭代器，流型迭代器，反向迭代器，移动型迭代器。迭代器也可以分为五种，input，output，forward，bidirectional，random access。

* 插入型迭代器用在一个容器中，专门给一个特定的容易添加元素。back_inserter基于push_back的方式创建一个迭代器，front_inserter则是基于push_front的方式创建一个迭代器，inserter基于insert的方式创建一个迭代器。因此使用front_inserter插入时，总是插入到容器的头部。

* 流型迭代器，将流数据看成是一种特殊的元素序列。使用时，必须指明迭代器所指向对象的类型，读写元素的时候使用>>和<<。

  ```c++
  istream_iterator<int> int_iter(cin);
  istream_iterator<int> eof;            // istream end iterator
  while(in_iter != eof)
      vec.push_back(*in_iter++);
  // constructor
  istream_iterator<int> in(cin), eof;
  cout << accumulate(in, eof, 0) << endl;
  // ostream
  ostream_iterator<int> out_iter(cout, " ");
  for(auto e:vec)
      *out_iter++ = e;
  cout << endl;
  copy(vec.begin(), vec.end(), out_iter);
  cout << endl;
  ```

* 反向迭代器，除了单向链表外，都可以使用。执行iter++时，会向头部元素移动。相当于将原容器先反序，然后再执行遍历。此时的crend()是指向头部元素的前一位off_head元素。但是如果直接按照反向迭代器输出结果，特别是字符串，也将是反序的，而不是以word作为整体反序。

* 使用reverse_iterator进行迭代器转换时，实际所指位置和其代表的数值（逻辑位置）是不同的。这是C++区间半开性导致的，而逆向迭代器在使用时倒置了该“半开原则”，使得逆向迭代器定义的区间不包括起点，而包括终点，从而使得其逻辑位置小于实际位置一格，实现逻辑上的倒置关系。

  ```c++
  vector<int> iVec = {0, 1, 2, 3, 4, 5, 6, 7, 8}
  for (auto r_iter = iVec.crbegin(); r_iter != iVec.crend(); ++r_iter)
      cout << *r_iter << endl;
  // output of the inverse string
  auto rComma = find(line.crbegin(), line.crend(), ",");
  cout << string(rcomma.base(), line.cend()) << endl;
  ```

##### 2.3.5. Structure of Generic Algorithms

* 算法的参数调用形式有以下四种。dest是指向结果存储单元的迭代器。

  ```c++
  /*
  alg(beg, end, other args);
  alg(beg, end, dest, other args);
  alg(beg, end, beg2, other args);
  alg(beg, end, beg2, end2, other args);
  */
  ```

* 参数中有涉及比较运算的，可以使用特定的比较符号（Predicate）代替缺省量。

* 子函数作为原函数的扩展，一般是在原函数名字后面加上功能名作为一个新函数调用，如reverse_copy。

##### 2.3.6. Container-Specific Algorithmss

list和forward_list定义了许多成员函数，merge、remove、reverse、sort和unique。调用时，可以直接用lst.sort()而不是sort(lst,...)。还有一些移动函数，lst.splice()和fLst.splice_after()。和之前讲的通用算法不同的时，这些专用于链表的成员函数改变了原链表，以lst.merge(lst2)为例，从lst2中搬移元素到lst中最终达成合并，而合并之后被搬运链表lst2成为一个空链表。

splice函数在常数时间内实现两个list的拼接，可以选择参数是对list中的一个元素、范围元素或者全部元素进行拼接。

```c++
void splice (iterator pos, list<T, Allocator>& x);
void splice (iterator pos, list<T, Allocator>& x, iterator it);
void splice (iterator pos, list<T, Allocator>& x, iterator first, iterator last);
```

#### 2.4. Associative Containers

和序列化容器不同的是，关联型容器不是靠在内存中的位置（下标）访问元素，而是靠与元素关联的key访问值，本部分为了方便将这种类型称作字典。主要有两种元素，map和set。map存放键值对，set元素则只包含键，用来存放一些重要的键以便查找。在C++中具体有8种类型。multi的意思是，允许有多个相同的键，如果是multimap即一对多映射，一个key可以对应多个value。Unordered则是使用hash算法来管理元素。

* Elements ordered by Key：map，set，multimap，multiset。
* Unordered Collections：unordered_map，unordered_set，unordered_multimap，unordered_multiset。

##### 2.4.1. Using an Associative Container

map可以看成是关联数组（array），set是包含键的集合，可以用在不知道value的时候存键。使用下标访问字典时，如果不存在该key直接进行insert操作，找到key则返回改变该key值。

```c++
map<string, size_t> word_count;
string word;
set<string> exclude = {"The", "the", "A", "a", "Or", "or", "An", "an", "And", "and"};
while(cin >> word){
    if(exclude.find(word) == exclude.end())  // don not find word in the exclude set
        ++word_count[word];
}
for (const auto &w : word_count)
    cout << w.first << " occurs " << w.second 
    << ((w.second > 1) ? "times" : "time") << endl;
word_count["Anna"] = 1;   // subscript only on a map that is not const.
```

##### 2.4.2. Overview of the Associative Containers

* map和set的初始化都要指明所包含元素的类型，不过map有两类元素，因此要声明key和value的类型。初始化键值对时使用格式{key, val}。

* 在map和set中key是不能重复的，但是在multimap和multiset中没有这种约束。

* 使用key进行查找时，需要定义一种比较规则来进行key排序。这种比较规则需要是单向的，可传递的。如果两个key都不构成小于关系，那么就是相等的，相等也具有传递关系。而且当相等出现在map中时，这些相等的key只能对应同一个val，从而不违反查找上的一对一映射。

  ```c++
  bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs){
      return lhs.isbn() < rhs.isbn();
  }
  // pay attention to * used after the function name.
  multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
  ```

##### 2.4.3. Operations on Associatve Containers

* 初始化或者向map中进行键值对操作时，可以使用pair变量。pair中的first和second分别指示键值对的key和val。遍历使用迭代器即可。

* 插入。插入到set中时，一般将对应类型的容器作为插入参数。插入到map中时，需要使用键值对pair。insert或者emplace的返回值取决于容器的类型和参数。返回的结果中，first是指向给定key相应键值对的迭代器，second是指示该元素是否被插入的bool型变量。如果在map中已经有该键存在，则不作insert操作，second是false。如果没有，则second返回true，并进行插入键值对操作。

  ```c++
  word_count.insert({word, 1});
  word_count.insert(make_pair(word, 1));
  word_count.insert(pair<string, size_t>(word, 1));
  word_count.insert(map<string, size_t>::value_type(word, 1));
  // insert a word into word_count
  map<string, size_t> word_count;
  string word;
  while(cin >> word){
      auto ret = word_count.insert({word, 1});
      if(!ret.second)
          ++ret.first->second;
  }
  ```

* 删除操作。使用erase函数，一般会返回size_type类型显示删除数目。

* 在对key进行遍历时，由于key不是一个显式的序列化对象，需要使用lower_bound和upper_bound表示在multimap中key的第一个位置和最后一个位置，即同一个key所对应的键值对的迭代器范围。而搜索的key列表，不一定都在被搜索的map中，如果不存在lower_bound返回在容器中可以被插入的位置。multimap和multiset中的键是可以重复的，所以按键搜索返回的值是一个列表。如果对于一个map使用，则lower_bound和upper_bound返回同一个迭代器。

  ```c++
  string search_item("Alain de Botton");
  for (auto beg = authors.lower_bound(search_item),
      end = authors.upper_bound(search_item); beg!=end; ++beg)
      cout << beg->second << endl;
  // another function equal_range
  for (auto pos = authors.equal_range(search_item);
      pos.first != pos.second; ++pos.first)
      cout << pos.first->second << endl;
  ```

* 一个word_tranform的例子。

  ```c++
  map<string, string> bulidMap(ifstream &map_file){
      map<string, string> trans_map;
      string key;
      string value;
      while(map_file >> key && getline(map_file, value))
          if(value.size() > 1) // check that there is a transformation
              trans_map[key] = value.substr(1); // skip the space
          else
              throw_runtime_error("no value for " + key);
      return trans_map;
  }
  const string& transform(const string &s, const map<string, string> &m){
      auto map_it = m.find(s);
      if(map_it != m.cend())
          return map_it->second;
      else
          return s;
  }
  void word_transform(ifstream &map_file, ifstream &input){
      auto trans_map = buildMap(map_file);// read the file of transforation rules and creat a map from each word to its transformation
      string text;
      while(getline(input, text)){
          istringstream stream(text);
          bool firstword = true;
          while (stream >> word){
              if(firstword)
                  firstword = false;
              else
                  cout << " ";
              cout << transform(word, trans_map);
          }
          cout << endl; // print a \n
      }
  }
  ```

##### 2.4.4. The Unordered Associative Containers

本部分的字典在管理键值对时，不是使用一般的比较排序，而是使用计算各键值对的hash值，使用hash值取寻找键值对，从而叫做无顺序的字典。事实上，使用顺序字典更简单效果通常更好。除非key的类型内含无法排序的属性或者经过测试可以使用hash管理键值访问，一般不考虑使用unordered_map。

* 无顺序的容器好比是一个木桶的集合，每个木桶装载着零个或者多个元素（这和hash的多对一映射有关）。容器使用hash函数来匹配到元素存在的木桶，然后再利用木桶函数找到所要的key值。如果一个key值对应多个value，这些键值对也是相邻存储的。
* C++中处理bucket中的元素有很多函数。bucket_count，bucket_size，local_iterator，load_factor，rehash，reserve等。

#### 2.5. Dynamic Memory

对于一个程序而言，除了静态或者栈内存可用，还有一些动态空间可以使用。这些空间被视作free_store或heap。编程者可以基于该空间设置动态对象控制对象的生存时间，不过动态对象必须被明确销毁。使用动态空间在C++中很有必要，但是管理分配起来还是比较复杂的。

实际使用时，使用vector和string优先于动态分配的数组。

##### 2.5.1. Dynamic Memory and Smart Pointers



##### 2.5.2. Dynamic Arrays

##### 2.5.3. Using the Library: A Text-Query Program

### Part 3 Tools for Class Authors

#### 3.1. Copy Control

#### 3.2. Overloaded Operations and Conversions

#### 3.3. Obeject-Oriented Programming

#### 3.4. Templates and Generic Programming

STL，英文全称为standard template library，其中包含大量的模板类和模板函数，是C++提供的一个基础模板的集合，用于完成诸如输入/输出、数学计算等功能。STL最初由惠普实验室开发，于1988年被定为国际标准，正式成为C++程序库中的重要组成部分。目前，STL已经完全被内置到支持C++的编译器中，无需额外安装。

模板时C++支持**参数化多态**的工具，使用模板可以使得用户为类或者函数声明一种一般模式，使得类中的某些数据成员或者数据成员的参数、返回值取得任意类型，不需要因为类型不同而再写一类函数。

template\<class T\>和template\<typename T\>都可以用来定义函数模板和类模板。

模板的声明和定义只能在全局、命名空间或者类范围进行。不能在函数内或者局部范围内进行。

##### 3.4.1. 函数模板

```c++
template <class para1, class para2, ...>
    returnType funcName(paraList) {funcBody}
template <typename 
template<class T> 
    void swap(T &a, T &b){
    T Ttemp;
    Ttemp = b;
    b = a;
    a = Ttemp;
}
// 调用时引用好相应的头文件，并且声明T所指代的类型即可
swap<int>(num1, num2);
```

##### 3.4.2. 类模板

```c++
template<class T> class A
{
    public:
    T a;
    T b;
    T hy(T c, T &d);
};
template<class T> class A{
    public:
    T g(T a, T b);
    A();
};
// 上述是声明，下面是调用代码
template<class T> T A<T>::g(T a, T b){
    return a + b;
}
void main(){
    A<int> a;
    cout << a.g(2, 3.2) << endl;
}
```

##### 3.4.3. 模板的专门化

##### 3.4.4. 模板的类型转换

### Part 4: Advanced Topics

#### 4.1. Specialized Library Facilities

#### 4.2. Tools for Large Programs

#### 4.3. Specailized Tools and Techniques

