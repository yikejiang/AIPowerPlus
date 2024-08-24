# AI Power Plus

AI Power Plus does not contain any API key, but it makes you easily utilize the API of OpenAI, Claude AI or Google Gemini.

## AI Power Plus and AI Power Plus for Python

When I tried the voice interactive mode of the mobile app from OpenAI, I strongly felt that the development of AI could not be ignored now. Last year GPT 3.5 didn't give me a good impression, but this year I was greatly impressed by GPT-4o. And later I was interested in more AI models, including Claude AI 3.5 Sonnet and Google Gemini 1.5 Pro. How to utilize the APIs of the great AI models? I then decided to write this app.

At the beginning I used the modules from the AI companies, which also require a lot of dependency modules. Later, I realized the functions through REST APIs according to technical documentation from the AI companies.

Originally I used Python to write the app. It was good for me to locally run the app on my computer, but when the executable file complied through Nuitka was distributed through Internet, it was always mistakenly automatically deleted by Microsoft Defender on Windows 11. So I then distributed the executable file packaged through PyInstaller. The package made through PyInstaller was much bigger than through Nuitka, and I then became aware that the best way should be to reconstruct the app using C++.

I will release the C++ source code next week.

## How to run the source code

C++ and Qt are a great combination for software development. I reconstruct the app mainly based on Qt 6.8.0 beta3. Both of the C++ compilers MinGW-w64 13.1.0 (included by Qt) and MinGW-w64 14.2.0 (from MSYS2) works well. I also sucessfully compiled the app using Qt Creator and Clion on Fedora 40. If you use Qt 6.7.2, it should be also fine.

If you want to compile the source code thourgh MSVC 2022, it is better to change CMAKE_CXX_STANDARD from 23 to 17 in CMakeLists.txt, so Qt libraries related to processing Json won't get a warning notice from the compiler of MSVC 2022.

If you want to run or modify the source code using Qt Creator on Windows or Linux, you just need to create a project with the same name "AIPowerPlus" and then remove all files in the poject's folder but leave CMakeLists.txt.user, and put the app's source code to there. Then Qt Creator can recognize the project of the app.

When you want to run or modify the source code using Clion on Windows, if you have installed the MinGW-w64 compiled version of Qt 6.8.0 libraries, you need to add "-DCMAKE_PREFIX_PATH=C:\Qt\6.8.0\mingw_64" to "CMake options", and set "Working directory" to "C:\Qt\6.8.0\mingw_64\bin". When using Clion on Linux (Fedora 40), if you have installed the Desktop version of Qt 6.8.0 libraries through qt-online-installer-linux-x64-4.8.0.run (the version of the installer may be different), you need to add "-DCMAKE_PREFIX_PATH=/opt/Qt/6.8.0/gcc_64" to "CMake options", and set "Working directory" to "/opt/Qt/6.8.0/gcc_64/bin".

## License of AI Power Plus

August 9, 2024

AI Power Plus is released as free software under GNU General Public License version 3.

AI Power Plus uses Qt libraries dynamically under GNU Lesser General Public License version 3. There is no modification in Qt source code.

The software does not send any data to the developer.

For more information, please visit https://www.aipowerplus.com/license .
