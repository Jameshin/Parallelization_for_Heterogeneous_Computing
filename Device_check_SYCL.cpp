#include <sycl/sycl.hpp>

int main()
{
    for (auto platform : sycl::platform::get_platforms())
    {
        std::cout << "Platform: "
            << platform.get_info<sycl::info::platform::name>()
            << std::endl;

        for (auto device : platform.get_devices())
        {
            std::cout << "\tDevice: "
                << device.get_info<sycl::info::device::name>()
                << std::endl;
        }
    }
     
    // Create a SYCL queue
    sycl::queue q{ sycl::gpu_selector_v };

    // Get the device from the queue
    auto device = q.get_device();

    std::cout << "Running on Device: " << q.get_device().get_info<sycl::info::device::name>();
}