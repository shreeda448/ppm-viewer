#include "raylib.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

struct my_pixel {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct image {
  int img_height;
  int img_width;
  struct my_pixel *img;
};

const int MAX_BUFFER_SIZE = 256;

void parse_image(struct image *img, FILE *file) {
  // TODO: read the bytes from the file
  //  1.read the type of the file
  char img_buffer[MAX_BUFFER_SIZE];
  char *header_file_type = fgets(img_buffer, sizeof(img_buffer), file);
  if (header_file_type == NULL || strncmp(header_file_type, "P6", 2)) {
    fprintf(stderr, "Error: Invalid PPM file format (Must be P6 binary)\n");
    exit(EXIT_FAILURE);
  };
  //  2.skip any comments
  while (fgets(img_buffer, sizeof(img_buffer), file) != NULL) {
    if (img_buffer[0] == '#')
      continue;
    //  3.read the dimensions of the image
    int num_dimensions =
        sscanf(img_buffer, "%d %d", &img->img_width, &img->img_height);
    if (num_dimensions == 2) {
      break;
    }
  }
  // 4.read the max color value
  int max_color_val = 0;
  while (fgets(img_buffer, sizeof(img_buffer), file) != NULL) {
    if (img_buffer[0] == '#')
      continue;
    int val = sscanf(img_buffer, "%d", &max_color_val);
    if (val == 1)
      break;
  }
  // do max color intensity validation
  if (max_color_val != 255) {
    fprintf(stderr, "Error: Only 255 max color intensity value supported.\n");
    exit(EXIT_FAILURE);
  }
  int total_pixels = img->img_width * img->img_height;
  img->img = (struct my_pixel *)malloc(total_pixels * sizeof(struct my_pixel));
  if (img->img == NULL) {
    fprintf(stderr, "Error: Memory allocation failed for pixel buffer\n");
    exit(EXIT_FAILURE);
  }
  //  5.read the data 3 bytes at a time (1 pixel),
  //  MODIFY:directly bulk read the binary bits using fread()
  //  MY LEARNING: fread is like memcpy() but it reads files from disk instead
  //  of directly from memory
  size_t pixels_read =
      fread(img->img, sizeof(struct my_pixel), total_pixels, file);
  if (pixels_read != (size_t)total_pixels) {
    fprintf(stderr,
            "Warning: Not enough pixels. Expected %d pixels, read %zu\n",
            total_pixels, pixels_read);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Error: Missing filename.\n");
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }
  struct image my_img;
  FILE *my_file = fopen(argv[1], "rb");
  if (my_file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }
  printf("Successfully opened: %s\n", argv[1]);
  parse_image(&my_img, my_file);
  fclose(my_file);
  const int screenWidth = my_img.img_width + 50;
  const int screenHeight = my_img.img_height + 50;
  InitWindow(screenWidth, screenHeight, "image renderer");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    for (int y = 0; y < my_img.img_height; y++) {
      for (int x = 0; x < my_img.img_width; x++) {
        struct my_pixel *cur_pixel = &my_img.img[y * my_img.img_width + x];
        Color cur_color =
            (Color){cur_pixel->r, cur_pixel->g, cur_pixel->b, 255};
        DrawPixel(x + 25, y + 25, cur_color);
      }
    }
    EndDrawing();
  }
  free(my_img.img);
  CloseWindow();
  return EXIT_SUCCESS;
}
