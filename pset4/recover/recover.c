#include <stdio.h>
#include <stdint.h>

#define Max 512

typedef uint8_t BYTE;

typedef struct
{
    BYTE buffer[Max];
    int BLOCK_SIZE;
}
recover;

recover photos;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        printf("FILE == NULL\n");
        return 1;
    }

    photos.BLOCK_SIZE = Max; // max is 512
    int counter = 0;

    while (fread(photos.buffer, 1, photos.BLOCK_SIZE, file) == photos.BLOCK_SIZE)
    {
        if (photos.buffer[0] == 0xff && photos.buffer[1] == 0xd8 && photos.buffer[2] == 0xff && (photos.buffer[3] & 0xf0) == 0xe0)
        {
            char data[8];
        	sprintf(data, "%03i.jpg", counter);
            counter++;
            FILE *img = fopen(data, "wb");
            if (img == NULL)
            {
                printf("Error opening image file.\n");
                return 0;
            }
            fwrite(photos.buffer, 1, photos.BLOCK_SIZE, img);

            while (fread(photos.buffer, 1, photos.BLOCK_SIZE, file) == photos.BLOCK_SIZE)
            {
                if (photos.buffer[0] == 0xff && photos.buffer[1] == 0xd8 && photos.buffer[2] == 0xff && (photos.buffer[3] & 0xf0) == 0xe0)
                {
                    // start of a new image, break inner loop
                    fwrite(photos.buffer, 1, photos.BLOCK_SIZE, img);
                    break;
                }
            // put memory in img
            fwrite(photos.buffer, 1, photos.BLOCK_SIZE, img);
            }
            fclose(img);
            return 0;

        }
    }
    fclose(file);
    return 1;
}
