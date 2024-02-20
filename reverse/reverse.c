#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER *header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Please provide input and output file names.");
        return 1;
    }

    // Open input file for reading
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        printf("Could not open input file.");
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, file);

    // Use check_format to ensure WAV format
    if (!check_format(&header))
    {
        printf("Input file is not in WAV format.");
        fclose(file);
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open output file.");
        fclose(file);
        return 1;
    }

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Write reversed audio to file
    BYTE *audioBlock = malloc(block_size);
    if (audioBlock == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        fclose(output);
        return 1;
    }

    fseek(file, sizeof(WAVHEADER), SEEK_SET);
    long dataSize = ftell(file) - sizeof(WAVHEADER);
    fseek(file, 0, SEEK_END);

    while (dataSize >= block_size) {
        fseek(file, -block_size, SEEK_CUR);
        fread(audioBlock, block_size, 1, file);
        fwrite(audioBlock, block_size, 1, output);
        dataSize -= block_size;
    }

    free(audioBlock);
    fclose(file);
    fclose(output);
    return 0;
}

int check_format(WAVHEADER *header)
{
    if (memcmp(header->chunkID, "RIFF", 4) == 0 && memcmp(header->format, "WAVE", 4) == 0) {
        return 1; // It's a WAV file
    }

    return 0;
}

int get_block_size(WAVHEADER header)
{
    int block_size = header.numChannels * header.bitsPerSample / 8;
    return block_size;
}

























/*#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER *header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("pls write the name of the audio file tat should be read and reversed and then the name of the audio file that should store the reversed audio");
        return 1;
    }

    // Open input file for reading
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("file could not be opened");
        return 1;
    }

    // Read header
    WAVHEADER header;

    // Use check_format to ensure WAV format
    if (check_format(&header))
    {
        printf("check format");
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");

    if (output == NULL)
    {
        printf("file could not be opened");
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    BYTE *audioBlock = malloc(block_size);
    if (audioBlock == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Move file pointer to the end of audio data
    fseek(file, sizeof(WAVHEADER) + header->subchunk1Size + header->subchunk2Size, SEEK_SET);

    while (ftell(file) > sizeof(WAVHEADER)) {
        fseek(file, -block_size, SEEK_CUR);
        fread(audioBlock, block_size, 1, file);
        fwrite(audioBlock, block_size, 1, output);
    }

    free(audioBlock);
    fclose(file);
    fclose(output);

    return 0;
}

int check_format(WAVHEADER *header)
{
    if (memcmp(header->chunkID, "RIFF", 4) == 0 && memcmp(header->format, "WAVE", 4) == 0) {
        return 1;
    }

    return 0;

}

int get_block_size(WAVHEADER header)
{
    int block_size = header.numChannels * header.bitsPerSample / 8;
    return block_size;
}*/