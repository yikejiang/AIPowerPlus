# AIPowerPlus
AI Power Plus does not contain any API key, but it makes you easily utilize the API of OpenAI, Claude AI or Google Gemini.

AI Power Plus uses Qt libraries dynamically under the license of LGPL version 3. There is no modification in Qt source code.

When you run the source code through Python, you just need to install PySide6.

When you use Nuitka to compile the source code, here is a sample for how to run Nuitka.
python -m nuitka --standalone --windows-console-mode=disable --enable-plugin=pyside6 --windows-icon-from-ico=logo.ico --windows-product-name="AI Power Plus" --windows-file-description="AI Power Plus" --windows-file-version=1.0.0.0 --windows-product-version=1.0.0.0 --windows-company-name="Yike Jiang" AIPowerPlus.py
