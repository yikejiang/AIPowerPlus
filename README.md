# AIPowerPlus

AI Power Plus does not contain any API key, but it makes you easily utilize the API of OpenAI, Claude AI or Google Gemini.

Originally I wrote the software for my personal use. But I became aware that many people might need such a tool to utilize APIs of AI models, I decided to release it.

## How to run Python source code

When you run the source code through Python, you just need to install PySide6.

## How to compile .exe binary program through Nuitka

When you use Nuitka to compile the source code, here is a sample for how to run Nuitka.
python -m nuitka --standalone --windows-console-mode=disable --enable-plugin=pyside6 --windows-icon-from-ico=logo.ico --windows-product-name="AI Power Plus" --windows-file-description="AI Power Plus" --windows-file-version=1.0.0.0 --windows-product-version=1.0.0.0 --windows-company-name="Yike Jiang" AIPowerPlus.py

## License of AI Power Plus

August 9, 2024

AI Power Plus is released as free software under GNU General Public License version 3.

AI Power Plus uses Qt libraries dynamically under GNU Lesser General Public License version 3. There is no modification in Qt source code.

The software does not send any data to the developer.

For more information, please visit https://www.aipowerplus.com/license .
