#include <CL\cl.h>
#include <iostream>
using namespace std;
int main()
{
    cl_uint numPlatforms = 0;
    cl_platform_id * platforms = nullptr;
    // 第一次调用clGetPlatfromIDs，获取平台数量
    cl_int status = clGetPlatformIDs(0, nullptr, &numPlatforms);
    if(status != CL_SUCCESS)
    {
        cout << "error : getting platforms failed";
        return 1;
    }
    cout << "FIND " << numPlatforms << " PLATFORM(S)" << endl;
    if(numPlatforms == 0)
        return -1;
    platforms = new cl_platform_id[numPlatforms];
    status = clGetPlatformIDs(numPlatforms, platforms, nullptr);
    for(int i = 0; i < numPlatforms; ++i)
    {
        // 打印平台信息
        cl_char * param = new cl_char[30];
        cout << "PLATFORM " << i << " INFOMATION :" << endl;
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 30, param, nullptr);
        cout << "\tName    : " << param << endl;
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 30, param, nullptr);
        cout << "\tVendor  : " << param << endl;
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, 30, param, nullptr);
        cout << "\tVersion : " << param << endl;
        clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, 30, param, nullptr);
        cout << "\tProfile : " << param << endl;
        delete [] param;

        // 获取设备
        cl_uint numDevices = 0;
        cl_device_id * devices;
        status = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, nullptr, &numDevices);
        cout << "PLATFORM " << i << " HAS " << numDevices << " DEVICE(S) : " << endl;
        devices = new cl_device_id[numDevices];
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, numDevices, devices, nullptr);
        // 打印设备信息
        for(int j = 0; j < numDevices; ++j)
        {
            cl_char * device_param = new cl_char[50];
            cout << "DEVICE " << j << " INFOMATION :" << endl;
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 50, device_param, nullptr);
            cout << "\tName    : " << device_param << endl;
            clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, 50, device_param, nullptr);
            cout << "\tVendor  : " << device_param << endl;
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 50, device_param, nullptr);
            cout << "\tVersion : " << device_param << endl;
            clGetDeviceInfo(devices[j], CL_DEVICE_PROFILE, 50, device_param, nullptr);
            cout << "\tProfile : " << device_param << endl;
            delete [] device_param;
        }
        delete [] devices;
        cout << "---------------------------------------" << endl;
    }
    return 0;
}