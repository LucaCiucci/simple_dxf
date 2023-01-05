

#include <iostream>

#include <simple_dxf/dxf.hpp>

using simple_dxf::Vector3d;

int main(int argc, char* argv[])
{
	std::cout << "Hello World!\n";

	try {

		simple_dxf::CDxfWrite writer("test.dxf");

		writer.setLayerName("none");
		writer.init();
		{
			writer.writeLine(Vector3d(0, 0, 0), Vector3d(10, 10, 0));
			writer.writeCircle(Vector3d(0, 0, 0), 10);
			writer.writeArc(Vector3d(0, 0, 0), Vector3d(10, 10, 0), Vector3d(0, 10, 0), false);
		}
		writer.endRun();

	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		return 1;
	}

	// Open the file with the default program
	system("test.dxf");

	return 0;
}