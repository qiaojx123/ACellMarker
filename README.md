# ACellMarker
ZJU's Student Research Training Program

## Tips for adding files
所有继承自QT的类需要在UIClasses.h中定义，然后由moc.exe自动生成对应的UIClasses.cpp用于编译。moc.exe根据UIClasses.h生成UIClasses.cpp的过程会在每次生成时自动完成，
因此任何对UIClasses.cpp的编辑会在编译时被覆盖。

上述过程在项目属性-自定义生成步骤中被定义。

调试时的命令行窗口设置了临时的path变量，使其可以找到QtLibs/lib/中的dll文件。直接运行编译得到的可执行文件可能找不到对应的dll。