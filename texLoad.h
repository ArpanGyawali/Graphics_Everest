#pragma once

#include <stb/stb_image.h>
#include <string>
#include <vector>
#include "Vec3.h"
#include <iostream>

class Image {
public:
    std::string filename;
    int width, height, channel;
    int desired_channel;
    std::vector <std::vector<Vec3f>> imagedata;
    Image() {
        width = height = channel = 0;
        desired_channel = 3;//doesnt reads alpha for now
        filename = "None";
    };

    //returns 1 if the file loads succesfully
    bool load(std::string filename)
    {
        this->filename = filename;
        stbi_uc* data;
        stbi_set_flip_vertically_on_load(1);
        data = stbi_load(filename.c_str(), &width, &height, &channel, desired_channel);
        if (!data)
        {
            std::cout << filename << "  couldn't be loaded" << std::endl;
            return 0;
        }
        std::cout << filename << " loaded" << std::endl;
        convert(data);
        stbi_image_free(data);
        return 1;
    }

    //data has the image pixels in char so convert it to the rgb values and store it in 2d  array
    void convert(stbi_uc* data)
    {
        stbi_uc* tdata = data;
        std::vector<std::vector<Vec3f>> imaged(height, std::vector<Vec3f>(width, Vec3f()));

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Vec3f temp;
                temp.x = float(*tdata); tdata++;
                temp.y = float(*tdata); tdata++;
                temp.z = float(*tdata); tdata++;
                imaged[i][j] = temp;
            }
        }
        imagedata.resize(imaged.size());
        imagedata = imaged;
    }

    Vec3f getpixel(float u, float v) {
        return imagedata[(int)(v * (height - 1))][(int)(u * (width - 1))];
    }
};
