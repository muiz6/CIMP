# CIMP

CIMP is an image manipulation program written in C++. All features are developed from scratch (other
than the GUI which uses with WxWidgets library for graphical components).

![logo](/docs/icon.png)

### Download

If you're a 64-bit Windows 10 user you can download a pre-compiled binary from [here](https://github.com/muiz6/CIMP/releases/download/windows_10_x64/CIMP.win10.x64.zip).

### Features

- Open sevaral bitmap image formats
- Save as servaral bitmap image formats (including a quantised 8-bit bmp format)
- Apply colour filters such as alienate, invert colours, sepia & more
- Vertically invert the image
- Graphical User Interface

### Dependencies

CIMP depends upon [wxWidgets](https://github.com/wxWidgets/wxWidgets). Library for its
Graphic User Interface. Do add it in your project prior to compilation.

### Screenshots

![original image](/docs/sepia.jpg)

![alienate filter](/docs/alienate.jpg)

When image is saved as 8-bit bitmap it is quantised to have fewer than 256 colours:

![quantisation filter](/docs/quantisation.jpg)
