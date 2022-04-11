当前AD用于控制在环打开动力学模型挂载内部

当前AD与simpro默认使用UDP模式建立连接(支持切换TCP模式，切换后需要重新编译代码)

切换连接方法：修改main.cpp文件中的宏定义 USE_UDP_OR_TCP 的值
