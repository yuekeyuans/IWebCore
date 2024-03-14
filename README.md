# IWebCore 简介

<pre float="center">
 _____  _    _        _      _____
|_   _|| |  | |      | |    /  __ \
  | |  | |  | |  ___ | |__  | /  \/  ___   _ __  ___
  | |  | |/\| | / _ \| '_ \ | |     / _ \ | '__|/ _ \
 _| |_ \  /\  /|  __/| |_) || \__/\| (_) || |  |  __/
 \___/  \/  \/  \___||_.__/  \____/ \___/ |_|   \___|
</pre>


`IWebCore` 是一款基于 `c++` 的快速开发，高效运行的 网络框架。 它降低`c++`网络开发的难度，并提高开发效率。

这个库灵感来源于 `Spring` , `Flask`,`FastApi`, `drogon` 和其他的网络库。所以如果你了解过其中的一个现代网络库，你可以很轻松的学习`IWebCore`。

---

## 地址

- github地址 [yuekeyuans/IWebCore (github.com)](https://github.com/yuekeyuans/IWebCore)
- 文档地址：[IWebCore文档](http://www.iwebcore.com/)

## 优点

### c++11 / Qt 平台支持。

- **大量的c++11库和 Qt 库支持**

- **成熟的编程语言**

    目前主流的c++开发是基于c++11， 而Qt开发也是 c++ 开发的主流之一。

- **跨平台开发和运行**

    软件目前支持在所有Qt能够运行的环境上编译开发，实现软件的跨平台支持。所以开发者可以在windows 上面进行快速开发编译，而在完成开发之后部署到linux主机上面再次编译并运行。 

### 高效

- **降低 内存， cpu 等资源的消耗**

    c++ 拥有很高的运行效率，对比与其他的主流网络框架，它能够节省更多内存的使用，cpu使用，进而带动服务器数量的减少和能源消耗的减少，降低碳排放。(参见文章: [Why C++ ? 王者归来 | 酷 壳 - CoolShell](https://coolshell.cn/articles/6548.html) )

- 软件运行速度快。
- 秒速启动运行。

### 快速开发。

- 易于上手

    c++ 开发很多人觉得困难是因为c++本身带来的复杂性。`IWebCore` 对于新手非常友好，开发人员初期并不需要了解C++复杂的特性也可以 使用controller，并进行数据库的增删改查等操作。

- 类似Spring和 FastApi 等主流web开发框架

    降低了开发者的学习难度，使用了 `宏注解` 如 `$Controller` 等开发者熟悉的方式。

### Controller

- controller 自动注册
- url灵活配置，动态url
- 函数参数从请求中动态解析和注入绑定
- 灵活的返回方式，可以返回 text,json, xml, status等内容。
- 严格的参数检查。

### 强大的orm 支持

- 内置 database，table，view， model支持
- table sql 自动生成
- json 原生支持
- 内置各种Util转换，可以将 bean 或 bean 的集合转换成 json/string 类型。

### 内置 http server

- 支持 GET， POST，PUT，DELETE, PATCH, OPTION等方法。
- HttpMime, HttpStatus支持。
- **TODO:** 在将来的版本中优化tcp请求模型，使用`epoll`和 `IOCP` 等方式。

### 方便的配置方式。

- 支持 System和 Application两种级别的配置
- 提供包括 代码，json, yaml,`宏注解` 等多种配置方式

### 运行期错误检查。

- 友好的运行前检查，

    在实例运行之前，会对软件的逻辑进行详细的检查，在有问题的地方生成有好的 warning 或者 fatal 信息

### 稳定的roadmap

- `IWebCore` 会提供长期的开发，将在roadmap中间设计的内容实现出来。

---

## 应用场景

目前`IWebCore`主要致力于以下场景

### Qt Gui 等开发帮助

由于框架本身是基于Qt开发而来的，所以软件可以无缝集成到所有的Qt应用中来提供帮助，主要有两方面：

- 为 Qt Gui 提供一个 内置 server 。这样Qt应用既可以使用它向外提供服务，也可以改变Qt的层次结构，即使用 QtGui 做界面，而 IWebCore作为数据源和控制器。
- 直接使用`IWebCore` 的orm模型。`IWebCore` 内置的 orm 可以简化Qt 和数据库的交互，降低开发难度。

### 微服务开发

`IWebCore` 将会是一个云原生的网络服务框架。使用`IWebCore` 作为微服务开发框架将降低开发难度，提高运行效率。

### 嵌入式网络开发

对于支持 Qt5.12的嵌入式设备，`IWebCore`提供快捷便利的网络开发。

### PC端服务器开发

`IWebCore` 同样能够服务`PC` 端服务器。

---

## 代码样式

下面提供一个最简单的项目代码，只有两个文件`main.cpp` 和 `MyFirstController.h`

```cpp linenums='1'
// main.cpp
#include <IWebCore>

int main(int argc, char *argv[])
{
    IWebApplication app(argc, argv);
    IHttpServer server;
    server.listen();
    return app.exec();
} 
```

``` cpp linenums='1'
// MyFirstController.h
#pragma once

#include <IWebCore>

class MyFirstController : public IControllerInterface<MyFirstController>
{
    Q_GADGET
    $AsController(MyFirstController)
public:
    $GetMapping(index, /)
    QString index()
    {
        return "hello world";
    }
};
```

当运行项目的时候，一个webserver 已经创建并运行完成。

我们可以访问 http://127.0.0.1:8088, 并看到有 hello world 返回。

![image-20220226193138143](./doc/image-20220226193138143.png)

---


在`IWebCore` 的开发前后，受到很多个方便的帮助，在此表示感谢:

- 这款软件的灵感来源是曾经在大学学习并使用过的`Spring` 框架，虽然现在细节大部分已经忘记，但是`Spring` 清晰简洁的语法，基于`注解`方式的开发，`Aop` 和 `Ioc` 的思想深深的影响着项目的开发。
- 在学习并使用`Qt`时，`Qt` 的元对象系统使我想到既然`Qt`能够支持反射，那么为什么不能基于 `Qt` 提供的反射系统，来开发一款`Web Framework` 呢？我当时在工作之余验证了`Orm` 可以通过反射系统操作，之后也验证了`Controller` 同样可以使用 `Qt` 的反射技术，只不过不是基于 `Java`的包扫描机制，而是通过`静态初始化注册`(`SIR`) 机制进行。
- 另外之前曾经了解过的`node`，`python` 框架同样给了很多的启发，其中有`Flask`, `Django`等。其中有一款`python`框架, `FastApi`重点推荐，其中好多设计令人耳目一新。
- 感谢`C++` 框架 [drogon](https://github.com/drogonframework/drogon)。在看到它之后，我代码中的注册机制全部改成了`drogon` 的注册机制。代码真的太优秀了。
- 本软件中引用了 [jimmiebergmann/mini-yaml库](https://github.com/jimmiebergmann/mini-yaml)，同样表示感谢
- 感谢 `MkDocs` ，提供了便利的方式，能够开发出这么精美的文档。

`IWebCore` 到目前为止，并不完善。好多的`feature`由于时间原因，将被放到以后的版本中间实现。
