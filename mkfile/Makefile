src=$(wildcard ./*.c) #从当前目录下找到以.c结尾的文件，放到src变量中
#  src=a.c b.c
obj=$(patsubst %.c,%.o, $(src)) #将src中的数据，后缀名由.c修改为.o,将结果赋给obj变量
#  obj=a.o b.o

#  $@:目标对象，$^:全部依赖对象，$<:第一个依赖对象
main:$(obj)
	gcc $^ -o $@
%.o:%.c
	gcc -c $^ -o $@

#  伪对象的声明
.PHONY:clean
clean:
	rm -rf main $(obj)
