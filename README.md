# imageToTerm
Convert images to beautiful ASCII art directly in your terminal.
# Overview
imageToTerm is a command-line tool that transforms images into ASCII/text representations that can be displayed in terminal environments. Whether you want to view images without leaving your terminal or create stunning text-based art, imageToTerm makes it simple and fast.

# Features
Color support: Display images with ANSI color codes for terminals that support them</br>
Flexible sizing: Automatically scale images to fit your terminal dimensions</br>
Works with common image formats (PNG, JPEG)</br>

# Examples

<table>
<tr>
<td width="50%">
<img src="https://github.com/user-attachments/assets/6b05520c-3921-4a1c-9876-ff5c02ae9695" alt="Original Image 1" width="100%"/>
</td>
<td width="50%">
<img src="https://github.com/user-attachments/assets/720707a4-d6b3-4b3f-bb94-740984a9a2d4" alt="Terminal Output 1" width="100%"/>
</td>
</tr>
</table>
<table>
<tr>
<td width="50%">
<img src="https://github.com/user-attachments/assets/b63c8b33-81ee-4662-bb15-8e9e792b8011" alt="Original Image 2" width="100%"/>
</td>
<td width="50%">
<img src="https://github.com/user-attachments/assets/9ef5aa6f-f8a9-4dab-9377-50b0e8bb6ff2" alt="Terminal Output 2" width="100%"/>
</td>
</tr>
</table>
<table>
<tr>
<td width="50%">
<img src="https://github.com/user-attachments/assets/0c35c575-c11c-44ba-b0ba-6aac8811fbfa" alt="Original Image 3" width="100%"/>
</td>
<td width="50%">
<img src="https://github.com/user-attachments/assets/00163012-ab5b-4ac5-a03d-c1c8d1b782df" alt="Terminal Output 3" width="100%"/>
</td>
</tr>
</table>


# How to Run

## Build the Project

First, compile the project using make:
```bash
make
```

## Display in Terminal

To display an image as ASCII art in your terminal:
```bash
./imageToTerm Test/<image>.<extension>
```

**Example:**
```bash
./imageToTerm Test/photo.png
./imageToTerm Test/landscape.jpg
```

## Export as JPG

To create a JPG photo from the terminal output:
```bash
./imageToTerm Test/<image>.<extension> | aha --black | wkhtmltoimage - output.jpg
```

**Example:**
```bash
./imageToTerm Test/photo.png | aha --black | wkhtmltoimage - output.jpg
```

This command:
1. Converts the image to ASCII art (`./imageToTerm`)
2. Converts ANSI colors to HTML (`aha --black`)
3. Renders the HTML to a JPG image (`wkhtmltoimage`)

### Prerequisites for Export

Make sure you have the following tools installed:
- `aha` - ANSI HTML Adapter
- `wkhtmltoimage` - HTML to image converter
