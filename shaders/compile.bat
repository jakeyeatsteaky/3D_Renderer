
echo "Building Shaders!"
C:/VulkanSDK/1.3.243.0/Bin/glslc.exe vulk_shader.vert -o binaries/vert.spv
C:/VulkanSDK/1.3.243.0/Bin/glslc.exe vulk_shader.frag -o binaries/frag.spv

C:/VulkanSDK/1.3.243.0/Bin/glslc.exe vulk_shader2.vert -o binaries/vert2.spv
C:/VulkanSDK/1.3.243.0/Bin/glslc.exe vulk_shader2.frag -o binaries/frag2.spv

pause