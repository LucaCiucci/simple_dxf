# simple_dxf
 A DXF read/write library, extracted from FreeCAD

> :warning: Most of the core code comes from the [FreeCAD](https://github.com/FreeCAD/FreeCAD) project, specifically, from [src/Mod/Import/App/dxf](https://github.com/FreeCAD/FreeCAD/tree/620aaac90d259923d65324d68c3ceea9cd882970/src/Mod/Import/App/dxf)

## Usage

### Setup

If you are using CMake, you can use the following cmake code:
```cmake
include(FetchContent)

FetchContent_Declare(
    simple_dxf
    GIT_REPOSITORY https://github.com/LucaCiucci/simple_dxf
    GIT_TAG        origin/main
)
FetchContent_MakeAvailable(simple_dxf)

target_link_libraries(your_target PRIVATE simple_dxf)
```
If you are not using cmake, you can just add the [/include](./include) to your include path and link against the [/src](./src) folder.

### Writing a DXF file

You can follow the [basic_usage](./examples/basic_usage) example to see how to write a DXF file. In short, you just have to include `<simple_dxf/dxf.h>` and then:
```cpp

simple_dxf::CDxfWrite writer("test.dxf");

writer.setLayerName("none");
writer.init();
{
    writer.writeLine(Vector3d(0, 0, 0), Vector3d(10, 10, 0));
    writer.writeCircle(Vector3d(0, 0, 0), 10);
    writer.writeArc(Vector3d(0, 0, 0), Vector3d(10, 10, 0), Vector3d(0, 10, 0), false);
}
writer.endRun();
```

### Reading a DXF file

> TODO write a simple example...

## License

This project is licensed under the terms of the [GPLv2](./LICENSE) license since it is a derivative work of the FreeCAD project.