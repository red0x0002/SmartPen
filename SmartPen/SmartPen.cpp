// SmartPen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>

class Vector3
{
public:
    float x, y, z;

	
};


int main()
{
    std::ifstream file_stream;
    file_stream.open("C:\\Users\\Administrator\\Downloads\\CoolTerm Capture 2023-02-05 17-52-48.txt");

    std::string line_index;
    while (true)
    {
        std::getline(file_stream, line_index);

		auto strstr_result = strstr(line_index.c_str(), "Accelerometer");

        if (strstr_result)
        {
			auto x_result = strstr(line_index.c_str(), "X:");
			auto y_result = strstr(line_index.c_str(), "Y:");
			auto z_result = strstr(line_index.c_str(), "Z:");

			auto x_string = std::string(x_result);
			auto y_string = std::string(y_result);
			auto z_string = std::string(z_result);

			x_string = std::string(x_string.c_str() + 3);
            y_string = std::string(y_string.c_str() + 3);
            z_string = std::string(z_string.c_str() + 3);

			x_string.resize(6);
			if (x_string.find("-") != std::string::npos)
				x_string.resize(5);
			else
				x_string.resize(4);

			y_string.resize(6);
			if (y_string.find("-") != std::string::npos)
				y_string.resize(5);
			else
				y_string.resize(4);

			z_string.resize(6);
			if (z_string.find("-") != std::string::npos)
				z_string.resize(5);
			else
				z_string.resize(4);

			auto line_x = std::wstring(x_string.begin(), x_string.end());
			auto line_y = std::wstring(y_string.begin(), y_string.end());
			auto line_z = std::wstring(z_string.begin(), z_string.end());

            Vector3 velocity;
            velocity.x = std::stof(line_x);
			velocity.y = std::stof(line_y);
			velocity.z = std::stof(line_z);

			// magnitude is speed (cm/s?)
			auto velocity_magnitude = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);

			auto direction = 0;
        }
    }

    std::cin.get();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
