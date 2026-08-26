# PPM Image Renderer

A simple C program that parses a binary PPM (P6) image file and renders it to the screen using [raylib](https://www.raylib.com/).

## Features

- Parses PPM (P6 binary) files, including:
  - Header validation (`P6` magic number)
  - Comment lines (`#`) in the header
  - Width/height and max color value parsing
- Bulk-reads pixel data with `fread` for fast loading
- Renders the decoded image pixel-by-pixel in a raylib window

## Requirements

- A C compiler (e.g. `gcc` or `clang`)
- [raylib](https://github.com/raysan5/raylib) installed and available to the linker

## Building

```bash
gcc main.c -o image_renderer -lraylib -lm -lpthread -ldl -lrt -lX11
```

> On macOS or Windows, link against raylib according to your platform's setup instructions (flags above are for Linux).

## Usage

```bash
./image_renderer <path_to_image.ppm>
```

Example:

```bash
./image_renderer 1.ppm
```

This opens a window sized to the image (plus a small margin) and draws the image contents.

## Input Format

Only **binary PPM (P6)** files with a max color value of **255** are supported. ASCII PPM (P3) and other max color values will cause the program to exit with an error.

## Known Limitations

- Only supports 8-bit RGB PPM (P6) files with max value 255.
- Image is rendered at 1:1 scale — very large images (larger than your screen resolution) may not display fully or may open a window bigger than your monitor.
- Rendering uses `DrawPixel` in a per-frame loop rather than a GPU texture, so performance may degrade on large images.

## Potential Improvements

- Scale large images to fit the screen, or add pan/zoom support
- Convert the pixel buffer into a raylib `Texture2D` for faster rendering
- Support additional PPM variants (P3 ASCII, other max color values)
- Add command-line flags for window size, scaling, etc.

## License

Feel free to use and modify this project for personal or educational purposes.
