#include <stdlib.h>
#include <stdio.h>

static const char *src_filename = NULL;
static const char *audio_dst_filename = NULL;

int extract_raw_audio(const char *input_file, const char *output_file);

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <input_file> <output_file> \n\n", argv[0]);
        exit(1);
    }
    src_filename = argv[1];
    audio_dst_filename = argv[2];

    if (extract_raw_audio(src_filename, audio_dst_filename))
    {
        fprintf(stderr, "Error while decoding/demuxing!");
        exit(1);
    }

    return 0;
}
