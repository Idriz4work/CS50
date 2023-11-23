open memory card
    while looking for jpgs there are 4 main beginings
        first 3 bytes: 0xff 0xd8 0xff 0xef (each 512 per block)
        last bytes: 0xe0 0xe1 0xe2 0xef

look for beginning of JPG
    make a loop and look out for first 3 bytes and last bytes
        if found open up a new jpg file and make the same loop again
        if found close the old jpeg and proceed the same
            to read data from memory card you can use : while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)

open a new JPG FILE

write 512 bytes until new jpg is found
